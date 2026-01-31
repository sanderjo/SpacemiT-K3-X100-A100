#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
        return 1;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) { // CHILD PROCESS
        // 1. Get PID and write to /proc/set_ai_thread
        int fd = open("/proc/set_ai_thread", O_WRONLY);
        if (fd >= 0) {
            char pid_str[16];
            int len = snprintf(pid_str, sizeof(pid_str), "%d", getpid());
            write(fd, pid_str, len);
            close(fd);
        } else {
            // If the file doesn't exist, we print to stderr before redirecting
            perror("Warning: Could not open /proc/set_ai_thread");
        }

        // 2. Redirect output to pipe
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        dup2(pipefd[1], STDERR_FILENO);
        close(pipefd[1]);

        // 3. Execute the command
        execvp(argv[1], &argv[1]);
        
        // Only reached if execvp fails
        perror("execvp");
        exit(1);

    } else if (pid > 0) { // PARENT PROCESS
        close(pipefd[1]);

        char buffer[1024];
        ssize_t n;

        // printf("--- Captured Output Start ---\n");
        while ((n = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[n] = '\0';
            printf("%s", buffer);
        }
        // printf("--- Captured Output End ---\n");

        close(pipefd[0]);
        wait(NULL);
    } else {
        perror("fork");
        return 1;
    }

    return 0;
}

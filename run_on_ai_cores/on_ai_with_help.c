#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

void print_help(char *prog_name) {
    printf("Usage: %s [OPTIONS] <command> [args...]\n\n", prog_name);
    printf("A wrapper to execute commands, capture output via pipes, and register the PID.\n\n");
    printf("Options:\n");
    printf("  -h, --help    Show this help message and exit\n");
    printf("\nExample:\n");
    printf("  %s ls -la\n", prog_name);
}

int main(int argc, char *argv[]) {
    // 1. Check if help is requested or if no arguments provided
    if (argc < 2) {
        fprintf(stderr, "Error: Missing command.\n");
        print_help(argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        print_help(argv[0]);
        return 0;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) { // CHILD PROCESS
        // Get PID and write to /proc/set_ai_thread
        int fd = open("/proc/set_ai_thread", O_WRONLY);
        if (fd >= 0) {
            char pid_str[16];
            int len = snprintf(pid_str, sizeof(pid_str), "%d", getpid());
            write(fd, pid_str, len);
            close(fd);
        } else {
            perror("Warning: Could not open /proc/set_ai_thread");
        }

        // Redirect output to pipe
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        dup2(pipefd[1], STDERR_FILENO);
        close(pipefd[1]);

        // Execute the command
        execvp(argv[1], &argv[1]);
        
        perror("execvp");
        exit(1);

    } else if (pid > 0) { // PARENT PROCESS
        close(pipefd[1]);

        char buffer[1024];
        ssize_t n;

        while ((n = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[n] = '\0';
            printf("%s", buffer);
        }

        close(pipefd[0]);
        wait(NULL);
    } else {
        perror("fork");
        return 1;
    }

    return 0;
}

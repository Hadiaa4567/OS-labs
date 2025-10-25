#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // create child process

    if (pid == 0) {
        // child process runs 'top'
        execlp("top", "top", NULL);
    } else {
        // parent waits for child
        wait(NULL);
        printf("Child finished\n");
    }

    return 0;
}

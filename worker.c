#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define FILENAME_MAX_LEN 256
#define BUFFER_SIZE 40

void starFile(char* filename) {
    FILE* fp = fopen(filename, "w");


    int i;
    for (i = 0; i < BUFFER_SIZE; i++) {
        fputc('*', fp);
        fflush(fp);
        sleep(1);
    }
    fclose(fp);
}
void contHandler(){
        return;
}

void stopHandler(){
        pause();
        return;
}
int main(int argc, char* argv[]) {

    char* filename = argv[1];
    pid_t scheduler_pid = atoi(argv[2]);
    // Send SIGUSR1 signal to scheduler to add worker to circular linked list
    kill(scheduler_pid, SIGUSR1);
    // Wait for SIGCONT signal from scheduler to resume execution
    signal(SIGCONT, contHandler);
    signal(SIGSTOP, stopHandler);
    pause();
    starFile(filename);
    kill(scheduler_pid, SIGUSR2);
    return 0;
}


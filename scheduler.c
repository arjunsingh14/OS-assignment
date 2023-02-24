#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <stdatomic.h>
#include "queue.h"
int t, w;
Queue q;
atomic_int completed = 0;
void sigusr1_handler(int sig, siginfo_t* info, void* context){
        int p;
        p = info->si_pid;
        enqueue(&q, p, w);
	return;
}

void term_handler(int sig, siginfo_t* info, void* context){
        kill(info->si_pid, SIGTERM);
        return;
}
int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <timeslice> <num_workers>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    q.front = q.rear = -1;
    q.size = 0;
    // Parse command line arguments
    t = atoi(argv[1]);
    w = atoi(argv[2]);
    // Install signal handler for SIGUSR1 signal
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = sigusr1_handler;
    sigaction(SIGUSR1, &sa, NULL);

    //Signal handler for SIGTERM signal
    struct sigaction term;
    term.sa_flags = SA_SIGINFO;
    sigemptyset(&term.sa_mask);
    term.sa_sigaction = term_handler;
    sigaction(SIGUSR2, &term, NULL);
    pause();
    // Wait for worker processes to send SIGUSR1 signal
    // Execute worker processes in circular linked list
    while (1)
    {
        if (q.front != -1) {
            int p = dequeue(&q, w);
            if (kill(p, 0) == 0){
                kill(p, SIGCONT);
                sleep(t);
                kill(p, SIGSTOP);
                enqueue(&q, p, w);
            }
	    sleep(1);
        }
        else {
                break;
        }
    }

    return 0;
}


#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#define ngx_signal_helper(n)     SIG##n
#define signal_value(n)      ngx_signal_helper(n)
#define value_helper(n)   #n
#define value(n)          value_helper(n)

#define SHUTDOWN_SIGNAL      QUIT
#define TERMINATE_SIGNAL     TERM
#define NOACCEPT_SIGNAL      WINCH
#define RECONFIGURE_SIGNAL   HUP
#define REOPEN_SIGNAL        USR1
#define CHANGEBIN_SIGNAL     USR2
enum{
    PROCESS_MASTER,
    PROCESS_SINGLE,
    PROCESS_WORKER,
    PROCESS_HELPER,
}
static ngx_new_binary = 2; //test
int process;
int ngx_daemonized = 1;//test
typedef struct {
    int     signo;
    char   *signame;
    char   *name;
    void  (*handler)(int signo);
} signal_t;
void signal_handler(int signo);
signal_t  signals[] = {
    { signal_value(RECONFIGURE_SIGNAL),
      "SIG" value(RECONFIGURE_SIGNAL),
      "reload",
      signal_handler },

    { signal_value(REOPEN_SIGNAL),
      "SIG" value(REOPEN_SIGNAL),
      "reopen",
      signal_handler },

    { signal_value(NOACCEPT_SIGNAL),
      "SIG" value(NOACCEPT_SIGNAL),
      "",
      signal_handler },

    { signal_value(TERMINATE_SIGNAL),
      "SIG" value(TERMINATE_SIGNAL),
      "stop",
      signal_handler },

    { signal_value(SHUTDOWN_SIGNAL),
      "SIG" value(SHUTDOWN_SIGNAL),
      "quit",
      signal_handler },

    { signal_value(CHANGEBIN_SIGNAL),
      "SIG" value(CHANGEBIN_SIGNAL),
      "",
      signal_handler },

    { SIGALRM, "SIGALRM", "", signal_handler },

    { SIGINT, "SIGINT", "", signal_handler },

    { SIGIO, "SIGIO", "", signal_handler },

    { SIGCHLD, "SIGCHLD", "", signal_handler },

    { SIGSYS, "SIGSYS, SIG_IGN", "", SIG_IGN },

    { SIGPIPE, "SIGPIPE, SIG_IGN", "", SIG_IGN },

    { 0, NULL, "", NULL }
};
void signal_handler(int signo)
{
    char            *action;
    int        ignore;
    signal_t    *sig;

    ignore = 0;

    for (sig = signals; sig->signo != 0; sig++) {
        if (sig->signo == signo) {
            break;
        }
    }

    action = "";

    switch (process) {

    case PROCESS_MASTER:
    case PROCESS_SINGLE:
        switch (signo) {

        case signal_value(SHUTDOWN_SIGNAL):
            printf("quit:%d\n",signo);
            action = ", shutting down";
            break;

        case signal_value(TERMINATE_SIGNAL):
        case SIGINT:
            printf("terminate:%d\n",signo);
            action = ", exiting";
            break;

        case signal_value(NOACCEPT_SIGNAL):
            if (ngx_daemonized) {
                printf("stop accepting connections:%d\n",signo);
                action = ", stop accepting connections";
            }
            break;

        case signal_value(RECONFIGURE_SIGNAL):
            printf("reconfiguring:%d\n",signo);
            action = ", reconfiguring";
            break;

        case signal_value(REOPEN_SIGNAL):
            printf("reopening logs:%d\n",signo);
            action = ", reopening logs";
            break;

        case signal_value(CHANGEBIN_SIGNAL):
            if (getppid() > 1 || ngx_new_binary > 0) {

                /*
                 * Ignore the signal in the new binary if its parent is
                 * not the init process, i.e. the old binary's process
                 * is still running.  Or ignore the signal in the old binary's
                 * process if the new binary's process is already running.
                 */

                action = ", ignoring";
                ignore = 1;
                break;
            }
            printf("changing binary:%d\n",signo);
            action = ", changing binary";
            break;

        case SIGALRM:
            printf("SIGALRM:%d\n",signo);
            break;

        case SIGIO:
            printf("sigio:%d\n",signo);
            break;

        case SIGCHLD:
            printf("sigrep:%d\n",signo);
            break;
        }

        break;

    case PROCESS_WORKER:
    case PROCESS_HELPER:
        switch (signo) {

        case signal_value(NOACCEPT_SIGNAL):
            if (!ngx_daemonized) {
                break;
            }
            printf("debug quit:%d\n",signo);
        case signal_value(SHUTDOWN_SIGNAL):
            printf("shutting down:%d\n",signo);
            action = ", shutting down";
            break;

        case signal_value(TERMINATE_SIGNAL):
        case SIGINT:
            printf("exiting:%d\n",signo);
            action = ", exiting";
            break;

        case signal_value(REOPEN_SIGNAL):
            printf("reopening logs:%d\n",signo);
            action = ", reopening logs";
            break;

        case signal_value(RECONFIGURE_SIGNAL):
        case signal_value(CHANGEBIN_SIGNAL):
        case SIGIO:
            printf("ignoring:%d\n",signo);
            action = ", ignoring";
            break;
        }

        break;
    }

    
    printf("signal %d (%s) received%s\n", signo, sig->signame, action);

    /*
    if (ignore) {
        ngx_log_error(LOG_CRIT, ngx_cycle->log, 0,
                      "the changing binary signal is ignored: "
                      "you should shutdown or terminate "
                      "before either old or new binary's process");
    }
    */
    /*
    if (signo == SIGCHLD) {
        ngx_process_get_status();
    }
    */
    //ngx_set_errno(err);
}
static init_signals()
{
    signal_t      *sig;
    struct sigaction   sa;

    for (sig = signals; sig->signo != 0; sig++) {
        memset(&sa, sizeof(struct sigaction),0);
        sa.sa_handler = sig->handler;
        sigemptyset(&sa.sa_mask);
        if (sigaction(sig->signo, &sa, NULL) == -1) {
            printf("sigaction(%s) failed", sig->signame);
            return -1;
        }
    }

    return 0;
}
int main(int argc,char **argv){
    pid_t pid;
    int status;
    init_signals();
    pid = fork();
    if(pid == 0){
        process = PROCESS_WORKER;
        printf("child!!!\n");
        while(1){
            ;
        }
    }
    else{
        process = PROCESS_MASTER;
        printf("parent!!!\n");
        wait(&status); //block
        printf("child exit:%d\n",status);
    }
    
}

#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
static void my_sig_handler(int signo){
printf("Calling from signal handler");
}
int main(void){
struct sigaction act;
int count, count2;
count=count2=0;
double sum=0;
double x=0;
for(;count<1000000000;++count)
for(;count2<1000000000;++count2){
x=(rand()+0.5)/(RAND_MAX+1.0);
sum+=sin(x);
}

act.sa_handler=my_sig_handler;
act.sa_flags=0;
if(sigaction(SIGINT, &act, NULL)==-1){
perror("Failed to set SIGINT handler");
return 0;
}
sum=0;
printf("Signal handler Installed for SIGINT\n");
count=count2=0;
for(;count<1000000000;++count)
for(;count2<1000000000;++count2){
x=(rand()+0.5)/(RAND_MAX+1.0);
sum+=sin(x);
}
//portion about blocking and unblocking signals
sigset_t signal_set;
sigemptyset(&signal_set);
sigaddset(&signal_set, SIGSEGV);
sigprocmask(SIG_BLOCK, &signal_set, NULL);
printf("SIGSEGV blocked\n");
count=count2=0;
kill(0,SIGSEGV);
for(;count<1000000000;++count)
for(;count2<1000000000;++count2){
x=(rand()+0.5)/(RAND_MAX+1.0);
sum+=sin(x);
}
printf("going to unblock SIGSEGV \n");
sigprocmask(SIG_UNBLOCK, &signal_set, NULL);
printf("Unblocked SIGSEGV");
return 0;
}

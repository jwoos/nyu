/*
  patricide.c

  Kills off parent.
  What happens if you do that again, i.e. after your parent died?
  Used to be the "new" parent would be pid == 1, init, which couldn't
  be killed.
  Now (for me, in ubuntu 14.04) it's your login init.  Annoying to
  kill that.
 */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> // pid_t

int main(void) {
    printf("In original process. pid: %d, parent's pid: %d\n",
           getpid(), getppid());
    if (fork() == 0) {  // I'm the child
        //        pid_t ppid = getppid();
        printf("In child process. pid: %d, parent's pid: %d\n",
               getpid(), getppid());
        if (kill(getppid(), SIGKILL) == -1) perror("kill failed");
        else {
            fprintf(stderr, "Patricide succeeded on %d\n", getppid());
            sleep(2);
        }
        printf("pid: %d, parent's pid: %d\n", getpid(), getppid());

        // Don't really want to do this! Linux gives each loggin its
        // own "init".  While we cannot kill off the "real" init,
        // i.e. process id 1, interestingly we can kiil our own
        // login init, which will log you out.
        
        printf("Attempting to kill my new parent\n");
        if (kill(getppid(), SIGKILL) == -1) perror("kill failed"); else
          printf("Success!\n");
    }
    else {
        sleep(10);
    }

}

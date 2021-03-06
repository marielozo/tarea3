#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

using namespace std;

#define DAEMON_NAME "vdaemon"

void process(){
	syslog (LOG_NOTICE, "Tarea 3");
}

int main(int argc, char *argv[]){
	setlogmask(LOG_UPTO(LOG_NOTICE));
	openlog(DAEMON_NAME, LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_USER);
	syslog(LOG_INFO, "Entering daemon");
	pid_t pid, sid;

	pid = fork();

	if(pid < 0){
	exit(EXIT_FAILURE);
	} 
	if(pid > 0){
	exit(EXIT_SUCCESS);
	}
	
	umask(0);

	sid = setsid();
	if(sid < 0){
	exit(EXIT_FAILURE);
	}
	if(chdir("/") < 0){
	exit(EXIT_FAILURE);
	}

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	while(true){
	process();
	sleep(60);
	}
	closelog();
}

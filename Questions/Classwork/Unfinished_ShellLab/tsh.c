/* 
 * tsh - A tiny shell program with job control
 * 
 * Abhi Mangal Agarwal, ama684@nyu.edu
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/* Misc manifest constants */
#define MAXLINE    1024   /* max line size */
#define MAXARGS     128   /* max args on a command line */
#define MAXJOBS      16   /* max jobs at any point in time */
#define MAXJID    1<<16   /* max job ID */

/* Job states */
#define UNDEF 0 /* undefined */
#define FG 1    /* running in foreground */
#define BG 2    /* running in background */
#define ST 3    /* stopped */

/* 
 * Jobs states: FG (foreground), BG (background), ST (stopped)
 * Job state transitions and enabling actions:
 *     FG -> ST  : ctrl-z
 *     ST -> FG  : fg command
 *     ST -> BG  : bg command
 *     BG -> FG  : fg command
 * At most 1 job can be in the FG state.
 */

/* Global variables */
extern char **environ;      /* defined in libc */
char prompt[] = "tsh> ";    /* command line prompt (DO NOT CHANGE) */
int verbose = 0;            /* if true, print additional output */
int nextjid = 1;            /* next job ID to allocate */
char sbuf[MAXLINE];         /* for composing sprintf messages */

struct job_t {              /* The job struct */
	pid_t pid;              /* job PID */
	int jid;                /* job ID [1, 2, ...] */
	int state;              /* UNDEF, BG, FG, or ST */
	char cmdline[MAXLINE];  /* command line */
};
struct job_t jobs[MAXJOBS]; /* The job list */
/* End global variables */


/* Function prototypes */

/* Here are the functions that you will implement */
void eval(char *cmdline);
int builtin_cmd(char **argv);
void do_bgfg(char **argv);
void waitfg(pid_t pid);

void sigchld_handler(int sig);
void sigtstp_handler(int sig);
void sigint_handler(int sig);

/* Here are helper routines that we've provided for you */
int parseline(const char *cmdline, char **argv); 
void sigquit_handler(int sig);

void clearjob(struct job_t *job);
void initjobs(struct job_t *jobs);
int maxjid(struct job_t *jobs); 
int addjob(struct job_t *jobs, pid_t pid, int state, char *cmdline);
int deletejob(struct job_t *jobs, pid_t pid); 
pid_t fgpid(struct job_t *jobs);
struct job_t *getjobpid(struct job_t *jobs, pid_t pid);
struct job_t *getjobjid(struct job_t *jobs, int jid); 
int pid2jid(pid_t pid); 
void listjobs(struct job_t *jobs);

void usage(void);
void unix_error(char *msg);
void app_error(char *msg);
typedef void handler_t(int);
handler_t *Signal(int signum, handler_t *handler);

/*
 * main - The shell's main routine 
 */
int main(int argc, char **argv) 
{
	char c;
	char cmdline[MAXLINE];
	int emit_prompt = 1; /* emit prompt (default) */

	/* Redirect stderr to stdout (so that driver will get all output
	 * on the pipe connected to stdout) */
	dup2(1, 2);

	/* Parse the command line */
	while ((c = getopt(argc, argv, "hvp")) != EOF) {
		switch (c) {
			case 'h':             /* print help message */
				usage();
				break;
			case 'v':             /* emit additional diagnostic info */
				verbose = 1;
				break;
			case 'p':             /* don't print a prompt */
				emit_prompt = 0;  /* handy for automatic testing */
				break;
			default:
				usage();
		}
	}

	/* Install the signal handlers */

	/* These are the ones you will need to implement */
	Signal(SIGINT,  sigint_handler);   /* ctrl-c */
	Signal(SIGTSTP, sigtstp_handler);  /* ctrl-z */
	Signal(SIGCHLD, sigchld_handler);  /* Terminated or stopped child */

	/* This one provides a clean way to kill the shell */
	Signal(SIGQUIT, sigquit_handler); 

	/* Initialize the job list */
	initjobs(jobs);

	/* Execute the shell's read/eval loop */
	while (1) {

		/* Read command line */
		if (emit_prompt) {
			printf("%s", prompt);
			fflush(stdout);
		}
		if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin))
			app_error("fgets error");
		if (feof(stdin)) { /* End of file (ctrl-d) */
			fflush(stdout);
			exit(0);
		}

		/* Evaluate the command line */
		eval(cmdline);
		fflush(stdout);
		fflush(stdout);
	} 

	exit(0); /* control never reaches here */
}

/* 
 * eval - Evaluate the command line that the user has just typed in
 * 
 * If the user has requested a built-in command (quit, jobs, bg or fg)
 * then execute it immediately. Otherwise, fork a child process and
 * run the job in the context of the child. If the job is running in
 * the foreground, wait for it to terminate and then return.  Note:
 * each child process must have a unique process group ID so that our
 * background children don't receive SIGINT (SIGTSTP) from the kernel
 * when we type ctrl-c (ctrl-z) at the keyboard.  
 */
void eval(char *cmdline) 
{
	char *argv[MAXARGS];// The list of all the arguments, (*argv)
	int bg;// BG - Background Process, FG - Foreground Process (bg)
	pid_t pid;// Sets & stores the ID of the process (pid)
	sigset_t mask;// Variable to store all the 
	// blocking signals that are present (mask)
	bg = parseline(cmdline, argv);
	if(bg == -1) { // ERROR CHECKING
		return; // checks if the input (bg) was empty
	} // if it was then it asks user again + returns
	if(sigemptyset(&mask) != 0){
		unix_error("sigemptyset error");
	} // If it can't initalize the empty set (mask)
	if(sigaddset(&mask, SIGCHLD) != 0){
		unix_error("sigaddset error");
	} // If it can't add a signal to the set (mask)
	if(sigaddset(&mask, SIGINT) != 0){
		unix_error("sigaddset error");
	} // If it can't add a signal to the set (mask)
	if(sigaddset(&mask, SIGTSTP) != 0){
		unix_error("sigaddset error");
	} // If it can't add a signal to the set (mask)
	// The parseline() command determines 
	// if a input from the cmdline is a builtin function
	if(!builtin_cmd(argv)) {
		// If it isn't a builtin command
		// It will fork, and execute the command
		// If it isn't a builtin command, it blocks 
		// the Child Process and shoots an error
		if(sigprocmask(SIG_BLOCK, &mask, NULL) != 0){
			// If it can't change the current blocking signal
			unix_error("sigprocmask error");
		}
		// Duplicates proess - if can't do then throws and error
		if((pid = fork()) < 0){
			// If the child process is lower than 0 then throws an error
			unix_error("forking error");
		}
		// If the process ID is currently 0
		// Child Process
		else if(pid == 0) {
			// Changes blocked signal, if not then shoots an error
			if (sigprocmask(SIG_UNBLOCK, &mask, NULL) != 0){
				unix_error("sigprocmask error");
			}
			// Sets the process group ID, (0, 0), if it's less than
			// zero then throws an error
			if(setpgid(0, 0) < 0) {
				unix_error("setpgid error");
			}
			// If the command isn't found using the exec function,
			// then throws an error
			if(execvp(argv[0], argv) < 0) {
				printf("%s: Command not found\n", argv[0]);
				exit(1);
			}
		}
		// If there is a foreground job, then the job is added into queue
		// and waits to get finished or else output
		else {
			if(!bg){ // Checking FG first
				addjob(jobs, pid, FG, cmdline); 
				// Adding a Foreground Job 
			}
			else {
				addjob(jobs, pid, BG, cmdline); 
				// Adds to queue, forground Job
			}
			if (sigprocmask(SIG_UNBLOCK, &mask, NULL) != 0){
				unix_error("sigprocmask error"); 
				// Or else throws an error last
			}
		}
	}
}

/* 
 * parseline - Parse the command line and build the argv array.
 * 
 * Characters enclosed in single quotes are treated as a single
 * argument.  Return true if the user has requested a BG job, false if
 * the user has requested a FG job.  
 */
int parseline(const char *cmdline, char **argv) 
{
	static char array[MAXLINE]; /* holds local copy of command line */
	char *buf = array;          /* ptr that traverses command line */
	char *delim;                /* points to first space delimiter */
	int argc;                   /* number of args */
	int bg;                     /* background job? */

	strcpy(buf, cmdline);
	buf[strlen(buf)-1] = ' ';  /* replace trailing '\n' with space */
	while (*buf && (*buf == ' ')) /* ignore leading spaces */
		buf++;

	/* Build the argv list */
	argc = 0;
	if (*buf == '\'') {
		buf++;
		delim = strchr(buf, '\'');
	}
	else {
		delim = strchr(buf, ' ');
	}

	while (delim) {
		argv[argc++] = buf;
		*delim = '\0';
		buf = delim + 1;
		while (*buf && (*buf == ' ')) /* ignore spaces */
			buf++;

		if (*buf == '\'') {
			buf++;
			delim = strchr(buf, '\'');
		}
		else {
			delim = strchr(buf, ' ');
		}
	}
	argv[argc] = NULL;

	if (argc == 0)  /* ignore blank line */
		return 1;

	/* should the job run in the background? */
	if ((bg = (*argv[argc-1] == '&')) != 0) {
		argv[--argc] = NULL;
	}
	return bg;
}

/* 
 * builtin_cmd - If the user has typed a built-in command then execute
 *    it immediately.  
 */
int builtin_cmd(char **argv) 
{
	if (!strcmp(argv[0], "quit") || strcmp(argv[0], "exit") == 0) {
		exit(0);
	} 	
	// Checks if "Jobs" command
	else if (strcmp(argv[0], "jobs") == 0) {
		listjobs(jobs);
		return 1;
	}
	// Checks if "ps" command
    else if (strcmp(argv[0], "ps") == 0) {
        argv[0] = "/bin/ps";
        return 0;
    }	
    // Checks if "ls" command
	else if (strcmp(argv[0], "ls") == 0) {
        argv[0] = "/bin/ls";
        return 0;
    }
    // Checks if "echo" command
    else if (strcmp(argv[0], "echo") == 0) {
        argv[0] = "/bin/echo";
        return 0;
    }
    // Checks if "clear" command
    else if (strcmp(argv[0], "clear") == 0) {
        argv[0] = "/usr/bin/clear";
        return 0;
    }
    // Checks if "bg" or "fg" command - Foreground, or Background job
	else if (strcmp(argv[0], "bg") == 0 || strcmp(argv[0], "fg") == 0) {
		do_bgfg(argv);
		return 1;
	}
	// If entier then it's not a builtin command, and it'll return 0
    else {
        return 0; 
        // not a builtin command
    }
}

/* 
 * do_bgfg - Execute the builtin bg and fg commands
 */
void do_bgfg(char **argv) 
{
	struct job_t *job_s = NULL;

	int jid; // To find out if ID is Job ID or Process ID
	pid_t pid;
	char *id = argv[1]; // Later Reference of ID

	if(id == NULL) // if the ID is not presnet
	{
		printf("%s, Requires PID or JID \n", argv[0]);
		return;
	}
	// Either JID or PID,
	// Checking if %(Job) or digit(Process)
	if(id[0] == '%') 
	{ // or argv[1][0]
		jid = atoi(&id[1]);
		job_s = getjobjid(jobs, jid);

		if(job_s == NULL) { // if getjobjid(jobs, jid) is NULL
			printf("There is no such job for %s \n", id);
			return;
		}
	}
	else if(isdigit(id[0])) {
		pid = atoi(id);
		job_s = getjobpid(jobs, pid);

		if(job_s == NULL){ // checking if process is real
			printf("There is no such process for %d \n", pid);
			return;
		}
	}
	else{ // Neither JID or PID
			printf("Not recognized: %s must be PID or JID \n", argv[0]);
			return;
	}
	// Now if it is a JID or PID as JOB exists
	pid = job_s->pid;
	jid = job_s->jid; 
	char *bgfg = argv[0];

	if(kill(-(pid), SIGCONT) < 0){
		printf("Error - kill \n");
		// Kill if there's an Error
	}

	// If argv[0] is a background - Determine the job
	if(!strcmp("fg", argv[0])){
		if(job_s->state == ST){
			job_s->state = FG; // Changes the state to
			// FG if it is ST
			waitfg(job_s->pid);
		}
	}
	else if (!strcmp("bg", argv[0])){
		printf("%d, %d, %s", job_s->jid, job_s->pid, job_s->cmdline);
		job_s->state = BG;
	}
	else {
		printf("Background/Foreground Error for %s \n", argv[0]);
		// Throw the error to the user if isn't either
	}
}

/* 
 * waitfg - Block until process pid is no longer the foreground process
 */
void waitfg(pid_t pid)
{
	struct job_t* job_s;
	while((job_s = getjobpid(jobs, pid)) != NULL && (job_s->state = FG)) {
		sleep(0); // waits until the process if out of the
	}
	return;
}

/*****************
 * Signal handlers
 *****************/

/* 
 * sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
 *     a child job terminates (becomes a zombie), or stops because it
 *     received a SIGSTOP or SIGTSTP signal. The handler reaps all
 *     available zombie children, but doesn't wait for any other
 *     currently running children to terminate.  
 */
void sigchld_handler(int sig) 
{
    int pid = 0;
    int status = -1;
	// Waits for all the child processes, and handlings to finish according
	// to what their status are
	while ((pid = waitpid(-1, &status, WNOHANG|WUNTRACED))>0) {
        if (WIFSTOPPED(status)) {
        	// Find a job using the list, 
        	// and change its state to ST (predefined constant)
            getjobpid(jobs,pid)->state=ST;
            printf("Job %d %d is stopped by %d \n", pid2jid(pid), pid, WTERMSIG(status));
        } else if(WIFSIGNALED(status)) {
        	// Deletes the Job
        	// Checks if the process was actually terminated by another process 
        	if(WTERMSIG(status) == 2){
        		printf("%d %d was terminated by %d \n", pid2jid(pid), pid, WTERMSIG(status));
        	}
            deletejob(jobs,pid);
        } else if(WIFEXITED(status)) {
        	deletejob(jobs, pid); // Terminates normally from the list
        }
    }
}
/* 
 * sigint_handler - The kernel sends a SIGINT to the shell whenver the
 *    user types ctrl-c at the keyboard.  Catch it and send it along
 *    to the foreground job.  
 */
void sigint_handler(int sig) 
{
	pid_t pid = fgpid(jobs); // Declaring pid
	int jid = pid2jid(pid); // Declaring jid
	struct job_t* job_s = NULL; // Declaring job_s as a jot_t
	int i = 0; // Declaring i for the foor loop
	for(i = 0; i<MAXJOBS; i++){
		if(getjobjid(jobs, i) != NULL && getjobjid(jobs, i)->state == FG)
		{
			job_s = getjobjid(jobs, i);
		}
		if(job_s != NULL){ // Sends the Foreground job 
			// that is related to the process signal
			kill(-(job_s->pid), SIGINT); 
			// Deletes the job if this process continues / KILL
		}
	} // if((pid > 0) { printf("An error has occured"); 
		// kill(-pid, SIGTSTP); }
}

/*
 * sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
 *     the user types ctrl-z at the keyboard. Catch it and suspend the
 *     foreground job by sending it a SIGTSTP.  
 */
void sigtstp_handler(int sig) 
{
	pid_t pid = fgpid(jobs); // Declaring pid
	int jid = pid2jid(pid); // Declaring jid
	struct job_t* job_s = NULL; // Declaring job_s as a jot_t
	int i = 0; // Declaring i for the foor loop
	for(i = 0; i<MAXJOBS; i++){
		if(getjobjid(jobs, i) != NULL && getjobjid(jobs, i)->state == FG)
		{
			job_s = getjobjid(jobs, i);
		}
		if(job_s != NULL){ // Sends the Foreground job that is 
						   // related to the process signal
			kill(-(job_s->pid), SIGTSTP); 
			// Deletes the job if this process continues / KILL
		}
	} // if((pid > 0) { printf("An error has occured"); 
		// kill(-pid, SIGTSTP); }
}

/*********************
 * End signal handlers
 *********************/

/***********************************************
 * Helper routines that manipulate the job list
 **********************************************/

/* clearjob - Clear the entries in a job struct */
void clearjob(struct job_t *job) {
	job->pid = 0;
	job->jid = 0;
	job->state = UNDEF;
	job->cmdline[0] = '\0';
}

/* initjobs - Initialize the job list */
void initjobs(struct job_t *jobs) {
	int i;

	for (i = 0; i < MAXJOBS; i++)
		clearjob(&jobs[i]);
}

/* maxjid - Returns largest allocated job ID */
int maxjid(struct job_t *jobs) 
{
	int i, max=0;

	for (i = 0; i < MAXJOBS; i++)
		if (jobs[i].jid > max)
			max = jobs[i].jid;
	return max;
}

/* addjob - Add a job to the job list */
int addjob(struct job_t *jobs, pid_t pid, int state, char *cmdline) 
{
	int i;

	if (pid < 1)
		return 0;

	for (i = 0; i < MAXJOBS; i++) {
		if (jobs[i].pid == 0) {
			jobs[i].pid = pid;
			jobs[i].state = state;
			jobs[i].jid = nextjid++;
			if (nextjid > MAXJOBS)
				nextjid = 1;
			strcpy(jobs[i].cmdline, cmdline);
			if(verbose){
				printf("Added job [%d] %d %s\n", jobs[i].jid, jobs[i].pid, jobs[i].cmdline);
			}
			return 1;
		}
	}
	printf("Tried to create too many jobs \n");
	return 0;
}

/* deletejob - Delete a job whose PID=pid from the job list */
int deletejob(struct job_t *jobs, pid_t pid) 
{
	int i;

	if (pid < 1)
		return 0;

	for (i = 0; i < MAXJOBS; i++) {
		if (jobs[i].pid == pid) {
			clearjob(&jobs[i]);
			nextjid = maxjid(jobs)+1;
			return 1;
		}
	}
	return 0;
}

/* fgpid - Return PID of current foreground job, 0 if no such job */
pid_t fgpid(struct job_t *jobs) {
	int i;

	for (i = 0; i < MAXJOBS; i++)
		if (jobs[i].state == FG)
			return jobs[i].pid;
	return 0;
}

/* getjobpid  - Find a job (by PID) on the job list */
struct job_t *getjobpid(struct job_t *jobs, pid_t pid) {
	int i;

	if (pid < 1)
		return NULL;
	for (i = 0; i < MAXJOBS; i++)
		if (jobs[i].pid == pid)
			return &jobs[i];
	return NULL;
}

/* getjobjid  - Find a job (by JID) on the job list */
struct job_t *getjobjid(struct job_t *jobs, int jid) 
{
	int i;

	if (jid < 1)
		return NULL;
	for (i = 0; i < MAXJOBS; i++)
		if (jobs[i].jid == jid)
			return &jobs[i];
	return NULL;
}

/* pid2jid - Map process ID to job ID */
int pid2jid(pid_t pid) 
{
	int i;

	if (pid < 1)
		return 0;
	for (i = 0; i < MAXJOBS; i++)
		if (jobs[i].pid == pid) {
			return jobs[i].jid;
		}
	return 0;
}

/* listjobs - Print the job list */
void listjobs(struct job_t *jobs) 
{
	int i;

	for (i = 0; i < MAXJOBS; i++) {
		if (jobs[i].pid != 0) {
			printf("[%d] (%d) ", jobs[i].jid, jobs[i].pid);
			switch (jobs[i].state) {
				case BG: 
					printf("Running ");
					break;
				case FG: 
					printf("Foreground ");
					break;
				case ST: 
					printf("Stopped ");
					break;
				default:
					printf("listjobs: Internal error: job[%d].state=%d ", 
							i, jobs[i].state);
			}
			printf("%s\n", jobs[i].cmdline);
		}
	}
}
/******************************
 * end job list helper routines
 ******************************/


/***********************
 * Other helper routines
 ***********************/

/*
 * usage - print a help message
 */
void usage(void) 
{
	printf("Usage: shell [-hvp]\n");
	printf("   -h   print this message\n");
	printf("   -v   print additional diagnostic information\n");
	printf("   -p   do not emit a command prompt\n");
	exit(1);
}

/*
 * unix_error - unix-style error routine
 */
void unix_error(char *msg)
{
	fprintf(stdout, "%s: %s\n", msg, strerror(errno));
	exit(1);
}

/*
 * app_error - application-style error routine
 */
void app_error(char *msg)
{
	fprintf(stdout, "%s\n", msg);
	exit(1);
}

/*
 * Signal - wrapper for the sigaction function
 */
handler_t *Signal(int signum, handler_t *handler) 
{
	struct sigaction action, old_action;

	action.sa_handler = handler;  
	sigemptyset(&action.sa_mask); /* block sigs of type being handled */
	action.sa_flags = SA_RESTART; /* restart syscalls if possible */

	if (sigaction(signum, &action, &old_action) < 0)
		unix_error("Signal error\n");
	return (old_action.sa_handler);
}

/*
 * sigquit_handler - The driver program can gracefully terminate the
 *    child shell by sending it a SIGQUIT signal.
 */
void sigquit_handler(int sig) 
{
	printf("Terminating after receipt of SIGQUIT signal\n");
	exit(1);
}
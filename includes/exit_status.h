#ifndef EXIT_STATUS_H
# define EXIT_STATUS_H

                // ----- Standard Exit Codes ----- //

# define SUCCESS 0	            //Success: The command completed without any errors.
# define GEN_ERR 1	            //General error: Catch-all for errors that don’t have a specific code.
# define MSB 2	                //Misuse of shell builtins: Syntax errors or incorrect usage of shell commands (e.g., cd without arguments).
# define CICE 126	            //Command invoked cannot execute (e.g., permission denied).
# define CMD_N_FOUND 127	    //Command not found (e.g., typo or command not in $PATH).
# define INV_EXIT 128	        //Invalid exit argument (e.g., exit -1 or exit 256).
# define ST 130	                
# define ESOOFR 255	            //Exit status out of range (e.g., exit 256 wraps to 0).

                // ----- Exit Codes from Signals ----- //

// # define SIGHUP	    129 	    //Hangup detected (e.g., terminal closed).
// # define SIGINT	    130 	    //Script terminated by Ctrl+C (SIGINT).
// # define SIGQUIT	131 	    //Quit signal (usually triggered by Ctrl+\).
// # define SIGILL	    132 	    //Illegal instruction.
// # define SIGTRAP	133 	    //Trace/breakpoint trap.
// # define SIGABRT	134 	    //Aborted (e.g., by abort()).
// # define SIGBUS	    135 	    //Bus error (e.g., invalid memory access).
// # define SIGFPE	    136 	    //Floating point exception (e.g., division by zero).
// # define SIGKILL	137 	    //Process killed with SIGKILL (kill -9).
// # define SIGUSR1	138 	    //User-defined signal 1.
// # define SIGSEGV	139 	    //Segmentation fault (invalid memory access).
// # define SIGUSR2	140 	    //User-defined signal 2.
// # define SIGPIPE	141 	    //Broken pipe (writing to a closed pipe).
// # define SIGALRM	142 	    //Timer signal from alarm().
// # define SIGTERM	143 	    //Termination signal. Process killed with SIGTERM (kill -15)..
// # define SIGSTKFLT	144 	    //Stack fault on some architectures.
// # define SIGCHLD	145 	    //Child process stopped or terminated.
// # define SIGCONT	146 	    //Continue executing if stopped.
// # define SIGSTOP	147 	    //Stop process (cannot be caught or ignored).
// # define SIGTSTP	148 	    //Stop signal (from Ctrl+Z).
// # define SIGTTIN	149 	    //Background process tried to read from terminal.
// # define SIGTTOU	150 	    //Background process tried to write to terminal.
// # define SIGURG	    151 	    //Urgent socket condition.
// # define SIGXCPU	152 	    //CPU time limit exceeded.
// # define SIGXFSZ	153 	    //File size limit exceeded.
// # define SIGVTALRM	154 	    //Virtual timer expired.
// # define SIGPROF	155 	    //Profiling timer expired.
// # define SIGWINCH	156 	    //Window size change (e.g., resizing a terminal).
// # define SIGIO	    157 	    //I/O event occurred.
// # define SIGPWR	    158 	    //Power failure signal.
// # define SIGSYS	    159 	    //Bad system call.

#endif
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define oops(m,x) {perror(m);exit(x);}


main(int ac,char *av[])
{

	int thepipe[2],newpipe[2], /*file descriptors*/
		thepid,newpid; /* the pid*/

	if(ac != 4){
		fprintf(stderr,"usage: pipe cmd1 cmd2 cmd3\n");
		exit(1);
	}

	if(pipe(thepipe)==-1) /*get pipe*/
		oops("Cannot get a pipe",1);
/*now we have a thepipe, now let's get two processes*/
	if((thepid=fork())==-1) /*get a proc*/
		oops("Cannot fork",2);

/*right here, there are two processes*/
	if(thepid>0){	/*parent will exec av[3]*/
		close(thepipe[1]); /*parent doesn't write to pipe*/
		
		if(dup2(thepipe[0],0)==-1)
			oops("could not redirect stdin",3);

		close(thepipe[0]); /*stdin is duped, close pipe*/
		execlp(av[3],av[3],NULL);
		oops(av[3],4);

	}
	else{ /*child execs av[2] and write into pipe*/
 		close(thepipe[0]);

                if(dup2(thepipe[1],1)==-1)
                        oops("could not redirect stdout",5);
                close(thepipe[1]); /*stdout is duped, close pipe*/
	  	if(pipe(newpipe)==-1) /*get pipe*/
                	 oops("Cannot get a pipe",6);
/*now we have a newpipe, now let's get two processes*/
		if((newpid=fork())==-1)
             		 oops("Cannot fork",7);
/*right here, here are two processes*/
		if(newpid>0){ /*parent will exec av[2]*/
		close(newpipe[1]);  
		if(dup2(newpipe[0],0)==-1)
			oops("could not redirect stdin",8);
		close(newpipe[0]); /*stdin is duped, close pipe*/
		execlp(av[2],av[2],NULL);
		oops(av[2],9);

		}
		else{/*child execs av[1] and writes into pipe*/
			close(newpipe[0]);	/*child doesn't read from pipe*/
	
			if(dup2(newpipe[1],1) == -1)
				oops("could not redirect stdout",10);
			close(newpipe[1]);	/*stdout is duped, close pipe*/
			execlp(av[1],av[1],NULL);
			oops(av[1],11);
		}
	}
}


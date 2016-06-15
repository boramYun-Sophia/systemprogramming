#include <stdio.h>
#include <signal.h>

#define READ 0
#define WRITE 1
FILE *popen2(const char*,const char*);
int main(){

	FILE *fp;
	char buf[BUFSIZ];

	fp=popen2("ls","r");
	while(fgets(buf,BUFSIZ,fp)!=NULL)
		fputs(buf,stdout);


}

FILE *popen2(const char *command,const char *mode){
	int pfp[2],pid; /*the pipe and the process*/
	FILE *fdopen(),*fp; /*fdopen makes a fd a stream*/
	int parent_end,child_end; /*of pipe*/
	
	if(*mode == 'r'){ /*figure out direction*/
		parent_end = READ;
		child_end = WRITE;
	}else if(*mode == 'w'){
		parent_end = WRITE;
		child_end = READ;
	}else return NULL;

	if(pipe(pfp) == -1) /*get a pipe*/
		return NULL;
	if((pid=fork())==-1){ /*get a pipe*/
		close(pfp[0]);/*or dispose of pipe*/
		close(pfp[1]);
		return NULL;

}
/*parent code here*/
/*need to close one end and fdopen other end*/

	if(pid>0){
		if(close(pfp[child_end])==-1)
			return NULL;
		return fdopen(pfp[parent_end],mode); /*same mode*/

}

/*chlid code here*/
/*need to redirect stdin or stdout then exec the cmd*/
	if(close(pfp[parent_end]) == -1) /*close the other end*/
		exit(1);	/*do NOT return*/
	if(dup2(pfp[child_end],child_end) == -1)
		exit(1);
	if(close(pfp[child_end]) == -1) /*done with this one*/
		exit(1);
				/*all set to run cmd*/
	execl("/bin/sh","sh","-c",command,NULL);
	exit(1);

}

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

main(int ac,char *av[])
{
DIR *dir_ptr;
char A[100];
if(ac != 3)
{
	printf("error!!!");
	exit(0);
}

if((dir_ptr = opendir(av[2])) == NULL)
{
	rename(av[1],av[2]);
	printf("It renames the file %s into %s\n",av[1],av[2]);
}
else 
{

	strcpy(A,av[2]);
	strcat(A,"/");
	strcat(A,av[1]);
	link(av[1],A);
	unlink(av[1]);
	printf("It moves the file %s into the directory %s\n",av[1],av[2]);

}


}


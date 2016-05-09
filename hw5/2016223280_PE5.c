#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>


main()
{
        void f(int);
        int i;
        signal(SIGINT,f);
        for(i = 0 ; i < 20 ; i++){
                printf("hello\n");
                sleep(1);
        }
}

void f(int signum)
{
	int input;
        printf("Interrupted! Ok to quit(y/n)\n");
        input= tolower(get_ok_char());
        if(input == 'y')
                exit(0);
}

get_ok_char()
{
        int c;
        while ((c = getchar()) != EOF && strchr("yYnN",c) == NULL);
        return c;
}


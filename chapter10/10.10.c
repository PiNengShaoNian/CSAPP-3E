#include "csapp.h"

int main(int argc, char **argv) 
{
    int n;
    rio_t rio;
    char buf[MAXLINE];

    if (argc == 2) /* infile */
    {
        int fd = open(argv[1], O_RDONLY|O_CREAT);
        dup2(fd, STDIN_FILENO);
        close(fd);
    }

    Rio_readinitb(&rio, STDIN_FILENO);
    while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) 
	    Rio_writen(STDOUT_FILENO, buf, n);

    exit(0);
}

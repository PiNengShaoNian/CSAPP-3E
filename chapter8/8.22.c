int mysystem(char* command) {
    int status;
    char *argv[4];
    char *a0 = "sh";
    char *a1 = "-c";
    if(fork() == 0) {
        argv[0] = a0;
        argv[1] = a1;
        argv[2] = command;
        argv[3] = NULL;
        execve("/bin/sh", argv, environ);
        return -1;
    }
    else {
        if(wait(&status) != 0) {
            if(WIFEXITED(status) != 0)  return WEXITSTATUS(status);
            else return status; 
        }
        else {
            return -1;
        }
    }

}
if(Fork() == 0) {
    dup2(STDIN_FILENO, atoi(argv[1]));
    Execve("fstatcheck", argv, envp);
}
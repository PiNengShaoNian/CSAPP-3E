void get_filetype(char *filename, char *filetype) {
    if(strstr(filename, ".html")) {
        strcpy(filetype, "text/html");
    }
    else if(strstr(filename, ".gif")) {
        strcpy(filetype, "image/gif");
    }
    else if(strstr(filename, ".png")) {
        strcpy(filetype, "image/png");
    }
    else if(strstr(filename, ".jpg")) {
        strcpy(filetype, "image/jpg");
    }
    else if(strstr(filename, ".mpeg")) {
        strcpy(filetype, "video/mpeg");
    }
    else {
        strcpy(filetype, "text/plain");
    }
}
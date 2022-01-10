#include <stdio.h>;

void good_echo()  {
    const int SIZE = 5;
    char buffer[SIZE];

    while(1) {
        fgets(buffer, SIZE, stdin);
        printf("%s", buffer);

        if(buffer[strlen(buffer) - 1] == "\n") {
            break;
        }
    }
}
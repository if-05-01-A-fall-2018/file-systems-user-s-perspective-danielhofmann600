#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Got %i Arguments needet 3",argc);
    }
    int cpy = open(argv[1],O_RDONLY);
    if(!cpy){
        printf("The File %s does not exist! -> %i\n",argv[1],cpy);
        return -1;
    }
    int dest = open(argv[2],O_RDONLY);
    if(!dest){
        printf("The File %s already exists and will be overwritten!\n",argv[2]);
        remove(argv[2]);
    }
    mode_t m = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    dest = creat(argv[2], m);
    open(argv[2], O_WRONLY);
    char toCpy[100];
    int character;
    while(1){
        character = read(cpy, toCpy, 60);
        if(character == 0)break;
        write(dest, toCpy, character);
    }
    close(dest);
    close(cpy);
    return 1;
}
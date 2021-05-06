#include <stdio.h>
#include <unistd.h>

const int MAX_FILE_ADDR_STR_LEN=80;


void main(int argc, char argv[]){
    char *file_addr=malloc(MAX_FILE_ADDR_STR_LEN*sizeof(char));
    pid_t pid_a,pid_b,pid_c;

    if(pid_a=fork()){//process A

    }else{
        if(pid_b=fork()){//process B

        }else{
            if(pid_c=fork()){//process C

            }else{//mani process

            }
        }
    }
}
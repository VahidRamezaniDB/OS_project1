#include <stdio.h>
#include <unistd.h>

const int MAX_FILE_ADDR_STR_LEN=80;


void main(int argc, char *argv[]){
    char *file_addr=malloc(MAX_FILE_ADDR_STR_LEN*sizeof(char));
    char *output_file_addr=malloc(MAX_FILE_ADDR_STR_LEN*sizeof(char));
    int *before_hist = malloc(sizeof(int)*256);
    int *after_hist = malloc(sizeof(int)*256);

    pid_t pid_a,pid_b,pid_c;
    int parent_child_histogram_before_fd[2];
    int parent_child_histogram_after_fd[2];
    int parent_child_addr_fd[2];
    pipe(parent_child_addr_fd);
    pipe(parent_child_histogram_before_fd);
    pipe(parent_child_histogram_after_fd);
    
    if(!(pid_a=fork())){//process A

    }else{

    }
        if(!(pid_b=fork())){//process B

        }else{

        }
            if(!(pid_c=fork())){//process C
                
                char *input_file_addr=malloc(MAX_FILE_ADDR_STR_LEN*sizeof(char));
                int *before_hist_c = malloc(sizeof(int)*256);
                int *after_hist_c = malloc(sizeof(int)*256);
                char *output_file_addr_c = malloc(MAX_FILE_ADDR_STR_LEN*sizeof(char));

                close(parent_child_histogram_after_fd[0]);
                close(parent_child_histogram_before_fd[0]);


                read(parent_child_addr_fd[0], input_file_addr, MAX_FILE_ADDR_STR_LEN*sizeof(char));



                write(parent_child_histogram_before_fd[1], before_hist_c, sizeof(int)*256);

                write(parent_child_histogram_after_fd[1], after_hist_c, sizeof(int)*256);



                write(parent_child_addr_fd[1], output_file_addr_c, MAX_FILE_ADDR_STR_LEN*sizeof(char));

                close(parent_child_addr_fd[0]);
                close(parent_child_addr_fd[1]);
                close(parent_child_histogram_after_fd[1]);
                close(parent_child_histogram_before_fd[1]);



            }else{//main process
                
                close(parent_child_histogram_after_fd[1]);
                close(parent_child_histogram_before_fd[1]);

                write(parent_child_addr_fd[1], file_addr, MAX_FILE_ADDR_STR_LEN*sizeof(char));

                read(parent_child_histogram_before_fd[0], before_hist, sizeof(int)*256);

                read(parent_child_histogram_after_fd[0], after_hist, sizeof(int)*256);

                read(parent_child_addr_fd[0], output_file_addr, MAX_FILE_ADDR_STR_LEN*sizeof(char));

                close(parent_child_addr_fd[0]);
                close(parent_child_addr_fd[1]);
                close(parent_child_histogram_after_fd[0]);
                close(parent_child_histogram_before_fd[0]);

            }
        }
    }
}
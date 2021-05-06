#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

const int MAX_FILE_ADDR_STR_LEN=80;


void main(int argc, char *argv[]){
    char *file_addr=malloc(MAX_FILE_ADDR_STR_LEN*sizeof(char));
    char *output_file_addr=malloc(MAX_FILE_ADDR_STR_LEN*sizeof(char));
    int *before_hist = malloc(sizeof(int)*256);
    int *after_hist = malloc(sizeof(int)*256);

    pid_t pid_a,pid_b,pid_c;
    int named_pipe_fd_ac, named_pipe_fd_bc;
    int parent_child_histogram_before_fd[2];
    int parent_child_histogram_after_fd[2];
    int parent_child_addr_fd[2];
    char *ac_pipe_file_name = "acnamedpipe";
    char *bc_pipe_file_name = "bcnamedpipe";
    mkfifo(ac_pipe_file_name, 0666);
    mkfifo(bc_pipe_file_name, 0666);

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
                
                named_pipe_fd_bc = open(bc_pipe_file_name, O_RDWR);
                named_pipe_fd_ac = open(ac_pipe_file_name, O_RDWR);
                char *input_file_addr=malloc(MAX_FILE_ADDR_STR_LEN*sizeof(char));
                int *before_hist_c = malloc(sizeof(int)*256);
                int *after_hist_c = malloc(sizeof(int)*256);
                char *output_file_addr_c = malloc(MAX_FILE_ADDR_STR_LEN*sizeof(char));


                close(parent_child_histogram_after_fd[0]);
                close(parent_child_histogram_before_fd[0]);


                read(parent_child_addr_fd[0], input_file_addr, MAX_FILE_ADDR_STR_LEN*sizeof(char));
                write(named_pipe_fd_ac, input_file_addr, strlen(input_file_addr)+1);
                write(named_pipe_fd_bc, input_file_addr, strlen(input_file_addr)+1);

                sleep(2);

                read(named_pipe_fd_ac, before_hist_c, sizeof(int)*256);
                write(parent_child_histogram_before_fd[1], before_hist_c, sizeof(int)*256);


                read(named_pipe_fd_bc, output_file_addr_c, MAX_FILE_ADDR_STR_LEN*sizeof(char));
                write(named_pipe_fd_ac, output_file_addr_c, strlen(output_file_addr_c)+1);
                
                sleep(2);
                
                read(named_pipe_fd_ac, after_hist_c, sizeof(int)*256);
                write(parent_child_histogram_after_fd[1], after_hist_c, sizeof(int)*256);
                
                write(parent_child_addr_fd[1], output_file_addr_c, MAX_FILE_ADDR_STR_LEN*sizeof(char));

                close(parent_child_addr_fd[0]);
                close(parent_child_addr_fd[1]);
                close(parent_child_histogram_after_fd[1]);
                close(parent_child_histogram_before_fd[1]);
                close(named_pipe_fd_bc);
                close(named_pipe_fd_ac);
                
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
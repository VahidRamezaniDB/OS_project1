#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

const int KERNEL_SIZE=3;
const int IM_SIZE=512;

void generate_kernel(int kernel[KERNEL_SIZE][KERNEL_SIZE]){

}

void apply_kernel(int im[IM_SIZE][IM_SIZE],int output_im[IM_SIZE][IM_SIZE],int kernel[KERNEL_SIZE][KERNEL_SIZE]){


}

void image_pad(int im[IM_SIZE][IM_SIZE],int out[IM_SIZE+KERNEL_SIZE-1][IM_SIZE+KERNEL_SIZE-1]){
    
}

void main(int argc, char* argv[]){
    char* file_addr;
	char* fifo_name;
	int fd;
	int image[IM_SIZE][IM_SIZE];
    int kernel[KERNEL_SIZE][KERNEL_SIZE];

    if(argc<2){
        fputs("Eror: too few arguments. (filter)\n",stderr);
        exit(EXIT_FAILURE);
    }

    fifo_name=argv[1];

	mkfifo(fifo_name,0666);

	fd=open(fifo_name,O_RDONLY);


}
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
    for(int i=0;i<IM_SIZE+KERNEL_SIZE-1;i++){
        for(int j=0;j<IM_SIZE+KERNEL_SIZE-1;j++){
            if(i<KERNEL_SIZE/2 || j<KERNEL_SIZE/2
            || i-IM_SIZE>KERNEL_SIZE/2 || j-IM_SIZE>KERNEL_SIZE/2){
                out[i][j]=0;
            }else{
                out[i][j]=im[i-KERNEL_SIZE/2][j-KERNEL_SIZE/2];
            }
        }
    }
}

void main(int argc, char* argv[]){
    char* file_addr;
	char* fifo_name;
	int fd;
	int image[IM_SIZE][IM_SIZE];
    int output_image[IM_SIZE][IM_SIZE];
    int kernel[KERNEL_SIZE][KERNEL_SIZE];

    if(argc<2){
        fputs("Eror: too few arguments. (filtering)\n",stderr);
        exit(EXIT_FAILURE);
    }

    fifo_name=argv[1];

	mkfifo(fifo_name,0666);

	fd=open(fifo_name,O_RDONLY);

    FILE *file_pointer = fopen("outputimg.bmp", "w");
    if(file_pointer == NULL){
        fputs("failed to open output file. (filtering process)", stderr);
        exit(EXIT_FAILURE);
    }
    fwrite(output_image, sizeof(int), IM_SIZE*IM_SIZE, file_pointer);
    fclose(file_pointer);

}
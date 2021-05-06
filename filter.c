#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>

const int KERNEL_SIZE=3;
const int IM_SIZE=512;
const int MAX_FILE_ADDR_STR_LEN=80;

void generate_kernel(int kernel[KERNEL_SIZE][KERNEL_SIZE]){

    double sigma = 1.0;
    double r, s = 2.0 * sigma * sigma;
    double sum = 0.0;
  
    for (int x = -KERNEL_SIZE/2; x <= KERNEL_SIZE/2; x++) {
        for (int y = -KERNEL_SIZE/2; y <= KERNEL_SIZE/2; y++) {
            r = sqrt(x * x + y * y);
            kernel[x + KERNEL_SIZE/2][y + KERNEL_SIZE/2] = (exp(-(r * r) / s)) / (M_PI * s);
            sum += kernel[x + KERNEL_SIZE/2][y + KERNEL_SIZE/2];
        }
    }
  
    for (int i = 0; i < KERNEL_SIZE; ++i)
        for (int j = 0; j < KERNEL_SIZE; ++j)
            kernel[i][j] /= sum;
}

void apply_kernel(int im[IM_SIZE+KERNEL_SIZE-1][IM_SIZE+KERNEL_SIZE-1],int output_im[IM_SIZE][IM_SIZE],int kernel[KERNEL_SIZE][KERNEL_SIZE]){


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

int get_image(char *filename, int im[][IM_SIZE]){
	FILE *infile;
	int i, j;
	if ((infile = fopen(filename, "r")) != NULL){
		for (i = 0; i < IM_SIZE; i++){
			for (j = 0; j < IM_SIZE; j++){
				fscanf(infile, "%d", &im[i][j]);
			}
		}
		return 1;
	}
	return 0;
}

void main(int argc, char* argv[]){
    char* file_addr;
	char* fifo_name;
	int fd;
	int image[IM_SIZE][IM_SIZE];
    int image_padded[IM_SIZE+KERNEL_SIZE-1][IM_SIZE+KERNEL_SIZE-1];
    int output_image[IM_SIZE][IM_SIZE];
    int kernel[KERNEL_SIZE][KERNEL_SIZE];

    if(argc<2){
        fputs("Eror: too few arguments. (filtering)\n",stderr);
        exit(EXIT_FAILURE);
    }

    fifo_name=argv[1];

	mkfifo(fifo_name,0666);

	fd=open(fifo_name,O_RDONLY);

    if(read(fd,file_addr,MAX_FILE_ADDR_STR_LEN*sizeof(char))==-1){
		fputs("Error reading fifo. (hist_calc)\n",stderr);
		exit(EXIT_FAILURE);
	}
	close(fd);

    if (!(get_image(file_addr, image))){
        fputs("Eror opening the image. (filtering)\n",stderr);
        exit(EXIT_FAILURE);
	}

    generate_kernel(kernel);
    image_pad(image,image_padded);
    apply_kernel(image_padded,output_image,kernel);


    // FILE *file_pointer = fopen("outputimg.bmp", "w");
    // if(file_pointer == NULL){
    //     fputs("failed to open output file. (filtering process)\n", stderr);
    //     exit(EXIT_FAILURE);
    // }
    // fputs(output_image, file_pointer);
    // fclose(file_pointer);

}
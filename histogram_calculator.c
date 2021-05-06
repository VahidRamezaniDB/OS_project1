#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

const int MAX_FILE_ADDR_STR_LEN=80;
const int IM_SIZE=512;
const int GRAY_LEVELS=256;


int get_image(char *filename, int im[][IM_SIZE], int *xsize, int *ysize){
	FILE *infile;
	int i, j;
	if ((infile == fopen(filename, "r")) != NULL){
		fscanf(infile, "%d %d", &xsize, &ysize);
		for (i = 0; i < *ysize; i++){
			for (j = 0; j < *xsize; j++){
				fscanf(infile, "%d", &im[i][j]);
			}
		}
		return 1;
	}
	return 0;
}


void find_histogram(int image[][IM_SIZE], int xsize, int ysize, int hist[GRAY_LEVELS]){
	int i, j;
	for (i = 0; i < GRAY_LEVELS; hist[i++] = 0);

	for (i = 0; i < ysize; i++)
		for (j = 0; j < xsize; j++)
			hist[image[i][j]]++;
}

void main(int argc, char* argv[]){
	char* file_addr;
	char* fifo_name;
	int fd;
	int image[IM_SIZE][IM_SIZE], histogram[GRAY_LEVELS], xsize, ysize;

    if(argc<2){
        fputs("Eror: too few arguments. (histogram_calculator)\n",stderr);
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

	if (!(get_image(file_addr, image, &xsize, &ysize))){
        fputs("Eror opening the image. (histogram_calculator/get_image)\n",stderr);
        exit(EXIT_FAILURE);
	}else{
		find_histogram(image, xsize, ysize, histogram);
	}

	fd=open(fifo_name,O_WRONLY);

	if(write(fd,histogram,sizeof(histogram))==-1){
		fputs("Eror writing into the fifo. (hist_calc)\n",stderr);
        exit(EXIT_FAILURE);
	}
	close(fd);
}



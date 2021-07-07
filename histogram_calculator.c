#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct {
    unsigned short type;                 /* Magic identifier            */
    unsigned int size;                       /* File size in bytes          */
    unsigned int reserved;
    unsigned int offset;                     /* Offset to image data, bytes */
} HEADER;
typedef struct {
    unsigned int size;               /* Header size in bytes      */
    int width,height;                /* Width and height of image */
    unsigned short planes;       /* Number of colour planes   */
    unsigned short bits;         /* Bits per pixel            */
    unsigned int compression;        /* Compression type          */
    unsigned int imagesize;          /* Image size in bytes       */
    int xresolution,yresolution;     /* Pixels per meter          */
    unsigned int ncolours;           /* Number of colours         */
    unsigned int importantcolours;   /* Important colours         */
} INFOHEADER;
typedef struct {
    unsigned char r,g,b,junk;
} COLOURINDEX;

const int MAX_FILE_ADDR_STR_LEN=80;
const int IM_SIZE=512;
const int GRAY_LEVELS=256;


unsigned char* LoadBitmapFile(char *filename, INFOHEADER *bitmapInfoHeader)
{
    FILE *filePtr;  //our file pointer
    HEADER bitmapFileHeader;  //our bitmap file header
    unsigned char *bitmapImage;  //store image data
    int imageIdx=0;  //image index counter
    unsigned char tempRGB;  //our swap variable

    //open file in read binary mode
    filePtr = fopen(filename,"rb");
    if (filePtr == NULL)
        return "";

    //read the bitmap file header
    fread(&bitmapFileHeader, sizeof(HEADER),1,filePtr);

    //verify that this is a .BMP file by checking bitmap id
    if (bitmapFileHeader.type !=0x4D42)
    {
        fclose(filePtr);
        return "";
    }

    //read the bitmap info header
    fread(bitmapInfoHeader, sizeof(INFOHEADER),1,filePtr); 

    //move file pointer to the beginning of bitmap data
    fseek(filePtr, bitmapFileHeader.offset, SEEK_SET);

    //allocate enough memory for the bitmap image data
    bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->imagesize);

    //verify memory allocation
    if (!bitmapImage)
    {
        free(bitmapImage);
        fclose(filePtr);
        return "";
    }

    //read in the bitmap image data
    fread(bitmapImage,bitmapInfoHeader->imagesize,1,filePtr);

    //make sure bitmap image data was read
    if (bitmapImage == NULL)
    {
        fclose(filePtr);
        return "";
    }

    //swap the R and B values to get RGB (bitmap is BGR)
    for (imageIdx = 0;imageIdx < bitmapInfoHeader->imagesize;imageIdx+=3)
    {
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
    }

    //close file and return bitmap image data
    fclose(filePtr);
    return bitmapImage;
}


void find_histogram(unsigned char *im, int hist[GRAY_LEVELS]){
	int i, j;
	for (i = 0; i < GRAY_LEVELS; hist[i++] = 0);
	for (i = 0; i < strlen(im); i++){
		int temp;
		sscanf(im,"%d",&temp);
		hist[temp]++;
	}
	printf("done!\n");
}

void main(int argc, char* argv[]){
	char* file_addr;
	char* fifo_name;
	int fd;
	int image[IM_SIZE][IM_SIZE], histogram[GRAY_LEVELS];

    if(argc<2){
        fputs("Eror: too few arguments. (histogram_calculator)\n",stderr);
        exit(EXIT_FAILURE);
    }

    fifo_name=argv[1];

	mkfifo(fifo_name,0666);

	fd=open(fifo_name,O_RDONLY);
	printf("%d\n",fd);
	printf("%s\n",fifo_name);
	sleep(1);
	if(read(fd,file_addr,MAX_FILE_ADDR_STR_LEN*sizeof(char))==-1){
		fputs("Error reading fifo. (hist_calc)\n",stderr);
		exit(EXIT_FAILURE);
	}
	close(fd);

	INFOHEADER bitmapInfoHeader;
	unsigned char *bitmap_data;

	bitmap_data = LoadBitmapFile(file_addr, &bitmapInfoHeader);

	fputs("histogram calc successfully load image\nnow trying to find histogram of image\n",stdout);
	find_histogram(bitmap_data, histogram);
	fputs("histogram calculated successfully\n",stdout);

	fd=open(fifo_name,O_WRONLY);

	if(write(fd,histogram,sizeof(histogram))==-1){
		fputs("Eror writing into the fifo. (hist_calc)\n",stderr);
        exit(EXIT_FAILURE);
	}
	close(fd);
}



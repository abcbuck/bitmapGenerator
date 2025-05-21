#include <fstream>

enum colors {
	BLUE, GREEN, RED
};

const int BRIGHT=255;

//custom variables
const unsigned long width=512, height=512; //don't delete!
const unsigned long mean=(height+width)/2;

//custom headers
#include <cmath>

//custom function: change for different results
char defineColorValueOfPixel(int x, int y, int color) { //don't delete!
	char ret;

	if(color==RED)
		ret = BRIGHT*y/(height-1);
	else if(color==GREEN)
		ret = BRIGHT-std::pow(x+y-static_cast<int>(mean)-1, 2)/std::pow(mean-1, 2)*BRIGHT;
	else if(color==BLUE)
		ret = std::sqrt(std::pow(BRIGHT, 2)*x/(width-1));

	return ret;
}

void createFileHeader(char fileHeader[], unsigned long width, unsigned long height) {
	//Bitmap & DIB header (54 bytes)

	//Bitmap file header (14 bytes)

	//'BM' identifies the BMP and DIB file (2 bytes)
	fileHeader[0] = 'B';
	fileHeader[1] = 'M';

	unsigned long imageSize = 3 * width * height;
	unsigned long fileSize = 54 + imageSize;
	//size of the BMP file in bytes (4 bytes)
	fileHeader[2] = fileSize % 256;
	fileSize /= 256;
	fileHeader[3] = fileSize % 256;
	fileSize /= 256;
	fileHeader[4] = fileSize % 256;
	fileHeader[5] = fileSize / 256;

	//reserved; if created manually, can be 0 (2 bytes)
	fileHeader[6] = (char)0;
	fileHeader[7] = (char)0;

	//reserved; if created manually, can be 0 (2 bytes)
	fileHeader[8] = (char)0;
	fileHeader[9] = (char)0;

	//offset to data (4 bytes)
	fileHeader[10] = (char)54;
	fileHeader[11] = (char)0;
	fileHeader[12] = (char)0;
	fileHeader[13] = (char)0;

	//DIB header (bitmap information header) (different formats)
	//simplest common format is BITMAPINFOHEADER (40 bytes)

	//header size (4 bytes)
	fileHeader[14] = (char)40;
	fileHeader[15] = (char)0;
	fileHeader[16] = (char)0;
	fileHeader[17] = (char)0;

	//bitmap width in pixels (signed integer) (4 bytes)
	fileHeader[18] = width % 256;
	width /= 256;
	fileHeader[19] = width % 256;
	width /= 256;
	fileHeader[20] = width % 256;
	fileHeader[21] = width / 256;

	//bitmap height in pixels (signed integer) (4 bytes)
	fileHeader[22] = height % 256;
	height /= 256;
	fileHeader[23] = height % 256;
	height /= 256;
	fileHeader[24] = height % 256;
	fileHeader[25] = height / 256;

	//number of color planes (must be 1) (2 bytes)
	fileHeader[26] = (char)1;
	fileHeader[27] = (char)0;

	//number of bits per pixel (2 bytes)
	fileHeader[28] = (char)24;
	fileHeader[29] = (char)0;

	//compression method (4 bytes)
	//a value of '0' means no compression
	fileHeader[30] = (char)0;
	fileHeader[31] = (char)0;
	fileHeader[32] = (char)0;
	fileHeader[33] = (char)0;

	//image size in bytes (without header) (4 bytes)
	fileHeader[34] = imageSize % 256;
	imageSize /= 256;
	fileHeader[35] = imageSize % 256;
	imageSize /= 256;
	fileHeader[36] = imageSize % 256;
	fileHeader[37] = imageSize / 256;

	//(rest isn't needed)

	//horizontal resolution (pixels per metre, signed integer) (4 bytes)
	fileHeader[38] = (char)0;
	fileHeader[39] = (char)0;
	fileHeader[40] = (char)0;
	fileHeader[41] = (char)0;

	//vertical resolution (pixels per metre, signed integer) (4 bytes)
	fileHeader[42] = (char)0;
	fileHeader[43] = (char)0;
	fileHeader[44] = (char)0;
	fileHeader[45] = (char)0;

	//number of colors in the color palette, '0' defaults to 2**n (4 bytes)
	fileHeader[46] = (char)0;
	fileHeader[47] = (char)0;
	fileHeader[48] = (char)0;
	fileHeader[49] = (char)0;

	//number of important colors used, or '0' when every color is important (4 bytes)
	fileHeader[50] = (char)0;
	fileHeader[51] = (char)0;
	fileHeader[52] = (char)0;
	fileHeader[53] = (char)0;
}

void writeToFile(const char* fileName, unsigned long width, unsigned long height, char data[]) {
  char fileHeader[54];
  createFileHeader(fileHeader, width, height);
  std::ofstream file(fileName, std::ios::binary);
	file.write(fileHeader, 54);
	if(width%4 == 0)
		file.write(data, 3*width*height);
	else { //every row has to be padded to a multiple of four bytes
		for(int i=0; i<height; i++) {
			const int dataPerRowLength = 3*width;
			const int paddingPerRowLength = width%4;
			file.write(data+i*dataPerRowLength, dataPerRowLength);
			file.write("\0\0", paddingPerRowLength);
		}
	}
	file.close();
}

int main(int argc, char* argv[]){
	const char* fileName;
	if(argc > 1)
		fileName = argv[1];
	else
		fileName = "bitmap.bmp";

	char *data = new char[3*height*width];

	for(int x=0; x<width; x++) {
		for(int y=0; y<height; y++) {
			for(int color=0; color<3; color++) {
				data[3*x+3*width*y+color] = defineColorValueOfPixel(x, y, color);
			}
		}
	}

  writeToFile(fileName, width, height, data);

	return 0;
}

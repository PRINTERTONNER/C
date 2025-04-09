#include <stdio.h> //import print function
#include <stdlib.h> // import numpy
#include <stdint.h>


#pragma pack(push, 1)
/*
push는 이전의 정렬 규칙을 저장하고, 새로운 규칙을 설정하는 역할을 합니다.
1은 1바이트 정렬을 의미합니다. 즉, 구조체 내 모든 멤버들이 1바이트 간격으로 배치되도록 합니다. 패딩을 최소화하여 메모리를 절약하려는 목적입니다.
*/

typedef struct {
	//Bitmap file header
	unsigned short filetype;
	unsigned int filesize;  // The size of the BMP file in bytes
	unsigned short Reserved1;
	unsigned short Reserved2;
	unsigned int pixeldata; //픽셀 데이터 오프셋 (시작점)
} BMPFileHeader;

/*

typedef struct{
//uint8_t size; //DIB헤더의 크기
unsigned short size;
unsigned int width;
unsigned int height; //이미지의 너비 및 높이를 픽셀 단위로 보임
unsigned short planes; //planes 색상 평면의 수. BMP에선 항상 1
unsigned short bitcount; // 픽셀 하나를 표현하는 데 사용되는 비트 수를 나타냅니다. 이 값에 따라 색상 깊이가 결정됩니다 (예: 1, 4, 8, 16, 24, 32비트).
unsigned int compression; //이미지 데이터의 압축 타입
unsigned int imagesize; //비트맵 이미지 데이터의 실제 크기를 바이트 단위로 나타낸 것
unsigned int xPelsPerMeter;
unsigned int yPelsPerMeter; //각각 이미지의 수평 및 수직 해상도를 m/pixel 단위로
signed int clrUsed; //색상 테이블에서 실제 사용되는 색상 수
signed int clrImportant; //이미지 표현에 중요한 색상의 수. 0 <- 다중요함
}BMPInfoHeader;
*/


typedef struct {
	unsigned int size;             // DIB 헤더 크기 (40, 124)
	unsigned int width;            // 이미지 너비
	unsigned int height;           // 이미지 높이
	unsigned short planes;         // 색상 평면 수 (항상 1)
	unsigned short bitcount;       // PALLETE
	unsigned int compression;      // 압축 방식
	unsigned int imagesize;        // 이미지 크기 (압축된 경우)
	int xPelsPerMeter;             // 가로 해상도 (픽셀/미터)
	int yPelsPerMeter;             // 세로 해상도 (픽셀/미터)
	unsigned int clrUsed;          // 색상 테이블에서 사용되는 색상 수
	unsigned int clrImportant;     // 중요한 색상 수

	unsigned int redMask;          // 비트 필드 마스크 (빨간색)
	unsigned int greenMask;        // 비트 필드 마스크 (초록색)
	unsigned int blueMask;         // 비트 필드 마스크 (파란색)
	unsigned int alphaMask;        // 비트 필드 마스크 (알파)
	unsigned int csType;           // 색 공간 타입
	unsigned int endpoints[9];     // 색상 공간 좌표
	unsigned int gammaRed;         // 빨간색 감마 값
	unsigned int gammaGreen;       // 초록색 감마 값
	unsigned int gammaBlue;        // 파란색 감마 값
	unsigned int intent;           // 렌더링 의도
	unsigned int profileData;      // 색상 프로파일 데이터 오프셋
	unsigned int profileSize;      // 색상 프로파일 크기
	unsigned int reserved;         // reserved 값 (0)
} BMPInfoHeader;

typedef struct {

	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char Reserved;

}Pal;


typedef struct {
	unsigned char b, g, r;
}PIXEL;



#pragma pack(pop)

/*
#pragma pack(pop)은 push로 설정한 이전 정렬 규칙을 복원. 즉, #pragma pack(push, 1)을 사용하여 설정한 1바이트 정렬을 마친 후,
#pragma pack(pop)을 사용하여 원래의 정렬 규칙을 다시 적용.
*/

int main() {


	FILE* file;

	//errno_t err = fopen_s(&file, "C:/Users/tmdgh/Desktop/sample_4.bmp", "rb");
	//errno_t err = fopen_s(&file, "c:/Users/tmdgh/sample.bmp", "rb");
	//errno_t err = fopen_s(&file, "C:/Users/tmdgh/RGB_image.bmp", "rb");
	//errno_t err = fopen_s(&file, "C:/Users/tmdgh/grayscale_image.bmp", "rb");

	errno_t err = fopen_s(&file, "C:/Users/tmdgh/Desktop/polimg.bmp", "rb");

	//errno_t err = fopen_s(&file, "C:/Users/tmdgh/Desktop/grayscale.bmp", "rb+");
	//errno_t err = fopen_s(&file, "C:/Users/tmdgh/Desktop/zxczxv.bmp", "rb");
	//errno_t err = fopen_s(&file, "C:/Users/tmdgh/Desktop/SpaceTelescope.bmp", "rb");

	//errno_t err = fopen_s(&file, "C:/Users/tmdgh/OneDrive/바탕 화면/zxczxv.bmp","rb");

	//errno_t err = fopen_s(&file, "C:/Users/tmdgh/sample_1.bmp", "rb");
	//errno_t err = fopen_s(&file, "C:/Users/tmdgh/OneDrive/바탕 화면/face.bmp", "rb");

	BMPFileHeader fileHeader;
	BMPInfoHeader infoheader;
	Pal pal;
	//PIXEL pixel;

	//fread(&fileHeader, sizeof(BMPFileHeader), 1, file);
	//fread(&infoheader, sizeof(BMPInfoHeader), 1, file);
	//fread(&pixel, sizeof(PIXEL), 1, file);


	fread(&fileHeader, sizeof(BMPFileHeader), 1, file);
	fread(&infoheader, sizeof(BMPInfoHeader), 1, file);

	/*
	fread(&pal, sizeof(pal), 1, file);

	int numPixels = infoheader.width * infoheader.height; // 픽셀 수 계산
	PIXEL* pixels = (PIXEL*)malloc(numPixels * sizeof(PIXEL)); //malloc 이미지 시작 주소 반환. 그래서 fread(pixels)가능

	fseek(file, fileHeader.pixeldata, SEEK_SET);
	fread(pixels, sizeof(PIXEL), numPixels, file);


	for (int i = 0; i < infoheader.width * infoheader.height; i++) {      // for loop 조건문 신기해요

		//pixels[i].b = 0;
		//pixels[i].r = 0;
		//pixels[i].g = 0;

	}

	fseek(file, fileHeader.pixeldata, SEEK_SET); // 수정된 픽셀 데이터를 파일에 다시 쓰기
	fwrite(pixels, sizeof(PIXEL), numPixels, file);

	//PIXEL pixel

	fread(pixels, sizeof(PIXEL), 1, file);

	
	Pal pals[256];

	fseek(file, sizeof(BMPFileHeader) + infoheader.size, SEEK_SET);

	fread(pals, sizeof(Pal), 256, file);

	for (int i = 0; i < 256; i++) {

		//printf("\n Number(index) : %d \n \n Blue : %d \n, Green : %d \n, Red : %d \n", i, pals[i].blue, pals[i].green, pals[i].red, pals[i]);

	};

	unsigned char* pixelIndices = (unsigned char*)malloc(infoheader.width * infoheader.height * sizeof(unsigned char));
	fseek(file, fileHeader.pixeldata, SEEK_SET);
	fread(pixelIndices, sizeof(unsigned char), infoheader.width * infoheader.height , file);

	for (int i = 0; i < infoheader.height * infoheader.width; i++) {

	printf("\n index in the picture : %d \n ", pixelIndices[i]);

	}





	*/


	//fwrite(&pal, sizeof(PALLET), 3, file);

	//printf("\n\n\n Pixel Data Info : \n\n\n");

	//for (int i = 0; i < numPixels; i++) {
	//	//printf("Pixel %d : R = %d, G = %d, B = %d \n", i, pixels[i].r, pixels[i].g, pixels[i].b);
	//}



	printf("\n\n\nBitMaP file header\n\n\n");

	printf("Type : 0x%X\n", fileHeader.filetype);  //0x%X 16진수 형식 출력
	printf("size : %u 바이트\n", fileHeader.filesize);
	printf("Reserved 1 : %d\n", fileHeader.Reserved1);
	printf("Reserved 2 : %d\n", fileHeader.Reserved2);
	printf("offset stating position : %u\n\n\n\n", fileHeader.pixeldata);

	printf("infoHeader \n\n\n");

	printf("DIBheader (size of infoheader) : %u\n", infoheader.size);
	printf("Image width : %u\n", infoheader.width);
	printf("Image height : %u\n", infoheader.height);
	printf("plane : %u\n", infoheader.planes);
	printf("bitcount : %u\n", infoheader.bitcount);
	printf("compression type : %u\n", infoheader.compression);
	printf("image size on byte : %u\n", infoheader.imagesize);
	printf("resolution pixel/m on x : %u\n", infoheader.xPelsPerMeter);
	printf("resolution pixel/m on y : %u\n", infoheader.yPelsPerMeter);
	printf("color_profiles : %u\n", infoheader.clrUsed);
	printf("clrimportant : %u\n", infoheader.clrImportant);

	//printf("redMask : %u\n", infoheader.redMask);
	//printf("greenMask : %u\n", infoheader.greenMask);
	//printf("blueMask : %u\n", infoheader.blueMask);
	//printf("alphaMask : %u\n", infoheader.alphaMask);
	//printf("csType : %u\n", infoheader.csType);
	//printf("endpoints : %u\n", infoheader.endpoints);
	//printf("gammaRed : %u\n", infoheader.gammaRed);
	//printf("gammaGreen : %u\n", infoheader.gammaGreen);
	//printf("gammaBlue : %u\n", infoheader.gammaBlue);
	//printf("intent : %u\n", infoheader.intent);
	//printf("profildata : %u\n", infoheader.profileData);
	//printf("profilesize : %u\n", infoheader.profileSize);
	//printf("reserved : %u \n", infoheader.reserved);




	//typedef struct {
	//unsigned char b, g, r;



	fclose(file);



	return 0;

}
#include<stdio.h>
#include<unistd.h>
#include "bmp.h"

int main(void)
{
	char *path = "test.bmp";
	unsigned char imgdata[100][100];

	bmp_datainfo_t tBmpinfo;
	tBmpinfo.unWidth = 100;
	tBmpinfo.unHeight = 100;
	tBmpinfo.tImgWide = BMP_8WIDE;
	tBmpinfo.ucImgData = (unsigned char**)imgdata;
	
	for(int i = 0; i < 100; i++)
	{
		for(int j = 0; j < 100; j++)
		{
			imgdata[i][j] = i*2;
		}
	}	

	BMP_EncapsulateBmp(path, &tBmpinfo);

	return 0;
}




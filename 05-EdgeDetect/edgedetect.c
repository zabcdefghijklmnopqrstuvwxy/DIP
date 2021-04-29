#include"edgedetect.h"
#include"bmp.h"

static int8_t sobel_hor[3][3]=
{
    {-1, -2, 0},
    {0, 0, 0},
    {1, 2, 1}
};

static int8_t sobel_ver[3][3]=
{
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
};

bool isInarr(uint32_t col, uint32_t row, uint32_t height, uint32_t width)
{
	if(col >= 0 && col < height && row >= 0 && row < width)
	{
		return true;
	}
	
	return false;
}

int convolution(short **arr, uint32_t col, uint32_t row, uint32_t height, uint32_t width, int8_t filter[3][3], uint32_t len)
{
	int consum = 0;
	int x = 0;
	int y = 0;

   	for(int i = 0; i < len; i++)
	{
		for(int j = 0; j < len; j++)
		{
			x = i - len/2 + col;
			y = j - len/2 + row;
			if(isInarr(x, y, height, width))
			{		
				consum += arr[x][y]*filter[i][j];
			}
			else
			{
				consum += 0;
			}
		}
	}

	return consum;
}

int edgedetect(char *infile, char *outfile)
{
	int gx = 0;
	int gy = 0;
	int h, w;
    short **inarry;
    short **outarry;
    struct bmpfileheader fileheader;
	struct bitmapheader bmheader;

    get_image_size(infile, &h, &w);
    inarry = allocate_image_array(h, w);
    outarry = allocate_image_array(h, w);
    read_bmp_image(infile, inarry);

    bmheader.height = h;
    bmheader.width  = w;


	for(int i = 0; i < h; i++)
	{
		for(int j = 0; j < w; j++)
		{
			gx = 0;
			gy = 0;
			gx= convolution(inarry, i, j, h, w, sobel_hor, 3);
			gy= convolution(inarry, i, j, h, w, sobel_ver, 3);
			
			if(gx + gy > 0xff)
			{
				outarry[i][j] = 0xff;
			}
			else if(gx + gy < 0)
			{
				outarry[i][j] = 0;
			}
			else
			{
				outarry[i][j] = gx + gy;
			}
		}
	}

    create_allocate_bmp_file(outfile, &fileheader, &bmheader);
    write_bmp_image(outfile, outarry);

    free_image_array(inarry, h);
    free_image_array(outarry, h);

    return 0;
}



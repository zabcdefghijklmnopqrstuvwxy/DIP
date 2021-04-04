#include "transform.h"
#include "bmp.h"
#include <math.h>

#define		PI			3.14159267
#define 	RADIAN(angle) ((angle)*PI/180.0)

typedef struct
{
	int x;
	int y;
}pos_t, *p_pos_t;

int rotate(int8_t *infile, int8_t *outfile, uint32_t degree)
{
	int h, w;
	int unWidth, unHeight;
	struct bmpfileheader fileheader;
	struct bitmapheader bmheader;
    short  **in_array, **out_array;
	pos_t a, b, c, d;
	double sina, cosa;
	double dx, dy;

	get_image_size(infile, &h, &w);
    in_array = allocate_image_array(h, w);
    read_bmp_image(infile, in_array);

	sina = sin(RADIAN(degree));
	cosa = cos(RADIAN(degree));

	a.x = -w/2*cosa + h/2*sina;
	a.y = w/2*sina + h/2*cosa;

	b.x = w/2*cosa + h/2*sina;
	b.y = -w/2*sina + h/2*cosa;

	c.x = -w/2*cosa - h/2*sina;
	c.y = w/2*sina - h/2*cosa;

	d.x = w/2*cosa - h/2*sina;
	d.y = -w/2*sina - h/2*cosa;

	unWidth = abs(c.x - b.x) > abs(a.x -d.x) ? abs(c.x -b.x) : abs(a.x -d.x);
	unHeight = abs(a.y - d.y) > abs(b.y - c.y) ? abs(a.y - d.y) : abs(b.y - c.y);

	out_array = allocate_image_array(unHeight, unWidth);

	for(int i = 0; i < unHeight; i++)
	{
		for(int j = 0; j < unWidth; j++)
		{
			out_array[i][j] = 0;
		}
	}

	dx = -unWidth/2*cosa - unHeight/2*sina + w/2;
	dy = unWidth/2*sina - unHeight/2*cosa + h/2;

	for(int i = 0; i < unHeight; i++)
	{
		for(int j = 0; j < unWidth; j++)
		{
			int x = j*cosa + i*sina + dx;
			int y = -j*sina + i*cosa + dy;
			
			if((x >= 0) && (x < w) && (y >= 0) && (y < h))
			{
				out_array[i][j] = in_array[y][x];
			}
		}
	}

	bmheader.height = unHeight;
    bmheader.width  = unWidth;

	create_allocate_bmp_file(outfile, &fileheader, &bmheader);

	write_bmp_image(outfile, out_array);

    free_image_array(in_array, h);
    free_image_array(out_array, unHeight);

	return 0;
}

#include"graytrans.h"
#include"bmp.h"

#define     GRAYLEVEL           256

int histogram(char* infile, char* outfile)
{
    struct bmpfileheader fileheader;
	struct bitmapheader bmheader;
    unsigned long histogram[GRAYLEVEL];
    unsigned long sum[GRAYLEVEL];
    double coeffi = 0.0;
 
    int h, w, k;
    short  **in_array, **out_array;

    get_image_size(infile, &h, &w);
    in_array = allocate_image_array(h, w);
    out_array = allocate_image_array(h, w);
    read_bmp_image(infile, in_array);

    memset(histogram, 0, sizeof(histogram));

    //histogram_equalization(in_array, out_array, h, w);


    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            histogram[in_array[i][j]]++;
        }
    }

    sum[0] = histogram[0];
    for(int i = 1; i < GRAYLEVEL; i++)
    {
        sum[i] = sum[i-1] + histogram[i];
    }

    coeffi = (double)(GRAYLEVEL - 1)*1.0/(double)(h*w*1.0);
    printf("coeffi is %lf\n",coeffi);

    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            k = in_array[i][j];
            out_array[i][j] = sum[k]*coeffi;
        }
    }

    bmheader.height = h;
    bmheader.width  = w;

	create_allocate_bmp_file(outfile, &fileheader, &bmheader);

	write_bmp_image(outfile, out_array);

    free_image_array(in_array, h);
    free_image_array(out_array, h);



}

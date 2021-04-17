#include"dft.h"
#include"bmp.h"

#define         PI              3.14159267

int dft(char *infile, char *outfile)
{
    char *objfile = "objfile.bmp";
    int h, w;
    double re, im, dtmp;
    short **inarry;
    double **outarry;
    short **objarry;
    struct bmpfileheader fileheader;
	struct bitmapheader bmheader;
    double **rearry;
    double **imarry;
    double cosa,sina;

    get_image_size(infile, &h, &w);
    inarry = allocate_image_array(h, w);
    read_bmp_image(infile, inarry);

    rearry = allocate_double_array(h, w);
    imarry = allocate_double_array(h, w);
    outarry = allocate_double_array(h, w);
    objarry = allocate_image_array(h, w);

    bmheader.height = h;
    bmheader.width  = w;

    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {   
                re = 0;
                im = 0;
                for(int x = 0; x < h; x++)
                {
                    for(int y = 0; y < w; y++)
                    {
                         dtmp = (double)i *x /(double)h + (double)j*y/(double)w;
                         cosa = cos(-2*PI*dtmp);
                         sina = sin(-2*PI*dtmp);
                         re += inarry[x][y]*cosa;
                         im += inarry[x][y]*sina;
                    }
                }

                rearry[i][j] = re;
                imarry[i][j] = im;
//                rearry[i][j] = re;
  //              imarry[i][j] = im;
        }
    }

    printf("dft done\n");

    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            re = 0;

            for(int x = 0; x < h; x++)
            {
                for(int y = 0; y < w; y++)
                {
                    dtmp = (double)i *x /(double)h + (double)j*y/(double)w;
                    cosa = cos(2*PI*dtmp);
                    sina = sin(2*PI*dtmp);
                    
                    re+= rearry[x][y]*cosa - imarry[x][y]*sina;
                   // re+= rearry[x][y]*cosa - imarry[x][y]*sina;
                }
            }

            objarry[i][j] = re/(double)(1.0*h*w);
            if(objarry[i][j] >= 0xff)
            {
                objarry[i][j] = 0xff;
            }
            if(objarry[i][j] < 0)
            {
                objarry[i][j] = 0;
            }
        }
    }

    create_allocate_bmp_file(outfile, &fileheader, &bmheader);
    write_bmp_image(outfile, objarry);

    printf("idft done\n");

    free_image_array(inarry, h);
    free_image_array(objarry, h);
    free_double_array(rearry, h);
    free_double_array(imarry, h);
    free_double_array(outarry, h);

    return 0;
}

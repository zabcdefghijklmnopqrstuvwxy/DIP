#include <unistd.h>
#include <stdio.h>
#include "edgedetect.h"
int main(int argc, char * argv[])
{
    char infile[64];
    char outfile[64];
    int degree = 0; 
    int ch;

    printf("\n\n");
    printf("optind:%d，opterr：%d\n",optind,opterr);
    printf("--------------------------\n");
    while ((ch = getopt(argc, argv, "i:o:")) != -1)
    {
        printf("optind: %d\n", optind);
        switch (ch) 
        {
               case 'i':
                       memset(infile, 0, sizeof(infile));
					   strcpy(infile, optarg);
                       printf("input bmpfile path is %s\n", infile);
                       break;
               case 'o':
                       memset(outfile, 0, sizeof(outfile));
					   strcpy(outfile, optarg);	
                       printf("output bmpfile path is %s\n", outfile);
						break;
               default:
                       printf("Unknown option: %c\n",(char)optopt);
                       break;
        }
    }   


    edgedetect(infile, outfile);
    
	return 0;
}

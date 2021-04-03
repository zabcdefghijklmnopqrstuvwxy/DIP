#ifndef	_BMP_H_
#define	_BMP_H_

#define GRAY_LEVELS          255

struct bmpfileheader{
    unsigned short  filetype;
    unsigned long   filesize;
    short  reserved1;
    short  reserved2;
    unsigned long   bitmapoffset;
};

struct bitmapheader{
    unsigned long   size;
    long   width;
    long   height;
    unsigned short  planes;
    unsigned short  bitsperpixel;
    unsigned long   compression;
    unsigned long   sizeofbitmap;
    unsigned long   horzres;
    unsigned long   vertres;
    unsigned long   colorsused;
    unsigned long   colorsimp;
};

struct ctstruct{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};

union colortable_union{
    struct colortable
    {
        unsigned char blue;
        unsigned char green;
        unsigned char red;
        unsigned char reserved;
    }colortable;
    unsigned int l_num;
};

union short_char_union{
    short s_num;
    char  s_alpha[2];
};

union int_char_union{
    int  i_num;
    char i_alpha[2];
};

union long_char_union{
    int  l_num;
    char  l_alpha[4];
};

union float_char_union{
    float f_num;
    char  f_alpha[4];
};

union ushort_char_union{
    short s_num;
    char  s_alpha[2];
};

union uint_char_union{
    int  i_num;
    char i_alpha[2];
};

union ulong_char_union{
    int  l_num;
    char  l_alpha[4];
};


int get_image_size(const char* file_name, long* rows, long* cols);
void extract_long_from_buffer(char buffer[], int lsb, int start, long* number);
void extract_ulong_from_buffer(char buffer[], int lsb, int start,unsigned long* number);
void extract_short_from_buffer(char buffer[], int lsb, int start, short* number);
void extract_ushort_from_buffer(char buffer[], int lsb, int start, unsigned short* number);
void insert_short_into_buffer(char buffer[], int start, short number);
void insert_ushort_into_buffer(char buffer[], int start, unsigned short number);
void insert_long_into_buffer(char buffer[], int start, long number);
void insert_ulong_into_buffer(char buffer[], int start, unsigned long number);
short **allocate_image_array(long length, long width);
int free_image_array(short **the_array, long length);
void create_allocate_bmp_file(const char* file_name, struct bmpfileheader* file_header, struct bitmapheader* bmheader);
void read_bmp_file_header(const char* file_name, struct bmpfileheader* file_header);
void read_bm_header(const char* file_name, struct bitmapheader* bmheader);
int calculate_pad(long width);
void write_bmp_image(const char* file_name, short **array);
int does_not_exist(const char* file_name);
union colortable_union* read_allocate_colortable(const char* file_name, struct bitmapheader* bmheader);
void free_colortable(union colortable_union* colortable);


#endif

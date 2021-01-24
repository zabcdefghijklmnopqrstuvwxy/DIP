#ifndef	_BMP_H_
#define	_BMP_H_

#include<stdbool.h>

#define		bmp_ret		int

#define		bmp_ok				0
#define		bmp_argerr			-1
#define		bmp_out_of_memory	-2 		
#define		bmp_fileopen_failed	-3

/* *
* @brief bmp文件类型
*/
typedef enum
{
	BMP_1WIDE = 1,
	BMP_2WIDE = 2,
	BMP_8WIDE = 8,
	BMP_16WIDE = 16,
	BMP_24WIDE = 24,
	BMP_32WIDE = 32
}bmp_bitwide_t;


/* *
* @brief bmp数据信息
*/
typedef struct
{
	unsigned int unWidth;
	unsigned int unHeight;
	unsigned char **ucImgData;
	bmp_bitwide_t tImgWide;
}bmp_datainfo_t;


/**
* @brief BMP_IsBmp
* @params filepath表示待检测的bmp文件路径
* @note 通过文件魔术信息判断是否是bmp文件
* @return true表示是bmp文件，false表示非bmp文件
*/
bool BMP_IsBmp(unsigned char *ucFilepath);

/**
* @brief BMP_GetBmpInfo
* @params ucFilepath表示bmp文件路径，unWidth表示图像宽度，unHeight表示图像高度，bmptype表示bmp类型
* @note 读取信息头数据，提取相应的数据信息
* @return 返回bmp错误码
*/
bmp_ret	BMP_GetBmpInfo(unsigned char *ucFilepath,unsigned int *unWidth,unsigned int *unHeight,bmp_bitwide_t *bmptype);

/**
* @brief BMP_GetBmpData
* @params ucFilepath表示待获取的bmp文件路径，tInfo表示获取图像数据信息指针
* @note 读取bmp文件的图像数据
* @return 返回bmp错误码
*/
bmp_ret BMP_GetBmpData(unsigned char *ucFilepath, bmp_datainfo_t *tInfo);

/**
* @brief BMP_EncapsulateBmp
* @params ucFilepath待生成的文件路径, tInfo表示待封装的图像数据信息指针
* @note 读取bmp文件的图像数据
* @return 返回bmp错误码
*/
bmp_ret BMP_EncapsulateBmp(unsigned char *ucFilepath,bmp_datainfo_t *tInfo);

#endif


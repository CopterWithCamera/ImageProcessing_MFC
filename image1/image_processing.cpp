#include "stdafx.h"
#include <math.h>

#include "image_processing.h"

#define boolean_T bool

unsigned char gray_array[IMG_WIDTH*IMG_HEIGHT] = { 0 };
unsigned char gray_across_array[IMG_WIDTH*IMG_HEIGHT] = { 0 };
unsigned char result_across_array[IMG_WIDTH*IMG_HEIGHT] = { 0 };
unsigned char result_array[IMG_WIDTH*IMG_HEIGHT] = { 0 };
float length = 0;
float speed = 0;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//ͼ������
void Image_Fix(void)	//ͼ���㷨
{
	//demo
	length = 123.456;
	speed = -44.2233;
	for (int i = 0; i < IMG_WIDTH*IMG_HEIGHT; i++)
	{
		result_across_array[i] = gray_across_array[i];
	}

}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void across()	//��ͼ�����Խǵ�λ�ã�����gray_across_array
{
	for (int i = 0; i < 48; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			gray_across_array[j * 48 + i] = gray_array[i * 80 + j];
		}
	}
}

void back_across()	//��ͼ�����Խǵ�λ�ã�����gray_across_array
{
	for (int i = 0; i < 80; i++)
	{
		for (int j = 0; j < 48; j++)
		{
			result_array[j * 80 + i] = result_across_array[i * 48 + j];
		}
	}
}

void processing(unsigned char * c, double * pd1, double * pd2)
{
	//����ͼ��
	for (int i = 0; i < IMG_WIDTH*IMG_HEIGHT; i++)
	{
		gray_array[i] = c[i];
	}

	across();	//���ɶԽ���ͼ��

	Image_Fix();

	back_across();	//�ָ������ǶԽ���ͼ��

	//���򿽱�
	*pd1 = length;
	*pd2 = speed;
	for (int i = 0; i < IMG_WIDTH*IMG_HEIGHT; i++)
	{
		c[i] = result_array[i];
	}
}
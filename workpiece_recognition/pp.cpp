#include <tchar.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <vector> 
#include <cvaux.h>
#include <cmath> 


#ifdef _CH_
#pragma package <opencv>
#endif

#include "cv.h"
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp" 
#include <opencv2/core/core.hpp> 

using namespace std;
using namespace cv;


///************************Hu矩匹配********************************************/    
//int main(int argc, char * argv[])
//{
//
//	IplImage* img_8uc1 = cvLoadImage("E:\\weiSSD\\Desktop\\模式识别\\目标定位\\pipei - 副本\\1.png",CV_LOAD_IMAGE_GRAYSCALE);//改成自己的路径
//	IplImage* img_edge1 = cvCreateImage(cvGetSize(img_8uc1),8,1);
//	IplImage* img_8uc11 = cvCreateImage(cvGetSize(img_8uc1),8,3);
//
//	cvThreshold(img_8uc1,img_edge1,10,255,CV_THRESH_BINARY);//目标1图片的二值化阈值为100
//	CvMemStorage* storage1 = cvCreateMemStorage();
//	CvSeq* first_contour1 = NULL;
//	int Nc = cvFindContours(//输入图像必须为一个2值单通道图像
//		img_edge1,
//		storage1,
//		&first_contour1,
//		sizeof(CvContour),
//		CV_RETR_LIST
//		);
//	cvCvtColor(img_8uc1,img_8uc11,CV_GRAY2BGR);
//
//	IplImage* img_8uc2 = cvLoadImage("E:\\weiSSD\\Desktop\\模式识别\\目标定位\\pipei - 副本\\3.png",CV_LOAD_IMAGE_GRAYSCALE);//改成自己的路径
//	IplImage* img_edge2 = cvCreateImage(cvGetSize(img_8uc2),8,1);
//	IplImage* img_8uc22 = cvCreateImage(cvGetSize(img_8uc2),8,3);
//	IplImage *mask_img=cvCreateImage(cvGetSize(img_8uc22),8,1);//创建一幅图像
//
//	cvThreshold(img_8uc2,img_edge2,30,255,CV_THRESH_BINARY);//目标2图片的二值化阈值为30；目标3图片的二值化阈值为30(下面也得改)
//
//
//
//	CvMemStorage* storage2 = cvCreateMemStorage();
//	CvSeq* first_contour2 = NULL;
//
//	int Nc2 = cvFindContours(
//		img_edge2,
//		storage2,
//		&first_contour2,
//		sizeof(CvContour),
//		CV_RETR_LIST
//		);
//
//	cvCvtColor(img_8uc2,img_8uc22,CV_GRAY2BGR);
//
//	for(CvSeq* c=first_contour2;c!=NULL;c=c->h_next)
//	{	
//		double a=cvMatchShapes(first_contour1,c,CV_CONTOURS_MATCH_I1,0);
//		if(a<0.02)
//		{
//			continue;
//		}
//		cvZero(mask_img);//初始化图片，值都为0(黑色图)
//		CvBox2D  Rrect=cvMinAreaRect2(c);
//		cvDrawContours(
//			mask_img,
//			c,
//			CV_RGB(0,0,255),
//			CV_RGB(0,255,0),
//			0,2,8);
//		cvFloodFill(  
//			mask_img,  
//			cvPoint(1,1),  
//			CV_RGB(255, 255, 255),  
//			cvScalar(20, 30, 40, 0),  
//			cvScalar(20, 30, 40, 0),  
//			NULL,4,NULL); 
//		Mat mtx = img_8uc2;
//		Mat dst;
//		Mat mask = mask_img;
//		mask=255-mask;
//		mtx.copyTo(dst,mask);
//
//		cvShowImage("用于提取单个工件的“掩码”图",mask_img);
//		cvWaitKey(0);
//		imshow("提取出的单个工件",dst);
//		cvWaitKey(0);
//
//		IplImage ipl_img = dst; 
//		IplImage* img_edge3 = cvCreateImage(cvGetSize(&ipl_img),8,1);
//		cvThreshold(&ipl_img,img_edge3,30,255,CV_THRESH_BINARY);
//		IplImage* img_8uc33 = cvCreateImage(cvGetSize(&ipl_img),8,3);
//		CvMemStorage* storage3 = cvCreateMemStorage();
//		CvSeq* first_contour3 = NULL;
//		int Nc3 = cvFindContours(
//			img_edge3,
//			storage3,
//			&first_contour3,
//			sizeof(CvContour),
//			CV_RETR_LIST);
//		cvCvtColor(&ipl_img,img_8uc33,CV_GRAY2BGR);
//		int match=0;
//		for (CvSeq* c3=first_contour3;c3!=NULL;c3=c3->h_next)
//		{
//			cvDrawContours(
//				img_8uc33,
//				c3,
//				CV_RGB(0,0,255),
//				CV_RGB(0,255,0),
//				0,2,8);
//			cvShowImage("目标工件的轮廓",img_8uc33);
//			cvWaitKey(0);
//			cvCvtColor(img_8uc1,img_8uc11,CV_GRAY2BGR);
//			for (CvSeq* c1=first_contour1;c1!=NULL;c1=c1->h_next)
//			{
//				cvDrawContours(
//					img_8uc11,
//					c1,
//					CV_RGB(0,0,255),
//					CV_RGB(0,255,0),
//					0,2,8);
//				cvShowImage("工件模板的轮廓",img_8uc11);
//				cvWaitKey(0);
//				a=cvMatchShapes(c3,c1,CV_CONTOURS_MATCH_I1,0);
//				if(a<0.45)//以0.3为阈值进行判断，小于0.3认为匹配上，大于0.3认为没有匹配上
//				{
//					match++;
//					break;
//				}
//			}
//		}
//		if(match==Nc3)//模板的每个轮廓都和目标能匹配上
//		{
//			printf("该目标属于模板工件，在原图的二值化图像上框出来，使用Hu矩匹配方法（所取阈值为0.45）\n");
//			//则把这个目标框出来
//			cvDrawContours(
//				img_8uc22,
//				c,
//				CV_RGB(0,0,255),
//				CV_RGB(0,255,0),
//				0,2,8);
//
//		}
//		else
//		{
//			printf("该目标不属于模板工件\n");
//		}
//	}
//	cvShowImage("识别结果",img_8uc22);
//  	cvWaitKey(0);
//	return 0;
//}


///***************************轮廓树匹配***********************************************/
//int main(int argc, char * argv[])
//{
//	IplImage* img_8uc1 = cvLoadImage("E:\\weiSSD\\Desktop\\模式识别\\目标定位\\pipei - 副本\\1.png",CV_LOAD_IMAGE_GRAYSCALE);//改成自己的路径
//	IplImage* img_edge1 = cvCreateImage(cvGetSize(img_8uc1),8,1);
//	cvThreshold(img_8uc1,img_edge1,10,255,CV_THRESH_BINARY);
//	CvMemStorage* storage1 = cvCreateMemStorage();
//	CvSeq* first_contour1 = NULL;
//	int Nc = cvFindContours(
//		img_edge1,
//		storage1,
//		&first_contour1,
//		sizeof(CvContour),
//		CV_RETR_LIST
//		);
//	CvContourTree* tree1 = cvCreateContourTree(
//		first_contour1,
//		storage1,
//		200
//		);
//	IplImage* img_8uc12 = cvLoadImage("E:\\weiSSD\\Desktop\\模式识别\\目标定位\\pipei - 副本\\2.png",CV_LOAD_IMAGE_GRAYSCALE);
//	IplImage* img_edge12 = cvCreateImage(cvGetSize(img_8uc12),8,1);
//	cvThreshold(img_8uc12,img_edge12,10,255,CV_THRESH_BINARY);
//	CvMemStorage* storage2 = cvCreateMemStorage();
//	CvSeq* first_contour2 = NULL;
//	int Nc2 = cvFindContours(
//		img_edge12,
//		storage2,
//		&first_contour2,
//		sizeof(CvContour),
//		CV_RETR_LIST
//		);
//	CvContourTree* tree2 = cvCreateContourTree(
//		first_contour2,
//		storage2,
//		200
//		);
//	double n = cvMatchContourTrees(tree1,tree1,CV_CONTOURS_MATCH_I1,200);
//	printf("%d",n);
//	cvWaitKey();
//	return(0);
//}
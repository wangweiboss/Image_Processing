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


///************************Hu��ƥ��********************************************/    
//int main(int argc, char * argv[])
//{
//
//	IplImage* img_8uc1 = cvLoadImage("E:\\weiSSD\\Desktop\\ģʽʶ��\\Ŀ�궨λ\\pipei - ����\\1.png",CV_LOAD_IMAGE_GRAYSCALE);//�ĳ��Լ���·��
//	IplImage* img_edge1 = cvCreateImage(cvGetSize(img_8uc1),8,1);
//	IplImage* img_8uc11 = cvCreateImage(cvGetSize(img_8uc1),8,3);
//
//	cvThreshold(img_8uc1,img_edge1,10,255,CV_THRESH_BINARY);//Ŀ��1ͼƬ�Ķ�ֵ����ֵΪ100
//	CvMemStorage* storage1 = cvCreateMemStorage();
//	CvSeq* first_contour1 = NULL;
//	int Nc = cvFindContours(//����ͼ�����Ϊһ��2ֵ��ͨ��ͼ��
//		img_edge1,
//		storage1,
//		&first_contour1,
//		sizeof(CvContour),
//		CV_RETR_LIST
//		);
//	cvCvtColor(img_8uc1,img_8uc11,CV_GRAY2BGR);
//
//	IplImage* img_8uc2 = cvLoadImage("E:\\weiSSD\\Desktop\\ģʽʶ��\\Ŀ�궨λ\\pipei - ����\\3.png",CV_LOAD_IMAGE_GRAYSCALE);//�ĳ��Լ���·��
//	IplImage* img_edge2 = cvCreateImage(cvGetSize(img_8uc2),8,1);
//	IplImage* img_8uc22 = cvCreateImage(cvGetSize(img_8uc2),8,3);
//	IplImage *mask_img=cvCreateImage(cvGetSize(img_8uc22),8,1);//����һ��ͼ��
//
//	cvThreshold(img_8uc2,img_edge2,30,255,CV_THRESH_BINARY);//Ŀ��2ͼƬ�Ķ�ֵ����ֵΪ30��Ŀ��3ͼƬ�Ķ�ֵ����ֵΪ30(����Ҳ�ø�)
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
//		cvZero(mask_img);//��ʼ��ͼƬ��ֵ��Ϊ0(��ɫͼ)
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
//		cvShowImage("������ȡ���������ġ����롱ͼ",mask_img);
//		cvWaitKey(0);
//		imshow("��ȡ���ĵ�������",dst);
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
//			cvShowImage("Ŀ�깤��������",img_8uc33);
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
//				cvShowImage("����ģ�������",img_8uc11);
//				cvWaitKey(0);
//				a=cvMatchShapes(c3,c1,CV_CONTOURS_MATCH_I1,0);
//				if(a<0.45)//��0.3Ϊ��ֵ�����жϣ�С��0.3��Ϊƥ���ϣ�����0.3��Ϊû��ƥ����
//				{
//					match++;
//					break;
//				}
//			}
//		}
//		if(match==Nc3)//ģ���ÿ����������Ŀ����ƥ����
//		{
//			printf("��Ŀ������ģ�幤������ԭͼ�Ķ�ֵ��ͼ���Ͽ������ʹ��Hu��ƥ�䷽������ȡ��ֵΪ0.45��\n");
//			//������Ŀ������
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
//			printf("��Ŀ�겻����ģ�幤��\n");
//		}
//	}
//	cvShowImage("ʶ����",img_8uc22);
//  	cvWaitKey(0);
//	return 0;
//}


///***************************������ƥ��***********************************************/
//int main(int argc, char * argv[])
//{
//	IplImage* img_8uc1 = cvLoadImage("E:\\weiSSD\\Desktop\\ģʽʶ��\\Ŀ�궨λ\\pipei - ����\\1.png",CV_LOAD_IMAGE_GRAYSCALE);//�ĳ��Լ���·��
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
//	IplImage* img_8uc12 = cvLoadImage("E:\\weiSSD\\Desktop\\ģʽʶ��\\Ŀ�궨λ\\pipei - ����\\2.png",CV_LOAD_IMAGE_GRAYSCALE);
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
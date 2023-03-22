#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
void c1t1() {
	Mat srcMat = imread("F://01.jpg");
	int height = srcMat.rows;
	int width = srcMat.cols;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {
			//����ÿ�����ص�//
			uchar average = (srcMat.at<Vec3b>(i, j)[0] + srcMat.at<Vec3b>(i, j)[1] + srcMat.at<Vec3b>(i, j)[2]) / 3;
			srcMat.at<Vec3b>(i, j)[0] = average;
			srcMat.at<Vec3b>(i, j)[1] = average;
			srcMat.at<Vec3b>(i, j)[2] = average;
			//��������//
		}
	}
	imshow("c1t1", srcMat);
};


void c1t2() {
	Mat srcMat = imread("F://01.jpg", 0);
	imshow("c1t2", srcMat);

};

void c1t3() {
	Mat srcMat = imread("F://01.jpg");
	int height = srcMat.rows;
	int width = srcMat.cols;
	uchar threshold = 100;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {
			//����ÿ�����ص�//
			uchar average = (srcMat.at<Vec3b>(i, j)[0] + srcMat.at<Vec3b>(i, j)[1] + srcMat.at<Vec3b>(i, j)[2]) / 3;
			if (average > threshold) {
				average = 255;
			}
			else {
				average = 0;
			}
			srcMat.at<Vec3b>(i, j)[0] = average;
			srcMat.at<Vec3b>(i, j)[1] = average;
			srcMat.at<Vec3b>(i, j)[2] = average;
			//��������//

		}
	}
	imshow("c1t3", srcMat);
}

void c1t4() {
	Mat srcMat = imread("F://01.JPG");
	Mat deepMat;//�������
	srcMat.copyTo(deepMat);//ʹ��copyTo����ʵ�����
	Mat shallowMat;//����ǳ����mat
	shallowMat = srcMat;

	int height = srcMat.rows;
	int width = srcMat.cols;
	uchar threshold = 100;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {
			//����ÿ�����ص�//
			uchar average = (srcMat.at<Vec3b>(i, j)[0] + srcMat.at<Vec3b>(i, j)[1] + srcMat.at<Vec3b>(i, j)[2]) / 3;
			if (average > threshold) {
				average = 255;
			}
			else {
				average = 0;
			}
			srcMat.at<Vec3b>(i, j)[0] = average;
			srcMat.at<Vec3b>(i, j)[1] = average;
			srcMat.at<Vec3b>(i, j)[2] = average;
			//��������//

		}
	}

	imshow("c1t4���DeepMat", deepMat);
	imshow("c1t4ǳ����ShallowMat", shallowMat);
	//print("�ӽ���ɿ�����������ɵľ��������ڴ��еĵ�ַ��srcMat��ͬ��������ΪsrcMat�ĸı���仯����ǳ���Ƶõ��ľ�����Ȼָ��srcMat������srcMat�ĸı�������仯");

}
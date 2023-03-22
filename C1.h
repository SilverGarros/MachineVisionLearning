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
			//处理每个像素点//
			uchar average = (srcMat.at<Vec3b>(i, j)[0] + srcMat.at<Vec3b>(i, j)[1] + srcMat.at<Vec3b>(i, j)[2]) / 3;
			srcMat.at<Vec3b>(i, j)[0] = average;
			srcMat.at<Vec3b>(i, j)[1] = average;
			srcMat.at<Vec3b>(i, j)[2] = average;
			//结束处理//
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
			//处理每个像素点//
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
			//结束处理//

		}
	}
	imshow("c1t3", srcMat);
}

void c1t4() {
	Mat srcMat = imread("F://01.JPG");
	Mat deepMat;//定义深复制
	srcMat.copyTo(deepMat);//使用copyTo函数实现深复制
	Mat shallowMat;//定义浅复制mat
	shallowMat = srcMat;

	int height = srcMat.rows;
	int width = srcMat.cols;
	uchar threshold = 100;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {
			//处理每个像素点//
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
			//结束处理//

		}
	}

	imshow("c1t4深复制DeepMat", deepMat);
	imshow("c1t4浅复制ShallowMat", shallowMat);
	//print("从结果可看出，深复制生成的矩阵由于内存中的地址和srcMat不同，并不因为srcMat的改变而变化，而浅复制得到的矩阵依然指向srcMat，随着srcMat的改变而发生变化");

}
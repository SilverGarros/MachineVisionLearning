#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <core.hpp>
using namespace cv;
using namespace std;

//C1T1 获取摄像头图像并对图像进行中值滤波
//C1T2 获取摄像头图像并对图像进行均值滤波
//C1T3 读取摄像头头像并对图像进行高斯滤波`GaussianBlur()`
void c5t123();

//C1T4 边缘提取Sobel算子
void c5t4();

//C1T5 简单的磨皮程序


void c5t123() {
	VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened()) {
		cout << "不能打开摄像头或者视频文件" << endl;
		exit(0);
	}
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 540);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 960);
	while (1) {
		Mat frame;
		cap >> frame;
		namedWindow("Frame");
		imshow("Frame", frame);
		//C1T1 中值滤波
		Mat frameAfterMedianBlur;
		medianBlur(frame, frameAfterMedianBlur,7);
		imshow("FrameAfterMedianBlur", frameAfterMedianBlur);
		//C1T2 均值滤波
		Mat framAfterBlur;
		blur(frame, framAfterBlur, Size(7,7), Point(-1, -1));
		imshow("FramAfterBlur", framAfterBlur);
		//C1T3 高斯滤波
		Mat frameAfterGaussinBlur;
		GaussianBlur(frame, frameAfterGaussinBlur, Size(7, 7), 7);
		imshow("frameAfterGaussinBlur&Size(7,7)",frameAfterGaussinBlur);
		waitKey(20);
	}
};

void c5t4() {
	VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened()) {
		cout << "不能打开摄像头或者视频文件" << endl;
		exit(0);
	}
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 540);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 960);
	while (1) {
		Mat frame;
		cap >> frame;
		namedWindow("Frame");
		imshow("Frame", frame);
		//处理
		Mat frameGaussinBlur;
		GaussianBlur(frame, frameGaussinBlur, Size(7, 7), 7);
		Mat frameGray;
		cvtColor(frameGaussinBlur, frameGray, COLOR_BGR2GRAY);
		Mat dx, dy;
		Sobel(frameGray, dx, CV_16SC1, 1, 0, 3);
		Sobel(frameGray, dy, CV_16SC1, 0, 1, 3);

		convertScaleAbs(dx, dx);
		convertScaleAbs(dy, dy);

		imshow("x_grad", dx);
		imshow("y_grad", dy);

		waitKey(0);
	}
}

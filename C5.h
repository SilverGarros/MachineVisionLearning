#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <core.hpp>
using namespace cv;
using namespace std;

//C1T1 ��ȡ����ͷͼ�񲢶�ͼ�������ֵ�˲�
//C1T2 ��ȡ����ͷͼ�񲢶�ͼ����о�ֵ�˲�
//C1T3 ��ȡ����ͷͷ�񲢶�ͼ����и�˹�˲�`GaussianBlur()`
void c5t123();

//C1T4 ��Ե��ȡSobel����
void c5t4();

//C1T5 �򵥵�ĥƤ����


void c5t123() {
	VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened()) {
		cout << "���ܴ�����ͷ������Ƶ�ļ�" << endl;
		exit(0);
	}
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 540);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 960);
	while (1) {
		Mat frame;
		cap >> frame;
		namedWindow("Frame");
		imshow("Frame", frame);
		//C1T1 ��ֵ�˲�
		Mat frameAfterMedianBlur;
		medianBlur(frame, frameAfterMedianBlur,7);
		imshow("FrameAfterMedianBlur", frameAfterMedianBlur);
		//C1T2 ��ֵ�˲�
		Mat framAfterBlur;
		blur(frame, framAfterBlur, Size(7,7), Point(-1, -1));
		imshow("FramAfterBlur", framAfterBlur);
		//C1T3 ��˹�˲�
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
		cout << "���ܴ�����ͷ������Ƶ�ļ�" << endl;
		exit(0);
	}
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 540);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 960);
	while (1) {
		Mat frame;
		cap >> frame;
		namedWindow("Frame");
		imshow("Frame", frame);
		//����
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

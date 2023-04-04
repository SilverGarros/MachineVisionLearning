#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

//Skin Tone DetectionBinarization
void c3t1() {
	VideoCapture cap(0);
	cap.set(CV_CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
	cap.set(CV_CAP_PROP_FPS, 5);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	//VideoCapture cap;
	//cap.open("F://002.png");
	double scale = 0.7;
	//Set Skin TonewithHSV
	double minH = 0;
	double minS = 20;
	double minV = 43;
	double maxH = 255;
	double maxS = 55;
	double maxV = 255;

	/*	Mat frame;
	cap >> frame;
	Size ResImgSize = Size(frame.cols * scale, frame.rows * scale);//Reconstructing image size；
	Mat ResFrame = Mat(ResImgSize, frame.type());
	resize(frame, ResFrame, ResImgSize, INTER_LINEAR);
	Mat HSVMat;
	//Convert raw images to HSV format
	cvtColor(ResFrame, HSVMat, COLOR_RGB2HSV);

	Mat detectMat;
	ResFrame.copyTo(detectMat);

	inRange(HSVMat, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), detectMat);
	imshow("c3t1:Show while HSV in the range(0,20,43)-(255,55,255)", detectMat);
	imshow("c3t1Original image", ResFrame);
	waitKey(0);*/

	while (1) {
		Mat frame;
		bool rSucess = cap.read(frame);
		if (!rSucess) {
			cout << " 不能在视频文件中读取帧，或者视频已经结束" << endl;
			break;
		}
		else {
			cap >> frame;
			Size ResImgSize = Size(frame.cols * scale, frame.rows *scale);//Reconstructing image size；
			Mat ResFrame = Mat(ResImgSize, frame.type());
			resize(frame, ResFrame, ResImgSize, INTER_LINEAR);
			Mat HSVMat;
			//Convert raw images to HSV format
			cvtColor(ResFrame, HSVMat, COLOR_RGB2HSV);

			Mat detectMat;
			ResFrame.copyTo(detectMat);

			inRange(HSVMat, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), detectMat);
			imshow("c3t1:Show while HSV in the range(0,20,43)-(255,55,255)", detectMat);
			imshow("c3t1Original image", ResFrame);
			waitKey(25);
	}
		}

}

void c3t1_() {
	VideoCapture cap;
	cap.open("F://002.png");
	//Set Skin TonewithHSV
	double minH = 0;
	double minS = 20;
	double minV = 43;
	double maxH = 255;
	double maxS = 55;
	double maxV = 255;
	double scale = 0.7;
	Mat frame;
	cap >> frame;
	Size ResImgSize = Size(frame.cols * scale, frame.rows * scale);//Reconstructing image size；
	Mat ResFrame = Mat(ResImgSize, frame.type());
	resize(frame, ResFrame, ResImgSize, INTER_LINEAR);
	Mat HSVMat;
	//Convert raw images to HSV format
	cvtColor(ResFrame, HSVMat, COLOR_RGB2HSV);

	Mat detectMat;
	ResFrame.copyTo(detectMat);

	inRange(HSVMat, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), detectMat);
	imshow("c3t1:Show while HSV in the range(0,20,43)-(255,55,255)", detectMat);
	imshow("c3t1Original image", ResFrame);
	waitKey(0);
}
//GrayscaleImage Binarization using threshold() by OTSU(最大类间方差法/大津法) and adaptivethreshold()(区域自适应二值化)  and ThreshBinaryInv(二进制阈值)
void c3t2() {
	VideoCapture cap;
	cap.open(0);
	//cap.open("F://CAT.MP4");
	double scale = 0.7;
	Mat frame;
	while (1) {
		cap >> frame;
		Size ResImgSize = Size(frame.cols * scale, frame.rows * scale);//Reconstructing image size；
		Mat ResFrame = Mat(ResImgSize, frame.type());
		resize(frame, ResFrame, ResImgSize, INTER_LINEAR);
		Mat GrayFrame;
		cvtColor(ResFrame, GrayFrame, COLOR_RGB2GRAY);
		//Mat deepMat;
		//GrayFrame.copyTo(deepMat);
		Mat AfterThresholdMat;
		Mat AfterAdaptivethresholdMat;
		threshold(GrayFrame, AfterThresholdMat, 25, 255, 8);
		//cout << GrayFrame.channels()<<'\n';
		//waitKey(25);
		adaptiveThreshold(GrayFrame, AfterAdaptivethresholdMat,255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 7,2);
		imshow("c3t2:Image After ThresholdMat", AfterThresholdMat);
		imshow("c3t2:Image After AfterAdaptiveThresholdMat", AfterAdaptivethresholdMat);
		imshow("c3t2:Original image", GrayFrame);
		waitKey(25);
		//waitKey(0);
	}

}

//Slider
//回调函数TrackbarCallback
void ThreshodMat(int th,void*data) {
	string window_name = "binaryMat";
	Mat src = *(Mat*)(data);
	Mat dst;
	threshold(src, dst, th, 255, 0);
	imshow(window_name, dst);
	
}
void c3t3() {
	string window_name = "binaryMat";
	Mat srcMat;
	Mat gryMat;
	int lowTH = 30;//初始化阈值
	int maxTH = 255;//控件的刻度范围
	srcMat = imread("F://01.png");
	if (!srcMat.data) {
		cout << "图片载入失败" << endl;
	}
	cvtColor(srcMat, gryMat, CV_BGR2GRAY);
	imshow(window_name, gryMat);
	createTrackbar("threshold", window_name, &lowTH, maxTH, ThreshodMat, &gryMat);
	waitKey(0);

}
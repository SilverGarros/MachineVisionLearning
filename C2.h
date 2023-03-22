#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include "C1.h"
using namespace cv;
using namespace std;
//   C2T1 ����RGB��ͨ��
void c2t1();
//   C2T2 Opencv��������ͷ
void c2t2();
//   C2T3 Opencv��������
void c2t3();
//   c2t4 Opencv��ͼ��ֱ��ͼ
void c2t4();
void c2t1() {

	Mat imgBlueChannel, imgGreenChannel, imgRedChannel;
	Mat channels[3];
	Mat img, img_R, img_G, img_B;
	img = imread("F://RGB.jpg"/*,CV_LOAD_IMAGE_COLOR*/);
	imshow("c2t1", img);


	std::vector<Mat> channel;
	split(img, channel);
	imgBlueChannel = channel.at(0);
	imgGreenChannel = channel.at(1);
	imgRedChannel = channel.at(2);

	imshow("��ɫͨ��ͼ��", imgBlueChannel);
	imshow("��ɫͨ��ͼ��", imgGreenChannel);
	imshow("��ɫͨ��ͼ��", imgRedChannel);

	split(img, channels);
	img_B = channels[0];
	img_G = channels[1];
	img_R = channels[2];
	imshow("C2T1.02<1>BlueChannels", img_B);
	imshow("C2T1.02<2>GreenChannels", img_G);
	imshow("C2T1.02<3>RedChannels", img_R);

}


void c2t2() {
	VideoCapture cap;
	//cap.open("F://CAT.MP4");
	cap.open(0);

	if (!cap.isOpened()) {
		cout << "���ܴ�����ͷ������Ƶ�ļ�" << endl;
		exit(0);
	}

	cap.set(CV_CAP_PROP_FRAME_WIDTH, 1980);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 1080);
	double fps = cap.get(CAP_PROP_FPS);
	cout << "FPS" << fps << endl;
	while (1) {
		Mat frame;
		bool rSucess = cap.read(frame);
		if (!rSucess) {
			cout << "���ܴ���Ƶ�ļ��ж�ȡ֡" << endl;
			break;

		}
		else
		{
			imshow("frame", frame);

		}
		waitKey(30);
	}


}

void c2t3() {
	Point pt;
	pt.x = 150;
	pt.y = 150;
	Mat background(300, 300, CV_8UC3, CV_RGB(234, 228, 234));
	line(background, Point(0, 150), Point(300, 150), CV_RGB(0, 0, 0), 4);
	imshow("��������", background);

	circle(background, Point(150, 150), 50, CV_RGB(0, 0, 0), 5, 8, 0);
	circle(background, pt, 75, CV_RGB(0, 0, 0), 5, 8, 0);
	imshow("������Բ", background);

	Rect rect;
	rect.x = 75;
	rect.y = 75;
	rect.width = 150;
	rect.height = 150;
	rectangle(background, rect, CV_RGB(255, 0, 0), 2, 8, 0);
	imshow("����������", background);
	//rectangle(background,Point(75,75),150,150,CV_RGB(255,0,0),2,8,0);
}

void c2t4() {
	VideoCapture cap;
	cap.open("F://Cat.mp4");
	double scale = 1;
	while (1)
	{
		Mat SrcImg;
		bool rSucess = cap.read(SrcImg);
		if (!rSucess) {
			cout << " ��������Ƶ�ļ��ж�ȡ֡��������Ƶ�Ѿ�����" << endl;
			break;
		}
		else {
			cap >> SrcImg;
			Size ResImgSiz = Size(SrcImg.cols * scale, SrcImg.rows * scale);//�ع�ͼ���С��
			Mat matSrc = Mat(ResImgSiz, SrcImg.type());
			resize(SrcImg, matSrc, ResImgSiz, INTER_LINEAR);
			Mat matRGB[3];
			split(matSrc, matRGB);
			int Channels[] = { 0 };
			int dims = 1;//����ֱ��ͼ��ά�ȣ�
			int nHistSize[] = { 256 };//ֱ��ͼÿһ��ά�Ȼ��ֵ���������Ŀ������
			float range[] = { 0, 255 };//ȡֵ����
			const float* fHistRanges[] = { range };
			Mat histR, histG, histB;
			// ����ֱ��ͼ
			calcHist(&matRGB[0], 1, Channels, Mat(), histB, 1, nHistSize, fHistRanges, true, false);
			calcHist(&matRGB[1], 1, Channels, Mat(), histG, 1, nHistSize, fHistRanges, true, false);
			calcHist(&matRGB[2], 1, Channels, Mat(), histR, 1, nHistSize, fHistRanges, true, false);
			// ����ֱ��ͼ����
			int nHistWidth = 800;
			int nHistHeight = 600;
			int nBinWidth = cvRound((double)nHistWidth / nHistSize[0]);
			Mat matHistImage(nHistHeight, nHistWidth, CV_8UC3, Scalar(255, 255, 255));
			int scale = 4;
			int hist_height = 256;
			Mat mat_HistImage = Mat::zeros(800, 1200, CV_8UC3);
			//Mat mat_HistImage(nHistHeight, nHistWidth, CV_8UC3, Scalar(255, 255, 255));
			// ֱ��ͼ��һ��
			normalize(histB, histB, 0.0, matHistImage.rows, NORM_MINMAX, -1, Mat());
			normalize(histG, histG, 0.0, matHistImage.rows, NORM_MINMAX, -1, Mat());
			normalize(histR, histR, 0.0, matHistImage.rows, NORM_MINMAX, -1, Mat());
			// ��ֱ��ͼ1�л���ֱ��ͼ
			for (int i = 1; i < nHistSize[0]; i++)
			{
				line(matHistImage,
					Point(nBinWidth * (i - 1), nHistHeight - cvRound(histB.at<float>(i - 1))),
					Point(nBinWidth * (i), nHistHeight - cvRound(histB.at<float>(i))),
					Scalar(255, 0, 0),
					2,
					8,
					0);
				line(matHistImage,
					Point(nBinWidth * (i - 1), nHistHeight - cvRound(histG.at<float>(i - 1))),
					Point(nBinWidth * (i), nHistHeight - cvRound(histG.at<float>(i))),
					Scalar(0, 255, 0),
					2,
					8,
					0);
				line(matHistImage,
					Point(nBinWidth * (i - 1), nHistHeight - cvRound(histR.at<float>(i - 1))),
					Point(nBinWidth * (i), nHistHeight - cvRound(histR.at<float>(i))),
					Scalar(0, 0, 255),
					2,
					8,
					0);
			}
			// ��ֱ��ͼ2�л���ֱ��ͼ
			for (int i = 0; i < nHistSize[0]; i++)
			{
				float bin_val_B = histB.at<float>(i);   //����histԪ�أ�ע��hist����float���ͣ�
				int intensity_B = cvRound(bin_val_B * nHistHeight / SrcImg.cols);  //���Ƹ߶�
				rectangle(mat_HistImage, Point(i * scale, nHistHeight - 1), Point((i + 1) * scale - 1, nHistHeight - intensity_B), Scalar(255, 0, 0));//����ֱ��ͼ
				float bin_val_G = histG.at<float>(i);   //����histԪ�أ�ע��hist����float���ͣ�
				int intensity_G = cvRound(bin_val_G * nHistHeight / SrcImg.cols);  //���Ƹ߶�
				rectangle(mat_HistImage, Point(i * scale, nHistHeight - 1), Point((i + 1) * scale - 1, nHistHeight - intensity_G), Scalar(0, 255, 0));//����ֱ��ͼ
				float bin_val_R = histR.at<float>(i);   //����histԪ�أ�ע��hist����float���ͣ�
				int intensity_R = cvRound(bin_val_R * nHistHeight / SrcImg.cols);  //���Ƹ߶�
				rectangle(mat_HistImage, Point(i * scale, nHistHeight - 1), Point((i + 1) * scale - 1, nHistHeight - intensity_R), Scalar(0, 0, 255));//����ֱ��ͼ
			}
			// ��ʾֱ��ͼ
			imshow("C2T4-frame", matSrc);
			imshow("C2T4-histogram", matHistImage);
			imshow("C2T4-histogram2", mat_HistImage);
			waitKey(0);
		}
	}

}
#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <core.hpp>
using namespace cv;
using namespace std;
void gammaCorrection(cv::Mat& src, cv::Mat& dst, float gamma)
{
    CV_Assert(src.depth() != sizeof(uchar));

    // build a lookup table mapping pixel values [0, 255] to their adjusted gamma values
    unsigned char lut[256];
    for (int i = 0; i < 256; i++)
    {
        lut[i] = (unsigned char)(pow((float)(i / 255.0), gamma) * 255.0f);
    }

    // apply gamma correction using the lookup table
    const int channels = src.channels();
    switch (channels)
    {
    case 1:
        cv::LUT(src, cv::Mat(1, 256, CV_8UC1, lut), dst);
        break;

    case 3:
        cv::LUT(src, cv::Mat(1, 256, CV_8UC1, lut), dst);
        cv::cvtColor(dst, dst, cv::COLOR_BGR2RGB);
        break;

    default:
        CV_Error(cv::Error::StsBadArg, "Incorrect number of channels");
    }
}
/*
void c4t1() {
	Mat img = imread("F:\\Suzhou.jpg",0);
	Mat imgAfter;
    // ����Gamma����
    float gamma = 0.1;
    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.ptr();
    for (int i = 0; i < 256; i++)
    {
        p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);
    }

    // Ӧ��Gamma�任
    Mat img_gamma;
    LUT(img, lookUpTable, img_gamma);

    // ��ʾԭͼ�ͱ任���ͼ��
    imshow("Original Image", img);
    imshow("Gamma Transform", img_gamma);
    waitKey(0);
    //imshow("c4t1_ԭͼ",img);
    //imshow("c4t2_0.1", imgAfter);

}
*/

//ͼ�δ���ѧ�ļ򵥲���
void c4t2() {
    //1.����ͼ����лҶȻ�����
    Mat imgmat = imread("F://Coins.jpg");
    Mat imgGray;
    cvtColor(imgmat,imgGray,COLOR_RGB2GRAY);

    imshow("c4t1:Coins.img", imgGray);

    //2.ͼ���ֵ��
    Mat imgGrayAfterThreshold;
    threshold(imgGray, imgGrayAfterThreshold, 25, 255, 8);

    imshow("c4t1:imgGrayAfterThreshold", imgGrayAfterThreshold);

    //3.ͼ����̬ѧ����
    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(15, 15), Point(-1, -1));
    //3.1 ��ʴErode
    Mat imgAfterErode;
    erode(imgGrayAfterThreshold, imgAfterErode,kernel);
    Mat imgAfterErode2;
    erode(imgGrayAfterThreshold, imgAfterErode2, getStructuringElement(MORPH_ELLIPSE, Size(50, 50), Point(-1, -1)));

    imshow("c4t1:imgAfterErode", imgAfterErode);
    imshow("c4t1:imgAfterErode2", imgAfterErode2);

    //3.2 ����Dilate
    Mat imgAfterDilation;
    dilate(imgGrayAfterThreshold, imgAfterDilation, kernel);

    imshow("C4t1:imgAfterDilation", imgAfterDilation);


    //3.3������Opening(�Ƚ��и�ʴ����Ȼ��������Ͳ�������ϲ���)
    Mat imgAfterOpening;
    morphologyEx(imgGrayAfterThreshold, imgAfterOpening,MORPH_OPEN, kernel);
    imshow("c4t1:imgAfterOpening", imgAfterOpening);
    //3.4������Close
    Mat imgAfterClosing;
    morphologyEx(imgGrayAfterThreshold, imgAfterClosing, MORPH_CLOSE, kernel);
    imshow("c4t1:imgAfterClosing", imgAfterClosing);

}

//��ͨ���ǣ�������ͨ������ı���

void c4t3() {
    //1.����ͼ����лҶȻ�����
    Mat imgmat = imread("F://img/Coins.jpg");
    if (imgmat.empty()) {
        cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;
    }
    else {
        Mat imgGray;
        cvtColor(imgmat, imgGray, COLOR_RGB2GRAY);

        imshow("c4t1:Coins.img", imgGray);

        //2.ͼ���ֵ��
        Mat imgBinary;
        threshold(imgGray, imgBinary, 25, 255, 8);
        Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(15, 15), Point(-1, -1));
        morphologyEx(imgBinary, imgBinary, MORPH_OPEN, kernel);
        imshow("c4t1:imgGrayAfterThreshold", imgBinary);
        //3.������ͨ��
        RNG rng(10086);
        Mat dst, stats, centroids;
        int number = connectedComponentsWithStats(imgBinary, dst, stats, centroids, 8, CV_16U);
        cout << "��ͨ������Ϊ:"<<number << endl;
        cout << "Ӳ������Ϊ�� " << number-1 << endl;
        vector<Vec3b>colors;
        for (int i = 0; i < number; i++) {
            Vec3b vec3 = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
            colors.push_back(vec3);
        }
        for (int i = 0; i < number; i++) {
            //����λ�û�ȡ
            int center_x = centroids.at<double>(i, 0);
            int center_y = centroids.at<double>(i, 1);

            //���ƾ��α߿�
            int x = stats.at<int>(i, CC_STAT_LEFT);
            int y = stats.at<int>(i, CC_STAT_TOP);
            int w = stats.at<int>(i, CC_STAT_WIDTH);
            int h = stats.at<int>(i, CC_STAT_HEIGHT);
            int area = stats.at<int>(i, CC_STAT_AREA);

            //��������λ��
            circle(imgGray, Point(center_x, center_y), 2, Scalar(0, 255, 0), 2, 8, 0);

            //��Ӿ���
            Rect rect(x, y, w, h);
            rectangle(imgGray, rect, colors[i], 1, 8, 0);
            putText(imgGray, format("%d", i), Point(center_x, center_y), FONT_HERSHEY_SCRIPT_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);
            cout << "number" << i << ",area:" << area << endl;
        }
        imshow("ResultIMG", imgGray);

    }
    waitKey(0);
}

//��ͨ���ǲ�����ԭ�����
void c4t4() {
    Mat img = imread("F://img/ConnectedDomainTags.jpg");
    if (img.empty()) {
        cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;
    }
    else {
        Mat imgGray;
        cvtColor(img, imgGray, COLOR_RGB2GRAY);

        imshow("c4t4:ConnectedDomainTags.jpg", imgGray);

        //2.ͼ���ֵ����ͼ����̬ѧ����
        Mat imgBinary;
        //2.2 ʹ��BINARY_INV
        //threshold(imgGray, imgBinary, 25, 255, THRESH_BINARY_INV);

        //2.2 ʹ�ô��ȡ���������ͨ����
        threshold(imgGray, imgBinary, 25, 255, THRESH_OTSU);
        bitwise_not(imgBinary, imgBinary);
        Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(20, 20), Point(-1, -1));
        morphologyEx(imgBinary, imgBinary, MORPH_ERODE, kernel);
        //morphologyEx(imgBinary, imgBinary, MORPH_DILATE, kernel);
        imshow("c4t1:imgGrayAfterThreshold", imgBinary);
        //3.������ͨ��
        RNG rng(10086);
        Mat dst, stats, centroids;
        int number = connectedComponentsWithStats(imgBinary, dst, stats, centroids, 8, CV_16U);
        cout << "��ͨ������Ϊ:" << number << endl;
        cout << "ԭ������Ϊ�� " << number - 1 << endl;
        vector<Vec3b>colors;
        for (int i = 0; i < number; i++) {
            Vec3b vec3 = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
            colors.push_back(vec3);
        }
        for (int i = 0; i < number; i++) {
            //����λ�û�ȡ
            int center_x = centroids.at<double>(i, 0);
            int center_y = centroids.at<double>(i, 1);

            //���ƾ��α߿�
            int x = stats.at<int>(i, CC_STAT_LEFT);
            int y = stats.at<int>(i, CC_STAT_TOP);
            int w = stats.at<int>(i, CC_STAT_WIDTH);
            int h = stats.at<int>(i, CC_STAT_HEIGHT);
            int area = stats.at<int>(i, CC_STAT_AREA);

            //��������λ��
            circle(img, Point(center_x, center_y), 2, Scalar(0, 255, 0), 2, 8, 0);

            //��Ӿ���
            Rect rect(x, y, w, h);
            rectangle(img, rect, colors[i], 1, 8, 0);
            putText(img, format("%d", i), Point(center_x, center_y), FONT_HERSHEY_SCRIPT_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);
            cout << "number" << i << ",area:" << area << endl;
        }
        imshow("ResultIMG", img);

    }
    waitKey(0);
}

// ��Ƕ�ͼ�μ���

void c4t5(){
    Mat img = imread("F://img/MarkerNailCount.jpg");
    if (img.empty()) {
        cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;
    }
    else {
        Mat imgGray;
        cvtColor(img, imgGray, COLOR_RGB2GRAY);

        imshow("c4t1:Coins.img", imgGray);

        //2.ͼ���ֵ��������ͼ����̬ѧ����
        Mat imgBinary;
        //threshold(imgGray, imgBinary, 25, 255, 8);
        threshold(imgGray, imgBinary, 70, 255, THRESH_BINARY_INV);
        //adaptiveThreshold(imgBinary, imgBinary, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV,7,2);
        //bitwise_not(imgBinary, imgBinary);
        imshow("c4t1:imgGrayAfterThreshold", imgBinary);
        Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(15,15), Point(-1, -1));
        //morphologyEx(imgBinary, imgBinary, MORPH_ERODE, getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1)));
        morphologyEx(imgBinary, imgBinary, MORPH_CLOSE, kernel);
        
        imshow("c4t1:imgGrayAfterMorphologyEx", imgBinary);
        //3.������ͨ��
        RNG rng(10086);
        Mat dst, stats, centroids;
        int number = connectedComponentsWithStats(imgBinary, dst, stats, centroids, 8, CV_16U);
        int count = 0;
        cout << "��ͨ������Ϊ:" << number << endl;

        vector<Vec3b>colors;
        for (int i = 0; i < number; i++) {
            Vec3b vec3 = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
            colors.push_back(vec3);
            //����λ�û�ȡ
            int center_x = centroids.at<double>(i, 0);
            int center_y = centroids.at<double>(i, 1);

            //���ƾ��α߿�
            int x = stats.at<int>(i, CC_STAT_LEFT);
            int y = stats.at<int>(i, CC_STAT_TOP);
            int w = stats.at<int>(i, CC_STAT_WIDTH);
            int h = stats.at<int>(i, CC_STAT_HEIGHT);
            int area = stats.at<int>(i, CC_STAT_AREA);
            
            cout << "number" << i << ",area:" << area << endl;
            /*�����۲��������������1900С��3000�������Ϸ�������С��400*/
            if(area > 1900&&area<3000) {
                count ++;
                //��������λ��
                circle(imgGray, Point(center_x, center_y), 2, Scalar(0, 255, 0), 2, 8, 0);
                // ��Ӿ���
                Rect rect(x, y, w, h);
                rectangle(imgGray, rect, colors[i], 1, 8, 0);
                putText(imgGray, format("%d", count), Point(center_x, center_y), FONT_HERSHEY_SCRIPT_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);
                waitKey(20);
            }
            
        }
        cout << "����������Ϊ�� " << count  << endl;
        imshow("ResultIMG", imgGray);

    }
    waitKey(0);
}
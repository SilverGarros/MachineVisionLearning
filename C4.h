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
    // 构建Gamma函数
    float gamma = 0.1;
    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.ptr();
    for (int i = 0; i < 256; i++)
    {
        p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);
    }

    // 应用Gamma变换
    Mat img_gamma;
    LUT(img, lookUpTable, img_gamma);

    // 显示原图和变换后的图像
    imshow("Original Image", img);
    imshow("Gamma Transform", img_gamma);
    waitKey(0);
    //imshow("c4t1_原图",img);
    //imshow("c4t2_0.1", imgAfter);

}
*/

//图形处理学的简单操作
void c4t2() {
    //1.载入图像进行灰度化处理
    Mat imgmat = imread("F://Coins.jpg");
    Mat imgGray;
    cvtColor(imgmat,imgGray,COLOR_RGB2GRAY);

    imshow("c4t1:Coins.img", imgGray);

    //2.图像二值化
    Mat imgGrayAfterThreshold;
    threshold(imgGray, imgGrayAfterThreshold, 25, 255, 8);

    imshow("c4t1:imgGrayAfterThreshold", imgGrayAfterThreshold);

    //3.图像形态学处理
    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(15, 15), Point(-1, -1));
    //3.1 腐蚀Erode
    Mat imgAfterErode;
    erode(imgGrayAfterThreshold, imgAfterErode,kernel);
    Mat imgAfterErode2;
    erode(imgGrayAfterThreshold, imgAfterErode2, getStructuringElement(MORPH_ELLIPSE, Size(50, 50), Point(-1, -1)));

    imshow("c4t1:imgAfterErode", imgAfterErode);
    imshow("c4t1:imgAfterErode2", imgAfterErode2);

    //3.2 膨胀Dilate
    Mat imgAfterDilation;
    dilate(imgGrayAfterThreshold, imgAfterDilation, kernel);

    imshow("C4t1:imgAfterDilation", imgAfterDilation);


    //3.3开运算Opening(先进行腐蚀操作然后进行膨胀操作的组合操作)
    Mat imgAfterOpening;
    morphologyEx(imgGrayAfterThreshold, imgAfterOpening,MORPH_OPEN, kernel);
    imshow("c4t1:imgAfterOpening", imgAfterOpening);
    //3.4闭运算Close
    Mat imgAfterClosing;
    morphologyEx(imgGrayAfterThreshold, imgAfterClosing, MORPH_CLOSE, kernel);
    imshow("c4t1:imgAfterClosing", imgAfterClosing);

}

//连通域标记，绘制连通域外接四边形

void c4t3() {
    //1.载入图像进行灰度化处理
    Mat imgmat = imread("F://img/Coins.jpg");
    if (imgmat.empty()) {
        cout << "请确认图像文件名称是否正确" << endl;
    }
    else {
        Mat imgGray;
        cvtColor(imgmat, imgGray, COLOR_RGB2GRAY);

        imshow("c4t1:Coins.img", imgGray);

        //2.图像二值化
        Mat imgBinary;
        threshold(imgGray, imgBinary, 25, 255, 8);
        Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(15, 15), Point(-1, -1));
        morphologyEx(imgBinary, imgBinary, MORPH_OPEN, kernel);
        imshow("c4t1:imgGrayAfterThreshold", imgBinary);
        //3.计算连通域
        RNG rng(10086);
        Mat dst, stats, centroids;
        int number = connectedComponentsWithStats(imgBinary, dst, stats, centroids, 8, CV_16U);
        cout << "连通域数量为:"<<number << endl;
        cout << "硬币数量为： " << number-1 << endl;
        vector<Vec3b>colors;
        for (int i = 0; i < number; i++) {
            Vec3b vec3 = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
            colors.push_back(vec3);
        }
        for (int i = 0; i < number; i++) {
            //中心位置获取
            int center_x = centroids.at<double>(i, 0);
            int center_y = centroids.at<double>(i, 1);

            //绘制矩形边框
            int x = stats.at<int>(i, CC_STAT_LEFT);
            int y = stats.at<int>(i, CC_STAT_TOP);
            int w = stats.at<int>(i, CC_STAT_WIDTH);
            int h = stats.at<int>(i, CC_STAT_HEIGHT);
            int area = stats.at<int>(i, CC_STAT_AREA);

            //绘制中心位置
            circle(imgGray, Point(center_x, center_y), 2, Scalar(0, 255, 0), 2, 8, 0);

            //外接矩形
            Rect rect(x, y, w, h);
            rectangle(imgGray, rect, colors[i], 1, 8, 0);
            putText(imgGray, format("%d", i), Point(center_x, center_y), FONT_HERSHEY_SCRIPT_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);
            cout << "number" << i << ",area:" << area << endl;
        }
        imshow("ResultIMG", imgGray);

    }
    waitKey(0);
}

//连通域标记并计算原点个数
void c4t4() {
    Mat img = imread("F://img/ConnectedDomainTags.jpg");
    if (img.empty()) {
        cout << "请确认图像文件名称是否正确" << endl;
    }
    else {
        Mat imgGray;
        cvtColor(img, imgGray, COLOR_RGB2GRAY);

        imshow("c4t4:ConnectedDomainTags.jpg", imgGray);

        //2.图像二值化及图像形态学处理
        Mat imgBinary;
        //2.2 使用BINARY_INV
        //threshold(imgGray, imgBinary, 25, 255, THRESH_BINARY_INV);

        //2.2 使用大津法取反后进行连通域标记
        threshold(imgGray, imgBinary, 25, 255, THRESH_OTSU);
        bitwise_not(imgBinary, imgBinary);
        Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(20, 20), Point(-1, -1));
        morphologyEx(imgBinary, imgBinary, MORPH_ERODE, kernel);
        //morphologyEx(imgBinary, imgBinary, MORPH_DILATE, kernel);
        imshow("c4t1:imgGrayAfterThreshold", imgBinary);
        //3.计算连通域
        RNG rng(10086);
        Mat dst, stats, centroids;
        int number = connectedComponentsWithStats(imgBinary, dst, stats, centroids, 8, CV_16U);
        cout << "连通域数量为:" << number << endl;
        cout << "原点数量为： " << number - 1 << endl;
        vector<Vec3b>colors;
        for (int i = 0; i < number; i++) {
            Vec3b vec3 = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
            colors.push_back(vec3);
        }
        for (int i = 0; i < number; i++) {
            //中心位置获取
            int center_x = centroids.at<double>(i, 0);
            int center_y = centroids.at<double>(i, 1);

            //绘制矩形边框
            int x = stats.at<int>(i, CC_STAT_LEFT);
            int y = stats.at<int>(i, CC_STAT_TOP);
            int w = stats.at<int>(i, CC_STAT_WIDTH);
            int h = stats.at<int>(i, CC_STAT_HEIGHT);
            int area = stats.at<int>(i, CC_STAT_AREA);

            //绘制中心位置
            circle(img, Point(center_x, center_y), 2, Scalar(0, 255, 0), 2, 8, 0);

            //外接矩形
            Rect rect(x, y, w, h);
            rectangle(img, rect, colors[i], 1, 8, 0);
            putText(img, format("%d", i), Point(center_x, center_y), FONT_HERSHEY_SCRIPT_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);
            cout << "number" << i << ",area:" << area << endl;
        }
        imshow("ResultIMG", img);

    }
    waitKey(0);
}

// 标记钉图形计数

void c4t5(){
    Mat img = imread("F://img/MarkerNailCount.jpg");
    if (img.empty()) {
        cout << "请确认图像文件名称是否正确" << endl;
    }
    else {
        Mat imgGray;
        cvtColor(img, imgGray, COLOR_RGB2GRAY);

        imshow("c4t1:Coins.img", imgGray);

        //2.图像二值化并进行图像形态学处理；
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
        //3.计算连通域
        RNG rng(10086);
        Mat dst, stats, centroids;
        int number = connectedComponentsWithStats(imgBinary, dst, stats, centroids, 8, CV_16U);
        int count = 0;
        cout << "连通域数量为:" << number << endl;

        vector<Vec3b>colors;
        for (int i = 0; i < number; i++) {
            Vec3b vec3 = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
            colors.push_back(vec3);
            //中心位置获取
            int center_x = centroids.at<double>(i, 0);
            int center_y = centroids.at<double>(i, 1);

            //绘制矩形边框
            int x = stats.at<int>(i, CC_STAT_LEFT);
            int y = stats.at<int>(i, CC_STAT_TOP);
            int w = stats.at<int>(i, CC_STAT_WIDTH);
            int h = stats.at<int>(i, CC_STAT_HEIGHT);
            int area = stats.at<int>(i, CC_STAT_AREA);
            
            cout << "number" << i << ",area:" << area << endl;
            /*经过观察曲别针面积大于1900小于3000，而左上方噪点面积小于400*/
            if(area > 1900&&area<3000) {
                count ++;
                //绘制中心位置
                circle(imgGray, Point(center_x, center_y), 2, Scalar(0, 255, 0), 2, 8, 0);
                // 外接矩形
                Rect rect(x, y, w, h);
                rectangle(imgGray, rect, colors[i], 1, 8, 0);
                putText(imgGray, format("%d", count), Point(center_x, center_y), FONT_HERSHEY_SCRIPT_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);
                waitKey(20);
            }
            
        }
        cout << "曲别针数量为： " << count  << endl;
        imshow("ResultIMG", imgGray);

    }
    waitKey(0);
}
//
//  L02_Basic.cpp
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/7/29.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "../util/utils.cpp"

using namespace std;
using namespace cv;

void ch02_basic() {
    // $$ Load image
    Mat image = imread("res/lenna.png");
    
    // $$ Show image information
    // $ Mat.depth() - data type of each channels
    //   CV_8U=0, CV_8S=1, CV_16U=2, CV_16S=3, CV_32S=4, CV_32F=5, CV_64F=6
    // $ Mat.channels() - # of channels (3 for color, 1 for gray)
    Size s = image.size();
    cout << "Load image with height: " << s.height
         << ", width: " << s.width
         << ", channels: " << image.channels()
         << endl;
    MatType(image);
    
    // $$ Convert to gray scale
    Mat gray(s, CV_8U);
    cvtColor(image, gray, CV_BGR2GRAY);
    
    // $$ Show gray image information
    cout << "Gray scale image with height: " << gray.size().height
         << ", width: " << gray.size().width
         << ", channels: " << gray.channels()
         << endl;
    MatType(gray);
    
    vector<Mat> shows = { image, gray };
    ShowManyImages("Convert to Gray", shows);
    
    // $$ Save gray image
    imwrite("out/lenna_gray.png", gray);
    
    // $$ Split image into three color channels
    Mat black = Mat::zeros(s, CV_8U);
    vector<Mat> rgb_channels;
    split(image, rgb_channels);
    Mat B, G, R;
    vector<Mat> b_channels = { rgb_channels[0], black, black };
    vector<Mat> g_channels = { black, rgb_channels[1], black };
    vector<Mat> r_channels = { black, black, rgb_channels[2] };
    merge(b_channels, B);
    merge(g_channels, G);
    merge(r_channels, R);
    vector<Mat> show_colors = { image, B, G, R };
    ShowManyImages("BGR Color Channels", show_colors);
    
    // $$ Split image into HSV channels
    Mat hsv = Mat(s, CV_8UC3);
    cvtColor(image, hsv, CV_BGR2HSV);
    
    vector<Mat> hsv_channels;
    split(hsv, hsv_channels);
    
    double h_min, h_max, s_min, s_max, v_min, v_max;
    minMaxLoc(hsv_channels[0], &h_min, &h_max); // In openCV, this range of Hue is 0 ~ 179 (8bit)
    minMaxLoc(hsv_channels[1], &s_min, &s_max);
    minMaxLoc(hsv_channels[2], &v_min, &v_max);
    cout << "Hue: [" << h_min << ", " << h_max << "], "
         << "Saturation: [" << s_min << ", " << s_max << "], "
         << "Value: [" << v_min << ", " << v_max << "]" << endl;
    
    vector<Mat> show_hsv = { image, hsv_channels[0], hsv_channels[1], hsv_channels[2] };
    ShowManyImages("HSV Color Channels", show_hsv);
    
    
    destroyAllWindows();
}

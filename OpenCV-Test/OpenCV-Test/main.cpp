//
//  main.cpp
//  OpenCV-Test
//
//  Created by Adithya Bellathur on 2/11/17.
//  Copyright © 2017 Adithya Bellathur. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

//for a banana in good lighting//
//const int H_MIN = 10;
//const int S_MIN = 100;
//const int V_MIN = 0;
//
//const int H_MAX = 25;
//const int S_MAX = 255;
//const int V_MAX = 255;
//////////////////////


//for a green folder//
const int H_MIN = 40;
const int S_MIN = 80;
const int V_MIN = 0;

const int H_MAX = 70;
const int S_MAX = 255;
const int V_MAX = 255;
//////////////////////


const int FRAME_WIDTH = 1280;
const int FRAME_HEIGHT = 720;


Mat erodeDilate(Mat inMat);
string intToString(int number);
void drawObject(int x, int y,Mat &frame);

int main(){
    
    VideoCapture cap(0);
    
    if(!cap.isOpened()){
        cout << "Webcam is not opened" << endl;
    }
    
    while(true){
        
        cout << WINDOW_NORMAL << endl;
        
        Mat Webcam;
        Mat HSVimage;
        Mat filteredImage;
        Mat justBanana;
        
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        int x = 0;
        int y = 0;
        
        cap.read(Webcam);
        //convert to HSV
        cvtColor(Webcam, HSVimage, CV_BGR2HSV);
        
        //filter HSV range
        inRange(HSVimage, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), filteredImage);
        
        //erode and dilate image
        justBanana = erodeDilate(filteredImage);
        
        //find Contours of large image
        findContours(justBanana, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
        if (hierarchy.size() > 0) {
            double numObjects = hierarchy.size();
            
            bool objectFound = false;
            double refArea = 0;
            
            if(numObjects<20){
                for (int i = 0; i >= 0; i = hierarchy[i][0]) {
                    Moments moment = moments((Mat)contours[i]);
                    double area = moment.m00;
                    if(area>400 && area<FRAME_HEIGHT*FRAME_WIDTH && area>refArea){
                        x = moment.m10/area;
                        y = moment.m01/area;
                        objectFound = true;
                        refArea = area;
                    }
                    else{
                        objectFound = false;
                    }
                }
                if(objectFound ==true){
                    putText(Webcam,"Tracking Object",Point(0,50),2,1,Scalar(255,255,255),2);
                    //draw object location on screen
                    drawObject(x,y,Webcam);
                }
            }
            else{
                    putText(Webcam,"TOO MUCH NOISE",Point(0,50),1,2,Scalar(0,0,255),2);
            }
        }
        
        
        namedWindow("Webcam", WINDOW_NORMAL);
        imshow("Webcam", Webcam);
        namedWindow("HSV", WINDOW_NORMAL);
        imshow("HSV", HSVimage);
        namedWindow("FilteredImage",WINDOW_NORMAL);
        imshow("FilteredImage", filteredImage);
        namedWindow("justBanana",WINDOW_NORMAL);
        imshow("justBanana", justBanana);
        waitKey(5);
    }
    return 0;
}


Mat erodeDilate(Mat inMat){
    Mat outMat;
    
    Mat erodeElement = getStructuringElement(MORPH_RECT, Size(7,7));
    Mat erodeElementFine = getStructuringElement(MORPH_RECT, Size(3,3));
    Mat dilateElement = getStructuringElement(MORPH_RECT, Size(7,7));
    
    
    erode(inMat, outMat, erodeElement);
    erode(outMat, outMat, erodeElementFine);
    erode(outMat, outMat, erodeElementFine);
//    erode(outMat, outMat, erodeElementFine);
//    erode(outMat, outMat, erodeElementFine);
    
    dilate(outMat, outMat, dilateElement);
    dilate(outMat, outMat, dilateElement);
    dilate(outMat, outMat, dilateElement);
//    dilate(outMat, outMat, dilateElement);
    
    return outMat;
}

string intToString(int number){
    stringstream ss;
    ss << number;
    return ss.str();
}

void drawObject(int x, int y,Mat &frame){
    circle(frame,Point(x,y),80,Scalar(255,255,255),3);
    putText(frame,"("+intToString(x)+","+intToString(y)+")",Point(x-68,y+9),1,1.75,Scalar(255,255,255),4);
    
}


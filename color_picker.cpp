#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

Mat imgHSV,mask;
int hmin=0,smin=0,vmin=0;
int hmax=179,smax=255,vmax=255;
VideoCapture cap(0);
Mat img;
int main()
{
    /*string path="Lena.png";
    Mat img=imread(path);*/
    
    namedWindow("TrackBars",(640,200));
    createTrackbar("Hue min","TrackBars",&hmin,179);
    createTrackbar("Hue max","TrackBars",&hmax,179);
    createTrackbar("Sat min","TrackBars",&smin,255);
    createTrackbar("Sat max","TrackBars",&smax,255);
    createTrackbar("Val mim","TrackBars",&vmin,255);
    createTrackbar("Val Max","TrackBars",&vmax,255);
    while(true){
    cap.read(img);
    cvtColor(img,imgHSV,COLOR_BGR2HSV);
    Scalar lower(hmin,smin,vmin);
    Scalar upper(hmax,smax,vmax);
    inRange(imgHSV,lower,upper,mask);
    cout<<hmin<<","<<smin<<","<<vmin<<","<<hmax<<","<<smax<<","<<vmax<<endl;
    imshow("Image",img);
    //imshow("Image HSV",imgHSV);
    imshow("Image Mask",mask);
    waitKey(1);
    }
    return 0;
}
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
    string path="Lena.png";
    Mat img = imread(path);
    Mat imgResize,imgCrop;
    //cout<<img.size()<<endl;
    resize(img,imgResize,Size(250,250));
    Rect roi(100,100,300,250);
    imgCrop=img(roi);
    imshow("Image",img);
    imshow("Image Resize",imgResize);
    imshow("Image Crop",imgCrop);
    waitKey(0);
    return 0;
}
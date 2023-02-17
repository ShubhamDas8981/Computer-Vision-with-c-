#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

float w=250,h=350;
Mat matrix,imgWarp;

int main()
{
    string path="Lena.png";
    Mat img=imread(path);

    Point2f src[4]={{92,74},{400,372},{364,47},{404,401}};
    Point2f dst[4]={{0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h}};

    matrix=getPerspectiveTransform(src,dst);
    warpPerspective(img,imgWarp,matrix,Point(w,h));
    for (int i = 0; i < 4; i++)
    {
        circle(img,src[i],10,Scalar(0,0,255),FILLED);
    }
    
    imshow("Image",img);
    imshow("Image Wrap",imgWarp);
    waitKey(0);
    return 0;
}
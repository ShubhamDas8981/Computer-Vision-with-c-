#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

Mat imgGray,imgBlur,imgCanny,imgDia;

void getcontours(Mat imgDia, Mat img)
{
    /*{{Point(20,30),Point(50,60)},
    {},
    {}}*/
    vector<vector<Point>> contours;
    vector<Vec4i>hierarchy;
    findContours(imgDia,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
    //drawContours(img,contours,-1,Scalar(255,0,255),2);

    //variations
    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());
    string objType;
    for (int i = 0; i < contours.size(); i++)
    {
        int area=contourArea(contours[i]);
        cout<<area<<endl;
        
        if(area>2000)
        {
            float peri=arcLength(contours[i],true);
            approxPolyDP(contours[i],conPoly[i],0.02*peri,true);
            
            cout<<conPoly[i].size()<<endl;
            boundRect[i]=boundingRect(conPoly[i]);
            
            int objCor=(int) conPoly[i].size();

            if(objCor==3){objType="Triangle";}
            else if (objCor==4){
                float aspRatio= (float)boundRect[i].width/(float)boundRect[i].height;
                cout<<aspRatio<<endl;
                if(aspRatio>0.95 && aspRatio<1.05){objType="Sqare";}
                else {objType="Rectangle";}
                }
            else if (objCor>4) {objType="Circle";}
            drawContours(img,conPoly,i,Scalar(255,0,255),2);
            rectangle(img,boundRect[i].tl(),boundRect[i].br(),Scalar(0,255,0),5);
            putText(img,objType,{boundRect[i].x,boundRect[i].y-5},FONT_HERSHEY_DUPLEX,0.25,Scalar(0,69,255),2);
        }
    }
    
} 
int main()
{
    string path="shapes.png";
    Mat img=imread(path);
    //Pre-processing
    Mat kernel=getStructuringElement(MORPH_RECT,Size(5,5));
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray,imgBlur,Size(7,7),5,0);
    Canny(imgBlur,imgCanny,25,75);
    dilate(imgCanny,imgDia,kernel);

    getcontours(imgDia,img);

    imshow("Image",img);
    /*imshow("Image Gray",imgGray);
    imshow("Image Blur",imgBlur);
    imshow("Image Canny",imgCanny);
    imshow("Image Dil",imgDia);*/
    waitKey(0);
    return 0;
}
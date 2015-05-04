#include <ros/ros.h>
#define PI 3.1414

/*
bool Buoy::detectBuoy()
{
    if(!_image.empty())
    {
        Mat org,_finalImg, gray, edges,dst, org1;
        _finalImg = obj.run(_image,1,0);
//        imshow("max edge",obj.run(_image,1,0));
//        cvtColor(_finalImg, _imageHSV, CV_BGR2HSV);
//        Mat gray,dst;
        cvtColor(_finalImg,gray,CV_BGR2GRAY);
        adaptiveThreshold(gray,org,100,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,13,0);

//        fastNlMeansDenoising(org,dst,3,7,21 );
//        fastNlMeansDenoising(org, dst);
//        imshow("denoised ", dst);
//        inRange(_imageHSV,_lowerThreshYellow,_upperThreshYellow, org);
        // inRange(_imageHSV,_lowerThreshGreen,_upperThreshGreen, _imageBWGreen);

         imshow("org", org);

        Mat org2, erodeimg;
//        medianBlur(org, _imageBW, 3);

        erode(org, erodeimg, _kernelDilateErode);
        erode(erodeimg, erodeimg, _kernelDilateErode);
        imshow("erode", erodeimg);
        dilate(erodeimg, org2, _kernelDilateErode);
//        dilate(org2, org2, _kernelDilateErode);
        Canny(org2,edges,0,100);
//        imshow("eroded image", edges);
        imshow("dilated ", org2);
        imshow("canny", edges);
        waitKey(33);
        CBlobResult _blobs,_blobsClutter;
        CBlob * _currentBlob;
        IplImage _imageBWipl = org2;
        _blobs = CBlobResult(&_imageBWipl, NULL, 0);
        _blobs.Filter(_blobs, B_INCLUDE, CBlobGetArea(), B_INSIDE, 200, 5000);

//         _imageBW = Scalar(0, 0, 0);
        org2 = Scalar(0, 0, 0);

        cout << "number of blobs " << _blobs.GetNumBlobs() << endl;

        for(int i = 0; i < _blobs.GetNumBlobs(); i++)
        {
            _currentBlob = _blobs.GetBlob(i);
            _currentBlob->FillBlob(&_imageBWipl, Scalar(255));
        }

        Mat newimg;
//        Mat _imageBW2 = _imageBW.clone();
        Mat _imageBW2 = org2.clone();
        dilate(_imageBW2, newimg, _kernelDilateErode);
        imshow("newimg", newimg);
        Mat src;
        vector<Mat> channels;
        channels.push_back(org2);
        channels.push_back(org2);
        channels.push_back(org2);
        merge( channels, src);

        _contours.clear();
//        medianBlur(_imageBW2, _imageBW2, 5);
        imshow("imageBW2", _imageBW2);
        findContours(_imageBW2, _contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

        Point2f _centerBuff;
        float _radiusBuff;
        vector<Point> _contoursPolyBuff;
        _center.clear();
        _radius.clear();
        _contoursPoly.clear();

        _imageBW = Scalar(0, 0, 0);

        for(int i=0; i < _contours.size(); i++)
        {
            if(contourArea(_contours[i])>50)
            {
                approxPolyDP(_contours[i],_contoursPolyBuff,3,true);
                minEnclosingCircle((Mat)_contoursPolyBuff,_centerBuff,_radiusBuff);
                circle(_imageBW,_centerBuff,_radiusBuff,Scalar(255), -1);
                _center.push_back(_centerBuff);
                _radius.push_back(_radiusBuff);
                _contoursPoly.push_back(_contoursPolyBuff);
            }
        }

        Mat src_gray;
        cvtColor( src, src_gray, CV_BGR2GRAY );
        src = Scalar(0, 0, 0);

        GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );
        imshow("src_gray", src_gray);

        /// Apply the Hough Transform to find the circles
        HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, 80, 180, 25, 30, 300 );

        //       /// Draw the circles detected
        if(circles.size() == 0){
            cout<<"NOTHING CIRCULAR" << endl;
            return false;
        }





        for( size_t i = 0; i < circles.size(); i++ )
        {
            cout << "circle wala for loop " << endl;
            cout << "circle area = " << endl;
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            _fcenter.push_back(center);
            _fradius.push_back(cvRound(circles[i][2]));
            // circle center
            circle( src, center, 3, Scalar(0, 255, 0), 3, 8, 0 );
            // circle outline
            circle( src, center, radius, Scalar(0, 0, 255), 1, 8, 0 );
        }

        
        for (int i = 0; i < _fradius.size(); ++i)
        {
            if(_fradius[i] > max){
                index = i;
                max = _fradius[i];
            }
        }
        cout << "<<<<<<<<<<     largest radius = " << max << "          >>>>>>>>>>>>>>>"<<endl;
        if(max == 0){
            cout << "max  = 0" << endl;
            return false;
        }
        else{
            circle(src,_fcenter[index],3,Scalar(255,255,0),1,8,0);
            circle(src,_fcenter[index], max,Scalar(0,255,0),1,8,0);
//            return true;
        }
        cout << "show src image" << endl;
        imshow("src", src);

        _fcenter.clear();
        _fradius.clear();
//        if(_center.size() > 0){
//            cout << "center size > 0 " << endl;
//            return true;
//        }
//        else{
//            cout << "returns false" << endl;
//            return false;
//        }

        return true;
    }
    else{
        cout << "no image loaded.." << endl;
        return false;
    }


    waitKey(33);
    return 0;
}
*/
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges;
    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, CV_BGR2GRAY);
        imshow("edges", edges);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}

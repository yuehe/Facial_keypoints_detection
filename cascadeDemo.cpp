/*
 * File:   cascadeDemo.cpp
 * Author: Yue HE & Ephrem Berhe
 *
 * Created on 4 Nov 2015
 *
 * Simple example on the usage of
 * OpenCV's cascade classifiers
 *
 */

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <opencv2/ml/ml.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <ctime>
#include <cmath>
#include <sstream>
#include <ctime>
#include "cv.h"
#include "highgui.h"
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include <iomanip>
#include <locale>
#include <sstream>


using namespace cv;



//apply multi-scale detection
Rect cascadeDetection(Mat image, CascadeClassifier detector, int &n_det) {
	std::vector<Rect> rois;
	int max_area=0, max_roi=0;

	//histogram equalization
	equalizeHist(image, image);

	//object detection
	detector.detectMultiScale(image, rois);
	n_det = (int)rois.size();


	//if more than one object is detected
	//select the bigger one
	if (n_det > 0) {
		for (int i=0; i < n_det; ++i) {
			Rect r = rois[i];
			int a = r.width*r.height;

			if (a > max_area) {
				max_area = a;
				max_roi = i;
			}
		}

		return rois[max_roi];

	} else {
		return Rect(0, 0, 0, 0);
	}

}


//main
int main (int argc, char** argv) {


const char *cascade_name[5]={
			     "haar/eye.xml",
			     "haar/nose.xml",
			     "haar/mouth.xml",


 			      };
//const char *cascade_name[1]={"haar/mouth.xml",};


	CascadeClassifier detector;	//cascade detector
	string cascadeFile;
	Mat img, img_g;
	int n_det;
	Rect roi;

for(int f=0;f<12;f++){
		for(int i=0;i<3;i++)
		{

if ( not detector.load(cascade_name[i]) ) {
		std::cerr << "Cannot load cascade file: " << cascadeFile << std::endl;
		return(-1);
	}






            //read image from file
            char Source[100];

    sprintf(Source,"images\\%d.jpg",f);
	img = imread(Source);

	if (not img.data) {
        std::cerr << "Failed to load: " << argv[1] << std::endl;
        return -1;
	}

	if (img.channels() > 1) {
        cvtColor(img, img_g, CV_BGR2GRAY);
	} else {
        img.copyTo(img_g);
	}
// Call the function to detect and draw the face
            roi = cascadeDetection(img_g, detector, n_det);


//if object is detected
//if(i==1){
//
//    Point centers = Point((roi.x + roi.width)/2, (roi.y + roi.height)/2);
//   int r=(roi.width+roi.height)*0.2;
//    circle(img,centers,r,Scalar(255,0,0),1,4,0);
//}
 if (n_det) {
if(i==1){
    //draw noise

        Point center( roi.x + roi.width*0.5, roi.y + roi.height*0.5 );
        int radius = cvRound( (roi.width + roi.height)*0.15 );
        circle( img, center, radius, Scalar( 0, 255, 0 ), 1, 4, 0 );
} else


        //draw a rectangle around the object
		rectangle(img, roi, Scalar(0,0,255));
    }


  // cvCircle(img, centers, 3);
	//imshow("cascadeDemo", img);

	imwrite(Source,img);

    std::cerr <<((double)(i+1)/5)<<"(5)"<<f<<(double)((f+1)/11)*100<<"%"<<std::endl;
    std::cout<<"Working ... ";




		} // for all CascadeClassifier
		 char path[100];
    if (sizeof(roi)!=0){
    sprintf(path,"cascadeDemo\\%d.jpg",f);
	imwrite(path,img);}
}// for all files

 printf("Done!");


    //detection

	waitKey();

	return 0;
}

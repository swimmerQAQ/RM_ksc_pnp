#include "hsv_color_pre.hpp"
#include <opencv2/opencv.hpp>
 using namespace cv;
 #include <iostream>
 using namespace std;

extern int hmin;
extern int hmax;
extern int smin;
extern int smax;
extern int vmin;
extern int vmax;

void hsv_color_pre(void)
{
    cout << " origin_set " << endl;
    cout << "hmin="<<hmin;
 	cout << " hmax="<<hmax<<endl;
    cout << "smin="<<smin;
	cout << " smax="<<smax<<endl;
 	cout << "vmin="<<vmin;
 	cout << " vmax="<<vmax<<endl;
    namedWindow("Trackbars",1);
 	createTrackbar("Hue min ","Trackbars",&hmin,255);
	createTrackbar("Hue max ","Trackbars",&hmax,255);
	createTrackbar("sue min ","Trackbars",&smin,255);
	createTrackbar("sue max ","Trackbars",&smax,255);
	createTrackbar("vue min ","Trackbars",&vmin,255);
	createTrackbar("vue max ","Trackbars",&vmax,255);
}
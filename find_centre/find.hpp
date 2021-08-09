
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int findCentre(Mat in_img, vector<vector<Point>> contours, vector<Vec4i> hierarchy, vector<vector<Point>> & conPoly, int* & radius);
Point2f centrePoint(vector<Point> in_contours);
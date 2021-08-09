#include "find.hpp"
#include <opencv2/opencv.hpp>
using namespace cv;
#include <iostream>
using namespace std;

//寻找中点
int findCentre(Mat in_img, vector<vector<Point>> contours, vector<Vec4i> hierarchy, vector<vector<Point>> & conPoly, int* & radius)
{
    //遍历每个图形
	for (int i = 0; i < contours.size(); i++)
	{
		conPoly[i] = contours[i];
        //遍历每个图形所有的点
		for (int j = 0; j < contours[i].size(); j++)
		{
            //取最值
			if (conPoly[i][0].y >= contours[i][j].y) //min_up
			{
				conPoly[i][0].y = contours[i][j].y;
				conPoly[i][0].x = contours[i][j].x;
			}
			if (conPoly[i][1].y < contours[i][j].y) //max_down
			{
				conPoly[i][1].y = contours[i][j].y;
				conPoly[i][1].x = contours[i][j].x;
			}
		}
		cout << " the y_max is " << conPoly[i][0].y << " the y_min is " << conPoly[i][1].y << endl;
		//rectangle(img, conPoly[i][0], conPoly[i][1], Scalar(100, 255, 50),1);
		
		//中点的值暂时存在第3个点
		radius[i] = (conPoly[i][1].y - conPoly[i][0].y) / 2;
		conPoly[i][2].y = (conPoly[i][0].y + conPoly[i][1].y) / 2;
		conPoly[i][2].x = (conPoly[i][0].x + conPoly[i][1].x) / 2;
        
    }return 1;
}
Point2f centrePoint(vector<Point> in_contours)
{
	vector<Point> contours_Bulf;
	contours_Bulf = in_contours;
	Point2f centre;
	Moments contours_moments;
	contours_moments = moments(contours_Bulf);
	centre = Point(static_cast<float> (contours_moments.m10/contours_moments.m00),static_cast<float> (contours_moments.m01/contours_moments.m00));
	
	return centre;
}
#include <opencv2/opencv.hpp>
 using namespace cv;
 #include <iostream>
 using namespace std;
 class contoursSelect
{
    private:
    vector<Vec4i> hierarchy;
    vector<vector<Point>> contours;
    Mat origin;
    int nex =-2;
    int pre =-2;
    int son =-2;
    int dad =-2;
    Mat image;
    public:
    contoursSelect(Mat in_origin,Mat in_img,vector<vector<Point>> in_contours,vector<Vec4i> in_hierarchy);
    ~contoursSelect();
    vector<vector<Point>> selectContours(int inex,int ipre,int ison, int idad);
    void anti_selectContours(int inex,int ipre,int ison, int idad);
};
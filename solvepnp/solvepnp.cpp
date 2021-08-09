#include "solvepnp.hpp"

vector<Point3f> refer_obj_Point3;
//校准三维坐标
vector<Point2f> refer_2D_imagePoint2f;
//对应的二维点
 double cameraD[3][3] = {{1.2853517927598091e+03, 0., 3.1944768628958542e+02,},
                        {0.,1.2792339468697937e+03, 2.3929354061292258e+02,},
                        {0., 0., 1.,} };
 double distC[5] = { -6.3687295852461456e-01, -1.9748008790347320e+00,3.0970703651800782e-02, 2.1944646842516919e-03, 0. };

Mat cameraMatrix(3, 3, cv::DataType<double>::type, cameraD);
Mat distCoeffs(5, 1, cv::DataType<double>::type, distC);

//apply for whirling and translation vector
Mat rvecs = Mat::zeros(3,1,CV_64FC1);
Mat tvecs = Mat::zeros(3,1,CV_64FC1);
Mat obj_Cornor;//三维矩阵


void self_definition(void)
{
    //self definition spacial points
    refer_obj_Point3.push_back(Point3f( 0.0 , 0.0 , 0.0 ));//origin
    refer_obj_Point3.push_back(Point3f( 2.0 , 0.0 , 0.0 ));//x_axis
    refer_obj_Point3.push_back(Point3f( 0.0 , 2.0 , 0.0 ));//y_axis
    refer_obj_Point3.push_back(Point3f( 0.0 , 0.0 , 2.0 ));//z_axis
}

void solvepnp_init(void)
{
    self_definition();
    Mat(refer_obj_Point3).convertTo(obj_Cornor,CV_32F);//三维点向量转换成三维矩阵
}

void pnpDetect( RotatedRect rect)//------------------------------------从图形的四个角点，算出旋转平移的两个向量
{
    
    Point2f cornor_Buffer[4];
    rect.points(cornor_Buffer);//中间缓存，储存四个角点
    vector<Point2f> image_CPoints;//获取角点，放入solvepnp
    for(int i=0;i<4;i++)
    {
        image_CPoints.push_back(cornor_Buffer[i]);//找四个角点
    }
    
    solvePnP(obj_Cornor,image_CPoints,cameraMatrix,distCoeffs,rvecs,tvecs,false,SOLVEPNP_UPNP);//-------------------从图形的四个角点,综合三维和二维，算出旋转平移的两个向量
    
}
void find_image_axis(Mat origin)
{
    
    projectPoints(refer_obj_Point3,rvecs,tvecs,cameraMatrix,distCoeffs,refer_2D_imagePoint2f);//将三维和二维坐标对应起来画出对应的轴坐标，存到refer——2D——imagepoints里面
    line(origin,refer_2D_imagePoint2f[0],refer_2D_imagePoint2f[1],Scalar(255,0,0),1,8);
    line(origin,refer_2D_imagePoint2f[0],refer_2D_imagePoint2f[2],Scalar(0,255,0),1,8);
    line(origin,refer_2D_imagePoint2f[0],refer_2D_imagePoint2f[3],Scalar(0,0,255),1,8);
}
/*-------------------------------先初始化，循环里面申请图形四个角，在find——axis就行了----------------------*/
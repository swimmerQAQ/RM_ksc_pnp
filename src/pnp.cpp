#include <iostream>
#include <opencv2/opencv.hpp>
#include "../hsv_Color_pre/hsv_color_pre.hpp"
#include "../contours_tree/treeHierarchy.hpp"
#include "../find_centre/find.hpp"
#include "../kalmanFliter/kalman.hpp"
#include "../solvepnp/solvepnp.hpp"
#define T 0.01
using namespace std;
using namespace cv;
int hmin = 82;
int hmax = 255;
int smin = 98;
int smax = 255;
int vmin = 74;
int vmax = 255;
Mat imgmask,mask;
Mat imgblur,imgcanny;
Mat imgdilute,imgerode;
vector<vector<Point>> contours;
vector<vector<Point>> bulf_con;
vector<Vec4i> hierachy; 
vector<Vec4i> bulf_hierarchy;
//-------------------------------------------------------------kalmanfliter--------------------------------------------//
float getrand(void)
{
    return 0.5 * rand() / RAND_MAX - 0.25;
}
int stateSize = 6; int measSize = 2; int uSize = 1;
Eigen::MatrixXd A(stateSize,stateSize);
Eigen::VectorXd x(stateSize);
Eigen::MatrixXd B(stateSize,uSize);
Eigen::MatrixXd H(measSize,stateSize);
Eigen::MatrixXd P(stateSize,stateSize);


Eigen::MatrixXd R(measSize,measSize);


Eigen::MatrixXd Q(stateSize,stateSize);
Eigen::VectorXd Z(measSize);
Eigen::VectorXd U(uSize);
kal kalmanfliter(stateSize,measSize,uSize);
/*--------------------------------------------------------------kalmanfliter-------------------------------------------------*/
void selection(Mat origin,Mat in_img)
{
    //contoursSelect one(origin,in_img,contours,hierachy);-----------------------------------------------------对find contours tree_mod using
    findContours( in_img, contours, hierachy, RETR_TREE,CHAIN_APPROX_NONE);
    
    //findContours( in_img, bulf_con, bulf_hierarchy, RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);--------------------------想对父级轮廓操作---对应不了，介于opencv对图形的顺序迭代问题
    vector<float> area(contours.size());
    vector<float> external_area(contours.size());//--------------------------------------------------存 父级的区域面积
    
    //one.anti_selectContours(-2,-2,-2,-1);
    
    cout << " ----area------drawing-----begin--- =  " << endl;
    for(int i=0;i<contours.size();i++)
    {    
        area[i] = contourArea(contours[i]);
        
        if(hierachy[i][3] != -1)//-----------------------------------------------------------------------------有父级条件 1
        {   
            external_area[i] = contourArea(contours[hierachy[i][3]]);
            cout << " ----external------area---- =  " << external_area[i] << endl;
            //drawContours(origin,contours,hierachy[i][3],Scalar(255,255,0),3,8,hierachy);
            //if(hierachy[i][2] == -1)
            {
                if(area[i] > 500 && area[i] < 900)//---------------------------------------------------------区域面积条件 2
                {
                    
                    if(external_area[i] < 4500 && external_area[i] > 1500)//----------------------------父级区域面积条件 3
                    {
                        drawContours(origin,contours,i,Scalar(0,0,255),1,8,hierachy);
                        centrePoint(contours[i]);//---------------------------------------------------------库----返回中心点


                        /*--------------------------------------------------------------------kalmanfliter-----------------------------------------------*/
                        kalmanfliter.preInit(x,A,B,U,P,Q);
                        kalmanfliter.measure_init(H);
                        Z << centrePoint(contours[i]).x, centrePoint(contours[i]).y;
                        kalmanfliter.pridict(A,B,U);
                        kalmanfliter.update(Z,R);
                        cout << " update point is " << kalmanfliter.update(Z,R) << endl;
                        circle(origin,centrePoint(contours[i]),3,Scalar(0,255,0),1,8);
                        /*--------------------------------------------------------------------------------------------------------------------------------*/



                        RotatedRect rect = minAreaRect(contours[i]);//--------------------------------------转动矩形
                        Point2f p[4];
                        /*-------------------------------------------pnp-----------------------------------------*/
                        pnpDetect(rect);
                        find_image_axis(origin);
                        /*----------------------------------------------------------------------------------------*/
                        rect.points(p);
                        for(int j=0;j<4;j++)
                        {
                            line(origin,p[j],p[(j+1)%4],Scalar(100,255,50),2,8);
                        }
                        circle(origin,centrePoint(contours[i]),5,Scalar(0,0,255),2,8);
                        putText(origin,"kf(aim)",centrePoint(contours[i]), FONT_HERSHEY_SCRIPT_COMPLEX,0.4,Scalar(255, 255 ,255), 1);
                    }  
                   
                }
            }
            
        }
    }
    cout << "drawing finsh" << endl;
}


int main()
{
    VideoCapture flash;
    Mat frame;
    string path = "../src/a1.avi";
    frame = flash.open(path);
    if(!flash.isOpened())
    {
        cout << " cannot open the document.avi " << endl;
    }
    //-----------------------------------------------------------kalmanfliter-----------------------------------//
    
    A << 1,0,T,0,0.5*T*T,0,
         0,1,0,T,0,0.5*T*T,
         0,0,1,0,T,0,
         0,0,0,1,0,T,
         0,0,0,0,1,0,
         0,0,0,0,0,1;
    
    H <<    1,0,0,0,0,0,
            0,1,0,0,0,0;

    P.setIdentity();
    R.setIdentity()*0.1;
    Q.setIdentity()*0.01;
    Z.setZero();
    
    B(0,0);
    U(0);


    hsv_color_pre();/*---------------self--library-----------*/
    solvepnp_init();
    while (flash.read(frame))
    {
        cvtColor(frame,imgmask,COLOR_BGR2HSV);
        Scalar lower(hmin, smin, vmin);
	 	Scalar upper(hmax, smax, vmax);
        inRange(imgmask, lower, upper, mask);
        imshow("scream_mask",mask);
        GaussianBlur(mask,imgblur,Size(3,3),3);
        imshow("scream_blur",imgblur);
        Canny(imgblur, imgcanny, 25, 100);
 		imshow("imgcanny",imgcanny);
        
        selection(frame,imgcanny);

        if(waitKey(200)==32)
        {
            if(waitKey()==27)
            {
                break;
            }
        }
        imshow("scream",frame);
    }
    return 0;
}







































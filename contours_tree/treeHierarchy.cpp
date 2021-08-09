#include "treeHierarchy.hpp"
#include <opencv2/opencv.hpp>
 using namespace cv;
 #include <iostream>
 using namespace std;
/*
usage: 
初始化申请变量。传入参数 image/目标图片 contours/筛选的点云 hierarchy/图片等级 

调用变量的成员函数： xxxx.selectContours(输入四个int的图片等级筛选，不需要的使用-2)

函数返回为点云；可以直接操作该点云

例如：我需要筛选--前--没有别的图片的图像
设置为 --->  -2,-1,-2,-2

其他类似
*/

    contoursSelect::contoursSelect(Mat in_origin,Mat in_img,vector<vector<Point>> in_contours,vector<Vec4i> in_hierarchy)
    {
        origin = in_origin;
        image = in_img;
        contours = in_contours;
        hierarchy = in_hierarchy;
        //for tree_find
        findContours( in_img, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
        
        cout << " finish initial " << endl;
    }

    contoursSelect:: ~contoursSelect(){}

    vector<vector<Point>> contoursSelect::selectContours(int inex,int ipre,int ison, int idad)
    {
        nex = inex; pre = ipre; son = ison; dad = idad;
        
        for(int rank=0;rank < contours.size();rank++)//-2 = 不检查   -------  -1 = 不存在该级的图形 不存在和不检测完全不一样
        {
            if(dad != -2)
            {
                if(hierarchy[rank][3]==dad)
                {
                    if(son != -2)
                    {
                        if(hierarchy[rank][2] == son)
                        {
                            if(pre != -2)
                            {
                                if(hierarchy[rank][1]==pre)
                                {
                                    if(nex != -2)
                                    {
                                        if(hierarchy[rank][0]==nex)
                                        {
                                            
                                            cout << " hierarchy \n" << hierarchy[rank] << endl;
                                            drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                                       }
                                    }else
                                    {
                                        
                                        cout << " hierarchy \n" << hierarchy[rank] << endl;
                                        drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                                    }
                                }
                            }else
                            {
                                if(nex != -2)
                                {
                                    if(hierarchy[rank][0]==nex)
                                    {
                                        
                                        cout << " hierarchy \n" << hierarchy[rank] << endl;
                                        drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                                    }
                                }else
                                {
                                    
                                    cout << " hierarchy \n" << hierarchy[rank] << endl;
                                    drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                                }
                            }
                        }
                    }else
                    {
                        if(pre != -2)
                        {
                            if(hierarchy[rank][1]==pre)
                            {
                                if(nex != -2)
                                {
                                    if(hierarchy[rank][0]==nex)
                                    {
                                        
                                        cout << " hierarchy \n" << hierarchy[rank] << endl;
                                        drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                                    }
                                }else
                                {
                                    
                                    cout << " hierarchy \n" << hierarchy[rank] << endl;
                                    drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                            }
                            }
                        }else
                        {
                            if(nex != -2)
                            {
                                if(hierarchy[rank][0]==nex)
                                {
                                    
                                    cout << " hierarchy \n" << hierarchy[rank] << endl;
                                    drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                                }
                            }else
                            {
                                
                                cout << " hierarchy \n" << hierarchy[rank] << endl;
                                drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                            }
                        }
                    }
                }
            }else
            {
                if(son != -2)
                {
                    if(hierarchy[rank][2] == son)
                    {
                        if(pre != -2)
                        {
                            if(hierarchy[rank][1]==pre)
                            {
                                if(nex != -2)
                                {
                                    if(hierarchy[rank][0]==nex)
                                    {
                                       
                                       cout << " hierarchy \n" << hierarchy[rank] << endl;
                                       drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                                    }
                                }else
                                {
                                    
                                    cout << " hierarchy \n" << hierarchy[rank] << endl;
                                    drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                                }
                            }
                        }else
                        {
                            if(nex != -2)
                            {
                                if(hierarchy[rank][0]==nex)
                                {
                                    
                                    cout << " hierarchy \n" << hierarchy[rank] << endl;
                                    drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                                }
                            }else
                            {
                                
                                cout << " hierarchy \n" << hierarchy[rank] << endl;
                                drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                            }
                        }
                    }
                }else
                {
                    if(pre != -2)
                    {
                        if(hierarchy[rank][1]==pre)
                        {
                            if(nex != -2)
                            {
                                if(hierarchy[rank][0]==nex)
                                {
                                    
                                    cout << " hierarchy \n" << hierarchy[rank] << endl;
                                    drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                                }
                            }else
                            {
                               
                               cout << " hierarchy \n" << hierarchy[rank] << endl;
                               drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                            }
                        }
                    }else
                    {
                        if(nex != -2)
                        {
                            if(hierarchy[rank][0]==nex)
                            {
                                
                                cout << " hierarchy \n" << hierarchy[rank] << endl;
                                drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                            }
                        }else
                        {
                            
                            cout << " all hierarchy needn't select, please check out ! " << endl;
                            drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                        }
                    }
                }
            }
        }

    }
void contoursSelect::anti_selectContours(int inex,int ipre,int ison, int idad)
    {
        nex = inex; pre = ipre; son = ison; dad = idad;
        
        for(int rank=0;rank < contours.size();rank++)//-2 = 不检查   -------  -1 = 不存在该级的图形 不存在和不检测完全不一样
        {
            if(dad != -2)
            {
                if(hierarchy[rank][3] != dad)
                {
                    if(son != -2)
                    {
                        if(hierarchy[rank][2] != son)
                        {
                            if(pre != -2)
                            {
                                if(hierarchy[rank][1] != pre)
                                {
                                    if(nex != -2)
                                    {
                                        if(hierarchy[rank][0] != nex)
                                        {
                                            
                                            cout << " hierarchy \n" << hierarchy[rank] << endl;
                                            drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                                       }
                                    }else
                                    {
                                        
                                        cout << " hierarchy \n" << hierarchy[rank] << endl;
                                        drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                                    }
                                }
                            }else
                            {
                                if(nex != -2)
                                {
                                    if(hierarchy[rank][0] != nex)
                                    {
                                        
                                        cout << " hierarchy \n" << hierarchy[rank] << endl;
                                        drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                                    }
                                }else
                                {
                                    
                                    cout << " hierarchy \n" << hierarchy[rank] << endl;
                                    drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                                }
                            }
                        }
                    }else
                    {
                        if(pre != -2)
                        {
                            if(hierarchy[rank][1] != pre)
                            {
                                if(nex != -2)
                                {
                                    if(hierarchy[rank][0] != nex)
                                    {
                                        
                                        cout << " hierarchy \n" << hierarchy[rank] << endl;
                                        drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                                    }
                                }else
                                {
                                    
                                    cout << " hierarchy \n" << hierarchy[rank] << endl;
                                    drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                            }
                            }
                        }else
                        {
                            if(nex != -2)
                            {
                                if(hierarchy[rank][0] != nex)
                                {
                                    
                                    cout << " hierarchy \n" << hierarchy[rank] << endl;
                                    drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                                }
                            }else
                            {
                                
                                cout << " hierarchy \n" << hierarchy[rank] << endl;
                                cout << " i'm here" << endl;
                                drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                            }
                        }
                    }
                }
            }else
            {
                if(son != -2)
                {
                    if(hierarchy[rank][2] == son)
                    {
                        if(pre != -2)
                        {
                            if(hierarchy[rank][1]==pre)
                            {
                                if(nex != -2)
                                {
                                    if(hierarchy[rank][0] != nex)
                                    {
                                       
                                       cout << " hierarchy \n" << hierarchy[rank] << endl;
                                       drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                                    }
                                }else
                                {
                                    
                                    cout << " hierarchy \n" << hierarchy[rank] << endl;
                                    drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                                }
                            }
                        }else
                        {
                            if(nex != -2)
                            {
                                if(hierarchy[rank][0] != nex)
                                {
                                    
                                    cout << " hierarchy \n" << hierarchy[rank] << endl;
                                    drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                                }
                            }else
                            {
                                
                                cout << " hierarchy \n" << hierarchy[rank] << endl;
                                drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                            }
                        }
                    }
                }else
                {
                    if(pre != -2)
                    {
                        if(hierarchy[rank][1]==pre)
                        {
                            if(nex != -2)
                            {
                                if(hierarchy[rank][0] != nex)
                                {
                                    
                                    cout << " hierarchy \n" << hierarchy[rank] << endl;
                                    drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                                }
                            }else
                            {
                               
                               cout << " hierarchy \n" << hierarchy[rank] << endl;
                               drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                            }
                        }
                    }else
                    {
                        if(nex != -2)
                        {
                            if(hierarchy[rank][0] != nex)
                            {
                                
                                cout << " hierarchy \n" << hierarchy[rank] << endl;
                                drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                            }
                        }else
                        {
                            
                            cout << " all hierarchy needn't select, please check out ! " << endl;
                            drawContours(origin,contours,rank,Scalar(0,0,255),2,8,hierarchy);
                        }
                    }
                }
            }
        }
    }
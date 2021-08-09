#include <iostream>
using namespace std;
#include <eigen3/Eigen/Dense>
#include "kalman.hpp"



    kal::kal(int statesize = 0,int messize = 0, int usize = 0)
    {
        if(stateSize == 0 || measSize == 0)
        {
            cout << " invalid size settings" << endl;
        }
        x.resize(stateSize);//状态矩阵的大小 = stateSzie x 1
        x.setZero();

        A.resize(stateSize,stateSize);//状态矩阵的大小， 由于前后状态信息量一致,状态量叠加关系由预测模型定义，size = x.size * x.size
        A.setZero();

        B.resize(stateSize,uSize);//控制方程，usize是为了配对状态控制矩阵（matrix U）
        B.setZero();

        U.resize(uSize);//matrix U 是状态控制的矩阵，考虑的是对原状态是怎么改变的，由于左乘 控制方程B，肯定会变成一个stateSize行的usize列的矩阵，所以可以改变原状态
        U.setZero();

        P.resize(stateSize,stateSize);//现在还没有添加白噪声，当前为自然噪声（波动的协方差）
        P.setZero();

        Q.resize(stateSize,stateSize);//白噪声
        Q.setZero();


        H.resize(measSize, stateSize);
        H.setZero();


        R.resize(measSize,measSize);
        R.setZero();//测量方差
        z.resize(measSize);
        z.setZero();//测量状态
        //至此，我们已经准备好了预测的量，当前预测的理论状态
        //我们将在init 成员函数里面输入我们的目标状态
        /*-------理论架构----------(矩阵)
        X = F * X_ + B_ * U_ (F = A)
        P = F * P（origin） *F_T(转置) + Q 
        */
       
    }
    kal::~kal(){};
    int kal:: preInit(Eigen::VectorXd x_, Eigen::MatrixXd A_, Eigen::MatrixXd B_, Eigen::VectorXd U_, Eigen::MatrixXd P_, Eigen::MatrixXd Q_)
    {
        //部分初始化
        if(stateSize == 0 || measSize == 0)
        {
            x = x_; A = A_; B = B_; U = U_;
            P = P_; Q = Q_;
            cout << "  init " << endl;
            return 1;
        }else{
            cout << " initial failure " << endl;
            return 0;
        }
    }
    Eigen::MatrixXd kal::pridict(Eigen::MatrixXd A_, Eigen::MatrixXd B_, Eigen::MatrixXd U_)
    {
        //对预测要对状态转移矩阵，控制方程，以及控制向量进行更新
        //实时对标情况
        //通常稳定系统中不需要更新
        A = A_;
        B = B_;
        U = U_;
        Eigen::MatrixXd A_T = A.transpose();//转置矩阵，由于协方差矩阵的特性 A*P[i] = A * P * A_T
        
        x = A * x + B * U;
        P = A * P * A_T + Q;
        cout << " prediction " << endl;
        return x;
    }
    void kal::measure_init(Eigen::MatrixXd H_ )//划定我们要那些状态量，减少不必要的操作
    {
        H = H_;
        cout << " measure ok " << endl; 
    }
    /*--------------------理论------------------------------------
    两个高斯分布我们取最大的概率部分
    有  K_ = P_/(P_+R)//measure处理之后的
        P_ = P + K*H*P//K此处是measure之前的，所以要乘以H--------- K_ = H*K
        x = x+K(z - x)
        得到修正值


    */
    Eigen::VectorXd kal::update(Eigen::VectorXd z_,Eigen::MatrixXd R_ )
    {
        
        z = H * x;
        Eigen::MatrixXd HT ,Bulf1,Bulf2;
        HT = H.transpose();
        
        Bulf1 = H*P*HT + R_;
        Bulf2 = Bulf1.inverse();
        Eigen::MatrixXd K = P*HT*Bulf2;
        
        P = P - K*H*P;//注意矩阵先后顺序
        
        x = x + K*(z_ - z);
        cout << " updata " << endl;

        return x;
    }


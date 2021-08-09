#ifndef kalman_hpp
#define kalman_hpp
#include <eigen3/Eigen/Dense>
#include <iostream>
using namespace std;

class kal   //父类，初始化我们的当前的已得到的状态矩阵，让子类继承方便分块理解
{
    private:
    int stateSize;//我们要预测的状态矩阵
    int measSize;//先验矩阵大小 同时作为后验矩阵的大小 修正状态
    int uSize;//状态控制向量矩阵的大小
    Eigen::VectorXd x;//状态描述矩阵
    Eigen::MatrixXd A;//状态转移矩阵
    Eigen::MatrixXd B;//控制方程
    Eigen::VectorXd U;//状态控制向量
    Eigen::MatrixXd P;//变量之间的协方差——>指current P
    Eigen::MatrixXd Q;//自然噪声 ~N(0,Q)
    

    Eigen::MatrixXd H;//数学计算求解状态转移


    Eigen::MatrixXd R;//真实值的变化方差
    Eigen::VectorXd z;//状态真实测量值
    public:
    
    kal(int stateSize, int messSize, int uSize);
    
    ~kal();
    int preInit(Eigen::VectorXd x_, Eigen::MatrixXd A_, Eigen::MatrixXd B_, Eigen::VectorXd U_, Eigen::MatrixXd P_, Eigen::MatrixXd Q_);
    Eigen::MatrixXd pridict(Eigen::MatrixXd A_, Eigen::MatrixXd B_, Eigen::MatrixXd U_);
    void measure_init(Eigen::MatrixXd H_ );//划定我们要那些状态量，减少不必要的操作
    Eigen::VectorXd update(Eigen::VectorXd z_,Eigen::MatrixXd R_ );
    
};



#endif


#include "SPAAM_SVD.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>

cv::Mat glOrthoMat(double l, double r, double b, double t, double n, double f)
{
    cv::Mat m = cv::Mat::zeros(4, 4, CV_64F);

    m.at<double>(0, 0) = 2 / (r - l);
    m.at<double>(1, 1) = 2 / (t - b);
    m.at<double>(2, 2) = -2 / (f - n);
    m.at<double>(3, 3) = 1;

    m.at<double>(0, 3) = -(r + l) / (r - l);
    m.at<double>(1, 3) = -(t + b) / (t - b);
    m.at<double>(2, 3) = -(f + n) / (f - n);

    return m;
}

int main() 
{
    const char* filename = "C:\\Users\\Pavol\\source\\repos\\calibration_tools\\build\\display_calibration_params.yml";

    cv::Mat left_calib;
    cv::Mat right_calib;

    cv::FileStorage fs(filename, cv::FileStorage::READ);
    if (fs.isOpened()) {
        fs["left_display"] >> left_calib;
        fs["right_display"] >> right_calib;
    }

    std::cout << left_calib << std::endl;

    Eigen::MatrixXd m;
    cv::cv2eigen(left_calib, m);
    std::cout << "m=" << m << std::endl;

    double znear = 0.01, zfar = 10.0, right = 640, left = 0, top = 0, bottom = 720;

    SPAAM_SVD nsvd(m);
    nsvd.BuildGLMatrix3x4(znear, zfar, right, left, top, bottom);
    auto proj = cv::Mat(4, 4, CV_64F, &nsvd.ProjGL3x4);
    
    std::cout << "proj=" << proj << std::endl;
    
    std::cerr << "---" << std::endl;

    cv::Mat A = cv::Mat::zeros(4, 3, CV_64F);
    A.at<double>(0, 0) = 1;
    A.at<double>(1, 1) = 1;
    A.at<double>(2, 2) = -(zfar + znear);
    A.at<double>(3, 2) = 1;
    std::cerr << "A=" << A << std::endl;

    cv::Mat B = cv::Mat::zeros(4, 4, CV_64F);
    B.at<double>(2, 3) = zfar * znear;
    std::cerr << "B=" << B << std::endl;

    auto ortho = glOrthoMat(left, right, bottom, top, znear, zfar);
    // std::cerr << "ortho=" << ortho << std::endl;

    std::cout << (A * left_calib) + B << std::endl;

    cv::Mat my_proj = (ortho * ((A * left_calib) + B)).t();
    std::cerr << "my_proj=" << my_proj << std::endl;

    return 0;
}

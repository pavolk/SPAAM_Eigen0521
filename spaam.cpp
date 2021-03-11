
#include <exception>

#include "spaam.hpp"



#include "SPAAM_SVD.h"
#include <opencv2/core/mat.hpp>
#include <opencv2/core/eigen.hpp>


namespace spaam {

cv::Mat calculateProjectionMatrix(const Corresponcences& corr)
{

    SPAAM_SVD nsvd;

    for(auto& p : corr) {
        cv::Point3f w = p.first;
        cv::Point2f d = p.second;
        nsvd.corr_points.push_back(Correspondence_Pair(w.x, w.y, w.z, d.x, d.y));
    }
    
    
    auto m = nsvd.projectionDLTImpl();
    
    cv::Mat retv;
    cv::eigen2cv(m, retv);
    return retv;
}

void calculateOpenGlProjectionMatrix(const cv::Mat& display_matrix, const OrthoProjectionParams& params, double projection_matrix[16])
{
#if 1
    double znear = params.znear, zfar = params.zfar;

    auto tl = params.rect.tl();
    double top = tl.y, left = tl.x;

    auto br = params.rect.br();
    double bottom = br.y, right = br.x;
#else
    double znear = 0.01;    
    double zfar = 10.0;
    double right = 0;       //640;
    double left = 640;      //0;
    double top = 0;         //720;
    double bottom = 720;    //0;
#endif
    Eigen::MatrixXd m;
    cv::cv2eigen(display_matrix, m);
    std::cout << "m=" << m << std::endl;

    SPAAM_SVD nsvd(m);
    nsvd.BuildGLMatrix3x4(znear, zfar, right, left, top, bottom);
    
    std::memcpy(projection_matrix, nsvd.ProjGL3x4, 16*sizeof(double));
}

}


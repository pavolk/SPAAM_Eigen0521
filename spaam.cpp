
#include <exception>

#include "spaam.hpp"



#include "SPAAM_SVD.h"
#include <opencv2/core/mat.hpp>
#include <opencv2/core/eigen.hpp>


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


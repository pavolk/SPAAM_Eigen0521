#ifndef SPAAM_SPAAM_HPP
#define SPAAM_SPAAM_HPP

#include <vector>
#include <opencv2/core/types.hpp>

namespace spaam {

using Corresponcences = std::vector<std::pair<cv::Point3d, cv::Point2d>>;

cv::Mat calculateProjectionMatrix(const Corresponcences& corr);

struct OrthoProjectionParams {
    double znear;
    double zfar;
    cv::Rect rect;
    OrthoProjectionParams(double n, double f, const cv::Rect& viewport) 
        : znear(n)
        , zfar(f)
        , rect(viewport) 
    {}
};

void calculateOpenGlProjectionMatrix(const cv::Mat& display_matrix, const OrthoProjectionParams& params, double projection_matrix[16]);

}; // spaam

#endif // SPAAM_SPAAM_HPP
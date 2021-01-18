#ifndef SPAAM_SPAAM_HPP
#define SPAAM_SPAAM_HPP

#include <vector>
#include <opencv2/core/types.hpp>

using Corresponcences = std::vector<std::pair<cv::Point3d, cv::Point2d>>;

cv::Mat calculateProjectionMatrix(const Corresponcences& corr);


#endif // SPAAM_SPAAM_HPP
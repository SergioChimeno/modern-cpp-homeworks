#include "kMeans.h"
#include <opencv2/core.hpp>
#include <iostream>

cv::Mat ipb::kMeans(const std::vector<cv::Mat> &descriptors, int k, int max_iter)
{
    cv::Mat data;
    // concatenating all descriptors in 1 mat
    for(cv::Mat mat: descriptors)
    {
        data.push_back(mat);
    }

    cv::Mat labels, centers;

    cv::kmeans(data,k,labels,cv::TermCriteria( cv::TermCriteria::EPS+cv::TermCriteria::COUNT, max_iter, 1.0),3, cv::KMEANS_PP_CENTERS,centers);

    return centers;
}

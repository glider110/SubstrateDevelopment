//
// First Created by songjintao
//
#include <string>
#include <vector>
#include <iostream>
#include <Eigen/Dense>
#include <iostream>




typedef std::vector<Eigen::Vector3f> StdPoints;

void filterAxis(StdPoints &points, float axis_max, float axis_min,
                                       std::string axis_name) {
    int axis_index = 0;

    if (axis_name == "y") {
        axis_index = 1;
    } else if (axis_name == "z") {
        axis_index = 2;
    } else {
        return;
    }

    StdPoints filtered_points;

    for (int i = 0; i < points.size(); ++i) {
        const auto &point = points[i];
        float data = point[axis_index];
        if (data > axis_min && data < axis_max) {

            filtered_points.emplace_back(point);
        }
    }

    points = std::move(filtered_points);
}









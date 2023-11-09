//
// First Created by songjintao
//
#include <string>
#include <vector>
#include <iostream>
#include <Eigen/Dense>
#include <iostream>




typedef std::vector<Eigen::Vector3f> StdPoints;
struct SpaceRange3D {
    bool save_outside_point_flag = true;

    Eigen::Vector3f center_point;
    Eigen::Vector3f norm;
    Eigen::Vector3f norm_y;
    Eigen::Vector3f norm_z;

    float length;
    float weight;
    float height;
};
typedef std::shared_ptr<SpaceRange3D> SpaceRange3D_ptr;
typedef std::vector<SpaceRange3D_ptr> SpaceRange3DS;

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


void filterRange(StdPoints &oba_points, const SpaceRange3D_ptr range) {
    // 自定义区域滤波
    const float length_abs = std::abs(range->length) * 0.5f;
    const float weight_abs = std::abs(range->weight) * 0.5f;
    const float height_abs = std::abs(range->height) * 0.5f;

    StdPoints node_points;
    node_points.reserve(oba_points.size());

    for (int i = 0; i < oba_points.size(); ++i) {
        const auto &point = oba_points[i];
        Eigen::Vector3f vec_cp = point - range->center_point;
        float x_w = range->norm.transpose() * vec_cp;
        float y_w = range->norm_y.transpose() * vec_cp;
        float z_w = range->norm_z.transpose() * vec_cp;

        bool x_outside = std::abs(x_w) > length_abs;
        bool y_outside = std::abs(y_w) > weight_abs;
        bool z_outside = std::abs(z_w) > height_abs;

        if ((x_outside || y_outside || z_outside) != range->save_outside_point_flag) {
            continue;
        }
        node_points.emplace_back(point);
    }
    oba_points = std::move(node_points);
}








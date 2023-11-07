#include <gtest/gtest.h>
#include "base_point_cloud_process.h"

Eigen::Vector3f rotateZ(const Eigen::Vector3f& point, float angle) {
    float cos_theta = std::cos(angle);
    float sin_theta = std::sin(angle);
    Eigen::Matrix3f rotation;
    rotation << cos_theta, -sin_theta, 0,
                sin_theta, cos_theta, 0,
                0, 0, 1;
    return rotation * point;
}

// TEST(FilterRangeTest, SaveInsidePoints) {
//     // Arrange
//     StdPoints oba_points = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
//     SpaceRange3D_ptr range = std::make_shared<SpaceRange3D>();
//     range->length = 2.0;
//     range->weight = 2.0;
//     range->height = 2.0;
//     range->center_point = Eigen::Vector3f(0.0, 0.0, 0.0);
//     range->norm = Eigen::Vector3f(1.0, 0.0, 0.0);
//     range->norm_y = Eigen::Vector3f(0.0, 1.0, 0.0);
//     range->norm_z = Eigen::Vector3f(0.0, 0.0, 1.0);
//     range->save_outside_point_flag = false;

//     // Act
//     filterRange(oba_points, range);

//     // Assert
//     ASSERT_EQ(oba_points.size(), 3);
//     EXPECT_EQ(oba_points[0], Eigen::Vector3f(1.0, 2.0, 3.0));
//     EXPECT_EQ(oba_points[1], Eigen::Vector3f(4.0, 5.0, 6.0));
//     EXPECT_EQ(oba_points[2], Eigen::Vector3f(7.0, 8.0, 9.0));
// }

// TEST(FilterRangeTest, SaveOutsidePoints) {
//     // Arrange
//     StdPoints oba_points = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
//     SpaceRange3D_ptr range = std::make_shared<SpaceRange3D>();
//     range->length = 2.0;
//     range->weight = 2.0;
//     range->height = 2.0;
//     range->center_point = Eigen::Vector3f(0.0, 0.0, 0.0);
//     range->norm = Eigen::Vector3f(1.0, 0.0, 0.0);
//     range->norm_y = Eigen::Vector3f(0.0, 1.0, 0.0);
//     range->norm_z = Eigen::Vector3f(0.0, 0.0, 1.0);
//     range->save_outside_point_flag = true;

//     // Act
//     filterRange(oba_points, range);

//     // Assert
//     ASSERT_EQ(oba_points.size(), 0);
// }

// TEST(FilterRangeTest, MixedPoints) {
//     // Arrange
//     StdPoints oba_points = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
//     SpaceRange3D_ptr range = std::make_shared<SpaceRange3D>();
//     range->length = 2.0;
//     range->weight = 2.0;
//     range->height = 2.0;
//     range->center_point = Eigen::Vector3f(0.0, 0.0, 0.0);
//     range->norm = Eigen::Vector3f(1.0, 0.0, 0.0);
//     range->norm_y = Eigen::Vector3f(0.0, 1.0, 0.0);
//     range->norm_z = Eigen::Vector3f(0.0, 0.0, 1.0);
//     range->save_outside_point_flag = false;

//     // Act
//     filterRange(oba_points, range);

//     // Assert
//     ASSERT_EQ(oba_points.size(), 2);
//     EXPECT_EQ(oba_points[0], Eigen::Vector3f(4.0, 5.0, 6.0));
//     EXPECT_EQ(oba_points[1], Eigen::Vector3f(7.0, 8.0, 9.0));
// }

		
bool isPointInsideBox(const Eigen::Vector3f& point, const SpaceRange3D_ptr& range) {
    Eigen::Vector3f local_point = point - range->center_point;
    Eigen::Vector3f rotated_point = local_point;
    rotated_point(0) = local_point(0) * range->norm(0) + local_point(1) * range->norm_y(0) + local_point(2) * range->norm_z(0);
    rotated_point(1) = local_point(0) * range->norm(1) + local_point(1) * range->norm_y(1) + local_point(2) * range->norm_z(1);
    rotated_point(2) = local_point(0) * range->norm(2) + local_point(1) * range->norm_y(2) + local_point(2) * range->norm_z(2);
    return (std::abs(rotated_point(0)) <= range->length / 2.0) &&
           (std::abs(rotated_point(1)) <= range->weight / 2.0) &&
           (std::abs(rotated_point(2)) <= range->height / 2.0);
}


// TEST(FilterRangeTest, RotateZBox) {
//     // Arrange
//     StdPoints oba_points = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
//     SpaceRange3D_ptr range = std::make_shared<SpaceRange3D>();
//     range->length = 200.0;
//     range->weight = 200.0;
//     range->height = 200.0;
//     range->center_point = Eigen::Vector3f(0.0, 0.0, 0.0);
//     range->norm = Eigen::Vector3f(1.0, 0.0, 0.0);
//     range->norm_y = Eigen::Vector3f(0.0, 1.0, 0.0);
//     range->norm_z = Eigen::Vector3f(0.0, 0.0, 1.0);
//     range->save_outside_point_flag = false;

//     // Rotate the box around Z axis by 30 degrees
//     float angle = 30.0 * M_PI / 180.0;
//     range->center_point = rotateZ(range->center_point, angle);
//     range->norm = rotateZ(range->norm, angle);
//     range->norm_y = rotateZ(range->norm_y, angle);
//     range->norm_z = rotateZ(range->norm_z, angle);

//     // Act
//     filterRange(oba_points, range);

//     // Assert
//     // Add your assertions here
//     ASSERT_EQ(oba_points.size(), 2);
//     // EXPECT_FLOAT_EQ(oba_points[0](0), 4.330127);
//     // EXPECT_FLOAT_EQ(oba_points[0](1), 5.964102);
//     // EXPECT_FLOAT_EQ(oba_points[0](2), 6.0);
//     // EXPECT_FLOAT_EQ(oba_points[1](0), 6.330127);
//     // EXPECT_FLOAT_EQ(oba_points[1](1), 7.964102);
//     // EXPECT_FLOAT_EQ(oba_points[1](2), 9.0);
// }


		

		
TEST(IsPointInsideBoxTest, PointInsideBox) {
    // Arrange
    Eigen::Vector3f point_inside(1.0, 2.0, 3.0);
    Eigen::Vector3f point_outside(5.0, 6.0, 7.0);
    SpaceRange3D_ptr range = std::make_shared<SpaceRange3D>();
    range->length = 2.0;
    range->weight = 2.0;
    range->height = 2.0;
    range->center_point = Eigen::Vector3f(0.0, 0.0, 0.0);
    range->norm = Eigen::Vector3f(1.0, 0.0, 0.0);
    range->norm_y = Eigen::Vector3f(0.0, 1.0, 0.0);
    range->norm_z = Eigen::Vector3f(0.0, 0.0, 1.0);

    // Rotate the box around Z axis by 30 degrees
    float angle = 30.0 * M_PI / 180.0;
    range->center_point = rotateZ(range->center_point, angle);
    range->norm = rotateZ(range->norm, angle);
    range->norm_y = rotateZ(range->norm_y, angle);
    range->norm_z = rotateZ(range->norm_z, angle);

    // Act
    bool is_inside_point_inside = isPointInsideBox(point_inside, range);
    bool is_inside_point_outside = isPointInsideBox(point_outside, range);

    // Assert
    ASSERT_TRUE(is_inside_point_inside);
    ASSERT_FALSE(is_inside_point_outside);
}
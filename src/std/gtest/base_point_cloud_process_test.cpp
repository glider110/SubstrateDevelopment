// #pragma once
#include <gtest/gtest.h>
#include "base_point_cloud_process.h"



TEST(FilterAxisTest, FilterYAxis) {
    StdPoints points = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
    float axis_max = 6.0;
    float axis_min = 2.0;
    std::string axis_name = "y";

    filterAxis(points, axis_max, axis_min, axis_name);

    StdPoints expected_points = {{4.0, 5.0, 6.0}};
    ASSERT_EQ(points, expected_points);
}

TEST(FilterAxisTest, FilterZAxis) {
    StdPoints points = {{1.0, 2.0, 3.0}, {4.0, 5.0, 1.0}, {7.0, 8.0, 9.0}};
    float axis_max = 10.0;
    float axis_min = 4.0;
    std::string axis_name = "z";

    filterAxis(points, axis_max, axis_min, axis_name);

    StdPoints expected_points = {{7.0, 8.0, 9.0}};
    ASSERT_EQ(points, expected_points);
}

TEST(FilterAxisTest, InvalidAxisName) {
    StdPoints points = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
    float axis_max = 6.0;
    float axis_min = 2.0;
    std::string axis_name = "x";

    testing::internal::CaptureStderr();
    filterAxis(points, axis_max, axis_min, axis_name);
    std::string error_message = testing::internal::GetCapturedStderr();

    ASSERT_EQ(error_message, "Input axerroris name !\n");
}

// TEST(FilterAxisTest, NoPointsInRange) {
//     StdPoints points = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
//     float axis_max = 1.0;
//     float axis_min = 0.0;
//     std::string axis_name = "y";

//     filterAxis(points, axis_max, axis_min, axis_name);

//     StdPoints expected_points = {};
//     ASSERT_EQ(points, expected_points);
// }

// TEST(FilterAxisTest, AllPointsInRange) {
//     StdPoints points = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
//     float axis_max = 10.0;
//     float axis_min = 0.0;
//     std::string axis_name = "z";

//     filterAxis(points, axis_max, axis_min, axis_name);

//     StdPoints expected_points = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
//     ASSERT_EQ(points, expected_points);
// }
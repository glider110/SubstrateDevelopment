#include <iostream>
#include <vector>
#include <cmath>

struct Point2D {
    float x;
    float y;
};

class RadiusFilter {
public:
    RadiusFilter(float radius, float threshold, int minNeighborCount)
        : radius_(radius), threshold_(threshold), minNeighborCount_(minNeighborCount) {}

    std::vector<Point2D> filter(const std::vector<Point2D>& points) {
        std::vector<Point2D> filteredPoints;

        for (int i = 0; i < points.size(); i++) {
            Point2D currentPoint = points[i];
            std::vector<float> distances;
            int neighborCount = 0;

            for (int j = 0; j < points.size(); j++) {
                if (i != j) {
                    Point2D neighborPoint = points[j];
                    float distance = std::sqrt(std::pow(currentPoint.x - neighborPoint.x, 2) +
                                               std::pow(currentPoint.y - neighborPoint.y, 2));
                    if (distance <= radius_) {
                        distances.push_back(distance);
                        neighborCount++;
                    }
                }
            }

            if (neighborCount >= minNeighborCount_ && !distances.empty()) {
                float averageDistance = std::accumulate(distances.begin(), distances.end(), 0.0f) / distances.size();
                if (averageDistance < threshold_) {
                    filteredPoints.push_back(currentPoint);
                }
            }
        }

        return filteredPoints;
    }

private:
    float radius_;
    float threshold_;
    int minNeighborCount_;
};

int main() {
    // 输入一些点云数据
    std::vector<Point2D> points = {
        {1.0f, 2.0f},
        {3.0f, 4.0f},
        {5.0f, 6.0f},
        {7.0f, 8.0f},
        {9.0f, 10.0f}
    };

    // 创建半径滤波器对象
    RadiusFilter filter(5.0f, 3.0f, 5);

    // 应用半径滤波器
    std::vector<Point2D> filteredPoints = filter.filter(points);

    // 输出滤波后的点云数据
    for (const auto& point : filteredPoints) {
        std::cout << "Filtered Point: (" << point.x << ", " << point.y << ")" << std::endl;
    }

    return 0;
}
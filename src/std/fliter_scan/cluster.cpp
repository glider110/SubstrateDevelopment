// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <algorithm>

// struct Point {
//     double x;
//     double y;
// };

// double calculateDistance(const Point& p1, const Point& p2) {
//     double dx = p1.x - p2.x;
//     double dy = p1.y - p2.y;
//     return std::sqrt(dx * dx + dy * dy);
// }

// std::vector<Point> detectOutliers(const std::vector<Point>& points, double threshold) {
//     std::vector<double> distances;
//     for (int i = 0; i < points.size(); i++) {
//         for (int j = i + 1; j < points.size(); j++) {
//             double distance = calculateDistance(points[i], points[j]);
//             distances.push_back(distance);
//         }
//     }
    
//     double mean = 0.0;
//     for (const auto& distance : distances) {
//         mean += distance;
//     }
//     mean /= distances.size();
    
//     double stddev = 0.0;
//     for (const auto& distance : distances) {
//         stddev += (distance - mean) * (distance - mean);
//     }
//     stddev = std::sqrt(stddev / distances.size());
    
//     std::vector<Point> outliers;
//     for (int i = 0; i < points.size(); i++) {
//         for (int j = i + 1; j < points.size(); j++) {
//             double distance = calculateDistance(points[i], points[j]);
//             if (distance > mean + threshold * stddev) {
//                 outliers.push_back(points[i]);
//                 outliers.push_back(points[j]);
//             }
//         }
//     }
    
//     return outliers;
// }

// int main() {
//     std::vector<Point> points = {
//         {1.0, 2.0},
//         {2.0, 3.0},
//         {3.0, 4.0},
//         {4.0, 5.0},
//         {5.0, 6.0},
//         {6.0, 7.0},
//         {7.0, 8.0},
//         {8.0, 9.0},
//         {9.0, 10.0},
//         {10.0, 11.0}
//     };
    
//     double threshold = 1.5;
    
//     std::vector<Point> outliers = detectOutliers(points, threshold);
    
//     for (const auto& outlier : outliers) {
//         std::cout << "Outlier: (" << outlier.x << ", " << outlier.y << ")" << std::endl;
//     }
    
//     return 0;
// }




#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

struct Point {
    double x;
    double y;
};

double calculateDistance(const Point& p1, const Point& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}

std::vector<Point> detectOutliers(const std::vector<Point>& points, int k, double threshold) {
    std::vector<Point> outliers;
    
    for (const auto& point : points) {
        std::vector<double> distances;
        for (const auto& neighbor : points) {
            if (point.x == neighbor.x && point.y == neighbor.y) {
                continue;
            }
            double distance = calculateDistance(point, neighbor);
            distances.push_back(distance);
        }
        
        std::sort(distances.begin(), distances.end());
        
        double avgDistance = 0.0;
        for (int i = 0; i < k; i++) {
            avgDistance += distances[i];
        }
        avgDistance /= k;
        
        double maxDistance = distances[k - 1];
        
        if (maxDistance > threshold * avgDistance) {
            outliers.push_back(point);
        }
    }
    
    return outliers;
}

int main() {
    std::vector<Point> points = {
        {1.0, 2.0},
        {2.0, 3.0},
        {3.0, 4.0},
        {4.0, 5.0},
        {5.0, 6.0},
        {6.0, 7.0},
        {7.0, 8.0},
        {8.0, 9.0},
        {9.0, 10.0},
        {10.0, 11.0},
        {-2, 0}
    };
    
    int k = 3;
    double threshold = 1.1;
    
    std::vector<Point> outliers = detectOutliers(points, k, threshold);

    std::cout << "size:" << outliers.size()<<std::endl;
    
    
    for (const auto& outlier : outliers) {
        std::cout << "Outlier: (" << outlier.x << ", " << outlier.y << ")" << std::endl;
    }
    
    return 0;
}
#include "triangle.hpp"

#include <algorithm>

Point2D Point2D::operator-(const Point2D& other) const {
    return {x - other.x, y - other.y};
}

double Point2D::dot(const Point2D& other) const {
    return x * other.x + y * other.y;
}

Point3D Point3D::operator-(const Point3D& other) const {
    return {x - other.x, y - other.y, z - other.z};
}

double Point3D::dot(const Point3D& other) const {
    return x * other.x + y * other.y + z * other.z;
}

Point3D Point3D::cross(const Point3D& other) const {
    return {y * other.z - z * other.y, z * other.x - x * other.z,
            x * other.y - y * other.x};
}

Triangle<Point2D>::Triangle(const std::vector<double>& coordinates)
    : Triangle<Point2D>({coordinates[0], coordinates[1]},
                        {coordinates[2], coordinates[3]},
                        {coordinates[4], coordinates[5]}) {}
Triangle<Point3D>::Triangle(const std::vector<double>& coordinates)
    : Triangle<Point3D>({coordinates[0], coordinates[1], coordinates[2]},
                        {coordinates[3], coordinates[4], coordinates[5]},
                        {coordinates[6], coordinates[7], coordinates[8]}) {}
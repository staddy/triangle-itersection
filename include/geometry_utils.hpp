#ifndef GEOMETRY_UTILS_H
#define GEOMETRY_UTILS_H

#include <string>
#include <vector>

#include "triangle.hpp"

/**
 * A class that contains static functions to analyze geometry objects.
 */
class GeometryUtils {
   public:
    GeometryUtils() = delete;

    /**
     * This method checks if an axis is a separation axis of two convex hulls,
     * defined by sets of vertices.
     *
     * \param axis an axis to check
     * \param vertices1 a set of vertices defining the first convex hull
     * \param vertices2 a set of vertices defining the second convex hull
     * \returns true if the given axis is a separation axis of the two convex
     * hulls, false otherwise.
     */
    template <typename T>
    static bool isSeparatingAxis(const T& axis, const std::vector<T>& vertices1,
                                 const std::vector<T>& vertices2) {
        double min1 = std::numeric_limits<double>::infinity(),
               max1 = -std::numeric_limits<double>::infinity();
        double min2 = std::numeric_limits<double>::infinity(),
               max2 = -std::numeric_limits<double>::infinity();

        for (const auto& vertex : vertices1) {
            double projection = axis.dot(vertex);
            min1 = std::min(min1, projection);
            max1 = std::max(max1, projection);
        }

        for (const auto& vertex : vertices2) {
            double projection = axis.dot(vertex);
            min2 = std::min(min2, projection);
            max2 = std::max(max2, projection);
        }

        return max1 < min2 || max2 < min1;
    }
    /**
     * This method checks if triangles are intersecting (its vertices convex
     * hulls have at least one common point).
     *
     * \param triangle1 the first triangle
     * \param triangle2 the second triangle
     * \returns true if the triangles are intersecting, false otherwise.
     */
    static bool trianglesIntersect(const Triangle<Point2D>& triangle1,
                                   const Triangle<Point2D>& triangle2);
    static bool trianglesIntersect(const Triangle<Point3D>& triangle1,
                                   const Triangle<Point3D>& triangle2);
};

#endif  // GEOMETRY_UTILS_H

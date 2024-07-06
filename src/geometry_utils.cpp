#include "geometry_utils.hpp"

bool GeometryUtils::trianglesIntersect(const Triangle<Point2D>& triangle1,
                                       const Triangle<Point2D>& triangle2) {
    for (const auto& edge : triangle1.edges()) {
        Point2D axis = {-edge.y, edge.x};
        if (isSeparatingAxis(axis, triangle1.vertices(),
                             triangle2.vertices())) {
            return false;
        }
    }

    for (const auto& edge : triangle2.edges()) {
        Point2D axis = {-edge.y, edge.x};
        if (isSeparatingAxis(axis, triangle1.vertices(),
                             triangle2.vertices())) {
            return false;
        }
    }

    return true;
}

bool GeometryUtils::trianglesIntersect(const Triangle<Point3D>& triangle1,
                                       const Triangle<Point3D>& triangle2) {
    std::vector<Point3D> axes;

    auto edges1 = triangle1.edges();
    auto edges2 = triangle2.edges();

    Point3D normal1 = edges1[0].cross(edges1[1]);
    Point3D normal2 = edges2[0].cross(edges2[1]);

    axes.emplace_back(normal1);
    axes.emplace_back(normal2);

    for (const auto& edge1 : edges1) {
        for (const auto& edge2 : edges2) {
            axes.emplace_back(edge1.cross(edge2));
        }
    }

    for (const auto& axis : axes) {
        if (isSeparatingAxis(axis, triangle1.vertices(),
                             triangle2.vertices())) {
            return false;
        }
    }

    return true;
}

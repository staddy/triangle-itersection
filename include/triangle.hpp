#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>

/**
 * A struct that represents a 2D point.
 */
struct Point2D {
    double x = 0;
    double y = 0;

    Point2D operator-(const Point2D& other) const;
    /**
     * Dot product.
     */
    double dot(const Point2D& other) const;
};

/**
 * A struct that represents a 3D point.
 */
struct Point3D {
    double x = 0;
    double y = 0;
    double z = 0;

    Point3D operator-(const Point3D& other) const;
    /**
     * Dot product.
     */
    double dot(const Point3D& other) const;
    /**
     * Cross product.
     */
    Point3D cross(const Point3D& other) const;
};

/**
 * A class that represents a triangle.
 */
template <typename T>
class Triangle {
   public:
    /**
     * Create a degenerate triangle (all vertices are the at the same point).
     */
    Triangle() : m_vertices({T(), T(), T()}) {}

    /**
     * Create a triangle.
     *
     * \param a first vertex
     * \param b second vertex
     * \param c third vertex
     */
    Triangle(T&& a, T&& b, T&& c) : m_vertices({a, b, c}) {}

    /**
     * Create a triangle from std::vector of coordinates.
     *
     * \param coordinates an std::vector of vertices coordinates
     */
    Triangle(const std::vector<double>& coordinates);

    /**
     * Get triangle edges vectors.
     *
     * \returns an std::vector containing the triangle edges vectors.
     */
    std::vector<T> edges() const {
        return {m_vertices[1] - m_vertices[0], m_vertices[2] - m_vertices[1],
                m_vertices[0] - m_vertices[2]};
    }

    /**
     * Get triangle vertices.
     *
     * \returns an std::vector containing the triangle vertices.
     */
    const std::vector<T>& vertices() const { return m_vertices; }

   private:
    std::vector<T> m_vertices;
};

#endif  // TRIANGLE_H

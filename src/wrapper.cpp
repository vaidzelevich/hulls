#include "./convex_hull.h"
#include "./concaveman/concaveman.h"

using Point = hull::Point<double>;

std::vector<Point> make_convex_hull(
    const std::vector<Point> &points)
{
    const auto indices = hull::convex_hull(points);
    std::vector<Point> result;
    result.reserve(size(indices));
    transform(begin(indices), end(indices), back_inserter(result),
              [&points](int i)
              { return points[i]; });
    return result;
}

std::vector<Point> make_concave_hull(
    const std::vector<Point> &points,
    double concavity,
    double threshold)
{
    const auto hull = hull::convex_hull(points);
    return concaveman<double, 16>(points, hull, concavity, threshold);
}

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(hulls, m)
{
    m.def("make_convex_hull", &make_convex_hull);
    m.def("make_concave_hull", &make_concave_hull,
          py::arg("points"), py::arg("concavity") = 2.0,
          py::arg("threshold") = 0.0);
}
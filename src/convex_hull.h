#pragma once

#include <algorithm>
#include <array>
#include <numeric>
#include <vector>

namespace hull
{
    template <typename T>
    using Point = std::array<T, 2>;

    template <typename T>
    bool cw(const Point<T> &a, const Point<T> &b, const Point<T> &c)
    {
        return a[0] * (b[1] - c[1]) + b[0] * (c[1] - a[1]) + c[0] * (a[1] - b[1]) < 0;
    }

    template <typename T>
    bool ccw(const Point<T> &a, const Point<T> &b, const Point<T> &c)
    {
        return a[0] * (b[1] - c[1]) + b[0] * (c[1] - a[1]) + c[0] * (a[1] - b[1]) > 0;
    }

    template <typename T>
    std::vector<int> convex_hull(const std::vector<Point<T>> &points)
    {
        const auto n = (int)size(points);
        std::vector<int> indices(n);
        std::iota(begin(indices), end(indices), 0);
        if (n <= 1)
        {
            return indices;
        }
        std::sort(begin(indices), end(indices),
                  [&points](int lhs, int rhs)
                  { return points[lhs] < points[rhs]; });
        const auto &p1 = points[indices[0]];
        const auto &p2 = points[indices.back()];
        std::vector<int> up{
            indices[0],
        };
        std::vector<int> down{
            indices[0],
        };
        for (int i = 1; i < n; ++i)
        {
            const auto &p = points[indices[i]];
            if (i == n - 1 || cw(p1, p, p2))
            {
                while (size(up) >= 2 &&
                       !cw(points[up[size(up) - 2]], points[up.back()], p))
                {
                    up.pop_back();
                }
                up.push_back(indices[i]);
            }
            if (i == n - 1 || ccw(p1, p, p2))
            {
                while (size(down) >= 2 &&
                       !ccw(points[down[size(down) - 2]], points[down.back()], p))
                {
                    down.pop_back();
                }
                down.push_back(indices[i]);
            }
        }
        indices.clear();
        std::copy(begin(down), end(down), back_inserter(indices));
        std::copy(next(rbegin(up)), rend(up), back_inserter(indices));
        // // for (size_t i=0; i<up.size(); ++i)
		// //     indices.push_back (up[i]);
	    // for (size_t i=up.size()-2; i>0; --i)
		//     indices.push_back (up[i]);
        return indices;
    }

} // namespace hull
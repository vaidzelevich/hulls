from collections.abc import Sequence
from typing import TypeAlias

from matplotlib.axes import Axes
import matplotlib.pyplot as plt


from hulls import make_concave_hull, make_convex_hull


Point: TypeAlias = tuple[float, float]


def draw_contour(
        ax: Axes,
        points: Sequence[Point],
        label: str
) -> None:

    indices = range(-1, len(points))
    ax.plot([points[i][0] for i in indices],
            [points[i][1] for i in indices], label=label)


def main(
    points: Sequence[Point]
) -> None:

    ax: Axes = plt.gca()
    ax.set_aspect('equal')
    ax.plot(*zip(*points), 'o')
    draw_contour(ax, make_concave_hull(points), 'concave')
    draw_contour(ax, make_convex_hull(points), 'convex')

    ax.legend()
    plt.show()


if __name__ == '__main__':
    points = [(10, 5), (10, 0), (20, 0), (20, 10), (15, 10),
              (10, 15), (10, 20), (0, 20), (0, 10), (5, 10)]
    main(points)

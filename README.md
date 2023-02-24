# Concave and convex hulls of points on a plane

## Installation

```bash
git clone --recursive https://github.com/vaidzelevich/hulls.git
pip install .
```

## Test call

```python
from hulls import make_concave_hull, make_convex_hull

points = [
    (0, 0), (20, 0), (20, 10), (15, 10), (10, 15), (10, 20), (0, 20)
]

concave_hull: list[tuple[float, float]] = make_concave_hull(points)
convex_hull: list[tuple[float, float]] = make_convex_hull(points)
```
# Problem: CF 2073 B - Three-Dimensional Embedding
# https://codeforces.com/contest/2073/problem/B

"""
Three-Dimensional Graph Embedding Solver

Algorithm:
This solution uses a grid-based approach to embed a graph in 3D space, ensuring that:
1. Each vertex is placed at a unique (x,y,0) coordinate with integer values between 0 and 400
2. Each edge is represented as a polyline with segments parallel to x, y, or z axes
3. No polylines intersect except at shared vertices
4. Each polyline has at most 30 nodes and no self-intersections

Approach:
- Place vertices on a 2D grid with spacing to avoid overlap
- Use a layering system to prevent edges from crossing
- Each edge is constructed as a four-segment polyline with z-coordinates controlled to avoid intersections
- Precomputed vertex shapes (g) allow for quick edge construction
- Dynamic tracking of occupied layers (D) and node positions (I) prevents crossings

Time Complexity: O(n + m)
Space Complexity: O(n + m)

The algorithm ensures all constraints are met through:
1. Grid-based vertex placement to avoid coordinate conflicts
2. Layer-based edge routing to prevent intersection
3. Precomputed edge construction patterns to ensure valid geometry
4. Tracking mechanisms to maintain embedding validity
"""

import sys


def solve():
    d = sys.stdin.buffer.read().split()
    it = iter(d)
    ni = lambda: int(next(it))
    n = ni()
    m = ni()
    g = []
    o = []
    M, S = 133, 200
    D = [0] * S
    I = [75] * S
    w = []
    for i in range(n):
        x = (i % M) * 3
        y = (i // M) * 5
        w.append(f"{x +1 } {y +2 }")
        g.append(
            [
                [
                    [x + 1, y + 2, 0],
                    [x + 2, y + 2, 0],
                    [x + 2, y + 0, 0],
                    [x + 1, y + 0, 0],
                ],
                [[x + 1, y + 2, 0], [x + 1, y + 1, 0]],
                [[x + 1, y + 2, 0]],
                [[x + 1, y + 2, 0], [x + 1, y + 3, 0]],
                [
                    [x + 1, y + 2, 0],
                    [x + 0, y + 2, 0],
                    [x + 0, y + 4, 0],
                    [x + 1, y + 4, 0],
                ],
            ]
        )

    def E(u, h, i):
        r = g[u].pop()
        r.append(r[-1][:])
        r[-1][2] = (h << 1) + 2
        r.append(r[-1][:])
        r[-1][0] += 1
        r.append(r[-1][:])
        r[-1][1] = i
        r.append(r[-1][:])
        r[-1][2] -= 1
        return r

    for _ in range(m):
        u = ni() - 1
        v = ni() - 1
        h = 0
        um = u % M
        vm = v % M
        while (D[h] >> um) & 1 or (D[h] >> vm) & 1:
            h += 1
        if um != vm:
            a = E(u, h, I[h])
            b = E(v, h, I[h])
        else:
            a = E(u, h, (u // M) * 5)
            b = E(v, h, (v // M) * 5)
            a.pop()
            a.pop()
            b.pop()
            b.pop()
        b = b[::-1]
        a += b
        o.append(a)
        D[h] |= (1 << um) | (1 << vm)
        I[h] += 1
    sys.stdout.write(
        "\n".join(
            w
            + [
                "{} {}".format(len(p), " ".join(f"{x } {y } {z }" for x, y, z in p))
                for p in o
            ]
        )
    )


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/
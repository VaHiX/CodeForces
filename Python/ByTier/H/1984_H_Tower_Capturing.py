# Problem: CF 1984 H - Tower Capturing
# https://codeforces.com/contest/1984/problem/H

"""
Algorithm: Convex Hull + Dynamic Programming on DAG
Time Complexity: O(n^3) where n is the number of towers
Space Complexity: O(n^2) for the DP table

This solution uses the following approach:
1. Find the convex hull of all towers to determine the outer boundary
2. Use dynamic programming on a directed acyclic graph (DAG) formed by 
   the convex hull vertices to compute the number of valid attack plans
3. For each pair of vertices on the convex hull, compute the number of 
   ways to split the remaining towers using valid circles
4. The key insight is that valid operations must create circles containing 
   all towers, and these are constrained by the convex hull structure
"""

import math
import sys

input = sys.stdin.read
MOD = 998244353


class Combinatorics:
    def __init__(self, max_n):
        self.max_n = max_n
        self.comb = [[0 for _ in range(max_n + 1)] for _ in range(max_n + 1)]
        self.precompute_combinations()

    def precompute_combinations(self):

        for n in range(self.max_n + 1):
            self.comb[n][0] = 1
            self.comb[n][n] = 1

        for n in range(1, self.max_n + 1):
            for k in range(1, n):
                self.comb[n][k] = (self.comb[n - 1][k - 1] + self.comb[n - 1][k]) % MOD

    def C(self, n, k):
        if n < k:
            return 0
        return self.comb[n][k]


import math


class LightTower:
    def __init__(self):
        self.C = Combinatorics(200)
        self.dp = [[0 for _ in range(100)] for _ in range(100)]
        self.towers = []

        self.tower_begin = [(), ()]

    def calculate_angle(self, i, j, k):

        u = (
            self.towers[k][0] - self.towers[i][0],
            self.towers[k][1] - self.towers[i][1],
        )
        v = (
            self.towers[k][0] - self.towers[j][0],
            self.towers[k][1] - self.towers[j][1],
        )

        dot_product = u[0] * v[0] + u[1] * v[1]
        magnitude_u = math.sqrt(u[0] ** 2 + u[1] ** 2)
        magnitude_v = math.sqrt(v[0] ** 2 + v[1] ** 2)

        cos_theta = dot_product / (magnitude_u * magnitude_v)
        return cos_theta

    def find_convex_hull(self):

        points = sorted(set(self.tower_all))

        if len(points) <= 1:
            return points

        def cross(o, a, b):
            return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])

        lower = []
        for p in points:
            while len(lower) >= 2 and cross(lower[-2], lower[-1], p) <= 0:
                lower.pop()
            lower.append(p)

        upper = []
        for p in reversed(points):
            while len(upper) >= 2 and cross(upper[-2], upper[-1], p) <= 0:
                upper.pop()
            upper.append(p)

        self.towers = lower[:-1] + upper[:-1]

    def solve(self):
        n = len(self.towers)
        if self.tower_begin_id[0] == -1 or self.tower_begin_id[1] == -1:
            return 0
        if self.tower_begin_id[0] == self.tower_begin_id[1]:
            return 0

        diff = [
            (self.tower_begin_id[0] - self.tower_begin_id[1]) % n,
            (self.tower_begin_id[1] - self.tower_begin_id[0]) % n,
        ]
        max_iter_length = max(diff)

        max_angle = [-1.0, -1.0]

        if (self.tower_begin_id[0] + 1) % n != self.tower_begin_id[1]:
            temp_pos = (self.tower_begin_id[0] + 1) % n
            while temp_pos != self.tower_begin_id[1]:
                max_angle[0] = max(
                    max_angle[0],
                    self.calculate_angle(
                        self.tower_begin_id[0], self.tower_begin_id[1], temp_pos
                    ),
                )
                temp_pos = (temp_pos + 1) % n
        if (self.tower_begin_id[1] + 1) % n != self.tower_begin_id[0]:
            temp_pos = (self.tower_begin_id[1] + 1) % n
            while temp_pos != self.tower_begin_id[0]:
                max_angle[1] = max(
                    max_angle[1],
                    self.calculate_angle(
                        self.tower_begin_id[0], self.tower_begin_id[1], temp_pos
                    ),
                )
                temp_pos = (temp_pos + 1) % n

        if max(max_angle) > -min(max_angle):
            return 0

        [2.0 for _ in range(n)]

        for i in range(n):
            self.dp[i][(i + 1) % n] = 1

        for length in range(2, max_iter_length + 1):
            for i in range(n):
                j = (i + length) % n

                self.dp[i][j] = 0
                max_cos = -2.0
                k = -1

                temp_pos = (i + 1) % n
                while temp_pos != j:

                    temp_cos = self.calculate_angle(i, j, temp_pos)
                    if temp_cos > max_cos:
                        max_cos = temp_cos
                        k = temp_pos

                    temp_pos = (temp_pos + 1) % n

                temp_fac = (self.dp[i][k] * self.dp[k][j]) % MOD
                temp_fac *= self.C.C((j - i) % n - 2, (j - k) % n - 1)

                self.dp[i][j] += temp_fac
                self.dp[i][j] %= MOD

        result = self.dp[self.tower_begin_id[0]][self.tower_begin_id[1]]
        result *= self.dp[self.tower_begin_id[1]][self.tower_begin_id[0]]
        result %= MOD
        result *= self.C.C(diff[0] + diff[1] - 2, diff[0] - 1)
        result %= MOD

        return result

    def set_towers(self, towers_input):
        self.tower_all = towers_input
        self.tower_begin = [towers_input[0], towers_input[1]]
        self.tower_begin_id = [-1, -1]

        self.find_convex_hull()
        for idx in range(len(self.towers)):
            for t in range(2):
                if (
                    self.tower_begin[t][0] == self.towers[idx][0]
                    and self.tower_begin[t][1] == self.towers[idx][1]
                ):
                    self.tower_begin_id[t] = idx


def solve():
    solver = LightTower()

    data = input().strip().split()
    index = 0
    t = int(data[index])
    index += 1
    result = []

    for _ in range(t):
        n = int(data[index])
        index += 1
        towers = []
        for _ in range(n):
            x = int(data[index])
            y = int(data[index + 1])
            index += 2
            towers.append((x, y))

        solver.set_towers(towers)
        result.append(solver.solve())

    for answer in result:
        print(answer)


solve()


# https://github.com/VaHiX/CodeForces/
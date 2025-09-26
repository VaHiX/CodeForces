# Contest 630, Problem P: Area of a Star
# URL: https://codeforces.com/contest/630/problem/P

import math

n, r = map(int, input().split())
print(
    math.sin(math.pi / (2 * n))
    * math.sin(math.pi / n)
    / math.sin(3 * math.pi / (2 * n))
    * n
    * r
    * r
)  # 1698325501.685457

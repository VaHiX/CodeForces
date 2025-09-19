# Contest 861, Problem A: k-rounding
# URL: https://codeforces.com/contest/861/problem/A

import math

n, k = map(int, input().split())
print(math.lcm(n, 10**k))

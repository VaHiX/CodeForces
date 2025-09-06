# Contest 2040, Problem B: Paint a Strip
# URL: https://codeforces.com/contest/2040/problem/B

from math import log2, ceil
for i in [*open(0)][1:]:
    print(ceil(log2((int(i) + 2) / 3)) + 1)
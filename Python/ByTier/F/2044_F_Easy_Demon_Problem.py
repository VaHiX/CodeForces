# Problem: CF 2044 F - Easy Demon Problem
# https://codeforces.com/contest/2044/problem/F

"""
F. Easy Demon Problem

Purpose:
This code solves a problem where we construct an n x m grid M such that M[i][j] = a[i] * b[j].
For each query asking if it's possible to make the grid have beauty (sum of all elements) equal to x,
we check whether there exists a row r and column c such that removing all elements in row r and column c
results in the desired sum x.

The strategy is:
1. Compute the total sums of arrays a and b.
2. For each element in a, compute how much removing it contributes to the sum (x - a[i]).
3. Similarly for array b.
4. Build sets of valid differences (u and v) that would cause a valid removal.
5. For each query x, check if there exists a product of a valid difference from u and v such that their product equals x.

Time Complexity:
O(n + m + |u| * log(|v|) + q), where
- |u| is the number of valid differences in array a (at most 2*M),
- |v| is the number of valid differences in array b,
- M = 2*10^5, which is the range of possible sums.

Space Complexity:
O(M), where M = 2*10^5 for storing u and v arrays.

"""

from sys import stdin

R = stdin.readline
S = lambda: map(int, R().split())
P = print
from bisect import bisect_left as bil

n, m, q = S()
a = [*S()]
b = [*S()]
x, y = sum(a), sum(b)  # total sums of arrays a and b
M = 200000
u = [0] * (2 * M + 1)  # marks valid differences from array a
v = [0] * (2 * M + 1)  # marks valid differences from array b

# For each element in a, calculate the effect of removing it.
# Store only those values that are within range [-M, M]
for z in a:
    if 0 < abs(x - z) <= M:
        u[x - z] = 1
# Same for b
for z in b:
    if 0 < abs(y - z) <= M:
        v[y - z] = 1

# Convert boolean array to list of indices that are set to 1, representing valid differences
u = [i for i in range(-M, M + 1) if u[i]]
v = [i for i in range(-M, M + 1) if v[i]]

# Precompute all products of elements from valid differences, store in p
p = [0] * (2 * M + 1)
for k in u:
    z = abs(k)
    # Use binary search to bound the portion of v that may contribute to valid product
    for i in range(bil(v, -M // z), bil(v, M // z + 1)):
        if abs(k * v[i]) <= M:
            p[k * v[i]] = 1

# Process queries
for _ in range(q):
    P("YES" if p[int(R())] else "NO")


# https://github.com/VaHiX/codeForces/
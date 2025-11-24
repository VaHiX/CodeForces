# Problem: CF 1715 F - Crop Squares
# https://codeforces.com/contest/1715/problem/F

"""
Algorithm: Binary search on coordinates using polygon queries
Time Complexity: O(log(n) + log(m)) - Two binary searches, each requiring 2 queries
Space Complexity: O(1) - Only using a few variables

This solution uses two binary searches to find the poisoned 1x1 square:
1. First, it finds the x-coordinate by querying a polygon that sweeps from left to right
2. Then, it finds the y-coordinate by querying a polygon that sweeps from bottom to top
The intersection areas returned by the queries are used to determine the position of the poisoned square.
"""

MIN = "0.000000000000001"
n, m = [int(i) for i in input().split()]
# Query for x-coordinate: sweep from left to right
print(f"? {2 *m +1 }", flush=True)
print(0, 0)
for i in range(m):
    print(n, i, flush=True)
    print(MIN, i + 1, flush=True)
hx = float(input())

# Query for y-coordinate: sweep from bottom to top
print(f"? {2 *n +1 }", flush=True)
print(0, 0)
for i in range(n):
    print(i, m, flush=True)
    print(i + 1, MIN, flush=True)
hy = float(input())

# Calculate final coordinates based on the intersection areas
x = max(n * (1 - hx) - 0.5, 0)
y = max(m * (1 - hy) - 0.5, 0)

print("!", "{:.9f}".format(x), "{:.9f}".format(y), flush=True)


# https://github.com/VaHiX/CodeForces/
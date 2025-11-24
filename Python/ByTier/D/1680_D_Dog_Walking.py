# Problem: CF 1680 D - Dog Walking
# https://codeforces.com/contest/1680/problem/D

"""
Code purpose:
This code solves the problem of maximizing the number of distinct integer points visited by a dog 
during a walk of n minutes, given that some movement records are unknown (marked as 0) and can be 
filled with values in the range [-k, k]. The goal is to ensure the dog returns to the starting point (0).

Approach:
- The solution uses prefix sums and dynamic programming principles to compute the range of 
  possible positions the dog can reach.
- For each possible interval [i, j], we determine how much the unknown values (0s) in that 
  interval can contribute to the position.
- For the given interval, we compute the minimum and maximum reachable positions, and use
  this to find the maximum number of distinct points visited.

Time Complexity: O(n^2), due to nested loops over intervals.
Space Complexity: O(n), to store prefix arrays.
"""

R = lambda: map(int, input().split())
n, k = R()
n += 1
a = [0] + [*R()]  # prepend 0 to simplify indexing

# p0[i] counts number of 0s in a[0..i-1]
p0 = [0] * n
# p[i] is prefix sum of a[0..i-1]
p = [0] * n

for i in range(1, n):
    p0[i] = p0[i - 1] + int(a[i] == 0)
    p[i] = p[i - 1] + a[i]

s = p[-1]  # total displacement after all movements

# If the known movements alone are inconsistent with returning to 0, impossible.
if p0[-1] * k < abs(s):
    res = -1
else:
    res = 0
    # Enumerate all possible intervals [i, j]
    for i in range(n):
        for j in range(i + 1, n):
            # Number of zeros between i and j
            l0 = p0[j] - p0[i]
            # Number of zeros after j
            r0 = p0[-1] - l0
            # Determine the effective range of movement for the interval [i, j]
            # l is the minimum possible offset that can be added to v from the zeros in [i,j]
            l = max(-l0 * k, -s - r0 * k)
            # r is the maximum possible offset that can be added to v from the zeros in [i,j]
            r = min(l0 * k, -s + r0 * k)
            # v is the displacement in interval [i, j]
            v = p[j] - p[i]
            # Compute the maximum number of points in this interval
            res = max(res, 1 + abs(v + l), 1 + abs(v + r))
print(res)


# https://github.com/VaHiX/CodeForces/
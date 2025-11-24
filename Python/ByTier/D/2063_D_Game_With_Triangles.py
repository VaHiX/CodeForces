# Problem: CF 2063 D - Game With Triangles
# https://codeforces.com/contest/2063/problem/D

"""
D. Game With Triangles

Purpose:
This code solves a problem where we are given n points on the line y=0 and m points on the line y=2.
We can form triangles using three non-collinear points, and each triangle contributes its area to our score.
The goal is to determine the maximum number of operations (k_max) and then calculate f(k), the maximum possible score
achievable by performing exactly k operations.

Algorithm:
- We are essentially trying to pick triplets of points such that one point is from y=0 and two from y=2,
  or one from y=2 and two from y=0, in a way that maximizes total area.
- Points on the same horizontal line cannot form valid triangles (collinear).
- So, for maximum score:
    * We must combine points from both lines to make triangles.
    * The idea is to sort both point sets, then pair up the farthest points from each end of the sorted lists
      to maximize base lengths (and thus areas).
    * We then greedily select combinations that give maximum gain at each step.

Time Complexity:
  O(n log n + m log m) per test case due to sorting.
  The rest is linear in n and m.

Space Complexity:
  O(n + m) for storing arrays a and b, plus auxiliary space for storing differences (a_l, b_l).
"""

from sys import stdin

inp = stdin.readline
t = int(inp())
for _ in range(t):
    n, m = map(int, inp().split())
    a = [int(x) for x in inp().split()]
    b = [int(x) for x in inp().split()]
    a.sort()
    b.sort()
    # Compute differences between farthest points from centers for both lists
    a_l = [a[-1 - i] - a[i] for i in range(n // 2)]
    b_l = [b[-1 - i] - b[i] for i in range(m // 2)]
    k_max = min((n + m) // 3, n, m)
    print(k_max)
    k = []
    count_a = 0
    count_b = 0
    ans = 0
    # Greedily build the answer by choosing optimal triangle combinations at each step
    for i in range(1, k_max + 1):
        if count_a > n - i:   # If we have too many a-points selected, reduce one
            ans += b_l[count_b]
            count_b += 1
            count_a -= 1
            ans -= a_l[count_a]
        if count_b > m - i:
            ans += a_l[count_a]
            count_a += 1
            count_b -= 1
            ans -= b_l[count_b]
        if count_a == n - i:   # All remaining a-points must be used, so add one from b
            ans += b_l[count_b]
            count_b += 1
        elif count_b == m - i:  # All remaining b-points must be used, so add one from a
            ans += a_l[count_a]
            count_a += 1
        elif a_l[count_a] > b_l[count_b]:   # Pick the higher area difference
            ans += a_l[count_a]
            count_a += 1
        else:
            ans += b_l[count_b]
            count_b += 1
        k.append(ans)
    if k_max > 0:
        print(*k)


# https://github.com/VaHiX/codeForces/
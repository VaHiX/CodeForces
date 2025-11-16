# Problem: CF 1730 B - Meeting on the Line
# https://codeforces.com/contest/1730/problem/B

"""
Algorithm: Meeting on the Line
Approach: 
- For each person i, the total time to reach the meeting point x0 is t_i + |x_i - x0|.
- We can think of each person as having a "range" they must cover: [x_i - t_i, x_i + t_i].
- The problem reduces to finding the optimal meeting point x0 such that the maximum time for anyone to reach it is minimized.
- This is a classic problem solved by taking the median of the ranges [x_i - t_i, x_i + t_i] or more precisely,
  the midpoint between the minimum of left endpoints and maximum of right endpoints.

Time Complexity: O(n) per test case
Space Complexity: O(n) due to storing the transformed arrays x1 and x2
"""

I = lambda: [*map(int, input().split())]
for _ in range(*I()):
    (n,) = I()
    x, t = I(), I()
    # x1[i] represents the left boundary of person i's range [x_i - t_i, x_i + t_i]
    x1 = [x[i] - t[i] for i in range(n)]
    # x2[i] represents the right boundary of person i's range [x_i - t_i, x_i + t_i]
    x2 = [x[i] + t[i] for i in range(n)]
    # The optimal meeting point is the midpoint between the minimum of left boundaries and maximum of right boundaries
    print((min(x1) + max(x2)) / 2)


# https://github.com/VaHiX/CodeForces/
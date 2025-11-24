# Problem: CF 2019 B - All Pairs Segments
# https://codeforces.com/contest/2019/problem/B

"""
Code Purpose:
This solution efficiently determines how many integer points lie on exactly k segments, 
where each segment [x_i, x_j] is formed by pairing all points x_i and x_j with i < j.
The algorithm uses a sweep-line technique combined with a frequency counting map to 
precompute the number of segments covering each possible count, then answers queries in O(1).

Algorithms/Techniques:
- Sweep line + coordinate compression + frequency counting
- Uses a map to count how many segments cover a given number of points

Time Complexity: O(n^2 + q)
Space Complexity: O(n^2)
"""
R = lambda: map(int, input().split())
(t,) = R()
while t:
    t -= 1
    n, q = R()
    d = {}
    p = i = 0
    for x in (*R(), 0):  # Append 0 to handle final iteration
        # Count how many segments cover a certain number of points
        # r is the number of segments that contain points in the interval
        d[r] = d.get(r := i * (n - i), 0) + x - p - 1
        p = x
        # Account for the segment ending at current point
        d[r] = d.get(r := r + i - 1, 0) + 1
        i += 1
    for k in R():
        print(d.get(k, 0))


# https://github.com/VaHiX/CodeForces/
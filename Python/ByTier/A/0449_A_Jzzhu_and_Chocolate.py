# Problem: CF 449 A - Jzzhu and Chocolate
# https://codeforces.com/contest/449/problem/A

"""
Code Purpose:
This code solves the problem of determining the maximum possible area of the smallest piece 
when a chocolate bar of size n x m is cut exactly k times. The cuts must be straight (horizontal or vertical),
and each cut must be along unit square edges.

Approach:
- First, ensure that n >= m for simplification.
- Use mathematical reasoning to determine how to distribute k cuts optimally:
    * If k+1 <= m-1, we can cut horizontally to split the chocolate into (k+1) pieces with minimum area based on either 
      vertical splitting (n/(k+1) * m) or horizontal splitting (m/(k+1) * n).
    * If k+1 > m-1 but k+1 <= n, we adjust the logic to optimize for remaining cuts.
    * If k <= n + m - 2, we use another formula to find maximum area.
    * If k > n + m - 2, it's impossible to make k cuts.

Time Complexity: O(1)
Space Complexity: O(1)
"""

for pratyush in range(1):
    n, m, k = list(map(int, input().split()))
    if m > n:
        m, n = n, m  # Ensure n >= m
    if k + 1 <= m - 1:
        # When we can make k+1 horizontal cuts within the range
        print(max((n // (k + 1)) * m, (m // (k + 1)) * n))
    elif k + 1 <= n and k + 1 > m - 1:
        # When we can't make all cuts horizontally, adjust to maximize area
        print(max((n // (k + 1)) * m, (n // (k - m + 2))))
    elif k <= n + m - 2:
        # General case where k cuts are feasible
        print(max((n // (k - m + 2)), (m // (k - n + 2))))
    else:
        # Implies more cuts than possible
        print(-1)


# https://github.com/VaHiX/CodeForces/
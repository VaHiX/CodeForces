# Problem: CF 1695 C - Zero Path
# https://codeforces.com/contest/1695/problem/C

"""
Zero Path Problem

Algorithm/Techniques:
- Dynamic Programming with two arrays to track minimum and maximum path sums
- For each cell, we compute the minimum and maximum possible sums to reach that cell
- The path must go from (0,0) to (n-1,m-1) with only right and down moves
- The total number of steps is (n-1) + (m-1) = n+m-2
- To have a zero sum path, we need the minimum sum to be <= 0 and maximum sum to be >= 0

Time Complexity: O(n * m) where n is number of rows and m is number of columns
Space Complexity: O(n * m) for the two DP tables
"""

inf = 10**9


def slv():
    h, w = map(int, input().split())
    a = []
    for i in range(h):
        a.append(list(map(int, input().split())))
    
    # Check if path length allows for zero sum
    # Path has length n + m - 2 steps
    # We can only achieve zero sum if the path length is even (as we're alternating between +1 and -1)
    # However, a stricter check: if n + m - 2 < 0 or odd length, then it's impossible to have zero sum
    if (h + w - 3) < 0 or (h + w - 3) % 2:
        print("NO")
    else:
        # dp0[i][j] = minimum sum to reach cell (i, j)
        # dp1[i][j] = maximum sum to reach cell (i, j)
        dp0 = [[inf] * w for i in range(h)]
        dp1 = [[-inf] * w for i in range(h)]
        dp0[0][0] = dp1[0][0] = a[0][0]
        for i in range(h):
            for j in range(w):
                v = a[i][j]
                # Propagate from above
                if i:
                    dp0[i][j] = min(dp0[i][j], dp0[i - 1][j] + v)
                    dp1[i][j] = max(dp1[i][j], dp1[i - 1][j] + v)
                # Propagate from left
                if j:
                    dp0[i][j] = min(dp0[i][j], dp0[i][j - 1] + v)
                    dp1[i][j] = max(dp1[i][j], dp1[i][j - 1] + v)
        # Check if we can get a sum of 0
        if dp0[h - 1][w - 1] <= 0 and 0 <= dp1[h - 1][w - 1]:
            print("YES")
        else:
            print("NO")


t = int(input())
for _ in range(t):
    slv()


# https://github.com/VaHiX/CodeForces/
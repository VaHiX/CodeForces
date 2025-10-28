# Problem: CF 1955 G - GCD on a grid
# https://codeforces.com/contest/1955/problem/G

"""
Algorithm: Dynamic Programming with GCD tracking
Approach:
- Use dynamic programming to track possible GCD values at each cell
- At each cell (i,j), we maintain a list of possible GCD values that can be achieved 
  by reaching this cell from either the top (i-1,j) or left (i,j-1).
- For each new cell, we compute GCD with all previous possible GCD values from 
  the top and left cells, and keep only the two largest unique GCD values to 
  optimize space complexity.
- Finally, we return the maximum GCD value from the bottom-right cell.

Time Complexity: O(n * m * log(max_value)) where n and m are grid dimensions
Space Complexity: O(n * m) due to storing GCD values per cell

Note: The commented-out portion shows an alternative bottom-up DP approach 
      but it's not used in the active code.
"""

from math import gcd

for _ in range(int(input())):
    n, m = tuple(map(int, input().split()))
    matr = []
    val = []
    for i in range(n):
        val.append([0] * m)
        matr.append(list(map(int, input().split())))
    val[0][0] = [matr[0][0]]
    for i in range(n):
        for j in range(m):
            if i == 0 and j == 0:
                continue
            elif i == 0 and j != 0:
                # Only coming from left
                val[i][j] = [gcd(val[i][j - 1][0], matr[i][j])]
            elif i != 0 and j == 0:
                # Only coming from top
                val[i][j] = [gcd(val[i - 1][j][0], matr[i][j])]
            else:
                # Coming from both top and left
                vals = []
                for v in val[i - 1][j]:
                    vals.append(gcd(v, matr[i][j]))
                for v in val[i][j - 1]:
                    vals.append(gcd(v, matr[i][j]))
                vals = sorted(list(set(vals)), reverse=True)
                val[i][j] = vals[:2]  # Keep only the two largest unique GCDs
    ans = val[-1][-1][0]
    """
    val[-1][-1] = [matr[-1][-1]]
    for i in range(n-1, -1, -1):
        for j in range(m-1, -1, -1):
            if i == n-1 and j == m-1:
                continue
            elif i == n-1 and j != m-1:
                val[i][j] = [gcd(val[i][j+1][0], matr[i][j])]
            elif i != n-1 and j == m-1:
                val[i][j] = [gcd(val[i+1][j][0], matr[i][j])]
            else:
                vals = []
                for v in val[i+1][j]:
                    vals.append(gcd(v, matr[i][j]))
                for v in val[i][j+1]:
                    vals.append(gcd(v, matr[i][j]))
                vals = sorted(list(set(vals)), reverse=True)
                val[i][j] = vals[:2]
    if val[0][0][0] > ans:
        ans = val[0][0][0]
    """
    print(ans)


# https://github.com/VaHiX/CodeForces/
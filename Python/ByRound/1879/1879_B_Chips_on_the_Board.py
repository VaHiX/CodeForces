# Problem: CF 1879 B - Chips on the Board
# https://codeforces.com/contest/1879/problem/B

"""
Algorithm: Chips on the Board

Purpose:
This problem requires placing chips on an n×n board such that every cell has at least one chip in its row or column.
Each chip at position (i,j) has a cost of a[i] + b[j]. The goal is to minimize the total cost.

Key Insight:
To cover all cells optimally, we can either:
1. Place chips in rows such that each row has at least one chip (minimum cost is sum of all a[i] + n * min(b))
2. Place chips in columns such that each column has at least one chip (minimum cost is sum of all b[i] + n * min(a))

We try both strategies and take the minimum.

Time Complexity: O(n) per test case
Space Complexity: O(1) extra space (not counting input storage)
"""

t = int(input().strip())
results = []
for _ in range(t):
    n = int(input().strip())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    total_a = sum(a)
    total_b = sum(b)
    min_a = min(a)
    min_b = min(b)
    # Two strategies:
    # 1. Place chips such that each row has at least one chip
    #    Cost = sum of a[i] + n * min(b)
    # 2. Place chips such that each column has at least one chip
    #    Cost = sum of b[i] + n * min(a)
    ans = min(total_a + n * min_b, total_b + n * min_a)
    results.append(str(ans))
print("\n".join(results))


# https://github.com/VaHiX/CodeForces/
# Problem: CF 1791 F - Range Update Point Query
# https://codeforces.com/contest/1791/problem/F

"""
Algorithm: Range Update Point Query with Union-Find Optimization
Purpose: Efficiently handle range updates (digit sum) and point queries on an array.
Techniques:
- Union-Find (Disjoint Set Union) is used to optimize consecutive updates.
- For each update operation, we calculate digit sum and use union-find to skip already processed elements.
Time Complexity:
- Update: O(log n) amortized per element due to union-find path compression.
- Query: O(1)
Space Complexity: O(n) for the array and Union-Find structure.

This implementation uses a Union-Find data structure to track which indices have been updated to a single digit,
allowing us to skip them in future updates.
"""

import sys

input = sys.stdin.readline


def solve():
    n, q = map(int, input().split())
    v = list(map(int, input().split()))

    fa = [-1] * (n + 1)  # Union-Find parent array

    def Find(x: int) -> int:
        """Find root of x with path compression."""
        y = x
        while fa[y] >= 0:
            y = fa[y]
        while fa[x] >= 0:
            fa[x], x = y, fa[x]
        return y

    for _ in range(q):
        question = list(map(int, input().split()))
        if question[0] == 1:
            i = Find(question[1] - 1)  # Find starting index
            while i < question[2]:  # Process range [l, r]
                s = 0
                temp = v[i]
                while temp:  # Calculate digit sum
                    s += temp % 10
                    temp //= 10
                v[i] = s
                if s < 10:  # If digit sum is single digit, mark as processed
                    fa[i] = i + 1
                i = Find(i + 1)  # Move to next index using union-find
        else:
            print(v[question[1] - 1])  # Output value at index x


t = int(input())
for _ in range(t):
    solve()


# https://github.com/VaHiX/CodeForces/
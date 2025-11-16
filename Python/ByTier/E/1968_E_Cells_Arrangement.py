# Problem: CF 1968 E - Cells Arrangement
# https://codeforces.com/contest/1968/problem/E

"""
Algorithm: 
The problem is to place n cells on an n×n grid such that the number of distinct Manhattan distances between any pair of cells is maximized.

Approach:
1. For small values of n, a specific pattern is used to generate points.
2. Start by placing points along the diagonal (x, x) for all rows except row 2.
3. Add the point (1, 2) at the end to maximize distinct distances.

Time Complexity: O(n) per test case, as we iterate through the rows once to generate the points.
Space Complexity: O(n) for storing the result points.
"""

import sys

input = sys.stdin.read


def solve():
    data = input().split()
    idx = 0

    t = int(data[idx])
    idx += 1

    results = []

    for _ in range(t):

        n = int(data[idx])
        idx += 1

        test_case_result = []

        # Place points along the diagonal except for row 2
        for i in range(1, n + 1):
            if i != 2:
                # Add point (i, i) for all rows except row 2
                test_case_result.append(f"{i } {i }")

        # Add point (1, 2) to maximize distinct distances
        test_case_result.append("1 2")

        results.append("\n".join(test_case_result))

    print("\n".join(results))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/
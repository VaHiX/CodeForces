# Problem: CF 1987 F1 - Interesting Problem (Easy Version)
# https://codeforces.com/contest/1987/problem/F1

"""
Algorithm: Dynamic Programming with Interval Approach
Time Complexity: O(n^4)
Space Complexity: O(n^3)

This solution uses a 3D dynamic programming approach to compute the maximum number of operations.
The idea is to consider all possible subarrays and track the maximum operations that can be performed
within each interval, accounting for the constraints of the problem.

The key insight is to process intervals from smaller to larger and keep track of the number of elements
that can be removed in a valid sequence, based on the condition a[i] = i.

The DP state f[i][j][l] represents the maximum operations performed on interval [i, j] with a specific
constraint l, where l indicates some derived state from the problem logic.

The final result for each test case is derived by computing f[0][n-1][0] >> 1, where the right shift by 1
accounts for double counting in the final answer due to the problem's construction.
"""

import sys


def main():
    input = sys.stdin.readline
    t = int(input())
    for _ in range(t):
        n = int(input())
        a = list(map(int, input().split()))
        a = [x - 1 for x in a]  # Convert to 0-based indexing
        f = [[[0] * (n + 1) for _ in range(n)] for __ in range(n)]
        for w in range(2, n + 1):  # w is the length of the interval
            for i in range(0, n - w + 1):  # i is the start index
                j = i + w - 1  # j is the end index
                for l in range(i + 1):  # l represents a state in the DP
                    f[i][j][l] = f[i][j - 1][l]  # Initialize with previous value
                    for k in range(i, j):  # k is a pivot point
                        # Check if a[k] <= k and the parity condition holds
                        if a[k] <= k and ((k - a[k]) % 2) == 0:
                            # Calculate previous state based on current k
                            prev = f[i][k - 1][l] if k > i else 0
                            # Compute required elements based on current state
                            need = l + k - i - prev
                            # Check if a[k] satisfies the required count
                            if a[k] >= need:
                                # Check if the remaining segment matches the expected state
                                if f[k + 1][j - 1][a[k] + 1] == j - k - 1:
                                    # Compute candidate solution
                                    cand = prev + (j - k + 1)
                                    # Update if better solution found
                                    if cand > f[i][j][l]:
                                        f[i][j][l] = cand
        # Final result is halved to correct for overcounting in problem structure
        print(f[0][n - 1][0] >> 1)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
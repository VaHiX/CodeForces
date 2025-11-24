# Problem: CF 1987 F2 - Interesting Problem (Hard Version)
# https://codeforces.com/contest/1987/problem/F2

"""
Algorithm: Dynamic Programming with Range Matching
Time Complexity: O(N^3) where N <= 800
Space Complexity: O(N^2)

This problem involves determining the maximum number of operations to remove adjacent elements 
from an array such that a[i] = i. The approach uses dynamic programming over all possible subarrays 
to compute the maximum operations that can be performed.

The key idea is to precompute the minimum operations needed for a range [l, r] based on 
the adjusted values of the array elements, which helps in determining valid operations.
Then a second DP table is used to propagate the valid number of operations across the full array.

The transformation A[i] -= (1 + i) converts the problem into a zero-based index system 
to match the problem constraint that a[i] must equal the index for a valid operation.

Then DP[l][r] represents minimum operations needed to process range [l, r].
Finally, a second DP is used to compute how many operations are possible in total.
"""

import sys

input = sys.stdin.readline
print = sys.stdout.write


def main():
    for _ in range(int(input())):
        N = int(input())
        A = list(map(int, input().split()))
        # Transform array to 0-based indexing
        for i in range(N):
            A[i] -= 1 + i

        inf = 1 << 30
        # DP[l][r] stores the minimum operations to process range [l, r]
        DP = [[inf] * (N + 1) for _ in range(N + 1)]
        for i in range(N + 1):
            DP[i][i] = 0  # Base case: empty range requires 0 operations

        # Fill DP table for all even-length ranges
        for d in range(2, N + 1, 2):  # only even lengths since we need pairs
            for l in range(N - d + 1):
                r = l + d
                if A[l] <= 0 and A[l] % 2 == 0:  # Check if first element can be processed
                    if d == 2:
                        # Base case: if length is 2, we have one pair
                        DP[l][r] = min(DP[l][r], -A[l] // 2)
                    else:
                        # Try splitting the range at different middle points
                        if 0 >= DP[l + 1][r - 1] * 2 + A[l]:
                            # If we can process this substructure, update DP
                            DP[l][r] = min(DP[l][r], max(DP[l + 1][r - 1], -A[l] // 2))
                        # Try all midpoints to split range
                        for m in range(l + 2, r, 2):
                            DP[l][r] = min(
                                DP[l][r], max(DP[l][m], DP[m][r] - (m - l) // 2)
                            )

        # Second DP to track possible number of operations
        dp = [[0] * (N + 1) for _ in range(N + 1)]
        dp[0][0] = 1  # Base case: zero operations possible for empty array
        for r in range(1, N + 1):
            for c in range(N + 1):
                # Propagate from previous state
                dp[r][c] |= dp[r - 1][c]
            for l in range(r - 2, -1, -2):  # Go backwards in steps of 2
                # For valid values, propagate state
                for c in range(DP[l][r] + (r - l) // 2, N + 1):
                    dp[r][c] |= dp[l][c - (r - l) // 2]

        ans = 0
        # Find maximum operations possible
        for c in range(N + 1):
            if dp[N][c]:
                ans = max(ans, c)

        print(f"{ans }\n")


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
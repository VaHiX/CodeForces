# Problem: CF 1861 D - Sorting By Multiplication
# https://codeforces.com/contest/1861/problem/D

"""
Algorithm: Dynamic Programming
Time Complexity: O(n)
Space Complexity: O(n)

The approach uses dynamic programming to determine the minimum number of operations 
required to make the array sorted in strictly ascending order. The key idea is to 
precompute the suffix array `dp` where `dp[i]` represents the number of operations 
needed starting from index `i` to the end such that the subarray is sorted. Then, 
for each prefix, we calculate how many operations are needed if we merge the current 
prefix with the rest of the array while maintaining strict ascending order.

We iterate through the array and track the number of violations in the prefix (`res`)
and use the precomputed suffix values (`dp[i + 1]`) to avoid recomputation.
"""

import sys


def solve():
    data = sys.stdin.read().split()
    if not data:
        return
    t = int(data[0])
    pos = 1
    for _ in range(t):
        n = int(data[pos])
        pos += 1
        a = list(map(int, data[pos : pos + n]))
        pos += n
        # dp[i] stores the number of operations needed from index i to end
        dp = [0] * (n + 1)
        for i in range(n - 2, -1, -1):
            # Add 1 if current element is greater than or equal to next
            dp[i] = dp[i + 1] + (a[i] >= a[i + 1])
        ans = dp[0]  # Initial guess: number of operations for whole array
        res = 0      # Count of violations in prefix
        for i in range(1, n):
            # Increment res if current element is >= previous (violation)
            if a[i] >= a[i - 1]:
                res += 1
            # Suffix operations needed starting from i+1
            suf_op = dp[i + 1] if i + 1 < n else 0
            # Try making one operation to fix prefix and remaining suffix
            ans = min(ans, 1 + res + suf_op)
        print(ans)


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/
# Problem: CF 2027 D2 - The Endspeaker (Hard Version)
# https://codeforces.com/contest/2027/problem/D2

"""
D2. The Endspeaker (Hard Version)

Purpose:
This problem involves finding the minimum cost to empty an array `a` using two types of operations:
- Type 1: Increment `k` by 1 (costs 0).
- Type 2: Remove a prefix of `a` whose sum does not exceed `b[k]`, cost is `m - k`.

The solution uses dynamic programming with a sliding window technique to compute both the minimum cost and the number of optimal sequences.

Algorithms/Techniques:
- Dynamic Programming (DP)
- Sliding Window
- Prefix Sum
- Counter for tracking number of ways to achieve states

Time Complexity: O(n * m)
Space Complexity: O(n)

"""

import sys
from collections import *

input = iter(sys.stdin.read().splitlines()).__next__
P = 1000000007


def main():
    T = int(input())
    for _ in range(T):
        n, m = map(int, input().split())
        a = [int(i) for i in input().split()]
        b = [int(i) for i in input().split()]
        a.reverse()
        b.reverse()
        a = [0] + a  # Prefix sum array starts with 0
        for i in range(1, n + 1):
            a[i] += a[i - 1]  # Compute prefix sums
        dp = [1000000] * (n + 1)
        dp[0] = 0
        cnt = [0] * (n + 1)
        cnt[0] = 1  # Initially, there's one way to reach state 0
        for k in range(m):
            l = 0
            c = Counter()
            c[0] = 1  # Initialize counter with base value
            for r in range(1, n + 1):
                # Shrink window while prefix sum exceeds b[k]
                while a[r] - a[l] > b[k]:
                    c[dp[l]] = (c[dp[l]] - cnt[l] + P) % P  # Remove contribution of dp[l]
                    l += 1
                if l == r:
                    break
                # Update dp and cnt if we found better or equal cost path
                if dp[l] + k < dp[r]:
                    dp[r] = dp[l] + k
                    cnt[r] = c[dp[l]]
                elif dp[l] + k == dp[r]:
                    cnt[r] = (cnt[r] + c[dp[l]]) % P
                c[dp[r]] = (c[dp[r]] + cnt[r]) % P  # Add current state to counter
        if dp[n] == 1000000:
            print(-1)
        else:
            print(dp[n], cnt[n])


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/
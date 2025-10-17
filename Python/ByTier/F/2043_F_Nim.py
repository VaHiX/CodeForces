# Problem: CF 2043 F - Nim
# https://codeforces.com/contest/2043/problem/F

"""
F. Nim

Purpose:
This code solves a variant of the Nim game played on segments of an array.
Given a segment [l, r], we calculate:
1. The maximum number of piles Ruslan can remove so that Artem (first player) loses.
2. The number of ways to achieve this.

Technique:
- Uses prefix sums to compute frequency of each value in a range.
- For 0s: If any 0 exists, removing all but one 0 leaves the game in a losing state for first player.
- For non-zero numbers: Use bitmask DP to find minimally removing piles and count such ways.

Time Complexity: O(n * 51 + q * 51 + q * 2^51) in worst case (but optimized via memoization)
Space Complexity: O(n * 51 + 2^51)

"""
import sys

mod = 998244353
oo = 10**18


def main():
    input = sys.stdin.read
    data = input().split()
    ptr = 0
    n = int(data[ptr])
    q = int(data[ptr + 1])
    ptr += 2
    a = list(map(int, data[ptr : ptr + n]))
    ptr += n
    # Precompute prefix sums for each value from 0 to 50
    cnt = [[0] * 51 for _ in range(n + 1)]
    for i in range(n):
        for j in range(51):
            cnt[i + 1][j] = cnt[i][j]
        cnt[i + 1][a[i]] += 1
    mp = {} # Memoization table for bitmask DP
    for _ in range(q):
        l = int(data[ptr]) - 1
        r = int(data[ptr + 1])
        ptr += 2
        c = [0] * 51
        c2 = 0
        # Count occurrences of each value in segment [l, r)
        for i in range(51):
            c[i] = cnt[r][i] - cnt[l][i]
            c2 += c[i] * (c[i] - 1) # Count pairs (used to check if it's game losing state)
        
        # If there are 0s: we can remove all but one
        if c[0] > 0:
            print(r - l - 1, c[0]) # Remove all except one
        # If no 0 and pairs exist, it's a losing game for first player (remove all but 2)
        elif c2 > 0:
            print(r - l - 2, (c2 // 2) % mod)
        else:
            msk = 0 # Bitmask of elements present in current segment
            for i in range(51):
                if c[i]:
                    msk |= 1 << i
            if msk not in mp: # If not computed before
                cnt_dp = [0] * 64 # DP array to store number of ways
                f = [10] * 64 # Minimum piles needed to make XOR = 0
                for i in range(51):
                    if c[i]:
                        # Dynamic programming update
                        for j in range(64):
                            if f[j] > f[i ^ j] + 1:
                                f[j] = f[i ^ j] + 1
                                cnt_dp[j] = cnt_dp[i ^ j]
                            elif f[j] == f[i ^ j] + 1:
                                cnt_dp[j] += cnt_dp[i ^ j]
                                if cnt_dp[j] >= mod:
                                    cnt_dp[j] -= mod
                        # Initialize current value
                        f[i] = 1
                        cnt_dp[i] = 1
                if f[0] == 10: # No way to reach XOR=0, means we cannot force a win
                    mp[msk] = (-1, -1)
                else:
                    # Store result: max removal, count of ways
                    mp[msk] = (r - l - f[0], cnt_dp[0] % mod)
            if mp[msk][0] == -1:
                print(-1)
            else:
                print(mp[msk][0], mp[msk][1])


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/
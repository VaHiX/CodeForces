# Problem: CF 1968 G2 - Division + LCP (hard version)
# https://codeforces.com/contest/1968/problem/G2

"""
Algorithm: Longest Common Prefix (LCP) for K substrings using Z-algorithm and Union-Find
Time Complexity: O(n log n) per test case, where n is the length of the string
Space Complexity: O(n) per test case, for storing Z-array and auxiliary arrays

Approach:
- The key idea is to use the Z-algorithm to compute the longest substring starting at each position that matches a prefix of the string.
- Then, we use a Union-Find data structure to efficiently group positions that can be used for k substrings with a common prefix of length l.
- For each number of substrings k (from l to r), we compute the maximum possible LCP by processing the grouped positions.
- The solution maintains a `g` array where g[k] represents the number of segments of length k that can fit into the string, such that each segment's prefix matches some prefix of the string.
"""

import sys

input = sys.stdin.readline


def z_algo(s):
    # Z-algorithm: computes z[i] = length of the longest substring starting at i that matches a prefix of s
    n = len(s)
    z = [0] * n
    z[0] = n
    l = 0
    r = 0
    for i in range(1, n):
        if i <= r:
            k = min(r - i + 1, z[i - l])  # Use previously computed values when possible
        else:
            k = 0
        while i + k < n and s[k] == s[i + k]:
            k += 1
        z[i] = k
        if i + k - 1 > r:
            l, r = i, i + k - 1  # Update the rightmost segment
    return z


def solve():
    t = int(input())
    for _ in range(t):
        n, l, r = map(int, input().split())
        s = input().strip()
        z = z_algo(s)
        pos_by_z = [[] for _ in range(n + 1)]
        for i, zi in enumerate(z):
            pos_by_z[zi].append(i)
        t_max = n // l  # Maximum possible k value
        parent = [0] * (n + 1)
        for i in range(n):
            parent[i] = i if z[i] >= 1 else i + 1  # Union-Find initialization
        parent[n] = n

        def find(x):
            # Path compression in Union-Find
            while parent[x] != x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x

        g = [0] * (t_max + 2)
        for tval in range(1, t_max + 1):
            if tval > 1:
                # Update union-find structure for new prefix length
                for i in pos_by_z[tval - 1]:
                    parent[i] = find(i + 1)
            cnt = 0
            pos = find(0)
            limit = n - tval  # Limit based on the segment length
            while pos <= limit:
                cnt += 1
                pos = find(pos + tval)  # Jump to next valid position
            g[tval] = cnt  # Number of valid segments for this length

        f = [0] * (r + 2)
        for tval in range(1, t_max + 1):
            hi = g[tval]
            lo = g[tval + 1]
            if lo < hi:
                kl = lo + 1
                kr = min(hi, r)
                for k in range(kl, kr + 1):
                    f[k] = tval  # Assign LCP value to k ranges

        out = (str(f[k]) for k in range(l, r + 1))
        print(" ".join(out))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/
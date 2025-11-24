# Problem: CF 2065 H - Bro Thinks He's Him
# https://codeforces.com/contest/2065/problem/H

# ===================================================================
# Problem: H. Bro Thinks He's Him
# Purpose: For a binary string s, compute the sum of f(b) over all non-empty subsequences b,
#          where f(t) is the minimum number of contiguous identical substrings in t.
#          After each query flipping a bit in s, output the result modulo 998244353.
#
# Algorithm: Segment Tree with lazy propagation for efficient updates and range queries.
#            Each node stores four values (c00, c01, c10, c11) and (s00, s01, s10, s11)
#            representing counts and sums of subsequences ending at certain character types
#            during interval operations.
#
# Time Complexity: O(n log n + q log n)
# Space Complexity: O(n)
# ===================================================================

import sys

input = lambda: sys.stdin.readline().rstrip()
ii = lambda: int(input())
mii = lambda: map(int, input().split())
lii = lambda: list(mii())
MOD = 998244353


class SegmentTree:
    __slots__ = "height", "size", "c00", "c01", "c10", "c11", "s00", "s01", "s10", "s11"

    def __init__(self, nums):
        n = len(nums)
        self.height = (n - 1).bit_length()  # Height of segment tree
        self.size = 1 << self.height       # Size of the segment tree array
        self.c00 = [0] * (2 * self.size)    # Count values for transitions
        self.c01 = [0] * (2 * self.size)
        self.c10 = [0] * (2 * self.size)
        self.c11 = [0] * (2 * self.size)
        self.s00 = [0] * (2 * self.size)    # Sum of f values for subseqs
        self.s01 = [0] * (2 * self.size)
        self.s10 = [0] * (2 * self.size)
        self.s11 = [0] * (2 * self.size)
        # Initialize leaves with binary values
        for idx, val in enumerate(nums, self.size):
            if not val:
                self.c00[idx] = self.s00[idx] = 1
            else:
                self.c11[idx] = self.s11[idx] = 1
        # Build the segment tree from bottom up
        for idx in range(self.size - 1, 0, -1):
            self.pushup(idx)

    def pushup(self, rt):
        # Compute combined values for a node based on left and right child nodes
        ln, rn = rt * 2, rt * 2 + 1
        lc00, lc01, lc10, lc11, ls00, ls01, ls10, ls11 = (
            self.c00[ln],
            self.c01[ln],
            self.c10[ln],
            self.c11[ln],
            self.s00[ln],
            self.s01[ln],
            self.s10[ln],
            self.s11[ln],
        )
        rc00, rc01, rc10, rc11, rs00, rs01, rs10, rs11 = (
            self.c00[rn],
            self.c01[rn],
            self.c10[rn],
            self.c11[rn],
            self.s00[rn],
            self.s01[rn],
            self.s10[rn],
            self.s11[rn],
        )
        # Update count and sum values
        self.c00[rt] = ((lc00 + lc01) * (rc00 + rc10) + lc00 + rc00) % MOD
        self.c01[rt] = ((lc00 + lc01) * (rc01 + rc11) + lc01 + rc01) % MOD
        self.c10[rt] = ((lc10 + lc11) * (rc00 + rc10) + lc10 + rc10) % MOD
        self.c11[rt] = ((lc10 + lc11) * (rc01 + rc11) + lc11 + rc11) % MOD
        self.s00[rt] = (
            (ls00 + ls01) * (rc00 + rc10)
            + (lc00 + lc01) * (rs00 + rs10)
            - lc00 * rc00
            - lc01 * rc10
            + ls00
            + rs00
        ) % MOD
        self.s01[rt] = (
            (ls00 + ls01) * (rc01 + rc11)
            + (lc00 + lc01) * (rs01 + rs11)
            - lc00 * rc01
            - lc01 * rc11
            + ls01
            + rs01
        ) % MOD
        self.s10[rt] = (
            (ls10 + ls11) * (rc00 + rc10)
            + (lc10 + lc11) * (rs00 + rs10)
            - lc10 * rc00
            - lc11 * rc10
            + ls10
            + rs10
        ) % MOD
        self.s11[rt] = (
            (ls10 + ls11) * (rc01 + rc11)
            + (lc10 + lc11) * (rs01 + rs11)
            - lc10 * rc01
            - lc11 * rc11
            + ls11
            + rs11
        ) % MOD

    def inverse(self, idx):
        # Flip the bit at index idx and update affected nodes
        idx += self.size
        self.c00[idx] ^= 1
        self.c11[idx] ^= 1
        self.s00[idx] ^= 1
        self.s11[idx] ^= 1
        for i in range(1, self.height + 1):
            self.pushup(idx >> i)

    def all(self):
        # Return total sum of f over all subsequences
        return (self.s00[1] + self.s01[1] + self.s10[1] + self.s11[1]) % MOD


def solve():
    nums = list(map(int, input()))
    seg = SegmentTree(nums)
    nq = ii()
    ans = [0] * nq
    for qi, idx in enumerate(mii()):
        idx -= 1
        seg.inverse(idx)
        ans[qi] = seg.all()
    return ans


for _ in range(ii()):
    print(*solve())


# https://github.com/VaHiX/codeForces/
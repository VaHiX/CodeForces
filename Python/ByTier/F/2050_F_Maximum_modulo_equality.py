# Problem: CF 2050 F - Maximum modulo equality
# https://codeforces.com/contest/2050/problem/F

# ==============================================================================
# SparseTable_quick class implementation for range queries using Sparse Table
# 
# Purpose:
#   Efficiently answer range queries over a static array using precomputed table.
#   The implementation supports any associative and commutative function (like gcd).
#
# Algorithm:
#   - Preprocessing: Build a sparse table where each entry st[i][j] represents 
#     the result of applying fun to elements from index j to j + 2^i - 1.
#   - Query: For a range [left, right), find the largest power of two k such that
#     2^k <= (right - left). Then use precomputed values to compute the result.
#
# Time Complexity:
#   - Preprocessing: O(N * log N)
#   - Query: O(1)
#
# Space Complexity:
#   - O(N * log N) for storing the sparse table
# ==============================================================================

class SparseTable_quick:
    def __init__(self, lst, fun):
        self.fun = fun
        self.st = st = [list(lst)]  # Initialize with a copy of input list
        i, N = 1, len(st[0])
        # Build the sparse table by doubling the size each time
        while 2 * i <= N + 1:
            qz = st[-1]  # Get the last row
            # For every possible segment of length 2*i, apply function `fun`
            st.append([fun(qz[j], qz[j + i]) for j in range(N - 2 * i + 1)])
            i <<= 1  # Left shift to double i (equivalent to i *= 2)
        return

    def query(self, left, right):
        if left >= right:
            return 0
        lg = (right - left).bit_length() - 1  # Find highest bit set in (right-left)
        # Return the result of combining values from two segments
        return self.fun(self.st[lg][left], self.st[lg][right - (1 << lg)])


from sys import stdin

input = lambda: stdin.buffer.readline().rstrip()
from math import gcd

for _ in range(int(input())):
    n, q = map(int, input().split())
    a = list(map(int, input().split()))
    # Compute differences between adjacent elements
    l = [abs(a[i] - a[i + 1]) for i in range(n - 1)]
    st = SparseTable_quick(l, gcd)  # Build sparse table with GCD function
    ans = [None] * q
    for i in range(q):
        l, r = map(int, input().split())
        ans[i] = str(st.query(l - 1, r - 1))  # Query from 0-based indices
    print(" ".join(ans))


# https://github.com/VaHiX/codeForces/
# Problem: CF 1609 G - A Stroll Around the Matrix
# https://codeforces.com/contest/1609/problem/G

"""
Algorithm/Technique:
This solution uses a combination of prefix sums, Binary Indexed Trees (BIT), and mathematical optimization to handle range updates and queries efficiently on convex arrays.
The key insight is to transform the convex arrays into difference arrays and maintain prefix sums for fast updates.

Time Complexity: O(q * n * log m) where q is the number of operations, n is the size of array a, and m is the size of array b.
Space Complexity: O(n + m) for storing the arrays and BIT structures.

This algorithm supports two operations:
1. Adding an arithmetic progression to a suffix of array a
2. Adding an arithmetic progression to a suffix of array b

For each operation, it calculates the minimum path sum from (1,1) to (n,m) in the matrix where d[i][j] = a[i] + b[j].
The path must only move right or down, so dynamic programming on the matrix gives us a formula involving prefix sums and BIT queries.
"""

import sys

raw_input = sys.stdin.readline


class BIT(object):
    def __init__(self, n):
        self.__bit = [0] * (n + 1)

    def add(self, i, val):
        # Add value 'val' to position 'i' in BIT
        while i < len(self.__bit):
            self.__bit[i] += val
            i += i & -i

    def query(self, i):
        # Return prefix sum up to position 'i'
        ret = 0
        while i > 0:
            ret += self.__bit[i]
            i -= i & -i
        return ret

    def search(self, val):
        # Find the smallest index such that prefix sum >= val
        floor_log2_n = (len(self.__bit) - 1).bit_length() - 1
        pow_i = 2**floor_log2_n
        total = pos = 0
        for _ in reversed(range(floor_log2_n + 1)):
            if pos + pow_i < len(self.__bit) and total + self.__bit[pos + pow_i] < val:
                total += self.__bit[pos + pow_i]
                pos += pow_i
            pow_i >>= 1
        return pos


def solution():
    n, m, q = list(map(int, input().strip().split()))
    arr = list(map(int, input().strip().split()))
    brr = list(map(int, input().strip().split()))
    
    # Transform arrays from convex form to difference arrays for efficient updates
    for i in reversed(range(1, n)):
        arr[i] -= arr[i - 1]
    for i in reversed(range(1, m)):
        brr[i] -= brr[i - 1]
    
    # Precompute initial result using matrix sum formula
    curr = (arr[0] + brr[0]) * (n + m - 1) + sum(brr[i] * (m - i) for i in range(1, m))
    
    # Initialize BIT structures for maintaining prefix sums and range updates
    bit1, bit2, bit3 = BIT(m), BIT(m), BIT(m)
    for i in range(1, m):
        bit1.add(i, brr[i])
        bit1.add(i + 1, -brr[i])
        bit2.add(i, brr[i])
    bit1.add(m, float("inf"))
    result = []
    
    for _ in range(q):
        a, b, c = list(map(int, input().strip().split()))
        if a == 1:
            # Update suffix of array a
            for i in range(b):
                arr[i + (n - b)] += c
            if b == n:
                # Special case when modifying the entire array a
                curr += c * (n + m - 1)
        else:
            # Update suffix of array b
            if b == m:
                curr += c * (n + m - 1)
                b -= 1
            curr += (b) * (b + 1) // 2 * c  # Arithmetic progression sum
            bit1.add(m - b, c)              # Update BIT structures
            bit3.add(m - b, c)
            bit2.add(m - b, -c * (m - b - 1))
        
        # Calculate new minimum path sum
        ans = curr
        for i in range(1, n):
            idx = bit1.search(arr[i])  # Find index using binary search on BIT
            ans += bit3.query(idx) * idx + bit2.query(idx)  # Accumulate prefix sums efficiently
            ans += arr[i] * (n + m - i - idx - 1)  # Add contribution of current element
        result.append(ans)
        
    return "\n".join(map(str, result))


print("%s" % solution())


# https://github.com/VaHiX/CodeForces/
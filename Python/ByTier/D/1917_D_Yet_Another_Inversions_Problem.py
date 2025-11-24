# Problem: CF 1917 D - Yet Another Inversions Problem
# https://codeforces.com/contest/1917/problem/D

"""
Algorithm: Inversion Counting with Fenwick Tree Optimization
Time Complexity: O(n * log(n) + k * log(k))
Space Complexity: O(n + k)

This solution efficiently counts inversions in a constructed array 'a' from two input permutations.
The key insight is to build the array based on p[i] * 2^q[j] and compute inversions using a combination of Fenwick Tree techniques.
"""

from sys import *
input = stdin.readline
inputlist = lambda: map(int, stdin.readline().split())
from math import *

MOD = 998244353


class FenwickTree:
    def __init__(self, n):
        self.n = n
        self.bit = [0] * n

    @classmethod
    def from_array(cls, arr):
        tree = FenwickTree(len(arr))
        for i, v in enumerate(arr):
            tree.update(i, v)
        return tree

    def update(self, idx, delta):
        """Modifies the value at index idx by delta."""
        while idx < self.n:
            self.bit[idx] += delta
            idx |= idx + 1

    def sum(self, right_idx):
        """Calculates the sum for the range [0, right_idx]."""
        res = 0
        while right_idx >= 0:
            res += self.bit[right_idx]
            right_idx = (right_idx & (right_idx + 1)) - 1
        return res

    def sum2(self, left_index, right_idx):
        """Calculates the sum for the range [left_idx, right_idx]."""
        return self.sum(right_idx) - self.sum(left_index - 1)


def solve():
    n, k = inputlist()
    p = list(inputlist())
    q = list(inputlist())
    answer = 0

    # Initialize Fenwick Tree for odd numbers up to 2n-1
    tree = FenwickTree(2 * n)
    for i in range(1, 2 * n, 2):
        tree.update(i, 1)
    
    # Process p in forward order
    for i in p:
        left, right = i + 1, min(2 * n - 1, 2 * i)
        diff = 1
        while left != 2 * n - 1 and diff < k:
            count = tree.sum2(left, right)
            # Calculate contribution of inversion with current element
            answer = (answer + count * (k - diff) * (k - diff + 1) // 2) % MOD
            left, right = right, min(2 * n - 1, 2 * right)
            diff += 1
        tree.update(i, -1)

    # Re-initialize Fenwick Tree
    for i in range(1, 2 * n, 2):
        tree.update(i, 1)
    
    # Process p in reverse order
    for i in reversed(p):
        left, right = i + 1, min(2 * n - 1, 2 * i)
        diff = 1
        while left != 2 * n - 1:
            count = tree.sum2(left, right)
            if diff < k:
                # Calculate contribution of inversion with current element
                answer = (
                    answer + count * (k * k - (k - diff) * (k - diff + 1) // 2)
                ) % MOD
            else:
                answer = answer + count * k * k % MOD
            left, right = right, min(2 * n - 1, 2 * right)
            diff += 1
        tree.update(i, -1)

    # Handle q permutations
    temp = 0
    tree = FenwickTree(k)
    for i in q:
        temp += tree.sum2(i, k - 1)
        tree.update(i, 1)

    # Final calculation
    return (answer + temp * n) % MOD


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/CodeForces/
# Problem: CF 1983 D - Swap Dilemma
# https://codeforces.com/contest/1983/problem/D

"""
Code Purpose:
This solution determines whether two arrays can be made identical through a specific swapping operation.
The operation allows swapping elements in array 'a' and corresponding elements in array 'b' such that the length of the swap ranges are equal.
The approach is based on transforming the problem into a parity check of inversions.

Algorithms/Techniques:
1. Use of Fenwick Tree (Binary Indexed Tree) for efficient range updates and prefix sums.
2. Transform array 'b' into a permutation of indices in array 'a'.
3. For each element in transformed 'b', calculate how many elements in the prefix of 'a' are greater than current element (inversion count).
4. The sum of all such inversion counts determines the total number of inversions, which must be even for the arrays to be made equivalent.

Time Complexity: O(n log n) per test case due to Fenwick Tree operations.
Space Complexity: O(n) for storing the arrays and Fenwick Tree.

"""
import sys

input = sys.stdin.readline


class FenwickTree:
    def __init__(self, n):
        self.n = n
        self.data = [0] * n

    def build(self, arr):
        # Build the Fenwick tree from an array
        for i, a in enumerate(arr):
            self.data[i] = a
        for i in range(1, self.n + 1):
            if i + (i & -i) <= self.n:
                self.data[i + (i & -i) - 1] += self.data[i - 1]

    def add(self, p, x):
        # Add value x at position p in the Fenwick Tree
        p += 1
        while p <= self.n:
            self.data[p - 1] += x
            p += p & -p

    def sum(self, r):
        # Compute prefix sum up to index r
        s = 0
        while r:
            s += self.data[r - 1]
            r -= r & -r
        return s

    def range_sum(self, l, r):
        # Compute sum in range [l, r)
        return self.sum(r) - self.sum(l)


for _ in range(int(input())):
    n = int(input())
    A = list(map(int, input().split()))
    B = list(map(int, input().split()))
    FW = FenwickTree(n + 1)
    D = dict()
    f = 0
    # Map elements in A to their indices
    for i in range(n):
        D[A[i]] = i
    Z = []
    # Transform B into a sequence of indices in A
    for i in range(n):
        if B[i] not in D:
            f = 1
            break
        Z.append(D[B[i]])
    if f:
        print("NO")
        continue
    sm = 0
    # Calculate inversion count using Fenwick Tree
    for i, v in enumerate(Z):
        sm += i - FW.sum(v)
        FW.add(v, 1)
    # If total inversion count is odd, arrays cannot be made same
    if sm % 2:
        print("NO")
    else:
        print("YES")


# https://github.com/VaHiX/CodeForces/
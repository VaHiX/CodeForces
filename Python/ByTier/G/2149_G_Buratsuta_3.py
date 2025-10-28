# Problem: CF 2149 G - Buratsuta 3
# https://codeforces.com/contest/2149/problem/G

"""
G. Buratsuta 3

Purpose:
This problem involves finding elements in subarrays that appear more than a certain threshold,
which is calculated as floor((r - l + 1) / 3). A segment tree with frequency merging is used to efficiently process queries.

Algorithms/Techniques:
- Segment Tree with Map-based Frequency Merging
- Bit manipulation with randomization for hashing
- Binary search (bisect_left and bisect_right) for fast range queries

Time Complexity:
- Construction of Segment Tree: O(n)
- Query Operation: O(log n * log n) due to merge operation on maps and binary search
- Overall per test case: O(n + q * log n * log n)

Space Complexity:
- Segment Tree storage: O(n)
- Hash map storage for values: O(n)
- Additional space for bisect operations and auxiliary structures: O(n)

"""

import sys

input = lambda: sys.stdin.readline().rstrip()
import random
from bisect import bisect_left, bisect_right
from collections import defaultdict

RD = random.getrandbits(30)  # Random number for hashing


def II(base=10):
    return int(input(), base)


def LI():
    return list(map(int, input()))


def LII():
    return list(map(int, input().split()))


class Seg:
    def __init__(self, N):
        self.N = N  # Size of segment tree
        self.t = [{} for _ in range(N * 2)]  # Segment tree with maps

    def merge(self, a, b):
        """
        Merge two frequency maps.
        If merged size exceeds 3, remove the smallest count and adjust others accordingly.
        """
        res = b.copy()
        for x in a:
            res[x] = a[x] + res.get(x, 0)
            if len(res) == 3:
                w = min(res.values())
                # Reduce all values by minimum to maintain relative frequencies
                res = {y: w2 - w for y, w2 in res.items() if w2 > w}
        return res

    def up(self, o):
        """Update parent node from children."""
        self.t[o] = self.merge(self.t[o * 2], self.t[o * 2 + 1])

    def build(self, A):
        """Build the segment tree with initial values."""
        for i, a in enumerate(A):
            self.t[self.N + 1 + i] = {a: 1}  # Each leaf node holds one value
        for o in range(self.N - 1, 0, -1):
            self.up(o)  # Build up from leaves to root

    def query(self, a, b):
        """
        Query the frequency map over interval [a, b].
        Uses standard segment tree traversal.
        """
        a, b = a + self.N - 1, b + self.N + 1
        lres, rres = {}, {}
        while a ^ b ^ 1:
            if not a & 1:
                lres = self.merge(lres, self.t[a ^ 1])
            if b & 1:
                rres = self.merge(self.t[b ^ 1], rres)
            a, b = a >> 1, b >> 1
        return self.merge(lres, rres)


def main():
    n, q = LII()
    A = LII()
    Q = [LII() for _ in range(q)]
    
    # Create a mapping from XORed keys to indices
    d = defaultdict(list)
    for i, a in enumerate(A):
        d[a ^ RD].append(i)

    seg = Seg(1 << (n + 1).bit_length())  # Build segment tree with size just larger than n
    seg.build(A)  # Construct segment tree from A

    for l, r in Q:
        # Query frequency map over [l, r]
        ct = seg.query(l, r)
        l, r = l - 1, r - 1  # Convert to 0-based indexing
        t = (r - l + 1) // 3  # Threshold for occurrences
        
        res = []
        for x in ct:
            B = d[x ^ RD]  # Get indices of all occurrences of x in original array
            i, j = bisect_left(B, l), bisect_right(B, r)  # Find count of x in range [l,r]
            if j - i > t:  # If it's more than threshold
                res.append(x)
        
        if res:
            print(*sorted(res))  # Print sorted results
        else:
            print(-1)


for _ in range(II()):
    main()


# https://github.com/VaHiX/CodeForces/
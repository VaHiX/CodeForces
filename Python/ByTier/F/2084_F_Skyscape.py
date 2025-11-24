# Problem: CF 2084 F - Skyscape
# https://codeforces.com/contest/2084/problem/F

"""
F. Skyscape

Algorithm:
This problem involves determining whether a given permutation B can be derived from permutation A through a specific operation — cyclically shifting segments where the rightmost element is the minimum in that segment. We use segment trees to efficiently compute valid positions for elements and greedy matching to build the result.

Time Complexity: O(n log n) per test case due to use of segment trees and heaps.
Space Complexity: O(n) for storage of segment trees, arrays, and other supporting data structures.

Techniques:
- Segment Trees for range queries and updates
- Greedy approach with priority queues
- Preprocessing positions of elements in B
"""

import sys
from heapq import heappop, heappush

input = lambda: sys.stdin.buffer.readline()
mi = lambda: map(int, input().split())
li = lambda: list(mi())


class SegmentTree:
    def __init__(self, init_val, segfunc, ide_ele):
        n = len(init_val)
        self.segfunc = segfunc
        self.ide_ele = ide_ele
        self.num = 1 << (n - 1).bit_length()
        self.tree = [ide_ele] * 2 * self.num
        self.size = n
        for i in range(n):
            self.tree[self.num + i] = init_val[i]
        for i in range(self.num - 1, 0, -1):
            self.tree[i] = self.segfunc(self.tree[2 * i], self.tree[2 * i + 1])

    def update(self, k, x):
        k += self.num
        self.tree[k] = x
        while k > 1:
            k >>= 1
            self.tree[k] = self.segfunc(self.tree[2 * k], self.tree[2 * k + 1])

    def query(self, l, r):
        if r == self.size:
            r = self.num
        res = self.ide_ele
        l += self.num
        r += self.num
        while l < r:
            if l & 1:
                res = self.segfunc(res, self.tree[l])
                l += 1
            if r & 1:
                res = self.segfunc(res, self.tree[r - 1])
            l >>= 1
            r >>= 1
        return res


def solve(N, A, B):
    # Adjust indices to be 0-based
    for i in range(N):
        A[i] -= 1
        B[i] -= 1
    
    # Preprocessing: track the position of each element in B
    pos_on_B = [-1] * N
    for i in range(N):
        if B[i] != -1:
            pos_on_B[B[i]] = i

    # Initialize segment tree to keep track of rightmost occurrence of elements in a valid way.
    seg0 = SegmentTree([-1] * N, max, -1)
    
    # lmin[i] stores the minimum valid position where we could place element i in result array
    lmin = [-1] * N
    
    # rmax[i] stores the maximum valid position where we could place element i in result array
    rmax = [-1] * N

    # Forward pass to compute lmin values based on earlier positions
    for i in range(N):
        if pos_on_B[A[i]] == -1:  # i-th element of A has not been placed yet
            lmin[A[i]] = seg0.query(0, A[i]) + 1
            continue
        check = seg0.query(0, A[i])
        if check > pos_on_B[A[i]]:
            return (False, [])
        seg0.update(A[i], pos_on_B[A[i]])

    # Backward pass to compute rmax values
    seg1 = SegmentTree([N] * N, min, N)
    for i in range(N)[::-1]:
        if pos_on_B[A[i]] == -1:  # i-th element of A has not been placed yet
            rmax[A[i]] = seg1.query(A[i] + 1, N) - 1
        else:
            seg1.update(A[i], pos_on_B[A[i]])

    # Group elements by their required leftmost position into list l_to_rv
    l_to_rv = [[] for _ in range(N)]
    for i in range(N):
        if pos_on_B[A[i]] != -1:
            continue  # This value was already fixed
        if lmin[A[i]] == N:  # Invalid assignment
            return (False, [])
        l_to_rv[lmin[A[i]]].append((rmax[A[i]], A[i]))

    pq = []  # Priority queue for valid rightmost candidates
    res = B[:]

    # Construct final array using greedy selection from priority queue
    for i in range(N):
        # Add all items that can be considered at position i
        for r, val in l_to_rv[i]:
            heappush(pq, r * N + val)
        
        if B[i] != -1:
            continue  # Already determined

        if not pq:
            return (False, [])

        # Pop from priority queue and assign
        rv = heappop(pq)
        r, val = rv // N, rv % N
        if r < i:  # Assignment invalid due to constraints
            return (False, [])
        res[i] = val

    return (True, [x + 1 for x in res])


for _ in range(int(input())):
    N = int(input())
    A = li()
    B = li()
    flg, res = solve(N, A, B)
    if not flg:
        print(-1)
    else:
        print(*res)


# https://github.com/VaHiX/codeForces/
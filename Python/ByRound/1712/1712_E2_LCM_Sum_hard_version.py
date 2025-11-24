# Problem: CF 1712 E2 - LCM Sum (hard version)
# https://codeforces.com/contest/1712/problem/E2

"""
Purpose: Count the number of triplets (i, j, k) such that l <= i < j < k <= r and lcm(i,j,k) >= i + j + k.

Algorithm:
- Uses a segment tree to efficiently maintain and query counts of divisors.
- Preprocesses the number of divisors for each number.
- For each query (l, r), computes:
  1. Total number of triplets in range [l, r]
  2. Subtracts invalid triplets based on divisor conditions using prefix sums and segment tree.

Time Complexity: O(N log N + Q log N) where N = 2e5 and Q = 1e5
Space Complexity: O(N) for arrays and segment tree storage.
"""

import sys

input = sys.stdin.readline


class SegmentTree:
    def __init__(self, a, n):
        size = 1
        while size < n:
            size *= 2
        self.size = size
        self.tree = [0 for i in range(2 * size)]
        # Initialize leaf nodes with (count[i] - 1) * (count[i] - 2) // 2
        for i in range(size, n + size):
            self.tree[i] = (a[i - size] - 1) * (a[i - size] - 2) // 2
        # Build the tree bottom-up
        for i in range(size - 1, 0, -1):
            self.tree[i] = self.tree[2 * i] + self.tree[2 * i + 1]

    def set(self, i, v):
        # Update the value at index i
        i += self.size
        self.tree[i] = max(v, 0)
        i //= 2
        # Propagate the update upward
        while i > 0:
            left = 2 * i
            right = 2 * i + 1
            m1 = self.tree[left]
            m2 = self.tree[right]
            self.tree[i] = m1 + m2
            i //= 2

    def query(self, l, r):
        # Compute sum in range [l, r)
        l += self.size
        r += self.size
        s = 0
        while l < r:
            if l & 1:
                s += self.tree[l]
                l += 1
            if r & 1:
                r -= 1
                s += self.tree[r]
            l >>= 1
            r >>= 1
        return s


N = int(2e5) + 1
count, pref2, pref3 = [0] * N, [0] * N, [0] * N

# Count divisors for each number from 1 to N
for i in range(1, N):
    for j in range(i, N, i):
        count[j] += 1
    # Marking indices divisible by 6 for pref2
    if i % 6 == 0:
        pref2[i] += 1
    # Marking indices divisible by 15 for pref3
    if i % 15 == 0:
        pref3[i] += 1

# Compute prefix sums
for i in range(1, N):
    pref2[i] += pref2[i - 1]
    pref3[i] += pref3[i - 1]

# Build segment tree based on divisor counts
seg = SegmentTree(count, N)
size = 1
while size < N:
    size *= 2

q = int(input())
queries = []
for i in range(q):
    a, b = [int(x) for x in input().split()]
    queries.append([a, b, i])

# Sort queries by left bound for offline processing
queries.sort()
ans = [0] * q

last = 1
for a, b, idx in queries:

    # Update count of divisors for all numbers from last to a - 1
    while last < a:
        for j in range(last, N, last):
            old = count[j]
            new = old - 1
            seg.set(j, (new - 1) * (new - 2) // 2)
            count[j] = new
        last += 1

    # Total number of triplets in [a, b]
    n = b - a + 1
    tot = n * (n - 1) * (n - 2) // 6

    # Use segment tree to subtract invalid triplets
    p1 = seg.query(a + 2, b + 1)
    
    # Subtract triplets with specific gcd properties
    p2 = max(pref2[b] - pref2[2 * a - 1], 0) if 2 * a - 1 < N else 0
    p3 = max(pref3[b] - pref3[15 * a // 6 - 1], 0) if 15 * a // 6 - 1 < N else 0

    tot -= p1 + p2 + p3
    ans[idx] = tot

for i in ans:
    sys.stdout.write(str(i) + "\n")


# https://github.com/VaHiX/CodeForces/
# Problem: CF 2150 C - Limited Edition Shop
# https://codeforces.com/contest/2150/problem/C

"""
C. Limited Edition Shop

Algorithm/Techniques:
- Dynamic Programming with Segment Tree and Binary Indexed Tree (BIT)
- The problem involves simulating a game between Alice and Bob where they pick items in their preference order,
  and we want to find the maximum value of items Alice can collect.
- We use a segment tree with lazy propagation to maintain prefix maxima and BIT for counting
- Time Complexity: O(n log n) per test case
- Space Complexity: O(n) per test case

Approach:
1. For each possible state, we compute the best score Alice can get.
2. We simulate the process of Alice and Bob picking items in their order.
3. The DP state is computed such that dp[i] represents the maximum value sum of objects collected up to position i.
4. Segment Tree supports efficient range max queries with lazy propagation.
5. BIT helps in efficiently computing prefix sums for counting purposes.

"""

class segtreemax:
    def __init__(self, n):
        self.size = 1
        while self.size < n:
            self.size *= 2
        self.dat = [-(10**15)] * (self.size * 2)

    def update(self, x, a):
        x += self.size
        self.dat[x] = a
        while x > 1:
            x //= 2
            self.dat[x] = max(self.dat[2 * x], self.dat[2 * x + 1])

    def querry(self, u, v):
        u += self.size
        v += self.size
        score = -(10**15)
        while u < v:
            if u & 1:
                score = max(score, self.dat[u])
                u += 1
            if v & 1:
                v -= 1
                score = max(score, self.dat[v])
            u //= 2
            v //= 2
        return score


class segtree:
    def __init__(self, n, A):
        self.size = 1
        self.height = 0
        while self.size < n:
            self.size *= 2
            self.height += 1
        self.dat = [0] * (self.size * 2)
        for i in range(len(A)):
            self.dat[self.size + i] = A[i]
            if i > 0:
                self.dat[self.size + i] -= 10**15
        for i in range(self.size - 1, 0, -1):
            self.dat[i] = max(self.dat[2 * i], self.dat[2 * i + 1])
        self.lazy = [0] * (self.size * 2)

    def lazyup(self, l, r, a):
        l += self.size
        r += self.size
        while l < r:
            if l & 1:
                self.lazy[l] += a
                l += 1
            if r & 1:
                r -= 1
                self.lazy[r] += a
            l //= 2
            r //= 2

    def querry(self, l, r):
        l += self.size
        r += self.size
        score = -(10**17)
        while l < r:
            if l & 1:
                w = self.dat[l] + self.lazy[l]
                score = max(score, w)
                l += 1
            if r & 1:
                r -= 1
                w = self.dat[r] + self.lazy[r]
                score = max(score, w)
            l //= 2
            r //= 2
        return score

    def propagate(self, x):
        x += self.size
        for h in range(self.height, 0, -1):
            y = x >> h
            self.lazy[2 * y] += self.lazy[y]
            self.lazy[2 * y + 1] += self.lazy[y]
            self.dat[y] += self.lazy[y]
            self.lazy[y] = 0

    def bottom(self, x):
        x += self.size
        while x > 1:
            x //= 2
            self.dat[x] = max(
                self.dat[2 * x] + self.lazy[2 * x],
                self.dat[2 * x + 1] + self.lazy[2 * x + 1],
            )


class Bit:
    def __init__(self, n):
        self.size = n
        self.tree = [0] * (n + 1)

    def sum(self, i):
        s = 0
        while i > 0:
            s += self.tree[i]
            i -= i & -i
        return s

    def add(self, i, x):
        while i <= self.size:
            self.tree[i] += x
            i += i & -i


import sys

input = sys.stdin.readline
Q = int(input())
for _ in range(Q):
    N = int(input())
    A = list(map(int, input().split()))
    B = list(map(int, input().split()))
    C = list(map(int, input().split()))
    P = [0] * N
    L = [0] * N
    h = [0] * (N + 1)
    for i in range(N):
        h[B[i]] = i
        P[i] = A[B[i] - 1]
    for i in range(N):
        L[i] = h[C[i]] + 1
    v = [0] * (N + 1)
    for i in range(N - 1, -1, -1):
        v[i] = v[i + 1] + P[i]
    Z = segtree(N + 1, v)
    result = 0
    dp = [0] * (N + 1)
    R = Bit(N + 2)
    for i in range(N):
        pos = L[i]
        Z.propagate(0)
        Z.propagate(pos - 1)
        score = Z.querry(0, pos)
        count = R.sum(N + 1 - pos)
        ans = score - v[pos] + count
        dp[pos] = ans
        y = P[pos - 1]
        Z.lazyup(0, pos, -y)
        Z.propagate(pos)
        Z.lazyup(pos, pos + 1, ans + 10**15)
        Z.bottom(pos)
        R.add(N + 1 - pos, y)
        result = max(result, ans)
        dp[pos] = ans
    print(result)



# https://github.com/VaHiX/CodeForces/
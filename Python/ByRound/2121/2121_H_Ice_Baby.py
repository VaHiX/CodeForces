# Problem: CF 2121 H - Ice Baby
# https://codeforces.com/contest/2121/problem/H

"""
Algorithm: Dynamic Programming + Coordinate Compression + Fenwick Tree
Purpose: For each k from 1 to n, find the maximum length of the longest non-decreasing subsequence among all possible arrays of length k, where each element a_i satisfies l_i <= a_i <= r_i.

Approach:
1. Coordinate compress the values of l_i and r_i to reduce space.
2. Use a Fenwick tree to maintain the count of elements in different ranges.
3. For each element in the input, update the Fenwick tree and compute the maximum possible length of non-decreasing subsequence.
4. The key insight is to use a greedy approach with Fenwick tree to track the longest non-decreasing subsequence efficiently.

Time Complexity: O(n * log(n) * log(max_range))
Space Complexity: O(n * log(max_range))
"""

import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
import random

ran = random.randint(1, 10**9)


class fenwick(object):
    def __init__(self, n):
        self.n = n
        self.cul = [0] * n
        self.maxd = len(bin(n)) - 3

    def update(self, index, diff):
        i = index
        while i < self.n:
            self.cul[i] += diff
            i += (i + 1) & (-i - 1)

    def getaccu(self, index):
        output = 0
        i = index
        while i >= 0:
            output += self.cul[i]
            i -= (i + 1) & (-i - 1)
        return output

    def search(self, target):
        accunum = 0
        accuindex = 0
        for i in range(self.maxd, -1, -1):
            d = 1 << i
            if accuindex + d > self.n:
                continue
            if accunum + self.cul[accuindex + d - 1] <= target:
                accunum += self.cul[accuindex + d - 1]
                accuindex += d
        return accuindex


def main():
    n = int(input())
    data = []
    temp = []
    for _ in range(n):
        l, r = map(int, input().split())
        data.append((l, r))
        temp.append(l)
        temp.append(r)
    temp.sort()
    mapping = {}
    for num in temp:
        if num ^ ran in mapping:
            continue
        mapping[num ^ ran] = len(mapping)

    m = len(mapping)

    fen = fenwick(m + 1)
    fen.update(m, 1)

    ans = []
    for l, r in data:
        i1 = mapping[l ^ ran]
        i2 = mapping[r ^ ran]
        fen.update(i1, 1)
        tot = fen.getaccu(i2)
        if fen.search(tot) < m:
            fen.update(fen.search(tot), -1)
        if not ans:
            ans.append(tot)
        else:
            ans.append(max(ans[-1], tot))

    print(*ans)


T = int(input())
t = 1
while t <= T:
    main()
    t += 1


# https://github.com/VaHiX/CodeForces/
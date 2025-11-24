# Problem: CF 1690 G - Count the Trains
# https://codeforces.com/contest/1690/problem/G

"""
Algorithm: 
- Use a SortedList (custom implementation) to maintain carriages in order of their speeds
- For each message, update the speed of a carriage and rebalance the trains by removing and inserting carriages as needed
- After each update, count the number of trains by the number of elements in the sorted list

Time Complexity: O(m * log^2(n)) where m is the number of messages and n is the number of carriages
Space Complexity: O(n) for storing the carriages and their speeds

The code maintains a sorted list of carriages by their maximum speeds using a custom SortedList
implementation with block-based structure and Fenwick tree for efficient range queries.
Each message updates a carriage's speed and then recalculates which trains exist by
maintaining a sorted list of carriage indices and their corresponding speeds.
After each update, the number of trains (elements in the sorted list) is the answer.
"""

import sys
from bisect import bisect_left as lower_bound
from bisect import bisect_right as upper_bound


class FenwickTree:
    def __init__(self, x):
        bit = self.bit = list(x)
        size = self.size = len(bit)
        for i in range(size):
            j = i | (i + 1)
            if j < size:
                bit[j] += bit[i]

    def update(self, idx, x):
        """updates bit[idx] += x"""
        while idx < self.size:
            self.bit[idx] += x
            idx |= idx + 1

    def __call__(self, end):
        """calc sum(bit[:end])"""
        x = 0
        while end:
            x += self.bit[end - 1]
            end &= end - 1
        return x

    def find_kth(self, k):
        """Find largest idx such that sum(bit[:idx]) <= k"""
        idx = -1
        for d in reversed(range(self.size.bit_length())):
            right_idx = idx + (1 << d)
            if right_idx < self.size and self.bit[right_idx] <= k:
                idx = right_idx
                k -= self.bit[idx]
        return idx + 1, k


block_size = 700


class SortedList:
    def __init__(self):
        self.macro = []
        self.micros = [[]]
        self.micro_size = [0]
        self.fenwick = FenwickTree([0])
        self.size = 0

    def insert(self, x):
        i = lower_bound(self.macro, x)
        j = upper_bound(self.micros[i], x)
        self.micros[i].insert(j, x)
        self.size += 1
        self.micro_size[i] += 1
        self.fenwick.update(i, 1)
        if len(self.micros[i]) >= block_size:
            self.micros[i : i + 1] = (
                self.micros[i][: block_size >> 1],
                self.micros[i][block_size >> 1 :],
            )
            self.micro_size[i : i + 1] = block_size >> 1, block_size >> 1
            self.fenwick = FenwickTree(self.micro_size)
            self.macro.insert(i, self.micros[i + 1][0])

    def pop(self, k=0):
        i, j = self._find_kth(k)
        self.size -= 1
        self.micro_size[i] -= 1
        self.fenwick.update(i, -1)
        return self.micros[i].pop(j)

    def __getitem__(self, k):
        i, j = self._find_kth(k)
        return self.micros[i][j]

    def count(self, x):
        return self.upper_bound(x) - self.lower_bound(x)

    def __contains__(self, x):
        return self.count(x) > 0

    def lower_bound(self, x):
        i = lower_bound(self.macro, x)
        return self.fenwick(i) + lower_bound(self.micros[i], x)

    def upper_bound(self, x):
        i = upper_bound(self.macro, x)
        return self.fenwick(i) + upper_bound(self.micros[i], x)

    def _find_kth(self, k):
        return self.fenwick.find_kth(k + self.size if k < 0 else k)

    def __len__(self):
        return self.size

    def __iter__(self):
        return (x for micro in self.micros for x in micro)

    def __repr__(self):
        return str(list(self))


def solve():
    n, m = map(int, input().split())
    A = [-int(x) for x in input().split()]
    V, I = SortedList(), SortedList()

    prev = float("-inf")
    for i in range(n):
        if A[i] > prev:
            I.insert(i)
            V.insert(A[i])
            prev = A[i]

    res = []
    for _ in range(m):
        k, d = map(int, input().split())
        k -= 1
        A[k] += d

        i = I.lower_bound(k)
        if (i > 0 and V[i - 1] < A[k]) or (i < len(V) and V[i] <= A[k]):
            while i < len(V) and V[i] <= A[k]:
                V.pop(i)
                I.pop(i)
            I.insert(k)
            V.insert(A[k])

        ans = len(V)
        res.append(ans)

    return res


input = lambda: sys.stdin.readline().rstrip()
for _ in range(int(input())):
    input()
    res = solve()
    print(" ".join(str(x) for x in res))


# https://github.com/VaHiX/CodeForces/
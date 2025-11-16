# Problem: CF 1777 F - Comfortably Numb
# https://codeforces.com/contest/1777/problem/F

"""
Algorithm: Optimized approach using Cartesian Tree and Binary Trie
Time Complexity: O(n log n) per test case
Space Complexity: O(n) per test case

The problem involves finding the maximum "numbness" over all subarrays,
where numbness is defined as max(a_l, ..., a_r) XOR (a_l XOR ... XOR a_r).
We use a Cartesian tree and binary trie to efficiently process subarrays
and compute the maximum XOR values.

Approach:
1. Build a Cartesian tree of the array (based on values)
2. Process nodes in increasing order of values
3. For each node, maintain a trie of prefix XORs
4. Use trie to query maximum XOR for relevant range of elements
5. Merge subtrees in the trie when processing nodes

This solution efficiently handles the constraints and computes the result
using advanced data structures and tree-based optimization techniques.
"""

import operator
import sys
from bisect import *
from collections import *
from functools import *
from heapq import *
from itertools import *
from math import *
from string import *

input = sys.stdin.readline


class BinaryTrie:
    def __init__(self):
        self.nodes = []

    def get_new_node(self):
        self.nodes.append([-1, -1])
        return len(self.nodes) - 1

    def create_trie(self, val):
        curr = root = self.get_new_node()

        for k in range(30, -1, -1):
            nxt = self.get_new_node()
            self.nodes[curr][(val >> k) & 1] = nxt
            curr = nxt

        return root

    def query_max(self, curr, target):
        ans = 0

        for i in range(30, -1, -1):
            bit = (target >> i) & 1
            target_bit = bit ^ 1
            if self.nodes[curr][target_bit] != -1:
                ans ^= 1 << i
                curr = self.nodes[curr][target_bit]
            else:
                curr = self.nodes[curr][bit]

        return ans

    def query_min(self, target):
        return self.query_max(~target)

    def merge_into(self, u, v):
        if u == -1:
            return v
        if v == -1:
            return u
        for c in range(2):
            self.nodes[u][c] = self.merge_into(self.nodes[u][c], self.nodes[v][c])
        return u


def upper_bound(lo, hi, key):
    while lo <= hi:
        mid = (lo + hi) // 2
        if key(mid):
            lo = mid + 1
        else:
            hi = mid - 1
    return hi


def highest_int(x):
    if x < 0:
        return 0
    if x == 0:
        return 1
    return upper_bound(0, 32, key=lambda pw: (1 << pw) <= x)


class RMQ:
    def __init__(self, A):
        n = len(A)

        self.values = A[:]
        level = highest_int(n) + 1
        self.jump = [[] for _ in range(level)]

        for k in range(level):
            self.jump[k] = [-1] * (n - (2**k) + 1)

        for i in range(n):
            self.jump[0][i] = i

        for k in range(1, level):
            x = 2 ** (k - 1)
            for i in range(len(self.jump[k])):
                self.jump[k][i] = self.better_index(
                    self.jump[k - 1][i], self.jump[k - 1][i + x]
                )

    def better_index(self, a, b):
        return a if self.values[a] < self.values[b] else b

    def query_index(self, a, b):
        assert 0 <= a < b <= len(self.values)
        level = highest_int(b - a)
        return self.better_index(
            self.jump[level][a], self.jump[level][b - (1 << level)]
        )

    def query_value(self, a, b):
        return self.values[self.query_index(a, b)]


def build_cartesian_tree(A):
    N = len(A)
    rmq = RMQ([-x for x in A])
    root = -1
    adj = [[] for _ in range(N)]
    span = [None] * N

    stack = [(0, N - 1, -1)]
    while stack:
        lo, hi, par = stack.pop()

        if lo > hi:
            continue
        argmax = rmq.query_index(lo, hi + 1)
        span[argmax] = [lo - 1, hi + 1]

        if par == -1:
            root = argmax
        if par != -1:
            adj[par].append(argmax)

        stack.append((lo, argmax - 1, argmax))
        stack.append((argmax + 1, hi, argmax))

    return adj, span, root


def solve():
    N = int(input())
    A = list(map(int, input().split()))
    P = list(accumulate(A, operator.__xor__, initial=0))
    adj, span, root = build_cartesian_tree(A)

    ans = 0
    trie = BinaryTrie()
    roots = [None] * N

    def get_subtrees(u):
        left_tree = right_tree = -1

        for v in adj[u]:
            if v < u:
                assert left_tree == -1
                left_tree = roots[v]
            elif u < v:
                assert right_tree == -1
                right_tree = roots[v]
            else:
                assert False

        if left_tree == -1:
            left_tree = trie.create_trie(P[u])
        if right_tree == -1:
            right_tree = trie.create_trie(P[u + 1])

        return left_tree, right_tree

    for u in sorted(range(N), key=lambda i: A[i]):
        smaller, larger = get_subtrees(u)
        left, right = span[u]
        args = (left + 1, u + 1)

        if right - u < u - left:
            smaller, larger = larger, smaller
            args = (u + 1, right + 1)

        for i in range(*args):
            ans = max(ans, trie.query_max(larger, P[i] ^ A[u]))

        roots[u] = trie.merge_into(larger, smaller)

    print(ans)


def main():
    tests = int(input())
    for _ in range(tests):
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
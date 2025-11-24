# Problem: CF 1930 G - Prefix Max Set Counting
# https://codeforces.com/contest/1930/problem/G

"""
Code Purpose:
This code solves the problem of counting the number of distinct prefix maxima arrays (f(a)) over all possible pre-orders of a given tree.
The algorithm uses a combination of tree traversal, Fenwick tree (Binary Indexed Tree), and stack-based processing to determine the count efficiently.

Algorithms/Techniques:
- Tree traversal using DFS to compute parent relationships and path maxima
- Fenwick Tree (Binary Indexed Tree) for efficient range sum queries and updates
- Stack-based processing to handle the ordering constraints of pre-order traversal in trees

Time Complexity: O(n log n) per test case, where n is the number of nodes in the tree.
Space Complexity: O(n) for storing tree structure, traversal order, and Fenwick tree.

"""

from sys import stdin


def read_tree():
    n = int(stdin.readline())
    tree = [[] for i in range(n)]
    for i in range(n - 1):
        a, b = [int(w) - 1 for w in stdin.readline().split()]
        tree[a].append(b)
        tree[b].append(a)
    return tree


class FenwickTree:
    def __init__(self, data, copy_data=True):
        if isinstance(data, int):
            self.data = [0] * data
        else:
            self.data = data.copy() if copy_data else data
            size = len(self.data)
            for i in range(size - 1):
                p = i | (i + 1)
                if p < size:
                    self.data[p] += self.data[i]
        w = 1
        while w < len(self.data):
            w <<= 1
        self.w = w

    def bound(self, s):

        data = self.data
        n = len(data)
        if s <= 0 or n == 0:
            return 0
        lsum = 0
        l = 0
        w = self.w >> 1
        while w > 0:
            if l + w <= n and lsum + data[l + w - 1] < s:
                lsum += data[l + w - 1]
                l += w
            w >>= 1
        return l + 1

    def add(self, i, val):
        n = len(self.data)
        while i < n:
            self.data[i] += val
            i |= i + 1

    def get(self, i):
        data = self.data
        result = data[i]
        shift = 1
        while i & shift:
            result -= data[i ^ shift]
            shift <<= 1
        return result

    def set(self, i, val):
        self.add(i, val - self.get(i))

    def pref_sum(self, i):

        data = self.data
        result = 0
        i = i - 1
        while i >= 0:
            result += data[i]
            i = (i & (i + 1)) - 1
        return result

    def range_sum(self, a, b):

        data = self.data
        result = 0
        a, b = a - 1, b - 1
        while b > a:
            result += data[b]
            b = (b & (b + 1)) - 1
        while a > b:
            result -= data[a]
            a = (a & (a + 1)) - 1
        return result


def solve(tree):
    n = len(tree)
    P = 998_244_353
    bound = [-n] * n
    submax = list(range(n))
    immediate_successors = [[] for v in range(n)]
    path_max = [-n] * n
    parent = [None] * n
    parent[0] = 0
    traversal = [0]
    processed = 0
    while processed < len(traversal):
        v = traversal[processed]
        processed += 1
        for u in tree[v]:
            if u == parent[v]:
                continue
            traversal.append(u)
            parent[u] = v
            path_max[u] = max(path_max[v], v)

    for v in range(1, n):
        if path_max[v] < v:
            immediate_successors[path_max[v]].append(v)

    for v in reversed(traversal):
        for u in tree[v]:
            if u == parent[v]:
                continue
            submax[v] = max(submax[v], submax[u])

    assert submax[0] == n - 1
    stack = [0]
    maxs_stack = []
    order = []
    order_pos = [-n] * n
    while stack:
        v = stack.pop()
        if bound[v] == -n:
            if v == 0 or submax[parent[v]] > submax[v]:
                maxs_stack.append(submax[v])
            if maxs_stack[-1] > v or v == n - 1:
                bound[v] = maxs_stack[-1]
            else:
                bound[v] = maxs_stack[-2]

            if path_max[v] < v:
                order_pos[v] = len(order)
                order.append(v)

            stack.append(v)
            tree[v].sort(key=lambda x: -submax[x])
            for u in tree[v]:
                if u == parent[v]:
                    continue
                stack.append(u)
        else:
            if v == 0 or submax[parent[v]] > submax[v]:
                assert maxs_stack[-1] == submax[v]
                maxs_stack.pop()

    assert 0 == order[0]
    assert n - 1 == order[-1]

    fw_tree = FenwickTree(len(order))
    fw_tree.set(order_pos[n - 1], 1)
    for v in reversed(range(n)):
        v_pos = order_pos[v]
        if v_pos < 0:
            continue
        cnt = fw_tree.range_sum(v_pos, order_pos[bound[v]] + 1) % P
        fw_tree.set(v_pos, cnt)
        for u in immediate_successors[v]:
            fw_tree.set(order_pos[u], 0)

    return fw_tree.get(0) % P


n_tests = int(stdin.readline())
for test_id in range(n_tests):
    print(solve(read_tree()))


# https://github.com/VaHiX/CodeForces/
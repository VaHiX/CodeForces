# Problem: CF 1887 D - Split
# https://codeforces.com/contest/1887/problem/D

"""
Algorithm: Range Maximum Query with Fenwick Tree and Stack
Techniques: 
- Sparse Table for Range Maximum Query (RMQ)
- Fenwick Tree for efficient range updates and point queries
- Stack to maintain elements in decreasing order for finding valid splits

Time Complexity: 
- Preprocessing (Sparse Table): O(n log n)
- Each query processing: O(log n)
- Overall: O(n log n + q log n)

Space Complexity: 
- Sparse Table: O(n log n)
- Fenwick Tree: O(n)
- Stack and other variables: O(n)
- Overall: O(n log n)
"""

import math
import sys


class FenwickTree:
    def __init__(self, size):
        self.n = size
        self.tree = [0] * (self.n + 2)

    def add_point(self, idx, delta):
        while idx <= self.n:
            self.tree[idx] += delta
            idx += idx & -idx

    def query_prefix(self, idx):
        res = 0
        while idx > 0:
            res += self.tree[idx]
            idx -= idx & -idx
        return res

    def add_range(self, l, r, delta):
        self.add_point(l, delta)
        self.add_point(r + 1, -delta)


def main():
    data = sys.stdin.read().split()
    ptr = 0
    n = int(data[ptr])
    ptr += 1
    a = [0] * (n + 2)
    for i in range(1, n + 1):
        a[i] = int(data[ptr])
        ptr += 1

    # Build Sparse Table for Range Maximum Query
    max_level = 0
    while (1 << (max_level + 1)) <= n:
        max_level += 1
    st = [[0] * (max_level + 1) for _ in range(n + 2)]
    for i in range(1, n + 1):
        st[i][0] = a[i]
    for j in range(1, max_level + 1):
        j_power = 1 << j
        for i in range(1, n - j_power + 2):
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1])

    # Function to get maximum in range [l, r]
    def range_max(l, r):
        if l > r:
            return -math.inf
        length = r - l + 1
        k = length.bit_length() - 1
        return max(st[l][k], st[r - (1 << k) + 1][k])

    m = int(data[ptr])
    ptr += 1
    queries = [[] for _ in range(n + 2)]
    for query_idx in range(1, m + 1):
        l = int(data[ptr])
        r = int(data[ptr + 1])
        ptr += 2
        queries[r].append((l, query_idx))

    fen = FenwickTree(n)
    stack = []
    ans = [0] * (m + 2)

    for i in range(1, n + 1):
        # Process elements that are smaller than or equal to current
        while stack and a[i] <= a[stack[-1]]:
            top = stack.pop()
            prev_top = stack[-1] if stack else 0
            left = prev_top + 1
            p = 0
            l_bin, r_bin = 1, left - 1
            # Binary search for valid split point using RMQ
            while l_bin <= r_bin:
                mid = (l_bin + r_bin) // 2
                if range_max(mid, left - 1) < a[top]:
                    p = mid
                    r_bin = mid - 1
                else:
                    l_bin = mid + 1
            if p:
                fen.add_range(p, left - 1, -1)

        prev_top = stack[-1] if stack else 0
        left = prev_top + 1

        p = 0
        l_bin, r_bin = 1, left - 1
        # Binary search for valid split point using RMQ
        while l_bin <= r_bin:
            mid = (l_bin + r_bin) // 2
            if range_max(mid, left - 1) < a[i]:
                p = mid
                r_bin = mid - 1
            else:
                l_bin = mid + 1
        if p:
            fen.add_range(p, left - 1, 1)
        stack.append(i)

        # Answer queries ending at position i
        for l_query, idx in queries[i]:
            ans[idx] = fen.query_prefix(l_query)

    for i in range(1, m + 1):
        print("Yes" if ans[i] else "No")


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
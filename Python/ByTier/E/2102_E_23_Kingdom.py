# Problem: CF 2102 E - 23 Kingdom
# https://codeforces.com/contest/2102/problem/E

"""
E. 23 Kingdom

Purpose:
This code solves the problem of finding the maximum possible beauty of any "nice" array
derived from a given array `a`. A nice array `b` has elements satisfying 1 ≤ b_i ≤ a_i,
and the beauty is defined as the sum over all distinct values x of the maximum gap
between two occurrences of x in b (d_x(c)). The goal is to maximize this sum.

Algorithm:
- For each value x, we want to maximize the distance d_x(b), which corresponds to placing
  two instances of x as far apart as possible.
- We use a segment tree with range queries and updates to efficiently track which positions
  can still be used for setting a value. The algorithm maintains left and right candidate
  insertion points to compute maximal gaps.
- Two passes are made:
  - First pass from left to right to identify candidates for leftmost placements of values.
  - Second pass from right to left to identify candidates for rightmost placements.

Time Complexity: O(n log n) per test case, due to segment tree operations.
Space Complexity: O(n), space used by the segment tree storage.

Techniques:
- Segment Tree with point updates and range queries
- Greedy strategy using two passes
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


class SegmentTree:
    """
    https://en.wikipedia.org/wiki/Segment_tree:
    "In computer science, a segment tree, also known as a statistic tree, is a tree data structure used for
    storing information about intervals, or segments."
    See also: https://www.geeksforgeeks.org/segment-tree-data-structure/
    """

    def __init__(self, data, function=max, default_value=-1):
        self.function = function
        self.default_value = default_value
        self.n = len(data)
        self.sz = 1 << (self.n - 1).bit_length()  # Compute next power of two
        self.data = [self.default_value] * (2 * self.sz)
        self.data[self.sz : self.sz + self.n] = data
        for i in range(self.sz - 1, 0, -1):
            self.data[i] = function(self.data[2 * i], self.data[2 * i + 1])

    def __getitem__(self, i):
        return self.data[self.sz + i]

    def __setitem__(self, i, value):
        i += self.sz
        self.data[i] = value
        i >>= 1
        while i > 0:
            self.data[i] = self.function(self.data[2 * i], self.data[2 * i + 1])
            i >>= 1

    def __delitem__(self, i):
        self[i] = self.default_value

    def __len__(self):
        return self.n

    def update(self, i, value):
        """Updates the i-th data item to value."""
        self[i] = value

    def query(self, start, stop):
        """Queries segment [start, stop) with regard to func."""
        if start == stop:
            return self.default_value
        start += self.sz
        stop += self.sz
        result_left, result_right = self.default_value, self.default_value
        while start < stop:
            if start & 1:
                result_left = self.function(result_left, self.data[start])
                start += 1
            start >>= 1
            if stop & 1:
                stop -= 1
                result_right = self.function(self.data[stop], result_right)
            stop >>= 1
        return self.function(result_left, result_right)

    def __str__(self):
        return f"SegmentTree({self.function.__name__}, {self.data[1:self.sz]}{self.data[self.sz:]})"

    def __repr__(self):
        return self.__str__()


def solve_case():
    n = int(input())
    a = list(map(lambda x: int(x) - 1, input().split()))  # Convert to 0-based indexing
    left = []
    seg_tree = SegmentTree(range(n))  # Initialize segment tree with all indices
    for i in range(n):
        j = seg_tree.query(0, a[i] + 1)  # Find smallest index that is available
        if j != -1:
            left.append(i)
            seg_tree[j] = -1  # Mark index as used
    right = []
    seg_tree = SegmentTree(range(n))  # Re-initialize again for reverse pass
    for i in range(n - 1, -1, -1):
        j = seg_tree.query(0, a[i] + 1)  # Same logic going backwards
        if j != -1:
            right.append(i)
            seg_tree[j] = -1
    ans = 0
    for i, j in zip(left, right):
        if i >= j:
            break
        ans += j - i  # Add distance of valid pair
    return ans


ans = []
for _ in range(int(input())):
    ans.append(str(solve_case()))
print("\n".join(ans))


# https://github.com/VaHiX/codeForces/
# Problem: CF 1881 G - Anya and the Mysterious String
# https://codeforces.com/contest/1881/problem/G

"""
Code Purpose:
This code solves the problem of determining whether a substring of a string is "beautiful"
(i.e., does not contain any palindromic substring of length at least 2) after applying
various operations on the string. It uses a segment tree with lazy propagation techniques,
and tracks differences between consecutive characters in the string to efficiently detect
palindromes.

Algorithms/Techniques:
- Binary Indexed Tree (Fenwick Tree) for efficient range updates and queries
- Difference array technique to track changes in character differences
- Efficient palindrome detection using difference tracking

Time Complexity: O((n + m) * log(n)) where n is the length of string and m is number of queries
Space Complexity: O(n) for storing the string, difference arrays and segment trees
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def get_sum0(i, tree):
    """Get prefix sum up to index i in the Fenwick tree."""
    s = 0
    while i > 0:
        s += tree[i]
        i -= i & -i
    return s


def get_sum(s, t, tree):
    """Get sum in range [s, t] using prefix sums."""
    ans = 0 if s > t else get_sum0(t, tree) - get_sum0(s - 1, tree)
    return ans


def add(i, x, tree):
    """Add value x to index i in the Fenwick tree."""
    while i < len(tree):
        tree[i] += x
        i += i & -i


t = int(input())
ans = []
for _ in range(t):
    n, m = map(int, input().split())
    s = list(input().rstrip())
    # Convert characters to 0-25 range for easier computation
    s = [0] + [i - 97 for i in s]
    # x[i] represents difference between s[i+1] and s[i]
    x = [-1] * (n + 1)
    for i in range(1, n):
        x[i] = (s[i + 1] - s[i]) % 26
    # y[i] represents difference between s[i+2] and s[i] (used for detecting palindromes of len 3+)
    y = [-1] * (n + 1)
    for i in range(1, n - 1):
        y[i] = (s[i + 2] - s[i]) % 26
    # Segment trees for tracking changes in difference arrays
    tree1, tree2 = [0] * (n + 5), [0] * (n + 5)
    # Initialize segment trees with initial values
    for i in range(1, n):
        if not x[i]:
            tree1[i] = 1
        if not y[i]:
            tree2[i] = 1
    # Build BIT from initial values
    for i in range(1, n + 5):
        j = i + (i & -i)
        if j < n + 5:
            tree1[j] += tree1[i]
            tree2[j] += tree2[i]
    for _ in range(m):
        t = list(map(int, input().split()))
        l, r = t[1], t[2]
        if t[0] == 1:
            u = t[3] % 26
            if not u:
                continue
            # Update x and y arrays for affected indices
            for i in [l - 1, r]:
                d = u if i < l else -u
                if not 1 <= i < n:
                    continue
                if not x[i]:
                    add(i, -1, tree1)  # Remove from tree if it was zero
                x[i] = (x[i] + d) % 26  # Update difference
                if not x[i]:
                    add(i, 1, tree1)  # Add to tree if it became zero
            z = [l - 2, l - 1, r - 1, r] if l ^ r else [l - 2, r]
            # Process y array changes
            for i in z:
                d = u if i < l else -u
                if not 1 <= i < n - 1:
                    continue
                if not y[i]:
                    add(i, -1, tree2)
                y[i] = (y[i] + d) % 26
                if not y[i]:
                    add(i, 1, tree2)
        else:
            # Query for beautiful substring
            # Count zeros in x and y arrays to detect palindromes
            c = get_sum(l, r - 1, tree1) + get_sum(l, r - 2, tree2)
            ans0 = "YES" if not c else "NO"
            ans.append(ans0)
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/
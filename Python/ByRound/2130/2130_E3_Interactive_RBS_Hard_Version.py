# Problem: CF 2130 E3 - Interactive RBS (Hard Version)
# https://codeforces.com/contest/2130/problem/E3

"""
E3. Interactive RBS (Hard Version)

This problem involves reconstructing a hidden bracket sequence of length n using at most 100 queries.
Each query asks for the number of non-empty regular bracket substrings in a selected substring of the hidden sequence.

Key algorithms and techniques:
- Binary search on the answer to find the index where a certain property changes (to locate a '(')
- Using bit manipulation to reconstruct the string character by character
- Precomputed lookup table for triangular numbers to efficiently calculate results

Time Complexity: O(n * log n * log n) per test case due to binary search and bit manipulation steps
Space Complexity: O(log n) for precomputed array and auxiliary variables
"""

import os
import sys
from bisect import bisect_right

ans = None
debug = os.environ.get("USER") == "loic"


def conv(var):
    t = type(var)
    if t is int or t is str:
        arr = [var]
    elif t is tuple or t is list:
        arr = list(var)
    return [str(v) for v in arr]


line = lambda: sys.stdin.readline().split() if not debug else conv(ans)
us = lambda: line()[0]
ui = lambda: int(us())
mi = lambda: tuple(map(int, line()))
li = lambda: list(mi())
lsi = lambda: list(map(int, line()[0]))
A = "(()()()()(("


def read(func, cs, query=None):
    if debug:
        global ans
        if cs == -1:
            ans = 1
        elif cs == 0:
            ans = len(A)
        elif cs == 1:
            ans = 0
            cur = [A[i] for i in query]
            q = []
            for i, val in enumerate(cur):
                if not q:
                    q.append(0)
                if val == "(":
                    q.append(0)
                elif q:
                    last = q.pop()
                    ans += last * (last + 1) // 2
                    if q:
                        q[-1] += 1
            while q:
                last = q.pop()
                ans += last * (last + 1) // 2
    return func()


def write(pref, query, ans):
    if ans:
        q = pref + " " + "".join(v for v in query)
    else:
        q = pref + " " + str(len(query)) + " " + " ".join(str(v + 1) for v in query)
    os.write(1, b"%s\n" % q.encode())


def bs_pred_r(predicate, low, high):
    l = low
    r = high
    while l < r:
        mid = l + (r - l) // 2
        if not predicate(mid):
            l = mid + 1
        else:
            r = mid
    return l


def solve():
    n = read(ui, 0)  # Read length of bracket sequence
    res = [None] * n  # Result array to store characters

    def pred(p):
        args = [i for i in range(p + 1)]  # Prepare indices for query
        write("?", args, False)  # Send query
        ans = read(ui, 1, args)  # Get response and compute answer
        return ans >= 1  # Predicate to find first position where count of regular substrs is >= 1

    r = bs_pred_r(pred, 0, n)  # Binary search for index r that helps identify opening brackets
    if r == n:
        r = 0  # If no such index found, set default

    # Using precomputed values to determine bracket structure
    for st in range(0, n, sz):  # Iterate in chunks of size sz
        args = []
        # Build argument list based on precomputed array arr
        for i in range(st, min(st + sz, n)):
            inner, outer = arr[i - st]
            args += [i] * outer + [i, r] * inner + [r] * (outer + 1)

        write("?", args, False)  # Send query with constructed arguments
        ans = read(ui, 1, args)  # Get response

        # Process bits of answer to determine bracket type
        for k in range(min(st + sz, n) - st):
            if (ans >> k) & 1:  # If k-th bit is set
                ans -= 1 << k  # Clear the bit
                res[st + k] = "("  # Assign opening bracket
            else:
                res[st + k] = ")"  # Assign closing bracket

    write("!", res, True)  # Output final result


# Precompute triangular numbers for optimization
sq = [i * (i + 1) // 2 for i in range(1001)]
arr = []  # Store pairs (inner, outer)
k = 0
c = 0
while c <= 1000:
    idx = bisect_right(sq, 1 << k) - 1  # Find index of largest triangular number <= 2^k
    arr.append((idx, (1 << k) - sq[idx]))  # Append pair (inner, outer)
    c += 2 * (arr[-1][0] + arr[-1][1]) + 1  # Increase counter
    k += 1
arr.pop()  # Remove last entry if over limit
sz = len(arr)  # Size of chunk for processing

T = read(ui, -1)  # Read number of test cases
for test in range(1, T + 1):  # For each test case
    solve()  # Solve the current test case


# https://github.com/VaHiX/codeForces/
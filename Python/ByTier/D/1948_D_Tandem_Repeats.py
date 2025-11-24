# Problem: CF 1948 D - Tandem Repeats?
# https://codeforces.com/contest/1948/problem/D

"""
Algorithm: Tandem Repeats
Approach:
- Use binary search or reverse iteration to find the maximum possible length of a tandem repeat substring.
- For each possible length `m`, check if there exists a tandem repeat of that length.
- A tandem repeat of length 2*m has the form: s[j:j+m] == s[j+m:j+2*m]
- To handle question marks, we allow mismatches only if both characters are not '?'
- The function `f` checks if a tandem repeat of length 2*m can be formed in the string.
- Time Complexity: O(n^2) in worst case where n is the length of string, due to checking all substrings.
- Space Complexity: O(n) for storing input string.

"""

import sys

R = sys.stdin.readline
S = lambda: map(int, R().split())


def f(s, m):
    # Count consecutive valid matches for a tandem repeat of length 2*m
    c = 0
    for j in range(len(s) - m):  # iterate through possible start positions
        # If either character is '?', or they match, increment counter
        if s[j] != "?" and s[j + m] != "?" and s[j] != s[j + m]:
            c = 0  # reset counter if mismatch and both are not '?'
        else:
            c += 1
            if c == m:  # if we found m consecutive matching positions, we have a tandem repeat
                return 1
    return 0


def g():
    s = R().rstrip()
    # Check from largest to smallest possible length
    for m in range(len(s) // 2, 0, -1):
        if f(s, m):
            return 2 * m  # return the full length of tandem repeat
    return 0


for _ in range(int(R())):
    print(g())


# https://github.com/VaHiX/CodeForces/
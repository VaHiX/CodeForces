# Problem: CF 1837 D - Bracket Coloring
# https://codeforces.com/contest/1837/problem/D

"""
Brute Force Approach for Bracket Coloring Problem

Algorithm:
1. Check if the input string is a valid bracket sequence (equal number of '(' and ')').
2. Identify which brackets need to be colored with color 2:
   - Use a stack-like approach to track unmatched brackets.
   - For each opening bracket, add it to a list X.
   - For each closing bracket, if there's a matching opening bracket in X, pop from X.
   - If no matching opening bracket, add this closing bracket to list Y.
3. If both lists X and Y are empty, only one color is needed.
   Otherwise, we need two colors.
4. Assign colors:
   - All brackets in list X get color 2.
   - All brackets in list Y get color 2.
   - Others get color 1.

Time Complexity: O(n)
Space Complexity: O(n)

This implementation uses a greedy method to assign colors to minimize total count.
"""

import sys

input = sys.stdin.readline


def solve():
    n = int(input())
    s = input().rstrip()

    if 2 * s.count("(") != n:
        out.append("-1")
        return

    plus = s[0]
    X = []  # indices of brackets that need to be colored with color 2
    Y = []  # indices of brackets that need to be colored with color 2

    for i, char in enumerate(s):
        if char == plus:  # if it's an opening bracket
            X.append(i)  # add to stack
        else:  # if it's a closing bracket
            if X:  # if there's a matching opening bracket
                X.pop()  # remove the last unmatched opening bracket
            else:  # no matching opening bracket, so add to Y
                Y.append(i)

    # If all brackets are matched, we only need one color
    if not X and not Y:
        out.append("1")
    else:
        out.append("2")

    col = ["1"] * n  # initialize all brackets with color 1
    # Set color 2 for brackets in X and Y
    for lst in [X, Y]:
        for i in lst:
            col[i] = "2"

    out.append(" ".join(col))
    return


out = []
T = int(input())
for _ in range(T):
    solve()
print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/
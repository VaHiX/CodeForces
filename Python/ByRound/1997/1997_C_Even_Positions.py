# Problem: CF 1997 C - Even Positions
# https://codeforces.com/contest/1997/problem/C

"""
Algorithm: Greedy with Stack-like Tracking
Purpose: To reconstruct a valid bracket sequence from a partially known string (with '_' on odd positions)
         such that the total cost (sum of distances between matching brackets) is minimized.

Key Insight:
- We process the string from left to right.
- We maintain a counter `sk` that simulates an unmatched opening bracket count (like a stack size).
- For each character:
  - If it's a closing bracket ')', we decrease the counter.
  - If it's an opening bracket '(', we increase the counter.
  - If it's '_', we decide whether to treat it as '(' or ')' to minimize cost:
    - If `sk > 0`, we treat it as ')', which reduces the counter, and we add current `sk` to cost.
    - Otherwise, we treat it as '(', increasing the counter, and do not add to cost yet.

Time Complexity: O(n) per test case, where n is the length of string.
Space Complexity: O(1) additional space (only using a few variables).

"""
import sys

input = lambda: sys.stdin.readline().rstrip()


def solve():
    input()
    s = input()
    ans = 0
    sk = 0  # This acts like a stack size: positive = unmatched opening brackets, negative = unmatched closing brackets
    for c in s:
        ans += sk  # Add the current stack size to the total cost (distance to match)
        if c == "_":
            if sk > 0:
                # If stack is positive (we have unmatched opens), treat "_" as ")" to reduce stack
                sk -= 1
            else:
                # If no unmatched opens, treat "_" as "(" to increase stack
                sk += 1
        elif c == ")":
            # Regular closing bracket, decrease stack
            sk -= 1
        else:  # c == "("
            # Regular opening bracket, increase stack
            sk += 1
    print(ans)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/
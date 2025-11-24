# Problem: CF 2166 B - Tab Closing
# https://codeforces.com/contest/2166/problem/B

"""
Code Purpose:
This code solves the problem of finding the minimum number of mouse moves required to close all tabs on a screen of length `a`. Each tab has a dynamic length that decreases as tabs are closed, and the cursor starts at the left endpoint. The solution uses mathematical analysis to determine if one move is sufficient or if two moves are needed.

Algorithms/Techniques:
- Mathematical optimization based on comparing `a` and `b`, and the number of tabs `n`
- Greedy approach to minimize mouse moves by calculating how many tabs can be closed in one move

Time Complexity: O(1) - constant time per test case
Space Complexity: O(1) - only using a constant amount of extra space
"""

t = int(input())
for _ in range(t):
    a, b, n = map(int, input().split())
    # If the screen length equals the tab length OR
    # the number of tabs is less than or equal to the number of full-length segments that fit in the screen,
    # then we can close all tabs with just one move
    print(1 if (a == b or n <= a // b) else 2)


# https://github.com/VaHiX/CodeForces/
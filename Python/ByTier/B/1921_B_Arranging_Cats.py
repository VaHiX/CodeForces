# Problem: CF 1921 B - Arranging Cats
# https://codeforces.com/contest/1921/problem/B

"""
Code Purpose:
This code solves the problem of finding the minimum number of operations to rearrange cats in boxes from an initial configuration 's' to a desired configuration 'f'. The operations allowed are placing a cat, removing a cat, or moving a cat between boxes.

Algorithms/Techniques:
- Greedy approach: The solution counts mismatches between the initial and final states.
- It determines whether to count "10" mismatches (when a cat exists but should be removed, from s) or "01" mismatches (when a cat is missing but should be added, to f), based on which is smaller.
- Time and Space Complexity:
    - Time Complexity: O(n) where n is the number of boxes, because we iterate through the strings once.
    - Space Complexity: O(1) as only a few variables are used, independent of input size.
"""

import sys

input = sys.stdin.readline
t = 1
t = int(input())
for _ in range(t):
    n = int(input())
    s = input().strip()
    f = input().strip()
    ans = 0
    # If initial number of cats >= final number of cats
    if s.count("1") >= f.count("1"):
        # Count mismatches where cat exists in s but not in f (i.e., "10")
        for i in range(n):
            if s[i] + f[i] == "10":
                ans += 1
        print(ans)
    else:
        # Count mismatches where no cat in s but needed in f (i.e., "01")
        for i in range(n):
            if s[i] + f[i] == "01":
                ans += 1
        print(ans)


# https://github.com/VaHiX/CodeForces/
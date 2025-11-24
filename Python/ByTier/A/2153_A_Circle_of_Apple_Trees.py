# Problem: CF 2153 A - Circle of Apple Trees
# https://codeforces.com/contest/2153/problem/A

# Flowerbox
"""
Code Purpose:
This code solves a problem where we are given a circular array of apple trees,
each with a beauty value. We can choose to eat an apple only if its beauty is
strictly greater than the last eaten apple's beauty. The goal is to find the
maximum number of apples that can be eaten.

Algorithms/Techniques:
- Greedy approach: At each step, we attempt to eat the highest valid apple.
- We simulate eating apples in a circular fashion and track the maximum beauty
  of the last apple eaten.

Time Complexity: O(n^2) in worst case due to nested loop simulation for each node
Space Complexity: O(n) for storing the input array and auxiliary structures

Note:
The provided code snippet appears unrelated to the described problem.
It seems to compute the number of unique elements in a list, which does not
match the stated task of eating apples in a circular arrangement with constraints.
"""

# The actual code (as given)
for _ in range(int(input())):
    a = input()
    m = len(set(map(int, input().split())))
    print(m)


# https://github.com/VaHiX/CodeForces/
# Problem: CF 1936 B - Pinball
# https://codeforces.com/contest/1936/problem/B

"""
Purpose: Solve the pinball movement problem on a 1D grid where each cell contains '<' or '>' indicating direction.
         A pinball starts at each cell, moves according to the direction, and the direction flips after each move.
         The pinball stops when it exits the grid. For each starting position, compute the time to exit.

Algorithms/Techniques:
- Preprocessing with stacks to simulate the movement efficiently
- Two passes: one from right to left for '>' directions, and one from left to right for '<' directions
- Use of stack to keep track of indices that need processing

Time Complexity: O(n) where n is the length of the string s, since each element is pushed and popped from the stack at most once.
Space Complexity: O(n) for storing the answer array and the stacks.

"""

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    s = input().strip()
    ans = [0] * n
    # Stack to store indices of '>' characters, processed from right to left
    stack = [i for i in range(n) if s[i] == ">"]
    c = 0
    # Process from right to left for '>' directions
    for i in range(n - 1, -1, -1):
        if stack:
            # Calculate cumulative move count and update answer
            c += 2 * (i - stack.pop())
            ans[i] = c + n - i
        else:
            break
    c = 0
    # Stack to store indices of '<' characters, processed from left to right
    stack = [i for i in range(n - 1, -1, -1) if s[i] == "<"]
    # Process from left to right for '<' directions
    for i in range(n):
        if stack:
            # Calculate cumulative move count and update answer
            c += 2 * (stack.pop() - i)
            ans[i] += c + i + 1
        else:
            break
    print(*ans)


# https://github.com/VaHiX/CodeForces/
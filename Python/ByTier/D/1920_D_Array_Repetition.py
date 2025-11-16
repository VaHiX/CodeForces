# Problem: CF 1920 D - Array Repetition
# https://codeforces.com/contest/1920/problem/D

"""
Algorithm: Array Repetition
Approach:
- We simulate the operations by maintaining a list of arrays, where each array represents a "level" in the construction.
- For operation type 1 (append integer): we simply append to the current array.
- For operation type 2 (repeat array): we create a new level by repeating the current array x times.
- For queries: we trace back from the final array to determine which original element is at the queried index.

Time Complexity: O(n * log(max_size) + q * log(n))
Space Complexity: O(n * max_size) where max_size is the size of the final array.
"""

import sys

input = sys.stdin.readline


def solve():
    n, q = map(int, input().split())
    sz = [0]  # Stores sizes of each level of array
    vals = [[]]  # Stores the arrays at each level
    for i in range(n):
        cmd, x = map(int, input().split())
        if sz[len(sz) - 1] > 10**18:
            continue
        if cmd == 1:
            vals[len(vals) - 1].append(x)
            sz[len(sz) - 1] += 1
        else:
            vals.append([])
            sz.append(sz[len(sz) - 1] * (x + 1))  # x copies of current array plus 1 original = x + 1 total

    queries = list(map(int, input().split()))
    stoans = []
    for cur in queries:
        k = cur - 1  # Convert to 0-based indexing
        done = False
        for i in range(len(sz) - 1, -1, -1):  # Traverse levels from top to bottom
            rem = k % sz[i]  # Find relative index in current level
            st = sz[i] - len(vals[i])  # Start index of actual values in current array
            if st <= rem:  # If the index falls in the values part
                stoans.append(vals[i][rem - st])  # Fetch the actual value
                done = True
                break
            else:
                k = rem  # Move to the parent level to look for the element

        if not done:
            stoans.append(vals[0][k])  # Fall back to root level if not found
    print(*stoans)


t = int(input())
for _ in range(t):
    solve()


# https://github.com/VaHiX/CodeForces/
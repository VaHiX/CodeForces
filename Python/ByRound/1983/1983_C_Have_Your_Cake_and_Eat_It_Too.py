# Problem: CF 1983 C - Have Your Cake and Eat It Too
# https://codeforces.com/contest/1983/problem/C

"""
Algorithm: Try all permutations of assigning Alice, Bob, Charlie to subarrays.
Time Complexity: O(n) per testcase, since each element is visited at most twice (once for each of the 3 people)
Space Complexity: O(n) for storing the arrays

Approach:
- For each of the 6 possible orderings of assigning people to slices, try to assign slices greedily.
- For a given order (e.g., Alice first, then Bob, then Charlie):
    - Assign the first slice to Alice; keep extending until her value >= ceil(total/3)
    - Then assign the next slice to Bob; keep extending until his value >= ceil(total/3)
    - Then assign the next slice to Charlie; keep extending until his value >= ceil(total/3)
- If we can successfully assign all three slices without overlap or insufficient value, return the indices.
"""

import math
import sys


def calc(tmp):
    i = 0
    ans = [0] * 6  # Stores [la, ra, lb, rb, lc, rc]
    for j in tmp:  # j is the index of the person in order (0=Alice, 1=Bob, 2=Charlie)
        ans[j * 2] = i + 1  # Start index of slice for person j
        cur = 0
        # Keep adding pieces until the cumulative value reaches threshold t
        while i < n and cur < t:
            cur += arr[j][i]
            i += 1
        # If we couldn't reach the threshold, this assignment is invalid
        if i == n and cur < t:
            return False
        ans[j * 2 + 1] = i  # End index of slice for person j
    print(*ans)
    return True


input = sys.stdin.buffer.readline
for _ in range(int(input())):
    n = int(input())
    arr = [[*map(int, input().split())] for _ in range(3)]
    t = math.ceil(sum(arr[0]) / 3)  # Threshold value needed for each person (ceil(total/3))
    # Try all 6 permutations of assigning 3 people to 3 slices
    for order in ((0, 1, 2), (0, 2, 1), (1, 0, 2), (1, 2, 0), (2, 0, 1), (2, 1, 0)):
        if calc(order):
            break
    else:
        print(-1)


# https://github.com/VaHiX/CodeForces/
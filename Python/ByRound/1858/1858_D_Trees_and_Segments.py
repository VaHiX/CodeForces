# Problem: CF 1858 D - Trees and Segments
# https://codeforces.com/contest/1858/problem/D

"""
Problem: Trees and Segments
Purpose:
    Given a binary string representing a row of trees (0 = oak, 1 = fir), 
    and a maximum number of k changes allowed, determine the maximum beauty 
    of the row for each possible inspector's favorite number a from 1 to n.
    Beauty = a * max_consecutive_0s + max_consecutive_1s

Algorithms/Techniques:
    - Sliding window technique to find maximum lengths of consecutive 0s and 1s
    - Binary search or brute force over possible lengths of 0s and 1s segments
    - Preprocessing prefix sums for efficient range sum queries

Time Complexity:
    O(n^3) in the worst case due to nested loops and possible sliding window operations
    for calculating optimal 0s and 1s segments for all possible combinations.
    
Space Complexity:
    O(n) for storing prefix sums and intermediate arrays.
"""

import sys

input = lambda: sys.stdin.readline()[:-1]
ni = lambda: int(input())
na = lambda: list(map(int, input().split()))
yes = lambda: print("yes")
Yes = lambda: print("Yes")
YES = lambda: print("YES")
no = lambda: print("no")
No = lambda: print("No")
NO = lambda: print("NO")


def solve(l, r):
    # Function to compute minimum changes needed for a segment of length l 0s
    # and r 1s, or vice versa.
    if l + r >= n + 1:
        return 10**9
    res = 10**9
    x = 10**9
    # Swap l and r to check both patterns
    l, r = r, l
    for i in range(l, n - r + 1):
        x = min(x, l - (s[i] - s[i - l]))
        res = min(res, x + s[i + r] - s[i])
    x = 10**9
    l, r = r, l
    for i in range(l, n - r + 1):
        x = min(x, s[i] - s[i - l])
        res = min(res, x + r - (s[i + r] - s[i]))
    return res


for _ in range(ni()):
    n, k = na()
    t = [int(i) for i in input()]
    s = [0]
    for i in range(n):
        s.append(s[-1] + t[i])
    j = n
    ans = []
    # Iterate over all possible combinations of l0 and l1
    for i in range(n + 1):
        while j >= 0:
            x = solve(i, j)
            if x > k:
                j -= 1
            else:
                ans.append((i, j))
                break
    f = []
    # For each possible 'a', calculate max beauty
    for a in range(1, n + 1):
        res = 0
        for i, j in ans:
            res = max(res, i * a + j)
        f.append(res)
    print(*f)


# https://github.com/VaHiX/CodeForces/
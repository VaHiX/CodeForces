# Problem: CF 2069 C - Beautiful Sequence
# https://codeforces.com/contest/2069/problem/C

"""
C. Beautiful Sequence
Algorithms/Techniques: Dynamic Programming, Counting Subsequences

Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem asks to count the number of beautiful subsequences in an array where each element is 1, 2, or 3.
A beautiful sequence satisfies:
1. Length >= 3
2. For every element except the first, there's a smaller element to its left
3. For every element except the last, there's a larger element to its right

This is solved using dynamic programming with states tracking:
- d[0]: number of subsequences ending in 1 (can extend to 2)
- d[1]: number of subsequences ending in 1,2 (can extend to 3)
- d[2]: number of subsequences ending in 1,2,3 (valid beautiful subsequences)

We process each element and update counts based on the value:
- If 1: increase count of sequences ending in 1
- If 2: double count of sequences ending in 1,2 (extend existing ones) + add sequences ending in 1
- If 3: add count of sequences ending in 1,2 to count of sequences ending in 1,2,3

This approach efficiently counts valid beautiful subsequences in linear time.
"""

from sys import stdin

R = stdin.readline
S = lambda: map(int, R().split())
P = print
X = 998244353
for _ in range(int(R())):
    n = int(R())
    d = [0, 0, 0]
    for x in S():
        if x == 1:
            d[0] += 1  # Add new subsequence starting with 1
        elif x == 2:
            d[1] = (2 * d[1] + d[0]) % X  # Extend existing subsequences ending in 1,2 or start new with 1 then 2
        else:
            d[2] = (d[2] + d[1]) % X  # Extend subsequences ending in 1,2 to 1,2,3
    P(d[2])


# https://github.com/VaHiX/codeForces/
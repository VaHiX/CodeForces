# Problem: CF 1815 D - XOR Counting
# https://codeforces.com/contest/1815/problem/D

"""
Algorithm: XOR Counting
Approach:
- For m=1, the answer is simply n.
- For m=2, we use a mathematical insight to compute the sum of XORs.
- For m>2 and n=0, the answer is 0.
- For m>2 and n>0, we compute based on even/odd nature of n.
- For m=2 and n>0, we use bit-by-bit dynamic programming to compute the contribution of each bit position.

Time Complexity: O(log n) per test case, due to bit manipulation and loop over bits.
Space Complexity: O(log n), for storing bit information and DP arrays.
"""

import sys

input = sys.stdin.readline

mod = 998244353
t = int(input())
for _ in range(t):
    a, m = map(int, input().split())
    if a == 0:
        print(0)
    elif m == 1:
        print(a % mod)
    elif m > 2:
        if a % 2 == 0:
            k = a // 2
            s = k * (k + 1)
            print(s % mod)
        else:
            k = a // 2 + 1
            s = k**2
            print(s % mod)
    else:
        bit = []
        while a > 0:
            bit.append(a % 2)
            a = a // 2
        dp1 = [[0, 0] for _ in range(len(bit))]
        dp2 = [[0, 0] for _ in range(len(bit))]
        dp1[0][0] = 1
        dp1[0][1] = 1 - bit[0]
        dp2[0][0] = bit[0]
        for i in range(1, len(bit)):
            if bit[i] == 1:
                dp1[i][0] = dp1[i - 1][1] + dp1[i - 1][0]
                dp1[i][1] = dp1[i - 1][1]
                dp2[i][0] = dp2[i - 1][1] + dp2[i - 1][0] + (dp1[i - 1][0] * (2**i))
                dp2[i][1] = dp2[i - 1][1]

            else:
                dp1[i][0] = dp1[i - 1][0]
                dp1[i][1] = dp1[i - 1][1] + dp1[i - 1][0]
                dp2[i][0] = dp2[i - 1][0]
                dp2[i][1] = dp2[i - 1][1] + (dp1[i - 1][1] * (2**i)) + dp2[i - 1][0]

        print(dp2[-1][0] % mod)


# https://github.com/VaHiX/CodeForces/
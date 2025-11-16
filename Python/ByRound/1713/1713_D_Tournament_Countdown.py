# Problem: CF 1713 D - Tournament Countdown
# https://codeforces.com/contest/1713/problem/D

"""
Algorithm: Single Elimination Tournament Winner Finder
Approach: 
- Use a tournament-style elimination process to determine the winner
- In each round, compare pairs of contestants and eliminate the loser
- The key idea is to reduce the problem size by half in each round
- Uses binary representation to track contestant positions and match outcomes
- Time Complexity: O(2^n)
- Space Complexity: O(2^n)

The algorithm works by:
1. Initially pairing up contestants in a specific pattern to build a tournament tree
2. For each round, query the match results
3. Based on results, update the list of potential winners
4. Continue until only one contestant remains as the winner
"""

import os
import sys

input = sys.stdin.buffer.readline
t = int(input())
pow2 = [1]
for _ in range(20):
    pow2.append(2 * pow2[-1])
a, b = "?".encode(), "!".encode()
for _ in range(t):
    n = int(input())
    if n == 1:
        os.write(1, b"%s %d %d\n" % (a, 1, 2))
        ans = int(input())
        os.write(1, b"%s %d\n" % (b, ans))
        continue
    pn = pow2[n]
    x = []
    p2, p4 = pn // 2, pn // 4
    for i in range(0, p2, 2):
        x.append(i + 1)
        x.append(i + 2)
        x.append(i + p2 + 1)
        x.append(i + p2 + 2)
    l = p4
    for _ in range(n - 1):
        k = 0
        q = []
        for i in range(l):
            if x[4 * i + 1] > x[4 * i + 2]:
                x[4 * i + 1], x[4 * i + 2] = x[4 * i + 2], x[4 * i + 1]
            u, v = x[4 * i], x[4 * i + 2]
            q.append(" ".join(("?", str(u), str(v))))
        os.write(1, b"%s\n" % "\n".join(q).encode())
        for i in range(l):
            c = int(input())
            if c == 0:
                x[k] = x[4 * i + 1]
                x[k + 1] = x[4 * i + 3]
            elif c == 1:
                x[k] = x[4 * i]
                x[k + 1] = x[4 * i + 3]
            else:
                x[k] = x[4 * i + 1]
                x[k + 1] = x[4 * i + 2]
            k += 2
        l //= 2
    os.write(1, b"%s %d %d\n" % (a, x[0], x[1]))
    c = int(input())
    if c == 1:
        ans = x[0]
    else:
        ans = x[1]
    os.write(1, b"%s %d\n" % (b, ans))
exit()


# https://github.com/VaHiX/CodeForces/
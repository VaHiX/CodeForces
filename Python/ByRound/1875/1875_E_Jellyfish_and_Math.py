# Problem: CF 1875 E - Jellyfish and Math
# https://codeforces.com/contest/1875/problem/E

"""
Algorithm: Bitwise BFS with memoization
Approach:
- Decompose each number into bits (0 to 29)
- For each bit position, determine the possible transitions from (ai, bi, mi) to (ci, di)
- If conflict arises, it's impossible
- Use BFS to compute minimum steps from (A, B) to (C, D) using allowed operations:
  1. (x & y, y)
  2. (x | y, y)
  3. (x, x ^ y)
  4. (x, y ^ M)
- Memoize results for (n, A, B, M) to avoid recomputation

Time Complexity: O(30 * 2^20) approximately due to bit-level processing and BFS
Space Complexity: O(2^20) for memoization and BFS queue
"""

from sys import stdin

input = lambda: stdin.readline()[:-1]

memo = {}
from collections import deque


def solve():

    a, b, c, d, m = map(int, input().split())
    D = {}

    # Process each bit position
    for i in range(30):
        ai, bi, ci, di, mi = (
            (a >> i) & 1,
            (b >> i) & 1,
            (c >> i) & 1,
            (d >> i) & 1,
            (m >> i) & 1,
        )
        # Check for conflicting transitions
        if (ai, bi, mi) in D:
            if D[(ai, bi, mi)] != (ci, di):
                print(-1)
                return

        else:
            D[(ai, bi, mi)] = (ci, di)

    res = []

    for ai, bi, mi in D:
        ci, di = D[(ai, bi, mi)]
        res.append((ai, bi, mi, ci, di))

    res.sort()
    A, B, C, D, M = 0, 0, 0, 0, 0
    n = len(res)

    # Reconstruct A, B, C, D, M from bit components
    for i in range(n):
        ai, bi, mi, ci, di = res[i]
        A |= ai << i
        B |= bi << i
        C |= ci << i
        D |= di << i
        M |= mi << i

    key = (n, A, B, M)
    if key not in memo:
        dist = {}
        dist[(A, B)] = 0
        todo = deque([(0, A, B)])

        while todo:
            d, x, y = todo.pop()
            # Operation 1: x := x & y
            if (x & y, y) not in dist:
                dist[(x & y, y)] = d + 1
                todo.appendleft((d + 1, x & y, y))
            # Operation 2: x := x | y
            if (x | y, y) not in dist:
                dist[(x | y, y)] = d + 1
                todo.appendleft((d + 1, x | y, y))
            # Operation 3: y := x ^ y
            if (x, x ^ y) not in dist:
                dist[(x, x ^ y)] = d + 1
                todo.appendleft((d + 1, x, x ^ y))
            # Operation 4: y := y ^ m
            if (x, y ^ M) not in dist:
                dist[(x, y ^ M)] = d + 1
                todo.appendleft((d + 1, x, y ^ M))
        memo[key] = dist

    if (C, D) in memo[key]:
        print(memo[key][(C, D)])
    else:
        print(-1)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/
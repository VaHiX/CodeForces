# Problem: CF 1874 B - Jellyfish and Math
# https://codeforces.com/contest/1874/problem/B

from collections import defaultdict, deque
from functools import lru_cache

inf = 1 << 30


# Flowerbox: 
# Purpose: Solve the minimum number of operations to transform (a,b) to (c,d) using bitwise operations.
# Algorithms/Techniques: BFS (Breadth-First Search) with bit manipulation and memoization.
# Time Complexity: O(30 * 2^30) in worst case due to bit-by-bit processing and BFS over bit states.
# Space Complexity: O(2^30) for storing visited states in the BFS.
@lru_cache(maxsize=None)
def solve(A, B, M):
    dist = defaultdict(lambda: inf)
    dist[A << 30 | B] = 0
    queue = deque([(A, B)])
    while queue:
        x, y = queue.popleft()
        # Operation 1: x := x & y
        # Operation 2: x := x | y
        # Operation 3: y := x ^ y
        # Operation 4: y := y ^ M
        for xx, yy in ((x & y, y), (x | y, y), (x, x ^ y), (x, y ^ M)):
            if dist[xx << 30 | yy] > dist[x << 30 | y] + 1:
                dist[xx << 30 | yy] = dist[x << 30 | y] + 1
                queue.append((xx, yy))
    return dist


T = int(input())
for t in range(T):
    A, B, C, D, M = map(int, input().split())
    dct = defaultdict(set)
    # Process each bit from 0 to 29
    for b in range(30):
        # Grouping (a_bit, b_bit, m_bit) and mapping to possible (c_bit, d_bit) outcomes
        dct[(A >> b & 1, B >> b & 1, M >> b & 1)].add((C >> b & 1, D >> b & 1))
        # Early check for impossibility conditions
        aa, bb, mm = A >> b & 1, B >> b & 1, M >> b & 1
        cc, dd = C >> b & 1, D >> b & 1
        if (aa, bb, mm) == (0, 0, 0) and cc + dd:
            ans = -1
            break
    else:
        # Check if more than one mapping exists for a given input bit group – that means ambiguous
        if any(len(lst) >= 2 for lst in dct.values()):
            ans = -1
        else:
            # Reconstruct bit sequences from mapping for BFS
            ABMCD = []
            A, B, C, D, M = 0, 0, 0, 0, 0
            le = 0
            for a, b, m in sorted(list(dct.keys())):
                for c, d in dct[(a, b, m)]:
                    if a + b + c + d + m:
                        ABMCD.append((a, b, m, c, d))
            ABMCD.sort()
            for a, b, m, c, d in ABMCD:
                A <<= 1
                A |= a
                B <<= 1
                B |= b
                D <<= 1
                D |= d
                C <<= 1
                C |= c
                M <<= 1
                M |= m
                le += 1
            # Run BFS for reconstructed values
            ans = solve(A, B, M)[C << 30 | D]
            if ans == inf:
                ans = -1
    print(ans)


# https://github.com/VaHiX/CodeForces/
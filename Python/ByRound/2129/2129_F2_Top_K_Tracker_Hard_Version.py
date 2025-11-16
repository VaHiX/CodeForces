# Problem: CF 2129 F2 - Top-K Tracker (Hard Version)
# https://codeforces.com/contest/2129/problem/F2

"""
Interactive Problem: F2. Top-K Tracker (Hard Version)

Algorithms/Techniques:
- Uses a combination of four query types to gather information about positions and values in a hidden permutation
- Employs a heuristic approach to deduce the permutation by building sets of possible positions and values
- Utilizes randomization to break ties in ambiguous cases
- Leverages precomputed patterns and statistical properties of the permutation

Time Complexity: O(n^2 log n) - This includes the queries and processing of sets
Space Complexity: O(n^2) - For storing the sets of positions (Sp) and values (Sv), and additional structures for mapping

The solution uses multiple queries to build sets Sv and Sp where Sv[i] contains indices of values that appear in position i, and Sp[i] contains values that appear in position i. Then a mapping is built to reconstruct the permutation.
"""

import random
import sys

input = lambda: sys.stdin.readline().strip()
flush = lambda: sys.stdout.flush()

N = 1010
Sv = [[] for _ in range(N)]
Sp = [[] for _ in range(N)]
prv = [[] for _ in range(N)]
prp = [[] for _ in range(N)]


def init():
    global n
    n = int(input())
    for i in range(N):
        Sv[i].clear()
        Sp[i].clear()
        prv[i].clear()
        prp[i].clear()


def ask(ty, v):
    print(f"{ty } {len (v )} {' '.join (map (str ,v ))}")
    flush()
    # The response size is determined by min(60, len(v)) for types 1,2 and min(300, len(v)) for types 3,4
    min(60, len(v)) if ty < 3 else min(300, len(v))
    res = list(map(int, input().split()))
    return res


def solve():
    cnt = 0
    cntr = 871
    p = [0] * (n + 4)

    # Pre-assigning patterns for set Sv to build initial clues
    for i in range(1, 30):
        cnt += 1
        Sv[cnt].append(i)
        cntr -= 1
        Sv[cntr].append(i)

    for i in range(1, 30):
        for j in range(i + 1, 30):
            cnt += 1
            Sv[cnt].extend([i, j])
            cntr -= 1
            Sv[cntr].extend([i, j])

    # Assigning the remaining elements for the rest of the permutation
    hd = 1
    for i in range(871, n):
        x, y, z = hd, hd + 1, hd + 2
        if x > 29:
            x -= 29
        if y > 29:
            y -= 29
        if z > 29:
            z -= 29
        Sv[i].extend([x, y, z])
        hd += 3

    # Querying for positions of values using query type 2
    for i in range(1, 30):
        v = []
        for j in range(1, n + 1):
            if i in Sv[j]:
                v.append(j)
        if not v:
            continue
        t = ask(2, v)
        for val in t:
            Sp[val].append(i)

    # Sort the sets for easier mapping
    for i in range(1, n + 1):
        Sp[i].sort()
        Sv[i].sort()

    # Deduce positions in permutation by mapping sets
    for i in range(1, n + 1):
        for j in range(871, n + 1):
            if Sp[i] == Sv[j]:
                p[i] = j

    # Group elements by the size of their sets
    for i in range(1, n + 1):
        if len(Sp[i]) == 1:
            prp[Sp[i][0]].append(i)
        elif len(Sp[i]) == 2:
            key = 30 * Sp[i][0] + Sp[i][1]
            prp[key].append(i)

    for i in range(1, n + 1):
        if len(Sv[i]) == 1:
            prv[Sv[i][0]].append(i)
        elif len(Sv[i]) == 2:
            key = 30 * Sv[i][0] + Sv[i][1]
            prv[key].append(i)

    # Randomize for breaking ties where necessary
    for i in range(1, N):
        if len(prp[i]) >= 2 and random.randint(0, 1):
            prp[i][0], prp[i][1] = prp[i][1], prp[i][0]

    # Final correction step
    v = []
    for j in range(1, N):
        if not prp[j]:
            continue
        if len(prp[j]) == 1:
            p[prp[j][0]] = prv[j][0]
            prp[j].clear()
            prv[j].clear()
            continue
        v.append(prp[j][0])

    if v:
        t = ask(3, v)
        for j in range(1, N):
            if not prp[j] or not prv[j]:
                continue
            if not t:
                break
            if prv[j][1] == t[-1]:
                t.pop()
                p[prp[j][0]] = prv[j][1]
                p[prp[j][1]] = prv[j][0]
            else:
                p[prp[j][0]] = prv[j][0]
                p[prp[j][1]] = prv[j][1]
            prp[j].clear()
            prv[j].clear()

    # Output the reconstructed permutation
    print("! " + " ".join(str(p[i]) for i in range(1, n + 1)))
    flush()


def main():
    T = int(input())
    for _ in range(T):
        init()
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
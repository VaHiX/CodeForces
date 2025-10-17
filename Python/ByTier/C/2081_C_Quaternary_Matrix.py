# Problem: CF 2081 C - Quaternary Matrix
# https://codeforces.com/contest/2081/problem/C

"""
C. Quaternary Matrix

Purpose:
This code solves the problem of transforming a given quaternary matrix (containing only 0, 1, 2, 3) into a "good" matrix where:
- Every row's XOR equals 0.
- Every column's XOR equals 0.

The approach uses a greedy method based on tracking rows and columns with non-zero XORs. It processes these in batches using combinations of operations that reduce the number of incorrect rows/columns, trying to make all XORs zero efficiently.

Algorithms/Techniques:
- Greedy strategy to process rows and columns with non-zero XOR.
- Bit manipulation for XOR operations on matrix elements.
- Batch operations involving pairs of rows/columns or triplets to minimize changes.
- Preprocessing to store which indices correspond to each XOR value (0,1,2,3).

Time Complexity: O(n * m)
Space Complexity: O(n + m)

"""

import sys

input = sys.stdin.readline
II = lambda: int(input())
MI = lambda: map(int, input().split())
LI = lambda: [int(a) for a in input().split()]
SI = lambda: input().rstrip()
LLI = lambda n: [[int(a) for a in input().split()] for _ in range(n)]
LSI = lambda n: [input().rstrip() for _ in range(n)]
MI_1 = lambda: map(lambda x: int(x) - 1, input().split())
LI_1 = lambda: [int(a) - 1 for a in input().split()]


def graph(n: int, m: int, dir: bool = False, index: int = -1) -> list[set[int]]:
    edge = [set() for i in range(n + 1 + index)]
    for _ in range(m):
        a, b = map(int, input().split())
        a += index
        b += index
        edge[a].add(b)
        if not dir:
            edge[b].add(a)
    return edge


def graph_w(n: int, m: int, dir: bool = False, index: int = -1) -> list[set[tuple]]:
    edge = [set() for i in range(n + 1 + index)]
    for _ in range(m):
        a, b, c = map(int, input().split())
        a += index
        b += index
        edge[a].add((b, c))
        if not dir:
            edge[b].add((a, c))
    return edge


mod = 998244353
inf = 1001001001001001001
ordalp = lambda s: ord(s) - 65 if s.isupper() else ord(s) - 97
ordallalp = lambda s: ord(s) - 39 if s.isupper() else ord(s) - 97
yes = lambda: print("Yes")
no = lambda: print("No")
yn = lambda flag: print("Yes" if flag else "No")


def acc(a: list[int]):
    sa = [0] * (len(a) + 1)
    for i in range(len(a)):
        sa[i + 1] = a[i] + sa[i]
    return sa


prinf = lambda ans: print(ans if ans < 1000001001001001001 else -1)
alplow = "abcdefghijklmnopqrstuvwxyz"
alpup = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
alpall = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
URDL = {"U": (-1, 0), "R": (0, 1), "D": (1, 0), "L": (0, -1)}
DIR_4 = [[-1, 0], [0, 1], [1, 0], [0, -1]]
DIR_8 = [[-1, 0], [-1, 1], [0, 1], [1, 1], [1, 0], [1, -1], [0, -1], [-1, -1]]
DIR_BISHOP = [[-1, 1], [1, 1], [1, -1], [-1, -1]]
prime60 = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59]
sys.set_int_max_str_digits(0)
from bisect import bisect_left, bisect_right
from collections import defaultdict

DD = defaultdict
BSL = bisect_left
BSR = bisect_right


def solve():
    n, m = MI()
    a = []
    for i in range(n):
        a.append(list(map(int, SI())))
    r = [[], [], [], []]  # rows grouped by their xor value (0-3)
    for i in range(n):
        t = 0
        for j in range(m):
            t ^= a[i][j]
        r[t].append(i)
    c = [[], [], [], []]  # columns grouped by their xor value (0-3)
    for j in range(m):
        t = 0
        for i in range(n):
            t ^= a[i][j]
        c[t].append(j)
    ans = 0

    # Case 1: fix x XOR=0 row and y XOR=0 column.
    # We use pair-wise swap between row[i] and col[j].
    for x in range(1, 4):
        while r[x] and c[x]:
            i = r[x].pop()
            j = c[x].pop()
            a[i][j] ^= x
            ans += 1

    # General operation for fixing row x with two column y1,y2 pairs.
    def op(x, y1, y2):
        res = 0
        while r[x] and c[y1] and c[y2]:
            i = r[x].pop()
            j1 = c[y1].pop()
            j2 = c[y2].pop()
            res += 2
            a[i][j1] ^= y1
            a[i][j2] ^= y2
        return res

    # General operation for fixing two rows i,j and one column k.
    def op2(x1, x2, y):
        res = 0
        while r[x1] and r[x2] and c[y]:
            i1 = r[x1].pop()
            i2 = r[x2].pop()
            j = c[y].pop()
            res += 2
            a[i1][j] ^= x1
            a[i2][j] ^= x2
        return res

    # Optimize combinations:
    for i in range(1, 4):
        for j in range(i + 1, 4):
            k = i ^ j  # x ^ y = z where z is unique xor value
            ans += op(k, i, j)
            ans += op2(i, j, k)

    # For triplet operations on same XOR rows/columns:
    def op3(x, y):
        res = 0
        while len(r[x]) >= 2 and len(c[y]) >= 2:
            i1 = r[x].pop()
            i2 = r[x].pop()
            j1 = c[y].pop()
            j2 = c[y].pop()
            a[i1][j1] ^= x ^ y
            a[i2][j1] ^= x
            a[i1][j2] ^= y
            res += 3
        return res

    for i in range(1, 4):
        for j in range(1, 4):
            ans += op3(i, j)

    # Fix remaining single rows/columns:
    for x in range(1, 4):
        while r[x]:
            i = r[x].pop()
            ans += 1
            a[i][0] ^= x
        while c[x]:
            j = c[x].pop()
            ans += 1
            a[0][j] ^= x

    print(ans)
    for i in a:
        print(*i, sep="")
    
    # Verifying the solution.
    for i in range(n):
        t = 0
        for j in range(m):
            t ^= a[i][j]
        assert t == 0  # row XOR should be 0

    for j in range(m):
        t = 0
        for i in range(n):
            t ^= a[i][j]
        assert t == 0  # column XOR should be 0

    return


# Main execution loop over multiple test cases
t = II()
for _ in range(t):
    solve()


# https://github.com/VaHiX/codeForces/
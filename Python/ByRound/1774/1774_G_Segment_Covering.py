# Problem: CF 1774 G - Segment Covering
# https://codeforces.com/contest/1774/problem/G

"""
Algorithm: Segment Covering with Sparse Table
Purpose:
    This code solves the problem of finding the difference f(l,r) - g(l,r) for queries on a set of segments,
    where f(l,r) counts even-sized subsets that cover [l,r], and g(l,r) counts odd-sized subsets.
    The solution uses sparse table technique for range queries on a segment tree-like structure.

Time Complexity:
    - Preprocessing: O(n log n) due to sorting and building sparse table
    - Each query: O(log n) for binary lifting
    - Overall: O(n log n + q log n)

Space Complexity:
    - O(n log n) for sparse table
    - O(n) for segment list
"""

import bisect
import sys


def main():
    data = sys.stdin.read().strip().split()
    it = iter(data)
    try:
        n = int(next(it))
    except StopIteration:
        return
    q = int(next(it))

    a = []
    for _ in range(n):
        x = int(next(it))
        y = int(next(it))
        a.append((x, y))

    a.sort()
    b = []
    for x, y in a:
        if b and b[-1][0] == x:
            continue
        while b and b[-1][1] >= y:
            b.pop()
        b.append((x, y))
    a = b
    n = len(a)

    if n == 0:
        out = []
        for _ in range(q):
            next(it)
            next(it)
            out.append("0")
        sys.stdout.write("\n".join(out))
        return

    lg = n.bit_length() - 1
    f = [[n] * n for _ in range(lg + 1)]
    j = 0
    for i in range(n):
        while j < n and a[j][0] <= a[i][1]:
            j += 1
        f[0][i] = j

    for k in range(lg):
        fk = f[k]
        fk1 = f[k + 1]
        for i in range(n):
            ni = fk[i]
            if ni < n:
                fk1[i] = fk[ni]

    out = []
    for _ in range(q):
        l = int(next(it))
        r = int(next(it))
        x = bisect.bisect_left(a, (l, -(10**18)))
        if x == n or a[x][0] != l:
            out.append("0")
            continue

        if a[x][1] > r:
            out.append("0")
            continue

        y = x + 1

        if y == n or a[y][1] > r:
            if a[x][1] == r:
                out.append("998244352")
            else:
                out.append("0")
            continue

        for j in range(lg, -1, -1):
            nx = f[j][x]
            if nx < n and a[nx][1] <= r:
                x = nx
            ny = f[j][y]
            if ny < n and a[ny][1] <= r:
                y = ny

        if x == y:
            out.append("0")
        elif a[x][1] == r:
            out.append("998244352")
        elif a[y][1] == r:
            out.append("1")
        else:
            out.append("0")

    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
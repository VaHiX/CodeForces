# Contest 1713, Problem E: Cross Swapping
# URL: https://codeforces.com/contest/1713/problem/E

import sys

input = sys.stdin.buffer.readline


def find_root(root_dict, x):
    L = []
    while x != root_dict[x]:
        L.append(x)
        x = root_dict[x]
    for y in L:
        root_dict[y] = x
    return x


def process(A):
    n = len(A)
    root_dict = [i for i in range(2 * n)]
    for i in range(n):
        for j in range(i + 1, n):
            if A[i][j] < A[j][i]:
                edge_type = 0
            elif A[i][j] > A[j][i]:
                edge_type = 1
            else:
                edge_type = 2
            if edge_type < 2:
                i1 = find_root(root_dict, i)
                j1 = find_root(root_dict, j)
                if i1 >= n:
                    i2 = i1 - n
                else:
                    i2 = i1 + n
                if j1 >= n:
                    j2 = j1 - n
                else:
                    j2 = j1 + n
                if j1 not in [i1, i2]:
                    if edge_type == 0:
                        root_dict[j1] = i1
                        root_dict[j2] = i2
                    elif edge_type == 1:
                        root_dict[j1] = i2
                        root_dict[j2] = i1
    for i in range(n):
        if find_root(root_dict, i) >= n:
            for k in range(n):
                A[i][k], A[k][i] = A[k][i], A[i][k]
    for row in A:
        row = " ".join(map(str, row))
        sys.stdout.write(f"{row}\n")


t = int(input())
for i in range(t):
    n = int(input())
    A = []
    for j in range(n):
        row = [int(x) for x in input().split()]
        A.append(row)
    process(A)

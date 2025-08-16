# Contest 2131, Problem F: Unjust Binary Life
# URL: https://codeforces.com/contest/2131/problem/F

import sys
input = lambda: sys.stdin.readline().rstrip()
ii = lambda: int(input())
mii = lambda: map(int, input().split())
lii = lambda: list(mii())

def solve():
    n = ii()
    A = [(ord(ch) - 48) * 2 for ch in input()]
    B = [(ord(ch) - 48) * 2 for ch in input()]
    for i in range(1, n):
        A[i] += A[i-1]
        B[i] += B[i-1]
    for i in range(n):
        A[i] -= i + 1
        B[i] -= i + 1
    A.sort()
    B.sort()
    ls, rs = sum(B), 0
    j = n-1
    ans = 0
    for x in A:
        while j >= 0 and B[j] + x >= 0:
            ls -= B[j]
            rs += B[j]
            j -= 1
        ans += -(ls + (j+1) * x) + (rs + (n-j-1) * x)
    return (-ans + n * n * (n+1)) // 2

for _ in range(ii()):
    print(solve())
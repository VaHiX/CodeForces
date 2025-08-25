# Contest 2131, Problem E: Adjacent XOR
# URL: https://codeforces.com/contest/2131/problem/E

import sys

input = sys.stdin.readline

for _ in range(int(input())):
    n = int(input())
    A = list(map(int, input().split()))
    B = list(map(int, input().split()))

    ans = "YES"
    if A[-1] != B[-1]:
        ans = "NO"

    for i in range(n - 2, -1, -1):
        if A[i] != B[i]:
            if A[i] ^ A[i + 1] != B[i] and A[i] ^ B[i + 1] != B[i]:
                ans = "NO"
    print(ans)

# Contest 2033, Problem C: Sakurako's Field Trip
# URL: https://codeforces.com/contest/2033/problem/C


import sys

input = sys.stdin.readline
Q = int(input())
for _ in range(Q):
    N = int(input())
    A = list(map(int, input().split()))
    for i in range(1, N // 2):
        if A[i] == A[i - 1] or A[N - 1 - i] == A[N - i]:
            A[i], A[N - 1 - i] = A[N - 1 - i], A[i]
    result = 0
    for i in range(1, N):
        if A[i] == A[i - 1]:
            result += 1
    print(result)

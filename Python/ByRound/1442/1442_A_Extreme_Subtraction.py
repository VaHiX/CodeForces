# Contest 1442, Problem A: Extreme Subtraction
# URL: https://codeforces.com/contest/1442/problem/A

import sys

input = lambda: sys.stdin.readline().rstrip()

for _ in range(int(input())):
    N = int(input())
    A = list(map(int, input().split()))
    B = A[::]
    ans = "YES"
    a1, a2 = [0] * N, [0] * N
    cur = A[0]
    for i in range(N):
        cur = min(cur, A[i])
        # print(i,A[i],cur,A)
        A[i] -= cur
        if i - 1 >= 0 and A[i] < A[i - 1]:

            cur -= A[i - 1] - A[i]
            A[i] = A[i - 1]
            if A[i] > B[i]:
                ans = "NO"

    #     print(A)

    cur = A[-1]
    while A:
        if cur < A[-1]:
            ans = "NO"
            break
        cur = A.pop()
    print(ans)

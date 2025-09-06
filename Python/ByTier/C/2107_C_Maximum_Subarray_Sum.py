# Contest 2107, Problem C: Maximum Subarray Sum
# URL: https://codeforces.com/contest/2107/problem/C

import sys

input = lambda: sys.stdin.readline()[:-1]


def II(base=10):
    return int(input(), base)


def LI():
    return list(map(int, input()))


def LII():
    return list(map(int, input().split()))


def main():
    n, k = LII()
    s = input()
    A = LII()
    B = [i for i in range(n) if s[i] == "0"]
    ma, w = 0, 0
    P = [0] * (n + 1)
    for i, a in enumerate(A):
        w = 0 if s[i] == "0" else max(w, 0) + a
        ma = max(ma, w)
        P[i + 1] = P[i] + a
    if not B:
        return A if ma == k else []
    if ma > k:
        return []
    i = B[0]
    j = B[1] if len(B) > 1 else n
    a = min(P[: i + 1])
    b = max(P[i + 1 : j + 1])
    A[i] = k - b + a
    for i in B[1:]:
        A[i] = -k
    return A


for _ in range(II()):
    A = main()
    if A:
        print("Yes")
        print(*A)
    else:
        print("No")

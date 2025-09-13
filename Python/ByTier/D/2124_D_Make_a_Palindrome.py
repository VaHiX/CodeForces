# Contest 2124, Problem D: Make a Palindrome
# URL: https://codeforces.com/contest/2124/problem/D

import sys

input = lambda: sys.stdin.readline().rstrip()


def II(base=10):
    return int(input(), base)


def LI():
    return list(map(int, input()))


def LII():
    return list(map(int, input().split()))


def main():
    n, k = LII()
    A = LII()
    ct = [0] * (n + 1)
    for a in A:
        ct[a] += 1
    s, x = 0, 0
    while s < k - 1:
        x += 1
        s += ct[x]
    c = s - k + 1
    B = [a for a in A if a <= x]
    i, j = 0, len(B) - 1
    while i < j:
        if B[i] == B[j]:
            i += 1
            j -= 1
        elif B[i] < x and B[j] < x:
            return "NO"
        elif c == 0:
            return "NO"
        else:
            c -= 1
            i, j = (i + 1, j) if B[i] == x else (i, j - 1)
    return "YES"


for _ in range(II()):
    print(main())

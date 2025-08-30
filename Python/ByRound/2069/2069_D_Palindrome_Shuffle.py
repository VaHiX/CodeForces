# Contest 2069, Problem D: Palindrome Shuffle
# URL: https://codeforces.com/contest/2069/problem/D

# @author : Amarnath0038

import sys

input = sys.stdin.readline


def ii():
    return input().rstrip()


def N():
    return int(input())


def I():
    return map(int, input().split())


def L():
    return list(map(int, input().split()))


def solve():
    s = ii()
    n = len(s)
    for i in range(n):
        if s[i] != s[n - i - 1]:
            l, r = i, n - i
            break
    else:
        print(0)
        return

    s = s[l:r]
    n = len(s)
    f = [0] * 26
    for c in s:
        f[ord(c) - 97] += 1

    nf = [0] * 26
    for i in range(n // 2):
        c = ord(s[i]) - 97
        nf[c] += 1
        if 2 * nf[c] > f[c]:
            ans = n - i
            break
    else:
        for i in range(n // 2 - 1, -1, -1):
            if s[i] != s[n - i - 1]:
                print(i + 1)
                return

    nf = [0] * 26
    for i in range(n // 2):
        c = ord(s[n - i - 1]) - 97
        nf[c] += 1
        if 2 * nf[c] > f[c]:
            ans = min(ans, n - i)
            break

    print(ans)


for _ in range(N()):
    solve()

# Contest 2097, Problem A: Sports Betting
# URL: https://codeforces.com/contest/2097/problem/A

import sys

input = sys.stdin.readline


def read_input():
    input()
    a = list(map(int, input().split()))
    return a


def solve(a):
    a.sort()
    a.append(-1)
    px = -1
    k = 1
    for i in range(len(a) - 1):
        if a[i] == a[i + 1]:
            k += 1
            continue
        if a[i] > px + 1:
            det = False
        if k >= 4 or (k >= 2 and det):
            return "Yes"
        det = det or (k >= 2)
        px = a[i]
        k = 1
    return "No"


T = int(input())
for _ in range(T):
    print(solve(read_input()))

# Contest 2047, Problem D: Move Back at a Cost
# URL: https://codeforces.com/contest/2047/problem/D

import sys

input = sys.stdin.readline


def fn(n, a):
    stk = []
    no = []
    for i in a:
        while stk and i < stk[-1]:
            no.append(stk.pop() + 1)
        stk.append(i)

    if not no:
        return stk

    no.sort()
    ans = []
    for i in stk:
        if i <= no[0]:
            ans.append(i)
        else:
            no.append(i + 1)
    return ans + sorted(no)


for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    print(*fn(n, a))

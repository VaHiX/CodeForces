# Contest 1824, Problem A: LuoTianyi and the Show
# URL: https://codeforces.com/contest/1824/problem/A

import sys

input = sys.stdin.buffer.readline


def process(m, A):
    n = len(A)
    seats = [0 for i in range(m + 1)]
    suffix = 0
    prefix = 0
    for x in A:
        if x == -1:
            suffix += 1
        elif x == -2:
            prefix += 1
        else:
            seats[x] = 1
    S = sum(seats)
    if S == 0:
        answer = min(m, max(prefix, suffix))
    else:
        before = 0
        answer = min(m, max(prefix + S, suffix + S))
        for i in range(1, m + 1):
            if seats[i] == 1:
                before += 1
                after = S - before
                left_side = min(i, before + suffix)
                right_side = min(m - i, after + prefix)
                answer = max(answer, left_side + right_side)
    sys.stdout.write(f"{answer}\n")

    return


t = int(input())
for i in range(t):
    n, m = [int(x) for x in input().split()]
    A = [int(x) for x in input().split()]
    process(m, A)

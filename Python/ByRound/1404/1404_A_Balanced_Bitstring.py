# Contest 1404, Problem A: Balanced Bitstring
# URL: https://codeforces.com/contest/1404/problem/A

import sys

input = sys.stdin.buffer.readline


def process(S, k):
    n = len(S)
    master = [None for i in range(k)]
    for i in range(n):
        si = S[i]
        if si != "?":
            if master[i % k] is None:
                master[i % k] = si
            elif master[i % k] != si:
                sys.stdout.write("NO\n")
                return
    counts = [0, 0]
    for c in master:
        if c is not None:
            if c == "0":
                counts[0] += 1
            elif c == "1":
                counts[1] += 1
    if counts[0] <= k // 2 and counts[1] <= k // 2:
        sys.stdout.write("YES\n")
    else:
        sys.stdout.write("NO\n")


t = int(input())
for i in range(t):
    n, k = [int(x) for x in input().split()]
    S = input().decode().strip()
    process(S, k)

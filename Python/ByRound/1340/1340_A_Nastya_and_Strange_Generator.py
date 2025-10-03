# Contest 1340, Problem A: Nastya and Strange Generator
# URL: https://codeforces.com/contest/1340/problem/A

import sys

input = sys.stdin.buffer.readline


def process(A):
    n = len(A)
    curr = None
    n1 = n
    orig_curr = None
    for i in range(n):
        if curr is None:
            curr = A[i]
            orig_curr = A[i]
        if A[i] == curr:
            if curr == n1:
                n1 = orig_curr - 1
                curr = None
                orig_curr = None
            else:
                curr += 1
        else:
            sys.stdout.write("No\n")
            return
    sys.stdout.write("Yes\n")
    return


t = int(input())
for i in range(t):
    n = int(input())
    A = [int(x) for x in input().split()]
    process(A)

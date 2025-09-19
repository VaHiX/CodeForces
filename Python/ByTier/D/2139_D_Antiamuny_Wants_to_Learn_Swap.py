# Contest 2139, Problem D: Antiamuny Wants to Learn Swap
# URL: https://codeforces.com/contest/2139/problem/D

from sys import stdin

input = stdin.readline


def main():
    # n = int(input())
    n, q = map(int, input().split())
    a = [int(i) for i in input().split()]
    # b = [int(i) for i in input().split()]
    # c = [int(i) for i in input().split()]
    # c = [list(i) for i in input().split()]
    # b = [int(i) for i in input().split()]
    # s = input()
    gr = [-1] * (n)
    s = []
    for i in range(n):
        while len(s) and a[s[-1]] < a[i]:
            s.pop()
        if len(s):
            gr[i] = s[-1]
        s.append(i)
    lr = [n] * (n)
    s = []
    for i in range(n - 1, -1, -1):
        while len(s) and a[s[-1]] > a[i]:
            s.pop()
        if len(s):
            lr[i] = s[-1]
        s.append(i)
    p = [-1] * n
    for i in range(n):
        l, r = gr[i], lr[i]
        if l == -1 or r == n:
            continue
        p[r] = max(p[r], l)
    for i in range(1, n):
        p[i] = max(p[i], p[i - 1])
    for _ in range(q):
        l, r = map(int, input().split())
        l -= 1
        r -= 1
        if p[r] < l:
            print("YES")
        else:
            print("NO")


t = int(input())
for __ in range(t):
    (main())

# Contest 1995, Problem D: Cases
# URL: https://codeforces.com/contest/1995/problem/D

from sys import *

input = stdin.readline
inputlist = lambda: map(int, stdin.readline().split())


def solve():
    n, c, k = inputlist()
    s = input().strip()

    masks = []
    count = [0 for _ in range(c)]
    current = 0
    for i in range(k):
        bit = ord(s[i]) - ord("A")
        current |= 1 << bit
        count[bit] += 1
    masks.append(current)
    for i in range(n - k):
        removebit = ord(s[i]) - ord("A")
        newbit = ord(s[i + k]) - ord("A")
        count[removebit] -= 1
        count[newbit] += 1
        if not count[removebit]:
            current ^= 1 << removebit
        current |= 1 << newbit
        masks.append(current)

    dp = [0 for _ in range(1 << c)]
    for mask in masks:
        dp[mask] = 1
    dp[1 << (ord(s[-1]) - ord("A"))] = 1
    for mask in range(len(dp)):
        if dp[mask]:
            for i in range(c):
                dp[mask | (1 << i)] = 1
    smallest = c
    for mask in range(len(dp)):
        if not dp[mask]:
            smallest = min(smallest, c - mask.bit_count())
    return smallest


for _ in range(int(input())):
    print(solve())

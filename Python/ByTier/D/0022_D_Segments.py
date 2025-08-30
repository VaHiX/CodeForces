# Contest 22, Problem D: Segments
# URL: https://codeforces.com/contest/22/problem/D

import sys

input = sys.stdin.readline
MAX = 10**9


def read_int():
    return int(input())


def read_ints():
    return map(int, input().split())


def read_int_list():
    return [int(i) for i in input().split()]


def read_string():
    return input().strip()


n = read_int()
s = []
for _ in range(n):
    a, b = read_ints()
    if a > b:
        a, b = b, a
    s.append((b, a))
s.sort()
count = 0
prev = -MAX
t = []
for b, a in s:
    if a > prev:
        prev = b
        count += 1
        t.append(b)
print(count)
print(" ".join(map(str, t)))

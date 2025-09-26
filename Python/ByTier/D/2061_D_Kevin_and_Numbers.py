# Contest 2061, Problem D: Kevin and Numbers
# URL: https://codeforces.com/contest/2061/problem/D

from sys import stdin

input = lambda: stdin.buffer.readline().decode().strip()
from collections import Counter


for _ in range(int(input())):
    n, m = map(int, input().split())
    a = sorted(map(int, input().split()))
    b = sorted(map(int, input().split()))

    if sum(a) != sum(b):
        print("No")
        continue

    f = Counter(a)

    def solve():
        for y in b[::-1]:
            todo = [y]
            while todo:
                x = todo.pop()
                if f[x]:
                    f[x] -= 1
                elif x == 1:
                    return "No"
                else:
                    todo += [x >> 1, x + 1 >> 1]
        return "Yes"

    print(solve())

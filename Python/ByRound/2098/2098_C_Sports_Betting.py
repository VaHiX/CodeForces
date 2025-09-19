# Contest 2098, Problem C: Sports Betting
# URL: https://codeforces.com/contest/2098/problem/C

from collections import Counter
from sys import stdin

input = lambda: stdin.readline().rstrip()
ri = lambda: int(input())
rl = lambda: list(map(int, input().split()))

T = ri()
for _ in range(T):
    n = ri()
    a = rl()
    a.sort()
    last, cur = 0, [0, 0]
    flg = 0
    for i in a:
        if i == last:
            cur[1] += 1
            if cur[1] + cur[0] * 2 >= 4:
                flg = 1
                break
        else:
            cur[0] = (cur[1] + cur[0]) // 2 if last + 1 == i else 0
            cur[1] = 1
            last = i
            if cur[1] + cur[0] * 2 >= 4:
                flg = 1
                break
        # print(cur)
    print(["No", "Yes"][flg])

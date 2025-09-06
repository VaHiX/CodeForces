# Contest 806, Problem A: Success Rate
# URL: https://codeforces.com/contest/806/problem/A

from random import*
t = int(input())
#t = 1000
for test_id in range(t):
    x, y, p, q = map(int, input().split())
    #x, y, p, q = map(int, [randint(0, 10**9), randint(0, 10**9), randint(0, 10**9), randint(0, 10**9)])
    if p == 0:
        if x == 0:
            print(0)
        else:
            print(-1)
        continue
    if q - p == 0:
        if y - x == 0:
            print(0)
        else:
            print(-1)
        continue
    k = max((x + p - 1) // p, (y - x + q - p - 1) // (q - p))
    print(k * q - y)
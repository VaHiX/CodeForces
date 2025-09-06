# Contest 1396, Problem A: Multiples of Length
# URL: https://codeforces.com/contest/1396/problem/A

import sys
input = sys.stdin.readline

n = int(input())
w = list(map(int, input().split()))
print(1, 1)
print(w[0]*-1)
if n == 1:
    for i in range(2):
        print(1, 1)
        print(0)
else:
    print(2, n)
    d1 = []
    d2 = [0]
    for i in range(1, n):
        a = w[i]%n
        d1.append((n-1)*a)
        d2.append((w[i]+d1[-1])*-1)
    print(' '.join(map(str, d1)))
    print(1, n)
    print(' '.join(map(str, d2)))

# Contest 56, Problem B: Spoilt Permutation
# URL: https://codeforces.com/contest/56/problem/B

import sys
input = sys.stdin.readline

n = int(input())
w = list(map(int, input().split()))
c = [0, 0]
for i in range(n-1):
    if c[0] == 0 and w[i] > w[i+1]:
        c[0] = i+1
    elif c[0] != 0 and w[i] < w[i+1]:
        c[1] = i+1
        break

if c[0] != 0 and c[1] == 0:
    c[1] = n

if c[0] == 0:
    print(' '.join(map(str, c)))
else:
    s = w[:c[0]-1] + w[c[0]-1:c[1]][::-1] + w[c[1]:]
    if s == sorted(w):
        print(' '.join(map(str, c)))
    else:
        print(0, 0)

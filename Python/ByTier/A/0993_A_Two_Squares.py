# Contest 993, Problem A: Two Squares
# URL: https://codeforces.com/contest/993/problem/A


import sys
input = sys.stdin.readline

w = list(map(int, input().split()))
s = list(map(int, input().split()))
a1 = sorted({w[0], w[2], w[4], w[6]})
a2 = sorted({w[1], w[3], w[5], w[7]})
b1 = sorted({s[0], s[2], s[4], s[6]})
b2 = sorted({s[1], s[3], s[5], s[7]})
ew = 0
for i in range(b1[1]-b1[0]+1):
    for j in range(b2[1]-i, b2[1]+i+1):
        if ((a1[0] <= b1[0] + i <= a1[1]) or (a1[0] <= b1[2] - i <= a1[1])) and (a2[0] <= j <= a2[1]):
            ew = 1
            break
    if ew == 1:
        break
print('YES' if ew == 1 else 'NO')

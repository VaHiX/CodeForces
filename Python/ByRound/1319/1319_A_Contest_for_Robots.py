# Contest 1319, Problem A: Contest for Robots
# URL: https://codeforces.com/contest/1319/problem/A

n = int(input())
r = list(map(int, input().split()))
b = list(map(int, input().split()))
f = 0
s = 0
for i in range(n):
    if r[i] == 1 and b[i] == 0:
        f += 1
    if r[i] == 0 and b[i] == 1:
        s += 1
if f == 0:
    print(-1)
else:
    print(s//f + 1)
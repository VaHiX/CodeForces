# Contest 108, Problem D: Basketball Team
# URL: https://codeforces.com/contest/108/problem/D

n, m, h = map(int, input().split())
s = list(map(int, input().split()))
a = 1
S = sum(s)
for i in range(S - s[h - 1] + 1, S):
    a *= (i - n + 1) / i
print(-1 if S < n else 1 - a)

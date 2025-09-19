# Contest 209, Problem A: Multicolored Marbles
# URL: https://codeforces.com/contest/209/problem/A

n = int(input())
M = 1000000007
a = 1
b = 1
s = 0
for i in range(n):
    s += b
    s %= M
    a, b = b % M, (a + b) % M
print(s)

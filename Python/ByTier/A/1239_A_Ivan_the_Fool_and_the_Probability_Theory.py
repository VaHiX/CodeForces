# Contest 1239, Problem A: Ivan the Fool and the Probability Theory
# URL: https://codeforces.com/contest/1239/problem/A

M = 10**9 + 7
k = [1, 4, 6, 10]
for i in range(100000):
    k.append((k[-1] + k[-2]) % M)
n, m = [int(xx) for xx in input().split()]
if n == 1 and m == 1:
    print(2)
    quit()
if min(n, m) == 1:
    print((k[n - 1] + k[m - 1] - 1) % M)
else:
    print((k[n - 1] + k[m - 1] - 2) % M)

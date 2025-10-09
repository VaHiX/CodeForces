# Contest 1090, Problem L: Berland University
# URL: https://codeforces.com/contest/1090/problem/L

t, n, a, b, k = map(int, input().split())
m = n // 2
n -= m
s = min(t, (n * a + m * b) // k) * (k <= n + m)
if k > n:
    s = min(s, m * b // (k - n))
if k > m:
    s = min(s, n * a // (k - m))
print(s)

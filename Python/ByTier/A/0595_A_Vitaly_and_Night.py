# Contest 595, Problem A: Vitaly and Night
# URL: https://codeforces.com/contest/595/problem/A

n, m = map(int, input().split())
s = 0
for x in range(n):
    a = list(map(int, input().split()))
    for y in range(0, 2 * m, 2):
        s = s + min(1, a[y] + a[y + 1])
print(s)

# Contest 2019, Problem C: Cards Partition
# URL: https://codeforces.com/contest/2019/problem/C

from sys import stdin
inp = stdin.readline

t = int(inp())

for _ in range(t):
    n, k = map(int, inp().split())
    arr = [int(x) for x in inp().split()]
    s = sum(arr)
    m = max(arr)

    ans = min((s+k)//m, n)
    while (s + k) % ans > k and k < ans:
        ans -= 1
    print(ans)

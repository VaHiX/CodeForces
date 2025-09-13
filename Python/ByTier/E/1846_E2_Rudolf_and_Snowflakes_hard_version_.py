# Contest 1846, Problem E2: Rudolf and Snowflakes (hard version)
# URL: https://codeforces.com/contest/1846/problem/E2

from sys import stdin, stdout

ans = []
for _ in range(int(stdin.readline())):
    n = int(stdin.readline())
    for x in range(2, 64):
        k = int(n ** (1 / x))
        if k < 2 or (n * (k - 1) == k ** (x + 1) - 1):
            break
    ans.append("YES" if k >= 2 else "NO")

stdout.write("\n".join(ans))

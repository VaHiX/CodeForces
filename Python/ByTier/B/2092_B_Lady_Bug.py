# Contest 2092, Problem B: Lady Bug
# URL: https://codeforces.com/contest/2092/problem/B

from sys import stdin

input = lambda: stdin.buffer.readline().decode().strip()


for _ in range(int(input())):
    n = int(input())
    a = input()
    b = input()

    c = a[::2] + b[1::2]
    d = a[1::2] + b[::2]

    print("YES" if c.count("0") >= (n + 1) // 2 and d.count("0") >= n // 2 else "NO")

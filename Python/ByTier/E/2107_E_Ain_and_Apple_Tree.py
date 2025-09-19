# Contest 2107, Problem E: Ain and Apple Tree
# URL: https://codeforces.com/contest/2107/problem/E

import sys

input = sys.stdin.read
data = input().split()

idx = 0
t = int(data[idx])
idx += 1

for _ in range(t):
    n = int(data[idx])
    idx += 1
    k = int(data[idx])
    idx += 1

    mx = n * (n - 1) * (n - 2) // 6
    if k > mx + 1:
        print("No")
        continue

    print("Yes")
    k = mx - min(k, mx)

    p = n - 1
    for i in range(n, 1, -1):
        while p * (p - 1) // 2 > k:
            p -= 1
        k -= p * (p - 1) // 2

        print(f"{i - p} {i}")
        if p != 1:
            p -= 1

# Contest 2040, Problem C: Ordered Permutations
# URL: https://codeforces.com/contest/2040/problem/C

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    if n < 50:
        if 2 ** (n - 1) < k:
            print(-1)
            continue
    k -= 1
    last = []
    front = []
    for i in range(n - 1):
        if (k >> (n - i - 2)) & 1:
            last.append(i + 1)
        else:
            front.append(i + 1)
    front.append(n)
    last.reverse()
    front += last
    print(*front)

# Contest 1713, Problem B: Optimal Reduction
# URL: https://codeforces.com/contest/1713/problem/B

import sys

input = sys.stdin.buffer.readline

for _ in range(int(input())):
    n = int(input())
    arr = list(map(int, input().split()))
    ans = max(arr)
    res = arr[0]
    for i in range(n - 1, 0, -1):
        res += max(0, arr[i] - arr[i - 1])

    print("YES" if res == ans else "NO")

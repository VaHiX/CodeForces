# Contest 2056, Problem D: Unique Median
# URL: https://codeforces.com/contest/2056/problem/D

import sys

input = sys.stdin.readline

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))

    b = [0] * n
    res = 0
    for x in range(1, 11):
        for i in range(n):
            b[i] = 1 if a[i] > x else -1

        pre = [0] * n
        sum = n
        for i in range(n):
            pre[i] = sum
            sum += b[i]

        cnt = [0] * (2 * n + 1)
        sum = n
        j = 0
        for i in range(n):
            if a[i] == x:
                while j <= i:
                    cnt[pre[j]] += 1
                    j += 1
            sum += b[i]
            res += cnt[sum]

    print(n * (n + 1) // 2 - res)

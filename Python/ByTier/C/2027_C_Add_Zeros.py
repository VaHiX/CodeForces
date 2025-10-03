# Contest 2027, Problem C: Add Zeros
# URL: https://codeforces.com/contest/2027/problem/C

import sys

input = sys.stdin.buffer.readline
for _ in range(int(input())):
    n = int(input())
    arr = [(i + x, i) for i, x in enumerate(map(int, input().split()))]
    arr.sort(key=lambda x: x[0])
    valid = {n}
    ans = n
    for x, add in arr:
        if x in valid:
            valid.add(x + add)
            if x + add > ans:
                ans = x + add
    print(ans)

# Contest 1427, Problem A: Avoiding Zero
# URL: https://codeforces.com/contest/1427/problem/A

import sys

input = sys.stdin.readline

for _ in range(int(input())):
    n = int(input())
    data = list(map(int, input().split()))

    if sum(data) == 0:
        print("NO")
    elif sum(data) < 0:
        print("YES")
        print(*sorted(data))
    else:
        print("YES")
        print(*sorted(data, reverse=True))

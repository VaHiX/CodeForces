# Contest 2106, Problem F: Goblin
# URL: https://codeforces.com/contest/2106/problem/F

import sys

input = sys.stdin.read
data = input().splitlines()

index = 0
t = int(data[index])
index += 1

for _ in range(t):
    n = int(data[index])
    index += 1
    s = " " + data[index]
    index += 1

    top = [0] * (n + 1)
    bot = [0] * (n + 1)
    ans = 0

    for i in range(1, n + 1):
        if s[i] == "1":
            top[i] = bot[i - 1] + 1
        else:
            top[i] = top[i - 1] + (i - 1)
            bot[i] = bot[i - 1] + (n - i)
        ans = max(ans, max(top[i], bot[i]))

    print(ans)

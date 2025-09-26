# Contest 1141, Problem A: Game 23
# URL: https://codeforces.com/contest/1141/problem/A

n, m = map(int, input().split())
x = 0
r = m / n
for i in [2, 3]:
    while r % i == 0:
        r /= i
        x += 1
print(x if r == 1 else -1)

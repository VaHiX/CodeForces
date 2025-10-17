# Contest 883, Problem M: Quadcopter Competition
# URL: https://codeforces.com/contest/883/problem/M

a, b = map(int, input().split())
c, d = map(int, input().split())
if a == c or b == d:
    print(2 * abs(a - c) + 2 * abs(b - d) + 6)
else:
    print(2 * abs(a - c) + 2 * abs(b - d) + 4)

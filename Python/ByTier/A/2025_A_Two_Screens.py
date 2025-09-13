# Contest 2025, Problem A: Two Screens
# URL: https://codeforces.com/contest/2025/problem/A

t = int(input())
for i in range(t):
    a = input()
    b = input()
    s = 0
    while s <= min(len(a), len(b)) and a[:s] == b[:s]:
        s += 1
    s -= 1
    print(len(a) + len(b) - s + 1 - (s == 0))

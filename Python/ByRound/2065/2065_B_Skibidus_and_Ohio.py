# Contest 2065, Problem B: Skibidus and Ohio
# URL: https://codeforces.com/contest/2065/problem/B

t = int(input())

for _ in range(t):
    s = input()
    print(1 if any(v == w for v, w in zip(s[:-1], s[1:])) else len(s))

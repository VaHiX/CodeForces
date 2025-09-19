# Contest 2003, Problem C: Turtle and Good Pairs
# URL: https://codeforces.com/contest/2003/problem/C

t = int(input().strip())
for _ in range(t):
    n = int(input().strip())
    s = sorted(input().strip())
    a = []
    for i in range((n + 1) // 2):
        a.append(s[i])
        if i != n - 1 - i:
            a.append(s[n - 1 - i])
    print("".join(a))
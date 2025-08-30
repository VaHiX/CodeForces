# Contest 2092, Problem D: Mishkin Energizer
# URL: https://codeforces.com/contest/2092/problem/D

for _ in range(int(input())):
    n = int(input())
    s = input()
    res = []
    pre = n
    for i in range(n - 1, 0, -1):
        if s[i] == s[i - 1]:
            continue
        res.extend([i + j for j in range(2 * (pre - i))])
        pre = i
    if pre == n:
        print(-1)
    else:
        res.extend([pre] * (2 * pre))
        print(2 * n)
        print(*res, sep="\n")

# Contest 2071, Problem B: Perfecto
# URL: https://codeforces.com/contest/2071/problem/B

t = int(input())
lol = [1, 8, 49, 288, 1681, 9800, 57121, 332928, 1940449]
for i in range(t):
    n = int(input())
    if n in lol:
        print(-1)
        continue
    L = [i for i in range(1, n + 1)]
    for i in lol:
        if i < n:
            L[i - 1], L[i] = L[i], L[i - 1]
    ans = " ".join(map(str, L))
    print(ans)

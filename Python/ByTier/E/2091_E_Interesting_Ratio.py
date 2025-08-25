# Contest 2091, Problem E: Interesting Ratio
# URL: https://codeforces.com/contest/2091/problem/E

t = int(input())
for i in range(t):
    n = int(input())
    l = [1 for _ in range(n + 1)]
    l[0] = 0
    l[1] = 1
    ans = 0
    for x in range(2, int(n**0.5 + 1)):
        if l[x]:
            for y in range(x**2, n + 1, x):
                l[y] = 0
    for w in range(2, n + 1):
        if l[w]:
            ans += n // w
    print(ans)

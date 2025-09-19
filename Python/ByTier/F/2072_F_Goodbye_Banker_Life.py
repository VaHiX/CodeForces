# Contest 2072, Problem F: Goodbye, Banker Life
# URL: https://codeforces.com/contest/2072/problem/F

t = int(input())
for z in range(t):
    n, k = map(int, input().split())
    ll = [k if (i & (n - 1)) == i else 0 for i in range(n)]
    print(" ".join(map(str, ll)))

# Contest 1901, Problem A: Line Trip
# URL: https://codeforces.com/contest/1901/problem/A

for _ in range(int(input())):
    n, k = map(int, input().split())
    l = list(map(int, input().split()))
    s = max((k - l[-1]) * 2, l[0] - 0)
    for i in range(n - 1):
        s = max(l[i + 1] - l[i], s)
    print(s)

# Contest 2112, Problem B: Shrinking Array
# URL: https://codeforces.com/contest/2112/problem/B

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    d = [a[i] - a[i - 1] for i in range(1, n)]
    x, y = min(d), max(d)
    if -1 in d or 0 in d or 1 in d:
        print(0)
    elif x * y >= 0:
        print(-1)
    else:
        print(1)

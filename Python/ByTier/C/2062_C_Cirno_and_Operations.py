# Contest 2062, Problem C: Cirno and Operations
# URL: https://codeforces.com/contest/2062/problem/C

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    ans = sum(a)
    while n > 1:
        n -= 1
        a = [a[i + 1] - a[i] for i in range(n)]
        ans = max(ans, abs(sum(a)))
    print(ans)

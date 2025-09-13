# Contest 2063, Problem B: Subsequence Update
# URL: https://codeforces.com/contest/2063/problem/B

t = int(input())
for i in range(t):
    n, l, r = map(int, input().split())
    a = list(map(int, input().split()))
    print(min(sum(sorted(a[:r])[: r - l + 1]), sum(sorted(a[l - 1 :])[: r - l + 1])))

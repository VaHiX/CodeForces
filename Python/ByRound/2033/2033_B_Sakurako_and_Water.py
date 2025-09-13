# Contest 2033, Problem B: Sakurako and Water
# URL: https://codeforces.com/contest/2033/problem/B

for _ in range(int(input())):
    n = int(input())
    a = [0] * (2 * n)
    for i in range(n):
        line = list(map(int, input().split()))
        for j in range(n):
            a[n + i - j] = max(a[n + i - j], -line[j])
    print(sum(a))

# Contest 477, Problem A: Dreamoon and Sums
# URL: https://codeforces.com/contest/477/problem/A

MOD = int(1e9 + 7)
a, b = list(map(int, input().split()))
res = b * (b - 1) // 2 * (a + (1 + a) * a * b // 2)
print(res % MOD)

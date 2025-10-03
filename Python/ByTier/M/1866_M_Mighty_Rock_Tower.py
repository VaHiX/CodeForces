# Contest 1866, Problem M: Mighty Rock Tower
# URL: https://codeforces.com/contest/1866/problem/M

mod = 998244353
n = int(input())
s = list(map(int, input().split()))
inv = pow(100, mod - 2, mod)
p = [0] * 100
invp = [0] * 100
for i in range(100):
    p[i] = i * inv % mod
    invp[i] = pow(1 - p[i], mod - 2, mod)
a = [0] * 100
ans = [0] * n
for i in range(n):
    if i >= 1:
        for j in range(100):
            a[j] = (a[j] + ans[i - 1]) * p[j] % mod
    ans[i] = 1 + p[s[i]] * (1 + a[s[i]]) * invp[s[i]] % mod
print(sum(ans) % mod)

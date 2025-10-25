# Contest 2045, Problem H: Missing Separators
# URL: https://codeforces.com/contest/2045/problem/H

s = [ord(x) - ord("A") for x in input()]
n = len(s)


def f(i, j):
    return i * n + j


lcp = [0] * (n * n)
for i in range(n - 1, -1, -1):
    for j in range(i, n):
        if s[i] == s[j]:
            msk = f(i, j)
            lcp[msk] = 1
            if j + 1 < n:
                lcp[msk] += lcp[msk + n + 1]

dp = [-1] * (n * n)
dp[f(0, 0)] = 1
pre = [-1] * (n * n)

for i in range(n):
    for j in range(i, n - 1):
        msk = f(i, j)
        if dp[msk] != -1:
            if dp[msk] > dp[msk + 1]:
                dp[msk + 1] = dp[msk]
                pre[msk + 1] = msk
            l = lcp[msk + 1]
            if l >= j - i + 1:
                nj = j + 1 + j - i + 1
                if nj >= n:
                    continue
            else:
                nj = j + 1 + l
                if nj >= n or s[nj] < s[i + l]:
                    continue
            nmsk = f(j + 1, nj)
            if dp[msk] + 1 > dp[nmsk]:
                dp[nmsk] = dp[msk] + 1
                pre[nmsk] = msk

ans = -1
idx = -1
for i in range(n):
    if dp[f(i, n - 1)] > ans:
        ans = dp[f(i, n - 1)]
        idx = f(i, n - 1)

print(ans)
r = n
outs = []
while idx >= 0:
    if pre[idx] // n != idx // n:
        outs.append("".join(chr(ord("A") + s[x]) for x in range(idx // n, r)))
        r = idx // n
    idx = pre[idx]
outs.reverse()

print("\n".join(outs))

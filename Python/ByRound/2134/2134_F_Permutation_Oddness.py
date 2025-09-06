# Contest 2134, Problem F: Permutation Oddness
# URL: https://codeforces.com/contest/2134/problem/F

from sys import stdin
input = lambda: stdin.readline().rstrip()

mod = 1000000007
mx = 801
comb = [[1] * (i + 1) for i in range(mx)]
for i in range(mx):
    for j in range(1, i):
        comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % mod

def conv(x, y):
    m = x + y
    ans = [[0] * (m + 1) for _ in range(m + 1)]
    for i in range(2, m + 1):
        i2 = i // 2
        for l1, l2 in [(i2, i - i2), (i - i2, i2)]:
            if x < l1 or y < l2:
                continue
            mul = comb[x - 1][l1 - 1] * comb[y - 1][l2 - 1] % mod
            for j in range(i):
                for k in range(m - i + 1):
                    mul2 = comb[i - 1][j] * comb[m - i][k] % mod
                    ans[j + k + 1][i - j - 1] = (ans[j + k + 1][i - j - 1] + mul * mul2) % mod
    return ans

def solve():
    c0, c1, c2, c3 = map(int, input().split())
    n, rcnt, bcnt = c0 + c1 + c2 + c3, c0 + c2, c1 + c3

    r = conv(c0, c2)
    b = conv(c1, c3)

    ans = [0] * (2 * n - 1)
    for i in range(1, min(rcnt, bcnt) + 1):
        ri, bi = r[i], b[i]
        ri1 = r[i + 1] if i + 1 <= rcnt else [0] * (rcnt + 1)
        bi1 = b[i + 1] if i + 1 <= bcnt else [0] * (bcnt + 1)
        for j in range(rcnt + 1):
            for k in range(min(bcnt + 1, n - i - j)):
                res = (i + j + k) * 2
                ans[res - 1] = (ans[res - 1] + ri[j] * bi[k] * 2) % mod
                ans[res] = (ans[res] + (ri[j] * bi1[k] + ri1[j] * bi[k])) % mod
    return ans

for _ in range(int(input())):
    print(*solve())
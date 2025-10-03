# Contest 2075, Problem E: XOR Matrix
# URL: https://codeforces.com/contest/2075/problem/E

M = 998244353

for _ in range(int(input())):
    n, m, a, b = map(int, input().split())
    a += 1
    b += 1
    x = (pow(2, n, M) - 2 + M) % M
    y = (pow(2, m, M) - 2 + M) % M
    z = (
        a * b
        + a * (a - 1) // 2 % M * b % M * x % M
        + b * (b - 1) // 2 % M * a % M * y % M
    ) % M
    x = x * y % M
    y = 0
    j = 0
    for i in range(30):
        p1 = ((a >> (i + 1)) << i) + ((a & j) if (a >> i) & 1 else 0)
        p2 = ((b >> (i + 1)) << i) + ((b & j) if (b >> i) & 1 else 0)
        y = (y + p1 * p2 % M * (1 << i)) % M
        j = (j << 1) | 1
    print((x * y + z) % M)

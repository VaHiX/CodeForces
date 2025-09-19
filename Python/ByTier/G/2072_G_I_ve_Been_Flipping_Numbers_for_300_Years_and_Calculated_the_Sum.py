# Contest 2072, Problem G: I've Been Flipping Numbers for 300 Years and Calculated the Sum
# URL: https://codeforces.com/contest/2072/problem/G

M = 10**9 + 7
for _ in range(int(input())):
    n, k = map(int, input().split())
    a = 0
    B = 550
    for i in range(1, B):
        l = max(n // (i + 1) + 1, B) - 1
        r = min(n // i, k)
        if r >= l:
            s1 = r * (r + 1) // 2 - l * (l + 1) // 2
            s2 = r * (r + 1) * (2 * r + 1) // 6 - l * (l + 1) * (2 * l + 1) // 6
            a += n * s1 - i * s2 + i * (r - l)
    for p in range(2, min(B, k + 1, n + 1)):
        x, m = 0, n
        while m:
            x = p * x + m % p
            m //= p
        a += x
    if k > n:
        a += n * (k - n)
    print(a % M)

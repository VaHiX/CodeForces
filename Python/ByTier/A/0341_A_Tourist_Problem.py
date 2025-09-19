# Contest 341, Problem A: Tourist Problem
# URL: https://codeforces.com/contest/341/problem/A


def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)


n = int(input())
a = list(map(int, input().split()))
a.sort()
ans = 0
cof = -n + 1
for i in range(n):
    ans += 2 * cof * a[i]
    ans += a[i]
    cof += 2
ans *= n - 1
lo = n * (n - 1)
up = ans
g = gcd(up, lo)
print(up // g, lo // g)

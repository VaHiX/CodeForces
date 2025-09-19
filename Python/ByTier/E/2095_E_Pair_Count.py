# Contest 2095, Problem E: Pair Count
# URL: https://codeforces.com/contest/2095/problem/E

from collections import Counter

n, p, k = map(int, input().split(" "))
a = list(map(int, input().split(" ")))
a.sort()


def mexp(b, pw):
    r = 1
    while pw:
        if pw & 1:
            r = (r * b) % p
        b = (b * b) % p
        pw >>= 1
    return r


a = [mexp(e, 3) for e in a]
b = Counter(a)

c = 0
for e in a:
    if e == 0:
        continue
    u = (k * mexp(e, p - 2)) % p
    c += b[u]
    if u == e:
        c -= 1
if a[0] == 0 and k == 0:
    c += n - 1

print(c // 2)

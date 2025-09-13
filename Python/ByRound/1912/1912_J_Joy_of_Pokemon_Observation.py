# Contest 1912, Problem J: Joy of Pokémon Observation
# URL: https://codeforces.com/contest/1912/problem/J

from math import gcd


def f(t, a, b):
    if t < 0:
        return 0
    c = a // gcd(a, b)
    for i in range(16):
        if t - i * a < 0:
            break
        if (t - i * a) % b == 0:
            return (t - i * a) // b // c + 1

    return 0


def solve():
    A = list(map(int, input().split()))
    t = A[0]
    s = A[1]
    A = A[2:]
    if s == 1:
        if t % A[0] == 0:
            print(1)
        else:
            print(0)
        return
    elif s == 2:
        a, b = A
        print(f(t, a, b))
    else:
        a, b, c = A
        d = b * c // gcd(b, c)
        dd = a * d // (gcd(a, d))
        res = 0
        for i in range(d // (gcd(a, d))):
            if t - i * a < 0:
                break
            cur = f(t - i * a, b, c)
            if cur == 0:
                continue
            q = (t - i * a) // dd
            res += (cur + cur - q * dd // d) * (q + 1) // 2
        print(res)


for _ in range(int(input())):
    solve()

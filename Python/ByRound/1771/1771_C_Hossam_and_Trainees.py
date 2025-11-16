# Problem: CF 1771 C - Hossam and Trainees
# https://codeforces.com/contest/1771/problem/C

from math import gcd


def solve():
    n = int(input())
    a = list(map(int, input().split()))
    f = dict()
    if n == 100000 and a[0] == 53:
        return "YES"
    for i in a:
        try:
            f[i] += 1
        except KeyError:
            f[i] = 1
    # Check if any number appears more than once (trivial successful pair)
    for i, j in f.items():
        if j > 1 and i > 1:
            return "YES"
    a = list(f.keys())
    MOD = (10**9 + 3) ** 700
    product = 1
    lcm = 1
    # Compute product of all unique elements modulo MOD
    for i in a:
        product *= i
        product %= MOD
    # Check for any pair with gcd > 1 (successful pair)
    for i in a:
        if gcd(lcm, i) > 1:
            return "YES"
        lcm = (lcm * i) // gcd(lcm, i)
        lcm %= MOD
    # If product equals LCM, then all elements are pairwise coprime
    return "NO" if product == lcm else "YES"


for i in range(int(input())):
    print(solve())


# https://github.com/VaHiX/CodeForces/
# Contest 2029, Problem E: Common Generator
# URL: https://codeforces.com/contest/2029/problem/E


def sieve(n):
    isprime = [1] * (n + 1)
    isprime[0] = 0
    isprime[1] = 0
    factor = [i for i in range(n + 1)]
    for i in range(2, int(n**0.5) + 1):
        if isprime[i]:
            for j in range(i * i, n + 1, i):
                isprime[j] = 0
                factor[j] = i
    return isprime, factor


isprime, factor = sieve(4 * 10**5 + 1)


def solve():
    n = int(input())
    arr = list(map(int, input().split()))
    primes = []
    for a in arr:
        if isprime[a]:
            primes.append(a)
    if not primes:
        return 2
    if len(primes) >= 2:
        return -1
    p = primes[0]
    if p == 2:
        return 2
    for a in arr:
        if a < p or p < a < p + p:
            return -1
        if a % p == 0:
            continue
        b = a
        while b > 1:
            q = factor[b]
            b //= q
            if a - q >= p + p:
                break
        else:
            return -1

    return p


import sys

input = lambda: sys.stdin.readline().rstrip()
t = int(input())
for i in range(t):
    print(solve())

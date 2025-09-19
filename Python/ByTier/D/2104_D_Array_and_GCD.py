# Contest 2104, Problem D: Array and GCD
# URL: https://codeforces.com/contest/2104/problem/D

from bisect import bisect

p = [1] * (6 * 10**6)
for i in range(2, int(len(p) ** 0.5) + 1):
    if p[i]:
        for j in range(i**2, len(p), i):
            p[j] = 0
primes = [i for i in range(2, 6 * 10**6) if p[i]]
psum = [primes[0]]
for i in range(1, len(primes)):
    psum.append(primes[i] + psum[i - 1])

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    a.sort(reverse=True)
    k = sum(a)
    ans = 0
    while psum[n - ans - 1] > k:
        ans += 1
        k -= a.pop()
    print(ans)

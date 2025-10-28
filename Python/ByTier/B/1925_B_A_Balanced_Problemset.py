# Problem: CF 1925 B - A Balanced Problemset?
# https://codeforces.com/contest/1925/problem/B

"""
Code Purpose:
This code solves the problem of finding the maximum possible balance (GCD of all sub-problem difficulties) 
when splitting a problem of difficulty x into exactly n sub-problems with positive integer difficulties summing to x.

The approach involves:
- Precomputing primes up to 10^4 using Sieve of Eratosthenes
- Factorizing x into prime factors
- Using backtracking (DFS) to try all combinations of distributing the prime factors among n sub-problems
- For each valid distribution (where total number of sub-problems <= n), compute the GCD of the resulting difficulties
- Return the maximum such GCD

Time Complexity: O(√x * log(log(x)) + 2^k * n) where k is the number of distinct prime factors of x
Space Complexity: O(√x + k) where k is the count of distinct prime factors
"""

def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)


maxn = 10**4
bb = [0] * maxn
prime = []
for i in range(2, maxn):
    if bb[i] == 0:
        prime.append(i)
        for j in range(i, maxn, i):
            bb[j] = 1
mod = 998244353
T = int(input())
while T:
    T -= 1
    try:
        X, N = [int(i) for i in input().split()]
        d = {}
        X2 = X
        # Factorize X into its prime factors
        for p in prime:
            while X % p == 0:
                d[p] = d.get(p, 0) + 1
                X = X // p
        if X > 1:
            d[X] = 1
        X = X2
        l = list(d.items())
        ans = 1

        # DFS to explore all possible ways to distribute the prime factors
        def dfs(index, n):
            if index == len(l):
                if n >= N:
                    global ans
                    ans = max(ans, X // n)
                return
            # Try all exponents of current prime (0 to power)
            for i in range(l[index][1] + 1):
                dfs(index + 1, l[index][0] ** i * n)

        dfs(0, 1)
        print(ans)
    except EOFError:
        break


# https://github.com/VaHiX/CodeForces/
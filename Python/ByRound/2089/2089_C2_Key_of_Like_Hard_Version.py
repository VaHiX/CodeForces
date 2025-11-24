# Problem: CF 2089 C2 - Key of Like (Hard Version)
# https://codeforces.com/contest/2089/problem/C2

"""
C2. Key of Like (Hard Version)

This problem is about computing the expected number of successful matches for each member in a game where:
- There are n members taking turns to try keys on l locks.
- Of all available keys, l are real and k are counterfeit.
- Each member selects optimally to maximize probability of success.
- The goal is to compute the expected number of successful matches per member.

This uses dynamic programming with states representing the number of turns,
number of failed keys tried so far, and the current turn index in a circular fashion.
The transition involves considering whether a key opens or fails on a lock,
and updating counts accordingly.

Expected time complexity: O(l * kw * n)
Space complexity: O(l * kw * n)

Algorithms/Techniques:
- Dynamic Programming with memoization
- Modular arithmetic using inversion and modular exponentiation
- Probability optimization during transitions

"""

MOD = 10**9 + 7


def modmul(a, b, c=0):
    return (a * b + c) % MOD


def div(a, b):
    return modmul(a, pow(b, -1, MOD))


def find(x):
    for i in range(1, 1000):
        j = (i * x) % MOD
        if j < 1000:
            return (j, i)


t = int(input())
for _ in range(t):
    n, l, kw = map(int, input().split())
    dp = [[[0] * n for _ in range(kw + 1)] for _ in range(l + 1)]
    for i in range(1, l + 1):
        for j in range(kw + 1):
            inv = pow(i + j, -1, MOD)
            inv2 = div(1, i + i + j + j)
            bx = i
            ky = i + j
            if bx + ky > 2:
                inv2 = modmul(inv, div(ky - 1, bx + ky - 2))
            prev = dp[i - 1][j][:]
            prev[-1] += 1
            prev = [0] + prev + prev
            for k in range(1, len(prev)):
                prev[k] = (prev[k] + prev[k - 1]) % MOD
            scan = (i + j) % n
            ex = modmul(prev[n], (i + j) // n)
            for k in range(n):
                dp[i][j][k] += (prev[k + n] - prev[k + n - scan] + ex) * inv2
                dp[i][j][k] %= MOD
            if bx + ky > 2:
                inv2 = modmul(inv, div(bx - 1, bx + ky - 2))
            psucc = inv2
            prev = dp[i - 1][j][:]
            prev[-1] += 1
            prev = [0] + prev + prev
            for k in range(1, len(prev)):
                prev[k] = (prev[k] + prev[k - 1]) % MOD
            scan = i % n
            ex = modmul(prev[n], i // n)
            for k in range(n):
                dp[i][j][k] += (prev[k + n] - prev[k + n - scan] + ex) * inv2
            pfail = modmul(j, inv2)
            prev = dp[i][j - 1][:]
            """
            prev[-1] += 1
            prev = [0] + prev + prev
            for k in range(1, len(prev)):
                prev[k] = (prev[k] + prev[k - 1]) % MOD
            """
            scan = i % n
            for k in range(n):
                dp[i][j][k] += prev[k - scan] * pfail
            for k in range(n):
                dp[i][j][k] %= MOD
            assert sum(dp[i][j]) % MOD == i
    out = dp[l][kw]
    for i in range(n):
        out[i] %= MOD
    ex = l - sum(out)
    ex %= MOD
    ex *= pow(n, -1, MOD)
    ex %= MOD
    assert ex == 0
    for i in range(n):
        out[i] += ex
        out[i] %= MOD
    print(" ".join(map(str, out)))


# https://github.com/VaHiX/codeForces/
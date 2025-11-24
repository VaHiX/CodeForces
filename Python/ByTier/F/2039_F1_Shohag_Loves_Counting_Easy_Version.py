# Problem: CF 2039 F1 - Shohag Loves Counting (Easy Version)
# https://codeforces.com/contest/2039/problem/F1

"""
F1. Shohag Loves Counting (Easy Version)
Algorithm: Dynamic Programming with Linear Sieve for factorization and divisor enumeration.
Time Complexity: O(N log N) where N = max(m) across all test cases.
Space Complexity: O(N) for storing lookup tables and DP arrays.

This solution uses a linear sieve to efficiently compute the smallest prime factor (SPF)
and primes up to N. Then, for each number x from N down to 1, it computes the number of
good arrays ending at x by using divisor enumeration and dynamic programming with memoization.
The key idea is based on how the function f(k), defined as the GCD of max elements in all
subarrays of length k, behaves in a good array, which ensures all f(k) values are distinct.

The problem can be solved using dynamic programming over the structure of subarrays,
leveraging prime factorization and divisor enumeration to efficiently track valid configurations.
"""

class LPF:
    @staticmethod
    def lpf_table(N: int) -> tuple[list[int], list[int]]:
        if N <= 1:
            return [0, 0], []
        small = [2, 3, 5]  # Precomputed small primes for initial check
        prod = 30
        next = 7
        assert next % 2 == 1

        def proc(x):
            for p in small:
                if x % p == 0:
                    return p
            return 0

        lookup = [proc(x) for x in range(prod)]  # Lookup table for SPF of numbers 0..prod-1
        dp = lookup * (N // prod + 1)  # Extend it to N, reusing the lookup
        del dp[N + 1 :]
        dp[0] = 0
        P = []
        for x in range(next, N + 1, 2):  # Process only odd numbers >= next
            lpf = dp[x]
            if lpf == 0:
                dp[x] = lpf = x  # x is prime
                P.append(x)
            if next <= lpf:  # Only proceed if we can generate products safely
                for np in P:
                    if lpf < np or not (np * x <= N):
                        break
                    dp[np * x] = np  # Update SPF of np*x to np
        P[:0] = [p for p in small if p <= N]  # Prepend small primes to P
        return dp, P


class LinearSieve:
    def __init__(self, N_) -> None:
        N = max(int(N_), 0) + 100  # Add buffer to avoid edge cases
        self.N = N
        self.lpf, self.P = LPF.lpf_table(N)

    def factors(self, X) -> list[tuple[int, int]]:
        assert 1 <= X <= self.N
        F = []
        while X > 1:
            p = self.lpf[X]  # Get the smallest prime factor of X
            e = 0
            while X % p == 0:  # Count how many times p divides X
                X //= p
                e += 1
            F.append((p, e))  # Add (prime, exponent) to factors list
        return F

    def divisors(self, X, *, sort=True):
        assert 1 <= X <= self.N
        D = [1]
        for p, e in self.factors(X):  # Iterate through prime factorization of X
            P = [p] * e  # Create list of powers of p: [p, p^2, ..., p^e]
            for i in range(1, e):
                P[i] = P[i - 1] * p  # Compute powers iteratively
            nD = D[:]  # Copy current divisors
            for p_power in P:  # For each power of p, extend existing divisors
                nD.extend([p_power * d for d in D])
            D = nD  # Update divisors
        if sort:
            D.sort()
        return D


def solve(N):
    ls = LinearSieve(N)
    dp = [0] * (N + 1)  # dp[x]: number of valid arrays ending at x
    Zdp = [0] * (N + 1)  # Zdp[x]: auxiliary sum for intermediate computation
    memo = [0] * (N + 1)  # Memoization space for current divisor operations
    for x in range(N, 0, -1):  # Process numbers from N down to 1
        D = ls.divisors(x)  # Get all divisors of x
        P = [p for p, _ in ls.factors(x)]  # Get distinct primes dividing x
        for d in D:
            memo[d] = Zdp[d]  # Save previous value of Zdp[d]
        for p in P:  # For each prime factor...
            for d in D:
                if d % p == 0:
                    memo[d // p] -= memo[d]  # Subtract contribution from d//p (invert sign)
        for d in D:
            dcnt = memo[d] - dp[d]  # Compute difference for update
            dcnt %= MOD
            memo[d] = dcnt * 2  # Scale and store updated value
            dp[d] += dcnt * 2
            dp[d] %= MOD
        for p in P:
            for d in reversed(D):
                if d % p == 0:
                    memo[d // p] += memo[d]  # Add back contribution to d//p (revert sign)
        for d in D:
            Zdp[d] += memo[d]
            Zdp[d] %= MOD
        dp[x] += 1  # Increment count of array with single element x
        for d in D:
            Zdp[d] += 1  # Add 1 to each divisor's Zdp (account for base case)
        for d in D:
            memo[d] = 0  # Reset memoization space for next iteration
    return sum(dp) % MOD


MOD = 998_244_353
ans = []
for _ in range(int(input())):
    N = int(input())
    ans.append(solve(N))
print(*ans, sep="\n")


# https://github.com/VaHiX/codeForces/
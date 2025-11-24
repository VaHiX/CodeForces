# Problem: CF 2154 C2 - No Cost Too Great (Hard Version)
# https://codeforces.com/contest/2154/problem/C2

"""
Algorithm: 
This problem involves finding the minimum cost to make two elements in array `a` have a GCD > 1. 
The approach is to:
1. For each element in `a`, compute its prime factorization.
2. For each prime factor of `a[i]`, increment `a[i]` by 1 to make it divisible by that prime, 
   and store the minimum cost to do so in `possible1`.
3. Also track how many numbers already contain each prime in their factorization (`avail`).
4. If any prime already divides two elements, we need 0 additional cost.
5. For each element, test how much we would need to add to make it divisible by a prime.

Time Complexity: O(n * sqrt(max_a) + number_of_primes * log(number_of_primes))
Space Complexity: O(n + number_of_primes)

The solution uses the Sieve of Eratosthenes to precompute primes up to MX, and then 
uses prime factorization to determine which operations are needed.
"""

import sys
from collections import Counter, defaultdict

input = lambda: sys.stdin.readline().rstrip()

INF = 1 << 31
MX = 2 * 10**5


class PrimesUtil:
    """
    Class that provides functionality to check for primality of numbers and to factorise numbers.
    A version of the Sieve of Eratosthenes is used to pre-compute all primes up to a certain number mx,
    and the Miller–Rabin primality test is used for larger numbers.

    See also: https://en.wikipedia.org/wiki/Prime_number
    See also: https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
    See also: https://stackoverflow.com/questions/2068372/fastest-way-to-list-all-primes-below-n.
    See also: https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
    """

    def __init__(self, mx):
        assert 1 <= mx
        self._mx = mx
        self._primes = []
        self._min_prime_factor = [0] * (mx + 1)
        self._sieve()

    def _sieve(self):
        primes = self._primes
        min_prime_factor = self._min_prime_factor
        mx = self._mx
        for i in range(2, mx + 1):
            if min_prime_factor[i] == 0:
                primes += [i]
                min_prime_factor[i] = i
            for p in primes:
                if p * i > mx or p > min_prime_factor[i]:
                    break
                min_prime_factor[p * i] = p

    def get_primes(self):
        return self._primes

    def is_prime(self, n):
        """Checks whether a number is prime. For numbers larger than self.mx, the Miller-Rabin test is used."""
        assert 1 <= n < 3_317_044_064_679_887_385_961_981
        return (
            self._min_prime_factor[n] == n
            if n <= self._mx
            else PrimesUtil.is_prime_miller_rabin(n)
        )

    def get_min_prime_factor(self, n):
        assert 1 <= n <= self._mx
        return self._min_prime_factor[n]

    @classmethod
    def is_prime_miller_rabin(cls, n):
        """Checks whether a number is prime according to the Miller–Rabin primality test."""
        assert 1 <= n < 3_317_044_064_679_887_385_961_981
        if n <= 4:
            return n == 2 or n == 3

        d, pow2 = n - 1, 0
        while d % 2 == 0:
            d //= 2
            pow2 += 1

        if n < 2_152_302_898_747:
            bases = [2, 3, 5, 7, 11]
        elif n < 341_550_071_728_321:
            bases = [2, 3, 5, 7, 11, 13, 17]
        else:
            bases = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41]

        for b in bases:
            x = pow(b, d, n)
            if x == 0 or x == 1 or x == n - 1:
                continue
            for _ in range(1, pow2):
                x = (x * x) % n
                if x == 1:
                    return False
                if x == n - 1:
                    break
            if x != n - 1:
                return False
        return True

    def factorise(self, n):
        """Returns a list of tuples (prime, exponent) representing the prime factorisation of n.
        Performance depends on whether the number is from [1, self.mx] or from [self.mx+1, self.mx**2].
        """
        assert 1 <= n <= self._mx**2
        prime_factorisation = []
        if n <= self._mx:
            while n > 1:
                prime_number, exp = self._min_prime_factor[n], 0
                while n % prime_number == 0:
                    exp += 1
                    n //= prime_number
                prime_factorisation += [(prime_number, exp)]
        else:
            for prime_number in self._primes:
                if prime_number**2 > n:
                    break
                if n % prime_number == 0:
                    exp = 0
                    while n % prime_number == 0:
                        exp += 1
                        n //= prime_number
                    prime_factorisation += [(prime_number, exp)]
            if n > 1:
                prime_factorisation += [(n, 1)]
        return prime_factorisation

    def divisors(self, n):
        """Returns all divisors of a number as an unsorted list.
        Performance depends on whether number is from [1, self.mx] or from [self.mx+1, self.mx**2].
        """
        assert 1 <= n <= self._mx**2
        div = [1]
        for p, e in self.factorise(n):
            div_new = div[:]
            d = 1
            for _ in range(1, e + 1):
                d *= p
                div_new.extend([x * d for x in div])
            div = div_new
        return div


primes_util = PrimesUtil(MX)


def solve_case():
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))

    avail = Counter()  # Count how many times each prime appears among factors of a[i]
    possible1 = defaultdict(lambda: INF)  # Minimum cost to make one element divisible by prime

    for i in range(n):
        # Factorize current element of a
        pf = primes_util.factorise(a[i])
        for p, _ in pf:
            avail[p] += 1  # Record that a prime appears in this number
        # Factorize a[i] + 1 (we can increment it to make the same number divisible by a prime)
        pf = primes_util.factorise(a[i] + 1)
        for p, _ in pf:
            possible1[p] = min(possible1[p], b[i])  # Track minimum cost to reach prime p

    # Sort costs to find minimum two
    b_sorted = sorted(b)

    # Base answer: sum of two minimum costs, or zero if two numbers are already divisible by same prime
    ans = b_sorted[0] + b_sorted[1]
    for p, c in avail.items():
        if c >= 2:
            ans = min(ans, 0)  # Already two numbers divisible by prime p
        if p in possible1:
            ans = min(ans, possible1[p])

    # Find index of minimum cost
    idx = next(i for i in range(n) if b[i] == b_sorted[0])
    # Try to use the cheapest element to make others divisible
    for k in avail.keys():
        r = a[idx] % k  # Remainder when idx'th element is divided by prime k
        if r != 0:
            req = k - r  # How many increments needed to become divisible by k
            ans = min(ans, b[idx] * req)  # Update answer with cost
    return ans


ans = []
for _ in range(int(input())):
    ans.append(str(solve_case()))
print("\n".join(ans))


# https://github.com/VaHiX/CodeForces/
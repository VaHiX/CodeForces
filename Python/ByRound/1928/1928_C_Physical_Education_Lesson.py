# Problem: CF 1928 C - Physical Education Lesson
# https://codeforces.com/contest/1928/problem/C

"""
Problem: Physical Education Lesson
Purpose: Given Vasya's position 'n' and the number 'x' he received during settling, 
         find how many values of k (k > 1) are valid for the settling pattern.

Approach:
- Analyze settling pattern:
    - Positions n and n+1 are critical in determining valid k values.
    - The pattern repeats every 2k - 2 positions.
    - If k = 1, then no settling happens, so k > 1.
    - For a valid k, x appears at position n in the sequence.
- The key insight:
    - We derive necessary conditions based on modular arithmetic.
    - Use factorization to enumerate possible k values efficiently.
    - Precompute primes up to sqrt(10^9) using sieve.
- Time Complexity: O(sqrt(N) * log(log(N)) + D_A * D_B) where D_A, D_B are the number of divisors of A, B
- Space Complexity: O(sqrt(N)) for storing primes up to sqrt(N)

Algorithms/Techniques:
- Sieve of Eratosthenes to precompute primes
- Prime factorization
- Divisor enumeration
"""

n_max = 31622
sieve = [True] * (n_max + 1)
sieve[0] = False
sieve[1] = False
primes = []
for i in range(2, n_max + 1):
    if sieve[i]:
        primes.append(i)
        for j in range(i * i, n_max + 1, i):
            sieve[j] = False


def gen_divisors(factors):
    # Generate all divisors from prime factorization
    divisors = {1}
    for prime, exp in factors.items():
        powers = [prime**i for i in range(exp + 1)]
        new_divisors = set()
        for d in divisors:
            for pwr in powers:
                new_divisors.add(d * pwr)
        divisors = new_divisors
    return divisors


def factorize(num):
    # Factorize a number into prime factors
    factors = {}
    temp = num
    for p in primes:
        if p * p > temp:
            break
        if temp % p == 0:
            cnt = 0
            while temp % p == 0:
                cnt += 1
                temp //= p
            factors[p] = cnt
    if temp > 1:
        factors[temp] = 1
    return factors


t = int(input().strip())
for _ in range(t):
    n, x = map(int, input().split())
    A = n - x
    B = n + x - 2
    factors_A = factorize(A) if A > 1 else {}
    divisors_A = gen_divisors(factors_A) if A > 1 else {1}
    factors_B = factorize(B)
    divisors_B = gen_divisors(factors_B)
    count = 0
    for d in divisors_A:
        if d < 2:
            continue
        if d % 2 != 0:
            continue
        k_val = (d + 2) // 2
        if k_val >= x:
            count += 1
    if x >= 2:
        for d in divisors_B:
            if d < 2 * x:
                continue
            if d % 2 != 0:
                continue
            count += 1
    print(count)


# https://github.com/VaHiX/CodeForces/
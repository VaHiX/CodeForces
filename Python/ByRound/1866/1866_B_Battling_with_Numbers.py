# Problem: CF 1866 B - Battling with Numbers
# https://codeforces.com/contest/1866/problem/B

"""
Algorithm: Count valid pairs (p, q) such that LCM(p, q) = X and GCD(p, q) = Y.

Key Concept:
- For any pair (p, q), if LCM(p, q) = X and GCD(p, q) = Y, then:
  - X = (p * q) / GCD(p, q) = (p * q) / Y
  - So p * q = X * Y
- Also, since GCD(p, q) = Y:
  - Let p = Y * p', q = Y * q', where GCD(p', q') = 1
  - Then LCM(p, q) = Y * LCM(p', q') = X
  - Thus LCM(p', q') = X / Y
- To find valid pairs (p', q'), we analyze prime factorizations:
  - Each prime in X must appear in either p' or q' (but not both, since their GCD is 1)
  - Since GCD(p', q') = 1, for each prime p_i, either p_i^a_i divides p' or p_i^a_i divides q',
    but not both.
  - However, this is not the main insight here.
- Main insight:
  - Let's consider the prime factorization of X and Y:
    - X = prod(p_i^a_i)
    - Y = prod(p_i^b_i)
  - For LCM(p, q) = X and GCD(p, q) = Y:
    - For each prime p_i:
      - max(c_i, d_i) = a_i
      - min(c_i, d_i) = b_i
    - So, for each prime:
      - c_i + d_i = a_i + b_i (since max + min = sum)
      - One of (c_i, d_i) is a_i and the other is b_i
    - Number of choices for c_i, d_i is 2 (either c_i = a_i, d_i = b_i or vice versa)
    - So total number of ways = 2^(number of primes)

Special Case:
- If there is a prime in Y that's not in X, or a prime in X with exponent less than in Y,
  then there's no solution.

Time and Space Complexity:
- Time complexity: O(N + M)
  - We scan through the primes in X and Y.
- Space complexity: O(1)
  - Only fixed variables are used.
"""

mod = 998244353


def mult(a, b):
    return (((a % mod + mod) % mod) * ((b % mod + mod) % mod)) % mod


def summ(a, b):
    return (a + b + 3 * mod) % mod


def binpow(x, n):
    if n == 0:
        return 1
    if n & 1:
        return mult(x, binpow(x, n - 1)) % mod
    t = binpow(x, n // 2) % mod
    return mult(t, t)


def divide(a, b):
    return a * binpow(b, mod - 2) % mod


def solve():
    n = int(input())
    a1 = list(map(int, input().split()))  # primes in X
    a2 = list(map(int, input().split()))  # exponents in X
    m = int(input())
    b1 = list(map(int, input().split()))  # primes in Y
    b2 = list(map(int, input().split()))  # exponents in Y
    
    k = 0  # pointer for a1
    cnt = n  # count of primes in X not matched to Y (but must be present in Y too)
    
    # For each prime in Y, check if it exists in X and compare exponents
    for i in range(m):
        while k < n and a1[k] != b1[i]:  # Find the matching prime in X
            k += 1
        if k == n:  # Prime in Y not found in X
            print(0)
            return
        if a2[k] == b2[i]:  # Exponent same in X and Y
            cnt -= 1  # It doesn't contribute to 2 choices
        elif a2[k] < b2[i]:  # Exponent in X less than in Y
            print(0)
            return
    # If all primes in Y are included in X and have higher or equal exponents,
    # number of valid pairs is 2^(number of distinct primes)
    print(binpow(2, cnt))


def main():
    t = 1
    for _ in range(t):
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
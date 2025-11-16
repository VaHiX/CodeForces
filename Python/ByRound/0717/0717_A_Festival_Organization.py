# Problem: CF 717 A - Festival Organization
# https://codeforces.com/contest/717/problem/A

"""
Algorithm: Dynamic Programming with Matrix Exponentiation and Combinatorics
Time Complexity: O(k^3 * log(r)) where k <= 200
Space Complexity: O(k^2) for storing precomputed values

This code solves the problem of counting k different tours of the same length 
between l and r, under the constraint that no two consecutive days-off are allowed.
The approach uses:
1. Matrix exponentiation to compute the number of valid sequences of a given length
2. Stirling numbers of the first kind for selecting k tours from a set
3. Combinatorics for computing binomial coefficients
4. Fast modular exponentiation for efficient computation
"""

MOD = 10**9 + 7
MAX_N = 210


def mod_pow(base, exponent=MOD - 2, mod=MOD):
    # Fast modular exponentiation using binary exponentiation
    result = 1
    while exponent:
        if exponent & 1:
            result = result * base % mod
        base = base * base % mod
        exponent >>= 1
    return result


class ComplexMod:
    def __init__(self, real=0, imag=0):
        # Define complex numbers in the field Z_mod[sqrt(5)] where 5 is treated as a module
        self.real = real % MOD
        self.imag = imag % MOD

    def __add__(self, other):
        # Addition of complex numbers
        if isinstance(other, ComplexMod):
            return ComplexMod(
                (self.real + other.real) % MOD, (self.imag + other.imag) % MOD
            )
        else:
            return ComplexMod((self.real + other) % MOD, self.imag)

    def __sub__(self, other):
        # Subtraction of complex numbers
        if isinstance(other, ComplexMod):
            return ComplexMod(
                (self.real - other.real + MOD) % MOD,
                (self.imag - other.imag + MOD) % MOD,
            )
        else:
            return ComplexMod((self.real - other + MOD) % MOD, self.imag)

    def __mul__(self, other):
        # Multiplication of complex numbers using sqrt(5) module arithmetic
        if isinstance(other, ComplexMod):
            real_part = (self.real * other.real + 5 * self.imag * other.imag) % MOD
            imag_part = (self.real * other.imag + self.imag * other.real) % MOD
            return ComplexMod(real_part, imag_part)
        else:
            return ComplexMod(self.real * other % MOD, self.imag * other % MOD)

    def __truediv__(self, other):
        # Division of complex numbers using conjugate
        denominator = (
            other.real * other.real - 5 * other.imag * other.imag + MOD
        ) % MOD
        inv_denominator = mod_pow(denominator)
        real_part = (self.real * other.real - 5 * self.imag * other.imag + MOD) % MOD
        imag_part = (-self.real * other.imag + self.imag * other.real + MOD) % MOD
        return ComplexMod(
            real_part * inv_denominator % MOD, imag_part * inv_denominator % MOD
        )

    def pow(self, exponent):
        # Efficiently compute the power of a complex number using binary exponentiation
        result = ComplexMod(1, 0)
        base = ComplexMod(self.real, self.imag)
        while exponent:
            if exponent & 1:
                result = result * base
            base = base * base
            exponent >>= 1
        return result


# Precomputed combinatorics tables
binomial = [[0] * MAX_N for _ in range(MAX_N)]
stirling_first = [[0] * MAX_N for _ in range(MAX_N)]
factorial = [1] * MAX_N
inv_factorial = [1] * MAX_N


def initialize_combinatorics():
    # Precompute binomial coefficients using Pascal's triangle
    for i in range(MAX_N):
        binomial[i][0] = 1
        for j in range(1, i + 1):
            binomial[i][j] = (binomial[i - 1][j] + binomial[i - 1][j - 1]) % MOD
    
    # Precompute Stirling numbers of the first kind
    stirling_first[0][0] = 1
    for i in range(1, MAX_N):
        for j in range(1, i + 1):
            stirling_first[i][j] = (
                stirling_first[i - 1][j - 1]
                - (i - 1) * stirling_first[i - 1][j] % MOD
                + MOD
            ) % MOD
    
    # Precompute factorials and their inverses for combinatorics
    for i in range(1, MAX_N):
        factorial[i] = factorial[i - 1] * i % MOD
    inv_factorial[MAX_N - 1] = mod_pow(factorial[MAX_N - 1])
    for i in range(MAX_N - 2, -1, -1):
        inv_factorial[i] = inv_factorial[i + 1] * (i + 1) % MOD


def solve_expression_sum():
    k, lower_bound, upper_bound = map(int, input().split())
    # Shift bounds by 2 due to problem transformations
    lower_bound += 2
    upper_bound += 2
    total_sum = ComplexMod(0, 0)
    
    # Define sqrt(5) in field Z_MOD
    sqrt5 = ComplexMod(0, mod_pow(5))
    neg_sqrt5 = ComplexMod(0, (MOD - sqrt5.imag) % MOD)
    
    # Base values related to the recurrence relations for valid sequences
    base_a = ComplexMod(mod_pow(2), mod_pow(2))
    base_b = ComplexMod(base_a.real, (MOD - base_a.imag) % MOD)
    
    # Compute sum over all possible subset sizes from 1 to k
    for subset_size in range(1, k + 1):
        subset_sum = ComplexMod(0, 0)
        # For each possible number of subsets in partition
        for j in range(subset_size + 1):
            # Calculate power terms
            power_term = base_a.pow(j) * base_b.pow(subset_size - j)
            
            # Handle case when power term is 1
            if power_term.real == 1 and power_term.imag == 0:
                sum_term = ComplexMod((upper_bound - lower_bound + 1) % MOD, 0)
            else:
                # Use geometric series formula for sum
                sum_term = (
                    power_term.pow(upper_bound + 1) - power_term.pow(lower_bound)
                ) / (power_term - ComplexMod(1, 0))
            
            # Apply transform for coefficient adjustment
            sum_term = neg_sqrt5.pow(subset_size - j) * sum_term
            sum_term = sqrt5.pow(j) * sum_term
            sum_term = sum_term * binomial[subset_size][j]
            subset_sum += sum_term
            
        # Account for Stirling coefficients
        subset_sum *= stirling_first[k][subset_size]
        total_sum += subset_sum
        
    # Final adjustment with inverse factorial
    total_sum *= inv_factorial[k]
    print(total_sum.real % MOD)


if __name__ == "__main__":
    initialize_combinatorics()
    solve_expression_sum()


# https://github.com/VaHiX/CodeForces/
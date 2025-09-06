# Contest 717, Problem A: Festival Organization
# URL: https://codeforces.com/contest/717/problem/A

MOD = 10**9 + 7
MAX_N = 210

def mod_pow(base, exponent=MOD - 2, mod=MOD):
    result = 1
    while exponent:
        if exponent & 1:
            result = result * base % mod
        base = base * base % mod
        exponent >>= 1
    return result

class ComplexMod:
    def __init__(self, real=0, imag=0):
        self.real = real % MOD
        self.imag = imag % MOD

    def __add__(self, other):
        if isinstance(other, ComplexMod):
            return ComplexMod((self.real + other.real) % MOD, (self.imag + other.imag) % MOD)
        else:
            return ComplexMod((self.real + other) % MOD, self.imag)

    def __sub__(self, other):
        if isinstance(other, ComplexMod):
            return ComplexMod((self.real - other.real + MOD) % MOD, (self.imag - other.imag + MOD) % MOD)
        else:
            return ComplexMod((self.real - other + MOD) % MOD, self.imag)

    def __mul__(self, other):
        if isinstance(other, ComplexMod):
            real_part = (self.real * other.real + 5 * self.imag * other.imag) % MOD
            imag_part = (self.real * other.imag + self.imag * other.real) % MOD
            return ComplexMod(real_part, imag_part)
        else:
            return ComplexMod(self.real * other % MOD, self.imag * other % MOD)

    def __truediv__(self, other):
        denominator = (other.real * other.real - 5 * other.imag * other.imag + MOD) % MOD
        inv_denominator = mod_pow(denominator)
        real_part = (self.real * other.real - 5 * self.imag * other.imag + MOD) % MOD
        imag_part = (-self.real * other.imag + self.imag * other.real + MOD) % MOD
        return ComplexMod(real_part * inv_denominator % MOD, imag_part * inv_denominator % MOD)

    def pow(self, exponent):
        result = ComplexMod(1, 0)
        base = ComplexMod(self.real, self.imag)
        while exponent:
            if exponent & 1:
                result = result * base
            base = base * base
            exponent >>= 1
        return result

binomial = [[0] * MAX_N for _ in range(MAX_N)]
stirling_first = [[0] * MAX_N for _ in range(MAX_N)]
factorial = [1] * MAX_N
inv_factorial = [1] * MAX_N

def initialize_combinatorics():
    for i in range(MAX_N):
        binomial[i][0] = 1
        for j in range(1, i + 1):
            binomial[i][j] = (binomial[i - 1][j] + binomial[i - 1][j - 1]) % MOD

    stirling_first[0][0] = 1
    for i in range(1, MAX_N):
        for j in range(1, i + 1):
            stirling_first[i][j] = (stirling_first[i - 1][j - 1] - (i - 1) * stirling_first[i - 1][j] % MOD + MOD) % MOD

    for i in range(1, MAX_N):
        factorial[i] = factorial[i - 1] * i % MOD

    inv_factorial[MAX_N - 1] = mod_pow(factorial[MAX_N - 1])
    for i in range(MAX_N - 2, -1, -1):
        inv_factorial[i] = inv_factorial[i + 1] * (i + 1) % MOD

def solve_expression_sum():
    k, lower_bound, upper_bound = map(int, input().split())
    lower_bound += 2
    upper_bound += 2

    total_sum = ComplexMod(0, 0)
    sqrt5 = ComplexMod(0, mod_pow(5))
    neg_sqrt5 = ComplexMod(0, (MOD - sqrt5.imag) % MOD)
    base_a = ComplexMod(mod_pow(2), mod_pow(2))
    base_b = ComplexMod(base_a.real, (MOD - base_a.imag) % MOD)

    for subset_size in range(1, k + 1):
        subset_sum = ComplexMod(0, 0)
        for j in range(subset_size + 1):
            power_term = base_a.pow(j) * base_b.pow(subset_size - j)

            if power_term.real == 1 and power_term.imag == 0:
                sum_term = ComplexMod((upper_bound - lower_bound + 1) % MOD, 0)
            else:
                sum_term = (power_term.pow(upper_bound + 1) - power_term.pow(lower_bound)) / (power_term - ComplexMod(1, 0))

            sum_term = neg_sqrt5.pow(subset_size - j) * sum_term
            sum_term = sqrt5.pow(j) * sum_term
            sum_term = sum_term * binomial[subset_size][j]
            subset_sum += sum_term

        subset_sum *= stirling_first[k][subset_size]
        total_sum += subset_sum

    total_sum *= inv_factorial[k]
    print(total_sum.real % MOD)

if __name__ == "__main__":
    initialize_combinatorics()
    solve_expression_sum()

# Problem: CF 1970 E2 - Trails (Medium)
# https://codeforces.com/contest/1970/problem/E2

"""
Code Purpose:
This program computes the number of possible combinations of trails Harry can take when hiking for n days, 
starting from cabin 1. Each day, he moves from his current cabin to the lake (using one trail) and then back to a cabin (using another trail). 
At least one of the two trails must be short.

The solution uses matrix exponentiation to efficiently compute results for large n (up to 10^9), 
by modeling the transitions as a linear recurrence relation.

Algorithms/Techniques:
- Matrix Exponentiation
- Linear Recurrence Relation modeling
- Modular Arithmetic

Time Complexity: O(m^3 * log n)
Space Complexity: O(1)
"""

MOD = 10**9 + 7


def mat_mult_2x2(A, B, mod):
    # Multiply two 2x2 matrices under modulo
    a00, a01 = A[0]
    a10, a11 = A[1]
    b00, b01 = B[0]
    b10, b11 = B[1]
    c00 = (a00 * b00 + a01 * b10) % mod
    c01 = (a00 * b01 + a01 * b11) % mod
    c10 = (a10 * b00 + a11 * b10) % mod
    c11 = (a10 * b01 + a11 * b11) % mod
    return [[c00, c01], [c10, c11]]


def mat_pow_2x2(matrix, power, mod):
    # Compute matrix^power using fast exponentiation
    res = [[1, 0], [0, 1]]  # Identity matrix
    base = matrix
    while power:
        if power & 1:  # If power is odd
            res = mat_mult_2x2(res, base, mod)
        base = mat_mult_2x2(base, base, mod)
        power >>= 1  # Divide power by 2
    return res


def solve():
    import sys

    data = sys.stdin.read().split()
    m = int(data[0])
    n = int(data[1])
    s = list(map(int, data[2 : 2 + m]))
    l_list = list(map(int, data[2 + m : 2 + 2 * m]))
    
    # Total trails from each cabin (short + long)
    t = [s[i] + l_list[i] for i in range(m)]
    
    # Initialize transition matrix components
    R00 = 0
    R01 = 0
    R10 = 0
    R11 = 0
    
    # Calculate components for the transition matrix
    for i in range(m):
        R00 = (R00 + t[i] * s[i]) % MOD
        R01 = (R01 + t[i] * l_list[i]) % MOD
        R10 = (R10 + s[i] * s[i]) % MOD
        R11 = (R11 + s[i] * l_list[i]) % MOD

    S_t = sum(t) % MOD
    S_s = sum(s) % MOD

    # Handle base case for n = 1
    if n == 1:
        a_val = s[0]
        b_val = l_list[0]
    else:
        # Build transition matrix
        R_mat = [[R00, R01], [R10, R11]]
        # Raise to (n-1) power
        R_exp = mat_pow_2x2(R_mat, n - 1, MOD)
        # Compute values based on initial state
        a_val = (s[0] * R_exp[0][0] + l_list[0] * R_exp[1][0]) % MOD
        b_val = (s[0] * R_exp[0][1] + l_list[0] * R_exp[1][1]) % MOD

    # Final result combining the two states
    ans = (a_val * S_t + b_val * S_s) % MOD
    print(ans)


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/
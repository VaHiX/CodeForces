# Problem: CF 1925 D - Good Trip
# https://codeforces.com/contest/1925/problem/D

"""
Code Purpose:
This program computes the expected sum of friendship values over k excursions,
where each excursion randomly selects a pair of children and increments the 
friendship value of friends by 1 for all subsequent excursions.

Algorithm:
- For each friend pair, compute its contribution to the total expected value.
- The expected value is computed using linearity of expectation.
- For a friend pair with value f_i, it contributes f_i * (k / C) + f_i * (k * (k-1) / (2 * C^2))
  where C = n * (n - 1) / 2 is the total number of possible pairs.
- Uses modular arithmetic and precomputed inverse elements for efficient computation.

Time Complexity: O(m + t), where t is number of test cases and m is total number of friend pairs
Space Complexity: O(1), only using constant extra space (excluding input/output)

"""

MOD = 10**9 + 7
inv_2 = 500000004  # Modular inverse of 2 mod (10^9 + 7)


def main():
    import sys

    input = sys.stdin.read().split()
    ptr = 0
    t = int(input[ptr])
    ptr += 1
    results = []
    for _ in range(t):
        n = int(input[ptr])
        m = int(input[ptr + 1])
        k = int(input[ptr + 2])
        ptr += 3
        c = n * (n - 1) // 2   # Total number of possible pairs
        if c == 0:
            results.append(0)
            ptr += 3 * m
            continue
        inv_c = pow(c, MOD - 2, MOD)  # Modular inverse of c
        inv_c_sq = (inv_c * inv_c) % MOD  # Square of modular inverse
        k_mod = k % MOD
        k_minus_1_mod = (k - 1) % MOD
        sum_ans = 0
        for __ in range(m):
            # Read the friend pair data
            int(input[ptr])  # a_i (not used in computation)
            int(input[ptr + 1])  # b_i (not used in computation)
            f_i = int(input[ptr + 2]) % MOD  # friendship value
            ptr += 3
            # Compute the expected contribution of this friend pair
            term1 = f_i * k_mod % MOD  # f_i * k
            term1 = term1 * inv_c % MOD  # (f_i * k) / C
            product = k_mod * k_minus_1_mod % MOD  # k * (k - 1)
            term2_part = product * inv_2 % MOD  # k * (k - 1) / 2
            term2 = term2_part * inv_c_sq % MOD  # [k * (k - 1) / 2] / C^2
            total = (term1 + term2) % MOD  # Add two terms for total contribution
            sum_ans = (sum_ans + total) % MOD  # Accumulate result
        results.append(sum_ans % MOD)
    print("\n".join(map(str, results)))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
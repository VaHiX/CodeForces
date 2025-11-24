# Problem: CF 2096 H - Wonderful XOR Problem
# https://codeforces.com/contest/2096/problem/H

"""
Problem: Wonderful XOR Problem
Algorithm: Fast Walsh-Hadamard Transform (FWHT) + Digit DP
Time Complexity: O(m * n * 2^m) where m is the number of bits and n is the number of intervals
Space Complexity: O(2^m) for storing intermediate results and transformations

This problem asks us to count the number of sequences where each element is within a given range,
and the XOR of all elements equals a specific value x. We use a combination of digit DP and FWHT.

The approach:
1. For each bit position, we compute the contribution of that bit to the total count using digit DP
2. We use the Fast Walsh-Hadamard Transform (FWHT) to efficiently combine these contributions
3. Finally, we compute the XOR of g_x values where g_x = f_x * 2^x

Key techniques:
- Digit DP (Dynamic Programming on digits)
- Fast Walsh-Hadamard Transform for efficient XOR convolution
- Modular arithmetic and precomputed powers
"""

import sys


def solve():
    MOD = 998244353
    L = 18
    N_MAX_FWHT = 1 << L

    V2 = pow(2, MOD - 2, MOD)  # Modular inverse of 2

    kk = [0] * N_MAX_FWHT  # Bit count for each number
    vv_ = [0] * (L + 1)    # Precomputed powers of modular inverse of 2

    def init():
        vv_[0] = 1
        for l in range(1, L + 1):
            vv_[l] = (vv_[l - 1] * V2) % MOD

        for b in range(1, N_MAX_FWHT):
            kk[b] = kk[b & (b - 1)] + 1  # Count of 1-bits

    init()

    def wht(a, length):
        # Walsh-Hadamard Transform
        if length <= 1:
            return

        length >> 1  # Divide by 2

        h = 1
        while h < length:
            for i in range(0, length, h * 2):
                for j in range(i, i + h):
                    u = a[j]
                    v = a[j + h]
                    a[j] = (u + v) % MOD
                    a[j + h] = (u - v + MOD) % MOD
            h <<= 1  # Multiply by 2

    def solve_internal(result_arr, current_l, n_segs, aa, bb, xx, yy, kk_arr):
        # Helper function to compute DP values
        size = 1 << current_l

        dp = [[1, 1] for _ in range(size)]

        a_xor_sum = 0
        for i in range(n_segs):
            b_idx = aa[i] ^ bb[i]
            if b_idx < size:
                x_plus_y = (xx[i] + yy[i]) % MOD
                x_minus_y = (xx[i] - yy[i] + MOD) % MOD

                dp[b_idx][0] = (dp[b_idx][0] * x_plus_y) % MOD
                dp[b_idx][1] = (dp[b_idx][1] * x_minus_y) % MOD

            a_xor_sum ^= aa[i]

        h_len = 1
        while h_len < size:
            for i in range(0, size, h_len * 2):
                for j in range(i, i + h_len):
                    b0 = j
                    b1 = j + h_len

                    w = (dp[b0][0] * dp[b1][0]) % MOD
                    x = (dp[b0][1] * dp[b1][1]) % MOD
                    y = (dp[b0][0] * dp[b1][1]) % MOD
                    z = (dp[b0][1] * dp[b1][0]) % MOD

                    dp[b0][0] = w
                    dp[b0][1] = x
                    dp[b1][0] = y
                    dp[b1][1] = z
            h_len <<= 1

        for b in range(size):
            sign = 1 if kk_arr[b & a_xor_sum] % 2 == 0 else -1
            res_val = (dp[b][0] * sign + MOD) % MOD
            result_arr[b] = res_val

    t = int(sys.stdin.readline())
    results = []

    for _ in range(t):
        n_segs, l_bits = map(int, sys.stdin.readline().split())
        N = 1 << l_bits

        ll_ = [0] * n_segs
        rr_ = [0] * n_segs
        for i in range(n_segs):
            ll_[i], rr_[i] = map(int, sys.stdin.readline().split())
            rr_[i] += 1  # Convert to exclusive upper bound

        ans = [0] * N

        aa = [0] * n_segs
        bb = [0] * n_segs
        xx = [0] * n_segs
        yy = [0] * n_segs

        tt = [0] * N

        for h in range(l_bits):
            current_solve_l = l_bits - 1 - h

            for i in range(n_segs):
                # Calculate the index ranges for current bit
                aa[i] = 0 if ll_[i] == 0 else (ll_[i] - 1) >> (h + 1)
                bb[i] = (rr_[i] - 1) >> (h + 1)

                mask_low = (1 << h) - 1
                bit_h_val = 1 << h

                l_low = ll_[i] & mask_low
                r_low = rr_[i] & mask_low

                xx[i] = 0
                if (ll_[i] & bit_h_val) == 0:
                    xx[i] = -l_low
                else:
                    xx[i] = -(bit_h_val - l_low)

                yy[i] = 0
                if (rr_[i] & bit_h_val) == 0:
                    yy[i] = r_low
                else:
                    yy[i] = bit_h_val - r_low

                xx[i] = (xx[i] % MOD + MOD) % MOD
                yy[i] = (yy[i] % MOD + MOD) % MOD

            solve_internal(tt, current_solve_l, n_segs, aa, bb, xx, yy, kk)

            size_tt = 1 << current_solve_l
            shift_amount = h + 1
            bit_h_set = 1 << h
            for b in range(size_tt):
                ans_idx = (b << shift_amount) | bit_h_set
                if ans_idx < N:
                    ans[ans_idx] = tt[b]

        ans[0] = 1
        for i in range(n_segs):
            ans[0] = (ans[0] * (rr_[i] - ll_[i])) % MOD

        wht(ans, N)

        inv_N = vv_[l_bits]
        for b in range(N):
            ans[b] = (ans[b] * inv_N) % MOD

        p = 1
        x_xor_sum = 0
        for b in range(N):
            term = (ans[b] % MOD + MOD) % MOD
            x_xor_sum ^= (term * p) % MOD
            p = (p * 2) % MOD

        results.append(x_xor_sum)

    for res in results:
        print(res)


solve()


# https://github.com/VaHiX/CodeForces/
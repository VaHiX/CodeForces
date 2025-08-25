# Contest 2096, Problem H: Wonderful XOR Problem
# URL: https://codeforces.com/contest/2096/problem/H

import sys

# Increase recursion depth for potentially deep calls in WHT/Solve variants
# sys.setrecursionlimit(2000)


def solve():
    MOD = 998244353
    L = 18  # Max bit length (m)
    N_MAX_SEGMENTS = 200005  # Max n
    N_MAX_FWHT = 1 << L  # Max 2^m

    # Modular inverse of 2
    V2 = pow(2, MOD - 2, MOD)

    # --- Precomputation ---
    kk = [0] * N_MAX_FWHT  # Popcount
    vv_ = [0] * (L + 1)  # Powers of V2

    def init():
        vv_[0] = 1
        for l in range(1, L + 1):
            vv_[l] = (vv_[l - 1] * V2) % MOD
        # Iterative popcount calculation
        for b in range(1, N_MAX_FWHT):
            kk[b] = kk[b & (b - 1)] + 1

    init()
    # --- End Precomputation ---

    # --- FWHT Implementation ---
    def wht(a, length):  # length must be power of 2
        if length <= 1:
            return

        m = length >> 1

        # Recursive calls (can be made iterative)
        # Be careful with slicing creating copies if modifying in-place

        # Iterative FWHT (more Pythonic and avoids deep recursion)
        h = 1
        while h < length:
            for i in range(0, length, h * 2):
                for j in range(i, i + h):
                    u = a[j]
                    v = a[j + h]
                    a[j] = (u + v) % MOD
                    a[j + h] = (u - v + MOD) % MOD  # Ensure positive result
            h <<= 1

    # --- Solve Function (Core DP/Aggregation Logic) ---
    # This is the most complex part, translating the C logic directly
    def solve_internal(result_arr, current_l, n_segs, aa, bb, xx, yy, kk_arr):
        size = 1 << current_l
        # dp[mask][0] and dp[mask][1]
        dp = [[1, 1] for _ in range(size)]

        # Aggregate contributions from intervals
        a_xor_sum = 0
        for i in range(n_segs):
            b_idx = aa[i] ^ bb[i]
            if b_idx < size:  # Ensure index is within bounds for this level
                x_plus_y = (xx[i] + yy[i]) % MOD
                x_minus_y = (xx[i] - yy[i] + MOD) % MOD  # Ensure positive

                dp[b_idx][0] = (dp[b_idx][0] * x_plus_y) % MOD
                dp[b_idx][1] = (dp[b_idx][1] * x_minus_y) % MOD
            # This XOR sum 'a' seems related to the final sign adjustment
            a_xor_sum ^= aa[i]

        # SOS DP / FWHT-like combination step within solve
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

        # Extract results for this level into result_arr
        for b in range(size):
            sign = 1 if kk_arr[b & a_xor_sum] % 2 == 0 else -1
            res_val = (dp[b][0] * sign + MOD) % MOD  # Ensure positive
            result_arr[b] = res_val

    # --- Main Loop per Test Case ---
    t = int(sys.stdin.readline())
    results = []  # Store results for printing at the end

    for _ in range(t):
        n_segs, l_bits = map(int, sys.stdin.readline().split())
        N = 1 << l_bits  # 2^m

        ll_ = [0] * n_segs
        rr_ = [0] * n_segs
        for i in range(n_segs):
            ll_[i], rr_[i] = map(int, sys.stdin.readline().split())
            rr_[i] += 1  # Make r exclusive upper bound

        ans = [0] * N

        # Temporary arrays used inside the loop
        aa = [0] * n_segs
        bb = [0] * n_segs
        xx = [0] * n_segs
        yy = [0] * n_segs

        tt = [0] * N  # Temp result array from solve_internal

        # Outer loop processing bits
        for h in range(l_bits):
            current_solve_l = l_bits - 1 - h  # Length for this solve call

            # Inner loop calculating coefficients based on bit h
            for i in range(n_segs):
                # Calculate aa, bb (indices based on high bits)
                aa[i] = 0 if ll_[i] == 0 else (ll_[i] - 1) >> (h + 1)
                bb[i] = (rr_[i] - 1) >> (h + 1)

                # Calculate xx, yy (sums/differences based on low bits and bit h)
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

                # Apply modulo arithmetic correctly
                xx[i] = (xx[i] % MOD + MOD) % MOD
                yy[i] = (yy[i] % MOD + MOD) % MOD

            solve_internal(tt, current_solve_l, n_segs, aa, bb, xx, yy, kk)

            # Interleave results into ans
            size_tt = 1 << current_solve_l
            shift_amount = h + 1
            bit_h_set = 1 << h
            for b in range(size_tt):
                ans_idx = (b << shift_amount) | bit_h_set
                if ans_idx < N:  # Bounds check
                    ans[ans_idx] = tt[b]

        # Calculate base case ans[0]
        ans[0] = 1
        for i in range(n_segs):
            ans[0] = (ans[0] * (rr_[i] - ll_[i])) % MOD

        # Final FWHT
        wht(ans, N)

        # Scale result
        inv_N = vv_[l_bits]  # Inverse of 2^l
        for b in range(N):
            ans[b] = (ans[b] * inv_N) % MOD

        # Calculate final XOR sum h
        p = 1
        x_xor_sum = 0
        for b in range(N):
            term = (ans[b] % MOD + MOD) % MOD  # Ensure positive
            x_xor_sum ^= (term * p) % MOD
            p = (p * 2) % MOD

        results.append(x_xor_sum)

    # Print all results
    for res in results:
        print(res)


solve()

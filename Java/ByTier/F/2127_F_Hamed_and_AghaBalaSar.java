// Problem: CF 2127 F - Hamed and AghaBalaSar
// https://codeforces.com/contest/2127/problem/F

/*
 * Problem: Hamed and AghaBalaSar
 * 
 * Purpose: Compute the sum of f(a) over all "snake" arrays of length n and sum m,
 *          where f(a) is defined by a specific algorithm involving next greater elements.
 *
 * Algorithms:
 *   - Combinatorial precomputation with modular arithmetic.
 *   - Dynamic recurrence with inclusion-exclusion principle on valid snake arrays.
 *   - Modular exponentiation and inverse factorials for combinations.
 * 
 * Time Complexity: O(MAX + n * m) where MAX = 400005
 * Space Complexity: O(MAX)
 */

import java.io.*;
import java.util.*;

public class Main {
    static final int MOD = 1_000_000_007;
    static final int MAX = 400000 + 5;
    static long[] fact = new long[MAX];        // Factorials mod MOD
    static long[] invFact = new long[MAX];     // Inverse factorials mod MOD

    // Fast modular exponentiation: a^e mod MOD
    static long modPow(long a, long e) {
        long r = 1;
        while (e > 0) {
            if ((e & 1) == 1) r = (r * a) % MOD;  // If e is odd, multiply result by a
            a = (a * a) % MOD;                     // Square a
            e >>= 1;                              // Halve e
        }
        return r;
    }

    // Precompute factorials and inverse factorials
    static void prep() {
        fact[0] = 1;
        for (int i = 1; i < MAX; i++) fact[i] = fact[i - 1] * i % MOD;
        invFact[MAX - 1] = modPow(fact[MAX - 1], MOD - 2);   // Fermat's little theorem
        for (int i = MAX - 2; i >= 0; i--) invFact[i] = invFact[i + 1] * (i + 1) % MOD;
    }

    // Compute combination C(n, r) mod MOD using precomputed values
    static long C(int n, int r) {
        if (r < 0 || r > n || n < 0) return 0;
        return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
    }

    // Recursive helper function to count valid configurations using inclusion-exclusion
    static long g(int n, int m, int l) {
        if (n < 0) return 0;
        if (n == 0) return m == 0 ? 1 : 0;
        long ans = 0;
        // Max t such that t * (l + 1) <= m + n - 1
        int maxT = Math.min(n, m / (l + 1));
        for (int t = 0; t <= maxT; t++) {
            int rem = m + n - 1 - t * (l + 1);     // Remaining sum after placing t elements of size >= l+1
            if (rem < (n - 1)) break;              // Not enough space for remaining elements
            long term = C(n, t) * C(rem, n - 1) % MOD;
            if ((t & 1) == 1) term = (MOD - term) % MOD;  // Alternating sign in inclusion-exclusion
            ans += term;
            if (ans >= MOD) ans -= MOD;
        }
        return ans;
    }

    public static void main(String[] args) throws Exception {
        prep();                                // Precompute factorials
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();
        int T = fs.nextInt();                  // Number of test cases

        while (T-- > 0) {
            int n = fs.nextInt();
            int m = fs.nextInt();
            
            long ans = 0;
            long invNminus1 = modPow(n - 1, MOD - 2);     // Modular inverse of (n-1)

            for (int x = 0; x <= m; x++) {                // Loop over possible peak values in array
                long g1 = g(n - 1, m - x, x);             // Count valid sequences ending with max x
                long g2 = g(n - 2, m - 2 * x, x);         // Count valid sequences after removing one element
                
                // Term for contribution to answer from current x
                long addMax = ( (g1 + (g2 * ((n - 1) % MOD)) % MOD) % MOD ) * (x % MOD) % MOD;
                ans += addMax;                            // Add term to global sum
                if (ans >= MOD) ans -= MOD;

                long bad = 0;                             // Subtract invalid terms using inclusion-exclusion

                long term1 = ((m - x) % MOD + MOD) % MOD; // Calculate (m - x)
                term1 = term1 * g1 % MOD;                 // Multiply by count of sequences where peak ≤ x
                term1 = term1 * invNminus1 % MOD;         // Divide by n-1 to adjust for overcounting

                bad += term1; if (bad >= MOD) bad -= MOD;

                long term2 = (x % MOD) * (g2 % MOD) % MOD;  // Another invalid term
                bad += term2; if (bad >= MOD) bad -= MOD;

                long term3 = ((m - 2L * x) % MOD + MOD) % MOD; // Yet another term
                term3 = term3 * (g2 % MOD) % MOD;
                bad += term3; if (bad >= MOD) bad -= MOD;

                ans = (ans - bad) % MOD;                  // Subtract all invalid contributions
                if (ans < 0) ans += MOD;
            }
            out.append(ans).append('\n');               // Append result for current test case
        }
        System.out.print(out.toString());
    }

    static class FastScanner {
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;
        private final InputStream in;

        FastScanner(InputStream in) { this.in = in; }
        private int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }

        int nextInt() throws IOException {
            int c, sign = 1, val = 0;
            do { c = read(); } while (c <= ' ');
            if (c == '-') { sign = -1; c = read(); }
            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = read();
            }
            return val * sign;
        }
    }
}


// https://github.com/VaHiX/CodeForces/
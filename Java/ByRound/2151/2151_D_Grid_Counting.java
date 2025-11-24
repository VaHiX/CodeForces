// Problem: CF 2151 D - Grid Counting
// https://codeforces.com/contest/2151/problem/D

/*
 * Problem: D. Grid Counting
 * 
 * Purpose:
 *   Given a grid of size n x n and an array a of size n, count the number of ways to color some cells black such that:
 *   - For each row k, exactly a[k] cells are black.
 *   - For each k, there exists exactly one black cell with max(x_i, y_i) = k.
 *   - For each k, there exists exactly one black cell with max(x_i, n+1-y_i) = k.
 * 
 * Algorithm:
 *   Uses combinatorics to compute the number of valid configurations efficiently. 
 *   Precomputes factorials to support modular inverse computation using Fermat's little theorem.
 *   The constraints on the maximum row/columns determine a specific structure for valid placements,
 *   reducing the problem to combinatorial selection with constraints.
 * 
 * Time Complexity:
 *   O(n) per test case, assuming precomputation of factorials. In practice: O(n) for each query after initial setup.
 * 
 * Space Complexity:
 *   O(n) for storing precomputed factorials and auxiliary arrays.
 */

import java.io.IOException;

public class Main {
    static int nextInt() throws IOException {
        int sign = 1;
        int input;
        while (!Character.isDigit(input = System.in.read())) {
            sign = (input == '-' ? -1 : 1);
        }
        int value = input & 15; // equivalent to input - '0'
        while (Character.isDigit(input = System.in.read())) {
            value = value * 10 + (input & 15); // same as value = value * 10 + (input - '0');
        }
        return sign * value;
    }

    static long[] f = new long[200_000 + 1]; // Precomputed factorials modulo MOD

    public static void main(String[] args) throws IOException {
        final int MOD = 998_244_353;
        f[0] = 1;
        for (int i = 1; i <= 200_000; i++) {
            f[i] = i * f[i - 1] % MOD;
        }
        int t = nextInt();
        StringBuilder result = new StringBuilder();
        while (t-- > 0) {
            int n = nextInt();
            int[] a = new int[n + 1];
            boolean flag = true;
            for (int i = 1; i <= n; i++) {
                a[i] = a[i - 1] + nextInt(); // prefix sum of array 'a'
            }
            if (a[n] != n) {
                flag = false; // Total number of black cells must be equal to n
            } else {
                for (int i = 1; i <= n / 2; i++) {
                    if (a[i] < 2 * i) {
                        flag = false;
                        break;
                    }
                }
                if (n % 2 == 1 && a[n / 2 + 1] < n) {
                    flag = false;
                }
            }

            if (flag) {
                long count = 1;
                for (int i = 1; i <= (n + 1) / 2; i++) {
                    // Compute combination C(n - 2*i - (a[n] - a[i]), a[i] - a[i-1])
                    count = count * comb(n + 2 - 2 * i - (a[n] - a[i]), a[i] - a[i - 1], MOD) % MOD;
                }
                result.append(count).append('\n');
            } else {
                result.append(0).append('\n');
            }
        }
        System.out.println(result);
    }

    // Compute combination C(N, K) mod P using Fermat's Little Theorem
    static long comb(int N, int K, int P) {
        if (N < 0) {
            return 0;
        }
        if (K == 0) {
            return 1;
        }
        // C(N,K) = N! / (K! * (N-K)!)
        return f[N] * modPow(f[K], P - 2, P) % P * modPow(f[N - K], P - 2, P) % P;
    }

    // Modular exponentiation: base^exp mod mod
    static long modPow(long base, long exp, int mod) {
        if (exp == 0) {
            return 1;
        }
        long h = modPow(base, exp / 2, mod);
        if (exp % 2 == 0) {
            return h * h % mod;
        } else {
            return h * h % mod * base % mod;
        }
    }
}


// https://github.com/VaHiX/CodeForces/
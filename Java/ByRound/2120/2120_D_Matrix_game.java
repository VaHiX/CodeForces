// Problem: CF 2120 D - Matrix game
// https://codeforces.com/contest/2120/problem/D

/*
 * Problem: Matrix game
 * 
 * Purpose:
 *   Given integers a, b, k, find the lexicographically smallest (n, m) such that
 *   any n x m matrix filled with values from 1 to k will contain a submatrix of size a x b 
 *   where all elements are equal.
 *
 * Algorithms/Techniques:
 *   - Combinatorial mathematics and pigeonhole principle
 *   - Modular arithmetic using Fermat's little theorem for modular inverse
 *   - Binary search or direct calculation based on threshold conditions
 *
 * Time Complexity: O(t * log(max(a,b,k))) where t is number of test cases
 * Space Complexity: O(1) excluding input/output
 */

import java.util.*;
import java.math.BigInteger;

public class Main {
    static final long MOD = 1_000_000_007L;
    
    // Computes C(n, r) mod MOD using modular inverse
    static long nCrMod(long n, int r) {
        if (r > n) return 0;
        long result = 1;
        for (int i = 0; i < r; i++) {
            long num = (n - i) % MOD;
            if (num < 0) num += MOD;
            result = (result * num) % MOD;
            long denom = i + 1;
            // Use modular inverse to compute division in mod space
            long inv = BigInteger.valueOf(denom)
                        .modInverse(BigInteger.valueOf(MOD))
                        .longValue();
            result = (result * inv) % MOD;
        }
        return result;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            int k = sc.nextInt();
            
            // Calculate n based on formula
            long n = (((long)k * (a - 1)) % MOD + 1) % MOD;
            
            // Calculate combination term
            long comb = nCrMod(((long)k * (a - 1) + 1), a);
            
            // Compute m using the derived formula
            long m = (((((long)(b - 1) % MOD) * (k % MOD)) % MOD) * comb) % MOD;
            m = (m + 1) % MOD;
            
            System.out.println(n + " " + m);
        }
        sc.close();
    }
}


// https://github.com/VaHiX/CodeForces/
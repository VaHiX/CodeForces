// Problem: CF 2132 C2 - The Cunning Seller (hard version)
// https://codeforces.com/contest/2132/problem/C2

/*
 * C2. The Cunning Seller (hard version)
 * 
 * Problem Description:
 * A seller offers deals where x watermelons can be bought for 3^(x+1) + x*3^(x-1) coins.
 * A buyer wants n watermelons using at most k deals and needs to minimize cost.
 *
 * Algorithm:
 * - Greedy approach with ternary representation analysis:
 *   Each deal of size x contributes a cost of 3^(x+1) + x*3^(x-1).
 *   We use dynamic programming ideas and ternary decomposition to compute optimal strategy.
 * 
 * Time Complexity: O(k * log n) per test case due to iteration up to k steps and logarithmic operations.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */
import java.io.*;
import java.util.*;
public class Main {
    static class a {
        private final byte[] b = new byte[1 << 16];
        private int c = 0, d = 0;
        private final InputStream e;
        a(InputStream f) { e = f; }
        private int g() throws IOException {
            if (c >= d) {
                d = e.read(b);
                c = 0;
                if (d == -1) return -1;
            }
            return b[c++];
        }
        long h() throws IOException {
            int i; long j = 0;
            do i = g(); while (i <= 32 && i != -1); // Skip whitespace
            while (i > 32 && i != -1) {
                j = j * 10 + (i - '0'); // Parse number
                i = g();
            }
            return j;
        }
    }
    public static void main(String[] z) throws Exception {
        a a = new a(System.in);
        int b = (int)a.h(); // Number of test cases
        StringBuilder c = new StringBuilder();
        while (b-- > 0) {
            long d = a.h(); // n: number of watermelons to buy
            long e = a.h(); // k: maximum number of deals allowed
            
            long f = 0, g = d; // f: sum of digits in base 3 of d, g: copy of d
            while (g > 0) { 
                f += g % 3; // Count base-3 digit sum
                g /= 3;
            }
            
            if (f > e) { 
                c.append("-1\n"); 
                continue; 
            } // Impossible to form n using at most k deals
            
            long h = 3 * d; // Base cost for d watermelons via deal of size 1
            if (d > e) { // If needed more than allowed number of deals, optimize
                long i = (d - e + 1) / 2; // Calculate how many extra deals we're considering
                long j = d / 3; // Start with smallest deal unit (3^1)
                long k = 1; // Power multiplier for base-3 representation
                while (i > 0 && j > 0) {
                    long l = Math.min(i, j); // Choose minimum of remaining needed and current quantity
                    h += l * k; // Add cost based on deal size
                    i -= l;   // Reduce remaining required deals
                    j /= 3;   // Move to next tier of larger deals
                    k *= 3;   // Increase multiplier for next deal level
                }
            }
            c.append(h).append('\n');
        }
        System.out.print(c);
    }
}


// https://github.com/VaHiX/codeForces/
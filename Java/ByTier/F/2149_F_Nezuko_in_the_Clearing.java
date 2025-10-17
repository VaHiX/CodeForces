// Problem: CF 2149 F - Nezuko in the Clearing
// https://codeforces.com/contest/2149/problem/F

/**
 * Problem: Nezuko in the Clearing
 *
 * Purpose:
 *   Computes the minimum number of turns required for Nezuko to reach point `d`
 *   on the number line starting from point 0 with initial health `h`.
 *   
 *   Nezuko can either rest (restore 1 health) or move forward 1 unit.
 *   Moving consumes health proportional to the consecutive movement count:
 *     - First move: 1 health consumed
 *     - Second move: 2 health consumed
 *     - etc.
 *   
 *   The optimal strategy involves minimizing total turns by using rest actions
 *   strategically in bursts of movements, where each burst moves a certain number
 *   of steps, then rests to recover enough health for another burst.
 *
 * Algorithms/Techniques:
 *   - Binary search on the number of rest actions (denoted as 'mid')
 *   - Mathematical formula to compute total damage from a sequence of moves
 *     using arithmetic series sum formulas
 *   
 * Time Complexity:
 *   O(t * log d), where t is the number of test cases and d is the target distance.
 *   Binary search on d, which takes log d time; for each step a constant-time calculation is done.
 *
 * Space Complexity:
 *   O(1) extra space (excluding input/output buffers).
 */

import java.io.*;
import java.util.*;

public class Main {
    static class FastScanner {
        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;
        FastScanner(InputStream is) { in = is; }
        private int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }
        long nextLong() throws IOException {
            int c;
            while ((c = read()) <= ' ') if (c == -1) return Long.MIN_VALUE;
            boolean neg = false;
            if (c == '-') { neg = true; c = read(); }
            long val = 0;
            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = read();
            }
            return neg ? -val : val;
        }
        int nextInt() throws IOException { return (int) nextLong(); }
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        int t = fs.nextInt();
        StringBuilder sb = new StringBuilder();
        while (t-- > 0) {
            long h = fs.nextLong();
            long d = fs.nextLong();
            long low = 0, high = d;
            while (low < high) {
                long mid = (low + high) >>> 1; // Binary search on number of rest actions
                long k = mid + 1;              // Number of moves in a single burst (including rest)
                long q = d / k;                // Quotient: number of full bursts
                long r = d % k;                // Remainder: steps remaining after full bursts
                long fq = q * (q + 1) / 2;     // Sum of first q natural numbers for full bursts
                long fq1 = (q + 1) * (q + 2) / 2;
                long C = r * fq1 + (k - r) * fq; // Total turns consumed by this distribution of moves and rests
                long rhs = h + mid - 1;        // RHS to check if the total cost is acceptable with given health
                if (C <= rhs) high = mid;      // If it's safe, try to reduce rest count
                else low = mid + 1;            // Else increase it
            }
            sb.append(d + low).append('\n'); // Final answer: total steps taken including rests
        }
        System.out.print(sb.toString());
    }
}


// https://github.com/VaHiX/CodeForces/
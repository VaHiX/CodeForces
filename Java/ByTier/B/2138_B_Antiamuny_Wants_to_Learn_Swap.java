// Problem: CF 2138 B - Antiamuny Wants to Learn Swap
// https://codeforces.com/contest/2138/problem/B

/**
 * Problem: B. Antiamuny Wants to Learn Swap
 *
 * Purpose:
 *   Determines whether a given subarray of a permutation is "perfect".
 *   A subarray is perfect if using both operations (adjacent swap and skip-swap)
 *   doesn't reduce the number of swaps needed compared to using only adjacent swaps.
 *
 * Algorithms/Techniques:
 *   - Monotonic stack for computing previous greater and next smaller elements
 *   - Preprocessing to find optimal ranges where operation 2 is useful
 *   - Range queries using precomputed results
 *
 * Time Complexity: O(n + q) per test case
 * Space Complexity: O(n) per test case
 */

import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

public class Main {
    private static final class FastScanner {
        private static final int BUFFER_SIZE = 1 << 16;
        private final byte[] buffer = new byte[BUFFER_SIZE];
        private int bufferPointer = 0, bytesRead = 0;

        private int readByte() {
            if (bufferPointer >= bytesRead) {
                try {
                    bytesRead = System.in.read(buffer);
                    bufferPointer = 0;
                } catch (Exception e) {
                    return -1;
                }
                if (bytesRead == -1) return -1;
            }
            return buffer[bufferPointer++];
        }

        int nextInt() {
            int c;
            do {
                c = readByte();
            } while (c <= ' ' && c != -1);
            boolean neg = false;
            if (c == '-') {
                neg = true;
                c = readByte();
            }
            int val = 0;
            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = readByte();
            }
            return neg ? -val : val;
        }

        long nextLong() {
            int c;
            do {
                c = readByte();
            } while (c <= ' ' && c != -1);
            boolean neg = false;
            if (c == '-') {
                neg = true;
                c = readByte();
            }
            long val = 0;
            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = readByte();
            }
            return neg ? -val : val;
        }

        String nextToken() throws IOException {
            int c = readByte();
            while (c <= ' ') c = readByte();
            StringBuilder sb = new StringBuilder();
            for (; c > ' '; c = readByte()) {
                sb.append((char) c);
            }
            return sb.toString();
        }
    }

    public static void main(String[] args) throws IOException {
        FastScanner fs = new FastScanner();
        int tests = fs.nextInt();
        PrintWriter pw = new PrintWriter(new BufferedOutputStream(System.out));
        StringBuilder out = new StringBuilder();

        while (tests-- > 0) {
            int n = fs.nextInt(), q = fs.nextInt();
            int[] a = new int[n + 1];
            for (int i = 1; i <= n; i++) a[i] = fs.nextInt();

            // prevGreater[i] stores index of previous element greater than a[i]
            int[] prevGreater = new int[n + 1];
            int[] st = new int[n + 1]; // stack for monotonic decreasing sequence
            int top = 0;

            // Compute for each i, the latest element larger than a[i] on its left
            for (int i = 1; i <= n; i++) {
                while (top > 0 && a[st[top - 1]] < a[i]) top--; // Pop until smaller or empty
                prevGreater[i] = top == 0 ? 0 : st[top - 1];    // If none found, set to 0
                st[top++] = i; // Push current index onto stack
            }

            // nextSmaller[i] stores index of next element smaller than a[i]
            int[] nextSmaller = new int[n + 2];
            top = 0;

            // Traverse from right to left, compute previous smaller indices with monotonic stack
            for (int i = n; i >= 1; i--) {
                while (top > 0 && a[st[top - 1]] > a[i]) top--; // Pop until larger or empty
                nextSmaller[i] = top == 0 ? n + 1 : st[top - 1]; // If none found, set to n+1
                st[top++] = i; // Push current index onto stack
            }

            // best[pg] represents the minimal nextSmaller for elements greater than a[pg]
            int[] best = new int[n + 2];
            Arrays.fill(best, n + 1);
            for (int j = 1; j <= n; j++) {
                int pg = prevGreater[j];
                if (pg > 0) {
                    int ns = nextSmaller[j];
                    if (ns < best[pg]) best[pg] = ns;
                }
            }

            // R[l] is the minimal nextSmaller of any element in range [l, n]
            int[] R = new int[n + 2];
            int run = n + 1;
            for (int l = n; l >= 1; l--) {
                if (best[l] < run) run = best[l]; // Update the running minimum of bests
                R[l] = run;
            }

            // Process queries
            while (q-- > 0) {
                int l = fs.nextInt(), r = fs.nextInt();
                if (r - l + 1 < 3) {
                    out.append("YES\n"); // Any subarray of size less than 3 needs at most one additional operation, so all are perfect
                    continue;
                }
                out.append(r < R[l] ? "YES\n" : "NO\n"); // If r is before the best range starting at l, then it is possible to rearrange with 2nd operation
            }
        }

        pw.println(out);
        pw.flush();
    }
}


// https://github.com/VaHiX/codeForces/
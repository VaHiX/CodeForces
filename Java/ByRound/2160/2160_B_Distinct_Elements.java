// Problem: CF 2160 B - Distinct Elements
// https://codeforces.com/contest/2160/problem/B

/*
 * Problem: B. Distinct Elements
 * Algorithm: Reconstruct array 'a' from given array 'b' where b[i] is sum of distinct elements in all subarrays ending at position i.
 * Approach:
 *   - For each element in b, calculate the difference between consecutive elements to get increment in distinct count.
 *   - Use a greedy method to assign values to array 'a':
 *     * If current distinct count increases, assign a new number (incrementing counter).
 *     * If it stays same, reuse previous value assigned at a previous position based on difference.
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the result array and temporary structures.
 */
import java.io.*;
import java.util.*;
public class B {
    static FastScanner fs = new FastScanner();
    static StringBuilder out = new StringBuilder();
    public static void main(String[] args) throws Exception {
        int t = fs.ni(); // Read number of test cases
        while (t-- > 0) procscse(); // Process each test case
        System.out.print(out.toString()); // Print all outputs
    }
    static void procscse() throws Exception {
        int n = fs.ni(); // Read length of array 'a'
        long[] b = new long[n + 1]; // Array to store cumulative distinct counts
        for (int i = 1; i <= n; i++) b[i] = fs.nl(); // Read values into b
        int[] a = nexas(n, b); // Compute array 'a' from 'b'
        echoarr(a, n); // Output array 'a'
    }
    static int[] nexas(int n, long[] b) {
        int[] a = new int[n + 1]; // Result array to be returned
        long prev = 0; // Previous cumulative count for difference calculation
        int nxt = 0; // Counter for next new number to assign
        for (int i = 1; i <= n; i++) {
            long g = b[i] - prev; // Difference gives the increment in unique elements
            prev = b[i]; // Update previous value for next iteration
            int p = i - (int) g; // Position we're referencing in a
            if (p == 0) { // If it's from start of array, assign new number
                nxt++;
                a[i] = nxt;
            } else {
                a[i] = a[p]; // Reuse value from the earlier position
            }
        }
        return a; // Return computed array 'a'
    }
    static void echoarr(int[] a, int n) {
        for (int i = 1; i <= n; i++) { // Loop through array to output
            if (i > 1) out.append(' '); // Add space between elements
            out.append(a[i]); // Append current element
        }
        out.append('\n'); // End line after each test case
    }
    static class FastScanner {
        private final InputStream in = System.in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;
        private int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }
        int ni() throws IOException {
            int c;
            while ((c = read()) <= ' ') if (c == -1) return -1;
            int sign = 1;
            if (c == '-') { sign = -1; c = read(); }
            int val = 0;
            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = read();
            }
            return val * sign;
        }
        long nl() throws IOException {
            int c;
            while ((c = read()) <= ' ') if (c == -1) return Long.MIN_VALUE;
            int sign = 1;
            if (c == '-') { sign = -1; c = read(); }
            long val = 0;
            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = read();
            }
            return val * sign;
        }
        String ns() throws IOException {
            int c;
            while ((c = read()) <= ' ') if (c == -1) return null;
            StringBuilder sb = new StringBuilder();
            while (c > ' ') {
                sb.append((char)c);
                c = read();
            }
            return sb.toString();
        }
        int[] na(int n) throws IOException {
            int[] a = new int[n];
            for (int i = 0; i < n; i++) a[i] = ni();
            return a;
        }
    }
}


// https://github.com/VaHiX/CodeForces/
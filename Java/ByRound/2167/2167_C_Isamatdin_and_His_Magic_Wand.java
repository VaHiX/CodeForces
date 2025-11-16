// Problem: CF 2167 C - Isamatdin and His Magic Wand!
// https://codeforces.com/contest/2167/problem/C

/*
 * Purpose: This code solves the problem of rearranging an array of integers
 *          using a magic wand that can only swap elements with different parity
 *          (even and odd). The goal is to achieve the lexicographically smallest
 *          arrangement possible under these constraints.
 *
 * Algorithm: 
 *   - If there are both even and odd numbers in the array, we can sort the entire
 *     array because any two elements can be swapped via a series of intermediate swaps.
 *   - If all elements are even or all are odd, then no swaps are possible, so output
 *     the original array.
 *
 * Time Complexity: O(n log n) per test case due to sorting when applicable.
 * Space Complexity: O(n) for the temporary array used for sorting.
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
        int nextInt() throws IOException {
            int c;
            while ((c = read()) <= ' ') if (c == -1) return Integer.MIN_VALUE;
            int sign = 1;
            if (c == '-') { sign = -1; c = read(); }
            int val = 0;
            while (c > ' ') { val = val * 10 + (c - '0'); c = read(); }
            return val * sign;
        }
    }
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder sb = new StringBuilder();
        int t = fs.nextInt();
        while (t-- > 0) {
            int n = fs.nextInt();
            int[] a = new int[n];
            boolean hasEven = false, hasOdd = false;
            for (int i = 0; i < n; i++) {
                a[i] = fs.nextInt();
                if ((a[i] & 1) == 0) hasEven = true; // Check if number is even using bitwise AND
                else hasOdd = true; // Check if number is odd
            }
            if (hasEven && hasOdd) { // If both even and odd numbers exist
                int[] b = Arrays.copyOf(a, n); // Create a copy of the array
                Arrays.sort(b); // Sort the copy to get the lexicographically smallest arrangement
                for (int i = 0; i < n; i++) {
                    if (i > 0) sb.append(' '); // Add space between elements
                    sb.append(b[i]); // Append sorted element
                }
            } else {
                // If all elements have same parity, no swaps are possible
                for (int i = 0; i < n; i++) {
                    if (i > 0) sb.append(' ');
                    sb.append(a[i]);
                }
            }
            sb.append('\n'); // Add newline after each test case
        }
        System.out.print(sb.toString());
    }
}


// https://github.com/VaHiX/CodeForces/
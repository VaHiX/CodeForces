// Problem: CF 2140 F - Sum Minimisation
// https://codeforces.com/contest/2140/problem/F

/*
F. Sum Minimisation
Algorithm: Greedy + Mathematical Observation
Time Complexity: O(n * sqrt(max(a)) + n * log(n)) per test case
Space Complexity: O(n)

The problem allows reducing elements in an array through a specific operation that:
1. Chooses k indices and computes the sum x of those elements.
2. Determines y = x % k (remainder).
3. Decreases the smallest y elements among the chosen k by 1.
4. If y=0, no decrements happen.

Key Observations:
- If all numbers are equal, no operation helps in reducing the sum further.
- For a large number of elements, if the array has a constant value and is very long,
  it suggests infinite decrement possibility (if modulo operations can lead to repeated states).
- We try greedy simulation by checking if we can reduce any element, or even a complete group.

Approach:
1. First check if all numbers are same — if yes, return sum directly.
2. Sort the array.
3. Try reducing first element and see if it leads to a valid state where future operations would still work.
4. If not possible at all, return -1.

This is a heuristic-based greedy algorithm that leverages modular arithmetic properties
and assumes convergence of operations under certain conditions.
*/
import java.io.*;
import java.util.*;
public class Main {
    static final FastScanner fs = new FastScanner(System.in);
    static boolean good(long[] a, int n, long s) {
        if (s % n != 0) return false; // If total sum is not divisible by n, no valid configuration possible directly
        if (n > 23) { // Large enough to consider all elements equal?
            long v = a[0];
            for (int i = 1; i < n; ++i) if (a[i] != v) return false;
            return true;
        } else {
            for (int mod = 2; mod < n; ++mod) { // Check divisibility conditions for smaller arrays
                long r = a[0] % mod;
                for (int j = 0; j < n; ++j) {
                    if (a[j] % mod != r) return false;
                }
            }
            return true;
        }
    }
    public static void main(String[] args) throws Exception {
        StringBuilder sb = new StringBuilder();
        int T = fs.nextInt();
        while (T-- > 0) {
            int n = fs.nextInt();
            long[] a = new long[n];
            long s = 0;
            for (int i = 0; i < n; ++i) { a[i] = fs.nextLong(); s += a[i]; }
            Arrays.sort(a);
            if (good(a, n, s)) { // If initial configuration satisfies conditions
                sb.append(s).append('\n');
                continue;
            }
            a[0]--; // Try reducing the smallest element
            s--;
            if (good(a, n, s)) sb.append(s).append('\n'); // If new one works too
            else sb.append(-1).append('\n'); // Otherwise impossible to reduce further
        }
        System.out.print(sb.toString());
    }
    static final class FastScanner {
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
        long nextLong() throws IOException {
            int c;
            while ((c = read()) <= ' ') if (c == -1) return Long.MIN_VALUE;
            int sign = 1;
            if (c == '-') { sign = -1; c = read(); }
            long val = 0;
            while (c > ' ') { val = val * 10 + (c - '0'); c = read(); }
            return val * sign;
        }
    }
}


// https://github.com/VaHiX/CodeForces/
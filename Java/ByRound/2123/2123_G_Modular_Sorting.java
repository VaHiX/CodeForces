// Problem: CF 2123 G - Modular Sorting
// https://codeforces.com/contest/2123/problem/G

/*
 * Problem: G. Modular Sorting
 * Purpose: Given an array of non-negative integers less than m and a modular operation,
 *          determine if the array can be made non-decreasing by applying operations of the form:
 *          a[i] := (a[i] + k) mod m.
 *
 * Approach:
 * - For each query of type 1 (update), efficiently update the affected counts
 * - For each query of type 2 (check), compute whether it's possible to make array non-decreasing using k.
 * - Precompute all divisors of m for efficient lookup.
 * - Maintain count of inversions per divisor class to quickly assess possible sorting via modular arithmetic.
 *
 * Time Complexity:
 *   - Preprocessing divisors: O(sqrt(m))
 *   - For each query 1 (update): O(d) where d is number of divisors
 *   - For each query 2 (check): O(1)
 *   - Total overall: O(q * sqrt(m) + n * sqrt(m))
 *
 * Space Complexity:
 *   - O(sqrt(m)) for storing divisors and divisor mappings
 *   - O(n) for input array
 *   - O(d) for counts array where d is number of divisors of m
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.StringTokenizer;

public class NonDecreasingArray {
    public static void solve(FastReader reader, PrintWriter out) throws IOException {
        int n = reader.nextInt();
        int m = reader.nextInt();
        int q = reader.nextInt();
        int[] a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = reader.nextInt();
        }
        List<Integer> divisors = new ArrayList<>();
        // Find all divisors of m
        for (int i = 1; i * i <= m; i++) {
            if (m % i == 0) {
                divisors.add(i);
                if (i * i != m) {
                    divisors.add(m / i);
                }
            }
        }
        Collections.sort(divisors);
        HashMap<Integer, Integer> divisorMap = new HashMap<>();
        // Map each divisor to its index in sorted list for fast access
        for (int i = 0; i < divisors.size(); i++) {
            divisorMap.put(divisors.get(i), i);
        }
        long[] counts = new long[divisors.size()];
        // Precompute inversion counts for all divisor classes, based on current array state
        if (n > 1) {
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < divisors.size(); j++) {
                    int d = divisors.get(j);
                    // If a[i] % d > a[i+1] % d, then there's an inversion in this divisor class
                    if (a[i] % d > a[i+1] % d) {
                        counts[j]++;
                    }
                }
            }
        }
        StringBuilder sb = new StringBuilder();
        for (int k = 0; k < q; k++) {
            int type = reader.nextInt();
            if (type == 1) {
                // Type 1: Update value at index i to x
                int i = reader.nextInt() - 1; 
                int x = reader.nextInt();
                int oldVal = a[i];
                if (n > 1) {
                    for (int j = 0; j < divisors.size(); j++) {
                        int d = divisors.get(j);
                        // Adjust counts when previous element changes
                        if (i > 0) {
                            int prevVal = a[i-1];
                            if (prevVal % d > oldVal % d) counts[j]--; // Remove old effect
                            if (prevVal % d > x % d) counts[j]++; // Add new effect
                        }
                        // Adjust counts when next element changes
                        if (i < n - 1) {
                            int nextVal = a[i+1];
                            if (oldVal % d > nextVal % d) counts[j]--; // Remove old effect
                            if (x % d > nextVal % d) counts[j]++; // Add new effect
                        }
                    }
                }
                a[i] = x;
            } else {
                // Type 2: Check if array can be sorted using modular operation with value k
                int valK = reader.nextInt();
                int g = gcd(valK, m); // GCD of k and m gives the effective modulo base for this query
                int divIdx = divisorMap.get(g); // Index in divisors list for corresponding divisor
                long wrapCount = counts[divIdx]; // Number of inversions in that class
                long lastElementModG = a[n-1] % g; // Last element reduced mod g
                // If we can add multiple wraps (modular additions) to last element to make it less than m,
                // then it is possible to sort the array
                if (lastElementModG + wrapCount * g < m) {
                    sb.append("YES\n");
                } else {
                    sb.append("NO\n");
                }
            }
        }
        out.print(sb.toString());
    }

    private static int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    public static void main(String[] args) throws IOException {
        FastReader reader = new FastReader();
        PrintWriter out = new PrintWriter(System.out);
        int t = reader.nextInt();
        while (t-- > 0) {
            solve(reader, out);
        }
        out.flush();
    }

    static class FastReader {
        BufferedReader br;
        StringTokenizer st;
        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }
        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }
        int nextInt() {
            return Integer.parseInt(next());
        }
        long nextLong() {
            return Long.parseLong(next());
        }
        double nextDouble() {
            return Double.parseDouble(next());
        }
        String nextLine() {
            String str = "";
            try {
                str = br.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return str;
        }
    }
}


// https://github.com/VaHiX/CodeForces/
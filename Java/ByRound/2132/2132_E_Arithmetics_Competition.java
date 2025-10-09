// Problem: CF 2132 E - Arithmetics Competition
// https://codeforces.com/contest/2132/problem/E

/*
 * Problem: E. Arithmetics Competition
 * 
 * Description:
 * In a team competition, two participants (Vadim and Kostya) each have a set of cards with numbers.
 * For each round, given constraints on how many cards they can take from their respective sets,
 * and the total number of cards to select in total, compute the maximum possible sum.
 * 
 * Approach:
 * - Sort both arrays in descending order for greedy selection (largest values first).
 * - Precompute prefix sums for both sorted arrays.
 * - Use ternary search to find the optimal split between Vadim's and Kostya's picks within bounds.
 * 
 * Time Complexity: O(n log n + m log m + q * log(max(x, y)))
 *   Sorting: O(n log n + m log m)
 *   Prefix sums: O(n + m)
 *   Q queries with ternary search: O(q * log(max(x, y)))
 * 
 * Space Complexity: O(n + m)
 *   For storing sorted arrays and their prefix sums.
 */

import java.util.*;
import java.io.*;
public class Main {
    static Read scan = new Read();
    static PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));
    public static void main(String[] args) throws IOException {
        int t = scan.nextInt();
        while (t-- != 0) {
            solve();
        }
        pw.flush();
    }
    private static void solve() throws IOException {
        int n = scan.nextInt();
        int m = scan.nextInt();
        int q = scan.nextInt();
        long[] a = new long[n];
        long[] b = new long[m];
        for (int i = 0; i < n; i++) {
            a[i] = scan.nextLong();
        }
        for (int i = 0; i < m; i++) {
            b[i] = scan.nextLong();
        }
        // Sort arrays in descending order to get maximum elements first.
        Arrays.sort(a);
        Arrays.sort(b);
        long[] A = new long[n + 1];
        long[] B = new long[m + 1];
        // Build prefix sums for a and b in reverse order (largest first).
        for (int i = 1; i <= n; i++) {
            A[i] = A[i - 1] + a[n - i];
        }
        for (int i = 1; i <= m; i++) {
            B[i] = B[i - 1] + b[m - i];
        }
        while (q-- > 0) {
            int x = scan.nextInt(); // Maximum cards Vadim can take
            int y = scan.nextInt(); // Maximum cards Kostya can take
            int z = scan.nextInt(); // Total cards to select
            // Compute range of valid splits between Vadim and Kostya.
            int L = Math.max(0, z - y);
            int R = Math.min(x, z);
            if (L > R) {
                pw.println(0);
                continue;
            }
            int low = L, high = R;
            // Use ternary search to find optimal value of k (cards Vadim takes).
            while (high - low > 2) {
                int mid1 = low + (high - low) / 3;
                int mid2 = high - (high - low) / 3;
                long f1 = A[mid1] + B[z - mid1]; // Sum if Vadim takes 'mid1' cards
                long f2 = A[mid2] + B[z - mid2]; // Sum if Vadim takes 'mid2' cards
                if (f1 < f2) {
                    low = mid1;
                } else {
                    high = mid2;
                }
            }
            long ans = 0;
            // Check remaining candidates in the narrowed down search space.
            for (int k = low; k <= high; k++) {
                long candidate = A[k] + B[z - k];
                if (candidate > ans) {
                    ans = candidate;
                }
            }
            pw.println(ans);
        }
    }
}
class Read {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st;
    String next() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(br.readLine());
        }
        return st.nextToken();
    }
    int nextInt() throws IOException {
        return Integer.parseInt(next());
    }
    long nextLong() throws IOException {
        return Long.parseLong(next());
    }
    String nextLine() throws IOException {
        return br.readLine();
    }
}


// https://github.com/VaHiX/CodeForces/
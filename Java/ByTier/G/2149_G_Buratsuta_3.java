// Problem: CF 2149 G - Buratsuta 3
// https://codeforces.com/contest/2149/problem/G

/*
 * Problem: Buratsuta 3
 * Purpose: For each query on subarray [l,r], find all values that occur strictly more than ⌊(r - l + 1)/3⌋ times.
 * 
 * Algorithms:
 *   - Coordinate compression for integers
 *   - Two-tiered approach:
 *     1. For short segments (length <= 3*B): brute-force count and check
 *     2. For long segments: use a prefix sum trick with heavy elements (> B occurrences)
 * 
 * Time Complexity: O(n * sqrt(n) + q * sqrt(n) * log(n))
 * Space Complexity: O(n + q)
 * 
 * Techniques:
 *   - Coordinate compression using TreeMap
 *   - TreeSet for sorted outputs
 *   - Prefix sum optimization
 *   - Heavy-light decomposition idea for large elements
 */

import java.util.*;

public class Q1_S20230010260 {
    static final int B = 200; // Threshold for small vs. large segments
    static int[] a = new int[200_000];       // Compressed input array
    static int[] inv = new int[200_000];     // Inverse mapping from compressed index to original value
    static int[] cnt = new int[200_000];     // Count array for frequency counting
    static int[] l = new int[200_000];       // Left boundaries of queries
    static int[] r = new int[200_000];       // Right boundaries of queries
    static int[] psum = new int[200_001];    // Prefix sum for heavy element optimization
    static TreeSet<Integer>[] ans = new TreeSet[200_000]; // Result storage, sorted per query

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        // Initialize TreeSet for each query result
        for (int i = 0; i < ans.length; i++) ans[i] = new TreeSet<>();

        while (T-- > 0) {
            int n = sc.nextInt();
            int q = sc.nextInt();

            Map<Integer, Integer> mp = new TreeMap<>(); // Coordinate compression map

            // Read input and prepare mapping
            for (int i = 0; i < n; i++) {
                a[i] = sc.nextInt();
                mp.put(a[i], 0); // Mark presence of element
            }

            // Read query boundaries
            for (int i = 0; i < q; i++) {
                l[i] = sc.nextInt() - 1; // Convert to 0-based indexing
                r[i] = sc.nextInt();
            }

            int c = 0;
            // Assign compressed indices
            for (Map.Entry<Integer, Integer> entry : mp.entrySet()) {
                entry.setValue(c);
                inv[c] = entry.getKey(); // Store original value at compressed index
                c++;
            }

            // Apply coordinate compression
            for (int i = 0; i < n; i++) a[i] = mp.get(a[i]);

            mp.clear();

            // Handle short queries: brute-force approach
            for (int i = 0; i < q; i++) {
                if (r[i] - l[i] > B * 3) continue; // Skip long queries for this phase

                for (int j = l[i]; j < r[i]; j++) cnt[a[j]]++; // Count frequencies

                for (int j = l[i]; j < r[i]; j++) {
                    // Check if frequency exceeds threshold
                    if (cnt[a[j]] * 3 > r[i] - l[i]) ans[i].add(inv[a[j]]);
                    cnt[a[j]] = 0; // Reset for next use
                }
            }

            // Handle long queries: use prefix sum trick on heavy elements (> B occurrences)
            for (int i = 0; i < n; i++) cnt[a[i]]++; // Count total occurrences

            for (int i = 0; i < c; i++) {
                if (cnt[i] < B) continue;

                psum[0] = 0;
                // Build prefix sum array
                for (int j = 0; j < n; j++) {
                    if (a[j] == i) psum[j + 1] = psum[j] + 2; // Add one extra for matching element
                    else psum[j + 1] = psum[j] - 1; // Subtract for non-matching
                }

                // For each query, check prefix sum difference
                for (int j = 0; j < q; j++) {
                    if (psum[r[j]] > psum[l[j]]) ans[j].add(inv[i]);
                }
            }

            // Clear frequency counters
            for (int i = 0; i < c; i++) cnt[i] = 0;

            // Output results per query
            for (int i = 0; i < q; i++) {
                if (ans[i].isEmpty()) {
                    System.out.println("-1");
                } else {
                    for (int x : ans[i]) System.out.print(x + " ");
                    System.out.println();
                    ans[i].clear(); // Reset for next test case
                }
            }
        }
        sc.close();
    }
}


// https://github.com/VaHiX/CodeForces/
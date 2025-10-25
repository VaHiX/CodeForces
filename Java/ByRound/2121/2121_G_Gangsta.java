// Problem: CF 2121 G - Gangsta
// https://codeforces.com/contest/2121/problem/G

/**
 * Problem: G. Gangsta
 * Purpose: For each binary string, compute the sum of maximum character frequencies 
 *          (f(s[l..r])) over all substrings s[l..r] where 1 <= l <= r <= n.
 * 
 * Algorithm:
 *   - Use prefix sums to transform the problem into evaluating contributions for each suffix.
 *   - Coordinate compression is used on prefix sums to manage Fenwick tree indices efficiently.
 *   - Two Fenwick trees are maintained:
 *     - One to count elements <= current value
 *     - One to sum elements <= current value
 *   - For each new element, calculate how much it contributes to the total by comparing 
 *     with values already seen and their counts/sums.
 * 
 * Time Complexity: O(n log n) per test case (due to Fenwick tree operations and coordinate compression)
 * Space Complexity: O(n) for storing prefix sums, coordinate mapping, and Fenwick trees
 */

import java.util.*;
import java.io.*;
public class Main {
    static class Fenwick {
        long[] tree;
        int size;
        public Fenwick(int size) {
            this.size = size;
            tree = new long[size + 1]; 
        }
        public void update(int idx, long delta) {
            while (idx <= size) {
                tree[idx] += delta;
                idx += idx & -idx; // Move to parent node
            }
        }
        public long query(int idx) {
            long res = 0;
            while (idx > 0) {
                res += tree[idx];
                idx -= idx & -idx; // Move to parent node
            }
            return res;
        }
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine());
        while (t-- > 0) {
            int n = Integer.parseInt(br.readLine());
            String s = br.readLine();
            long[] pre = new long[n + 1];
            pre[0] = 0;
            for (int i = 1; i <= n; i++) {
                // Build prefix sum: add 1 for '1', subtract 1 for '0'
                pre[i] = pre[i - 1] + (s.charAt(i - 1) == '1' ? 1 : -1);
            }
            Set<Long> set = new TreeSet<>();
            for (long val : pre) {
                set.add(val); // Collect all unique prefix sums
            }
            List<Long> sortedUnique = new ArrayList<>(set);
            Map<Long, Integer> valueToRank = new HashMap<>();
            int rank = 1;
            for (long val : sortedUnique) {
                valueToRank.put(val, rank++); // Assign ranks to compressed coordinates
            }
            int m = sortedUnique.size();
            Fenwick fenwickCount = new Fenwick(m);
            Fenwick fenwickSum = new Fenwick(m);
            long sumTotal = pre[0]; // Start with first prefix sum (0)
            int rank0 = valueToRank.get(pre[0]);
            fenwickCount.update(rank0, 1);
            fenwickSum.update(rank0, pre[0]);
            long sumAbsDiff = 0;
            for (int j = 1; j <= n; j++) {
                long currentVal = pre[j];
                int currentRank = valueToRank.get(currentVal); // Get rank of this prefix sum
                
                // Query count and sum of elements less than or equal to current value
                long countLe = fenwickCount.query(currentRank);
                long sumLe = fenwickSum.query(currentRank);
                
                // Derive count and sum of elements greater than current value
                long sumGt = sumTotal - sumLe;
                long countGt = j - countLe;
                
                // Calculate the contribution from this prefix sum
                long diff = currentVal * countLe - sumLe + (sumGt - currentVal * countGt);
                sumAbsDiff += diff; // Accumulate absolute difference contributions
                
                fenwickCount.update(currentRank, 1);
                fenwickSum.update(currentRank, currentVal);
                sumTotal += currentVal; // Update ongoing total prefix sum
            }
            
            long sumLengths = (long) n * (n + 1) * (n + 2) / 6; // Precompute sum of all substring lengths
            long ans = (sumLengths + sumAbsDiff) / 2;
            System.out.println(ans);
        }
    }
}


// https://github.com/VaHiX/CodeForces/
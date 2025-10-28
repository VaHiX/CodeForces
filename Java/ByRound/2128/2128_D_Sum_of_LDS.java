// Problem: CF 2128 D - Sum of LDS
// https://codeforces.com/contest/2128/problem/D

/**
 * Problem: D. Sum of LDS
 * Purpose: Given a permutation with a special property, compute the sum of lengths 
 *          of the longest decreasing subsequences (LDS) over all contiguous subarrays.
 * 
 * Algorithm:
 * - The key insight is that for each element p[i], we can determine how many subarrays 
 *   have their LDS ending at position i. However, the implementation uses a trick involving 
 *   counting valid pairs and subtracting invalid contributions from the total count.
 * - For every pair (i, j) such that p[i] < p[j], we calculate how many subarrays exist
 *   where this forms an increasing pair that cannot be part of any longer decreasing subsequence.
 * - Total number of subarrays is n*(n+1)*(n+2)/6 which accounts for all possible subarrays 
 *   in a specific combinatorial way related to the structure. Then we subtract those cases
 *   where the pattern breaks due to increasing adjacent elements.
 * 
 * Time Complexity: O(n) per test case, considering amortized operations.
 * Space Complexity: O(n), for storing the permutation array.
 */
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();
        int T = Integer.parseInt(in.readLine());
        while (T-- > 0) {
            int n = Integer.parseInt(in.readLine());
            StringTokenizer st = new StringTokenizer(in.readLine());
            int[] p = new int[n];
            for (int i = 0; i < n; i++) {
                p[i] = Integer.parseInt(st.nextToken());
            }
            // Total possible subarrays computed via formula: n*(n+1)*(n+2)/6
            long total = (long) n * (n + 1) * (n + 2) / 6;
            for (int i = 0; i + 1 < n; i++) {
                // If current element is smaller than next, it breaks potential decreasing subsequence
                if (p[i] < p[i + 1]) {
                    long idx = i + 1;
                    // Subtract contribution of invalid subarrays involving this violation
                    total -= idx * (n - idx);
                }
            }
            sb.append(total).append('\n');
        }
        System.out.print(sb);
    }
}


// https://github.com/VaHiX/CodeForces/
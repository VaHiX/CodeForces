// Problem: CF 2110 F - Faculty
// https://codeforces.com/contest/2110/problem/F

/*
 * Problem: Faculty - Calculate the "beauty" of prefixes of an array.
 * 
 * Description:
 * The beauty of an array is defined as the maximum value of f(x, y) = (x % y) + (y % x)
 * over all pairs (i, j) where 1 ≤ i, j ≤ n.
 * 
 * Algorithm:
 * - For each prefix of the input array, we maintain a running maximum (`maxSoFar`).
 * - We track all previously seen elements in `seen` array for comparison purposes.
 * - When processing a new element:
 *   - If current element is less than `maxSoFar`, compute f(x, maxSoFar) = x + (maxSoFar % x)
 *   - Else if equal to `maxSoFar`, do nothing.
 *   - Otherwise, update `maxSoFar`, and check all previous elements against the new maximum.
 * 
 * Time Complexity: O(n^2) worst case per test case due to nested loops when checking all past elements.
 * Space Complexity: O(n) for storing the seen array.
 */

import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();
        int t = Integer.parseInt(in.readLine().trim());
        while (t-- > 0) {
            int n = Integer.parseInt(in.readLine().trim());
            StringTokenizer st = new StringTokenizer(in.readLine());
            int[] seen = new int[n];          // Stores previously processed elements
            int seenSize = 0;                 // Current size of seen array
            int maxSoFar = 0;                 // Maximum element seen so far in current prefix
            int beauty = 0;                   // Current beauty value for the prefix
            
            for (int i = 0; i < n; i++) {
                int x = Integer.parseInt(st.nextToken());  // Read next element
                
                if (x < maxSoFar) {       // If x is smaller than current max
                    int cand = x + (maxSoFar % x);   // Compute f(x, maxSoFar)
                    if (cand > beauty) beauty = cand; // Update beauty if necessary
                }
                else if (x == maxSoFar) {   // If x equals maxSoFar
                    // No action needed since f(x,x) = 0
                }
                else {        // If x is greater than maxSoFar
                    if (maxSoFar > 0 && x < 2 * maxSoFar) {
                        // Special case: if x is less than twice the max, 
                        // we may get a better result by using x directly (f(x, maxSoFar) <= x)
                        if (x > beauty) beauty = x;
                    } else {
                        int best = 0;     // To store maximum f(y, x) for previous y values
                        for (int j = 0; j < seenSize; j++) {   // Check against all previously processed elements
                            int y = seen[j];
                            int val = y + (x % y);    // Compute f(y, x)
                            if (val > best) best = val;
                        }
                        if (best > beauty) beauty = best;  // Update global beauty
                    }
                    maxSoFar = x;   // Update maximum element seen so far
                }
                
                seen[seenSize++] = x;      // Add current element to seen list
                out.append(beauty).append(' ');    // Append current beauty to output
            }
            out.append('\n');
        }
        System.out.print(out.toString());
    }
}


// https://github.com/VaHiX/CodeForces/
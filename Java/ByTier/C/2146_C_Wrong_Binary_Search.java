// Problem: CF 2146 C - Wrong Binary Search
// https://codeforces.com/contest/2146/problem/C

/*
C. Wrong Binary Search
Algorithm: Greedy approach to construct a permutation based on the binary string s,
           where each position i in s indicates whether integer i should be stable (1) or not (0).

Time Complexity: O(n) per test case, as we process each element at most twice.
Space Complexity: O(n), for storing the permutation array p.

The key insight is that:
- If s[i] = '1', then p[i] must be i to make i stable (i.e., find(i) returns i).
- If s[i] = '0', then we need to place some number at position i such that it's not stable.
- Consecutive 0's must be handled by shifting values appropriately so they are not stable.

Approach:
1. First pass: verify if solution is possible (e.g., no single '0' alone).
2. Second pass: assign values to p based on the pattern of s.
*/

import java.io.*;
public class C_Wrong_Binary_Search {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int t = Integer.parseInt(br.readLine());
        while (t-- > 0) {
            int n = Integer.parseInt(br.readLine());
            String s = br.readLine();
            boolean possible = true;
            int ii = 1;
            while (ii <= n) {
                if (s.charAt(ii - 1) == '1') {
                    ii++;
                    continue;
                }
                // This block processes consecutive 0s
                int ll = ii;
                while (ii <= n && s.charAt(ii - 1) == '0') ii++;
                int rr = ii - 1;
                if (rr - ll + 1 == 1) {
                    possible = false;
                }
            }
            if (!possible) {
                out.println("NO");
                continue;
            }
            int[] p = new int[n + 1];
            int i = 1;
            while (i <= n) {
                if (s.charAt(i - 1) == '1') {
                    // If s[i] is '1', then p[i] must equal i
                    p[i] = i;
                    i++;
                    continue;
                }
                // Process consecutive 0s
                int l = i;
                while (i <= n && s.charAt(i - 1) == '0') i++;
                int r = i - 1;
                for (int j = l; j < r; j++) {
                    // Shift each element in range to next position
                    p[j] = j + 1;
                }
                // Last element points to first
                p[r] = l;
            }
            out.println("YES");
            for (int j = 1; j <= n; j++) {
                out.print(p[j]);
                out.print(" ");
            }
            out.println();
        }
        out.flush();
        out.close();
    }
}


// https://github.com/VaHiX/CodeForces/
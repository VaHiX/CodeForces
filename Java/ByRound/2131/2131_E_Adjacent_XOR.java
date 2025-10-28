// Problem: CF 2131 E - Adjacent XOR
// https://codeforces.com/contest/2131/problem/E

/*
 * Problem: E. Adjacent XOR
 * Purpose: Determine if array 'a' can be transformed into array 'b' using at most one XOR operation per element.
 * Algorithm: 
 *   - Traverse from right to left (n-2 down to 0)
 *   - For each element, check if it matches b[i] directly or can be obtained by XORing with adjacent elements
 *   - If neither condition holds, transformation is impossible
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1) excluding input storage
 */

import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            int n = sc.nextInt();
            int[] a = new int[n], b = new int[n];
            for (int i = 0; i < n; i++) a[i] = sc.nextInt(); // Read array a
            for (int i = 0; i < n; i++) b[i] = sc.nextInt(); // Read array b
            boolean c = (a[n - 1] == b[n - 1]); // Check last element directly
            for (int d = n - 2; d >= 0; d--) { // Traverse from second last to first
                // If a[d] != b[d], we need to determine if it's possible to reach b[d]
                // by applying XOR with either a[d+1] or b[d+1]
                if (a[d] != b[d] && (a[d] ^ a[d + 1]) != b[d] && (a[d] ^ b[d + 1]) != b[d]) {
                    c = false; // If none of the valid operations work, transformation is not possible
                    break;
                }
            }
            System.out.println(c ? "YES" : "NO"); // Output result for current test case
        }
        sc.close();
    }
}


// https://github.com/VaHiX/codeForces/
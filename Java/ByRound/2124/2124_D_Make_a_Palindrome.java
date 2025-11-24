// Problem: CF 2124 D - Make a Palindrome
// https://codeforces.com/contest/2124/problem/D

/*
 * Problem: D. Make a Palindrome
 *
 * Purpose:
 *   Determine if we can transform an array into a palindrome by deleting elements
 *   using specific operations: select a subarray of size at least k, then remove
 *   the k-th smallest element in that subarray.
 *
 * Algorithm:
 *   - If k == 1, we can remove any element, so we can always form a palindrome (YES).
 *   - Otherwise, we attempt to build a palindrome by checking if it's possible
 *     under certain constraints involving the sorted array and greedy pairing.
 *   - We extract all elements <= cutoff (k-2)-th smallest in sorted array,
 *     then try to pair them greedily from both ends to form a valid palindrome,
 *     allowing some flexibility when elements equal cutoff.
 *
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(n) for storing arrays and lists
 */

import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int tt = scanner.nextInt();
        while (tt-- > 0) {
            solve(scanner);
        }
        scanner.close();
    }

    private static void solve(Scanner scanner) {
        int n = scanner.nextInt();   // Read size of array
        int k = scanner.nextInt();   // Read k value
        int[] aa = new int[n];       // Original array
        for (int i = 0; i < n; i++) {
            aa[i] = scanner.nextInt();
        }

        if (k == 1) {
            System.out.println("YES");  // Can delete any element, so always possible
            return;
        }

        int[] bb = Arrays.copyOf(aa, n);  // Copy original array for sorting
        Arrays.sort(bb);                  // Sort it to find cutoff value

        int cutoff = bb[k - 2];           // k-th smallest element in sorted array (0-indexed)

        List<Integer> cc = new ArrayList<>();  // List of elements <= cutoff
        for (int a : aa) {
            if (a <= cutoff) {
                cc.add(a);
            }
        }

        int spare = cc.size() - k + 1;   // Number of extra elements we can "spare" for flexibility
        int L = 0;                       // Left pointer
        int R = cc.size() - 1;           // Right pointer
        boolean bad = false;             // Flag to indicate if palindrome can't be formed

        while (L < R) {
            if (!cc.get(L).equals(cc.get(R))) {
                // If elements don't match, check if we can use spare to fix it
                if (spare == 0) {
                    bad = true;
                    break;
                }

                // Try to move the pointer whose element equals cutoff
                if (cc.get(L) == cutoff) {
                    L++;        // Move left ptr forward
                    spare--;    // Reduce available spare
                } else if (cc.get(R) == cutoff) {
                    R--;        // Move right ptr backward
                    spare--;    // Reduce available spare
                } else {
                    // If neither side is cutoff, we cannot resolve mismatch with current spare
                    bad = true;
                    break;
                }
                continue;  // Skip decrementing pointers, restart loop
            }
            // If elements match, move both pointers inward
            L++;
            R--;
        }

        System.out.println(bad ? "NO" : "YES");
    }
}


// https://github.com/VaHiX/CodeForces/
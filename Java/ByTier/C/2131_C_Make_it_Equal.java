// Problem: CF 2131 C - Make it Equal
// https://codeforces.com/contest/2131/problem/C

/*
C. Make it Equal

Purpose:
This program determines whether two multisets S and T can be made equal by applying a specific operation: 
for any element x in S, we can remove x and insert either (x + k) or |x - k| into S.
The key insight is that elements are effectively grouped by their remainder when divided by k,
and the transformation preserves the "distance" from multiples of k.

Algorithms/Techniques:
- Modular arithmetic to map numbers to their equivalence class based on remainder mod k
- Sorting and comparison of transformed arrays to check if multisets can be matched

Time Complexity: O(n log n) per test case due to sorting of arrays of size n.
Space Complexity: O(n) for storing the remainder arrays of size n.

*/

import java.util.*;
public class C_Make_it_Equal {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            int n = sc.nextInt();
            int k = sc.nextInt();
            int[] arr1 = new int[n];
            int[] arr2 = new int[n];
            for (int i = 0; i < n; i++) {
                int x = sc.nextInt() % k;
                // Calculate minimal distance to closest multiple of k
                arr1[i] = Math.min(x, (k - x) % k);
            }
            for (int i = 0; i < n; i++) {
                int x = sc.nextInt() % k;
                // Calculate minimal distance to closest multiple of k
                arr2[i] = Math.min(x, (k - x) % k);
            }
            Arrays.sort(arr1);
            Arrays.sort(arr2);
            // If the sorted arrays of distances are equal, multisets can be made equal
            if (Arrays.equals(arr1, arr2)) {
                System.out.println("YES");
            } else {
                System.out.println("NO");
            }
        }
    }
}


// https://github.com/VaHiX/codeForces/
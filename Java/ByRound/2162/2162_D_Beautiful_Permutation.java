// Problem: CF 2162 D - Beautiful Permutation
// https://codeforces.com/contest/2162/problem/D

import java.util.*;
public class Mainaa {
    static void solve(Scanner sc) {
        int n = sc.nextInt();
        int l = 1, r = n;
        int k1, k2;
        // Query the entire array sum of modified array
        System.out.println("2 " + l + " " + r);
        System.out.flush(); 
        k2 = sc.nextInt();
        // Calculate k = r - l + 1 (size of the range that was incremented)
        int k = k2 - (n * (n + 1) / 2);
        // Binary search to find the exact range [l, r]
        while (r - l + 1 > k) {
            int  mid = (l + r) >> 1;
            // Query sum of original array in range [l, mid]
            System.out.println("1 " + l + " " + mid);
            System.out.flush();
            k1 = sc.nextInt();
            // Query sum of modified array in range [l, mid]
            System.out.println("2 " + l + " " + mid);
            System.out.flush();
            k2 = sc.nextInt();
            // If difference is equal to k, the range contains the modified segment
            if (k2 - k1 == k)
                r = mid;
            // If difference is 0, there is no modification in this segment
            else if (k2 - k1 == 0)
                l = mid+1;
            else {
                // If difference is between 0 and k, we found a partial overlap
                // Adjust range based on the difference to correctly identify l and r
                System.out.println("! " + (mid - (k2 - k1) + 1) + " " + (mid + (k - (k2 - k1))));
                System.out.flush();
                return;
            }
        }
        // Output the final answer when the range is narrowed down to k elements
        System.out.println("! " + l + " " + r);
        System.out.flush();
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int test = sc.nextInt();
        while (test-- > 0) {
            solve(sc);
        }
        sc.close();
    }
}

// https://github.com/VaHiX/CodeForces/
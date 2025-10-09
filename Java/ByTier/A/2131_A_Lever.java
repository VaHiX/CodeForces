// Problem: CF 2131 A - Lever
// https://codeforces.com/contest/2131/problem/A

/*
 * Problem: A. Lever
 * Purpose: Simulate a process where two arrays 'a' and 'b' are modified based on comparison,
 *          counting the number of iterations until no more valid operations can be performed.
 *
 * Algorithm:
 * - For each test case, iterate through the arrays and compute the total number of decrements needed
 *   to make all elements in array 'a' at least equal to corresponding elements in array 'b'.
 * - This is equivalent to summing up all positive differences (a[i] - b[i]) where a[i] > b[i].
 * - The result is this sum plus one, as the final iteration ends when no decrement operation is possible.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the arrays
 */

import java.util.*;
public class A_Lever {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt(); // Read number of test cases
        while (t-- >0){
            int n = sc.nextInt(); // Read size of arrays
            int[] a = new int[n]; // Initialize array 'a'
            for(int i=0;i<n;i++) a[i] = sc.nextInt(); // Fill array 'a'
            int[] b = new int[n]; // Initialize array 'b'
            for(int i=0;i<n;i++) b[i] = sc.nextInt(); // Fill array 'b'
            int ans = 0; // Variable to store the total excess in 'a' over 'b'
            for(int i=0;i<n;i++) if(a[i]>b[i]) ans += a[i]-b[i]; // Sum up excess values
            System.out.println(ans+1); // Output number of iterations (add 1 for final step)
        }
    }
}


// https://github.com/VaHiX/codeForces/
// Problem: CF 2124 A - Deranged Deletions
// https://codeforces.com/contest/2124/problem/A

/*
 * Problem: A. Deranged Deletions
 * 
 * Purpose: Determine if we can delete elements from an array such that the remaining
 *          elements form a derangement. A derangement is an array where no element
 *          appears in its sorted position.
 * 
 * Algorithm:
 *   - For each test case, iterate through all pairs of elements (i, j) where i < j.
 *   - If a[i] > a[j], it means we found two elements such that the first is greater than the second,
 *     which means by deleting one of them, the remaining array can become a derangement.
 *   - Output YES and show 2 elements if such pair exists, otherwise NO.
 * 
 * Time Complexity: O(n^2) per test case due to nested loops checking all pairs.
 * Space Complexity: O(n) for storing the input array.
 */

import java.util.*;
public class Main {
    static void solve(Scanner sc) {
        int n = sc.nextInt();
        int[] a = new int[n];
        for(int i = 0; i < n; i++) a[i] = sc.nextInt(); // Read array elements
        
       for(int i = 0; i < n; i++) // Outer loop to iterate over all elements
       {
           for(int j = i+1; j < n; j++) // Inner loop to compare with remaining elements
           {
               if(a[i] > a[j]) // If condition holds, we found a valid pair to form derangement
               {
                   System.out.println("YES");
                   System.out.println(2);
                   System.out.println(a[i] + " " + a[j]);
                   return;
               }
           }
       }
        System.out.println("NO"); // No such pair found, cannot make derangement
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt(); // Read number of test cases
        while(t-- > 0) solve(sc); // Process each test case
        sc.close();
    }
}


// https://github.com/VaHiX/CodeForces/
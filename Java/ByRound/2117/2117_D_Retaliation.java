// Problem: CF 2117 D - Retaliation
// https://codeforces.com/contest/2117/problem/D

/*
 * Problem: D. Retaliation
 * Purpose: Determine if an array can be reduced to all zeros using two types of operations:
 *          1. Decrease each element a[i] by i (1-indexed)
 *          2. Decrease each element a[i] by (n - i + 1)
 *
 * Algorithm:
 *   - Use mathematical derivation to check if there exist non-negative integers x and y
 *     such that:
 *       For each index i, we have:
 *         a[i] = (n - i) * x + (i + 1) * y
 *   - Rearranging for first two elements:
 *     a[0] = n*x + y
 *     a[1] = (n-1)*x + 2*y
 *   - From these equations, we derive:
 *     x = (2*a[0] - a[1]) / (n+1)
 *     y = a[0] - n*x
 *   - Check consistency across all elements using derived x and y.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1) excluding input storage
 */

import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int t = scan.nextInt(); // Read number of test cases
        
        while(t-->0){
            int n = scan.nextInt(); // Read size of array
            int[] arr = new int[n]; // Initialize array
            
            // Read array elements
            for(int i=0 ;i<n ;i++) arr[i] = scan.nextInt();
            
            boolean flag=true; // Flag to track if solution exists
            
            // Check if x can be computed as integer
            if((2*arr[0] - arr[1])%(n+1)!=0){
                flag = false;
            }
            
            int x = (2*arr[0] - arr[1])/(n+1); // Compute x based on derived formula
            int y = arr[0]-n*x; // Compute y using first equation
            
            // If either x or y is negative, it's invalid
            if(y<0 || x<0) flag=false;
            
            // Validate computed x and y against all elements in array
            for(int i=0 ; i<n ; i++){
                if((n-i)*x + (i+1)*y !=arr[i]){
                    flag = false;
                    break;
                }
            }
            
            // Output result
            if(flag) System.out.println("YES");
            else System.out.println("NO");
        }
    }   
}


// https://github.com/VaHiX/CodeForces/
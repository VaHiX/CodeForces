// Problem: CF 2112 B - Shrinking Array
// https://codeforces.com/contest/2112/problem/B

/**
 * Problem: B. Shrinking Array
 * 
 * Purpose: Given an array of integers, determine the minimum number of operations
 *          required to make the array "beautiful". An array is beautiful if there exists
 *          a position i such that |b[i] - b[i+1]| <= 1.
 *          
 *          Operation: Choose two adjacent elements, remove them, and insert a value 
 *                     x between min(a[i], a[i+1]) and max(a[i], a[i+1]).
 *                     
 * Algorithm:
 *   1. If the array is already beautiful (has adjacent pair with difference <= 1), return 0.
 *   2. If all elements are increasing or decreasing, it's impossible to make it beautiful → return -1.
 *   3. Otherwise, check if a single operation can produce a beautiful array → return 1.
 *   
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for input array storage
 */

import java.util.Scanner;
public class Main{
    public static int solve(int n, int[] a){
        // Check if array is already beautiful (has adjacent pair with difference <= 1)
        for(int i = 0;i<n-1;i++){
            if(Math.abs(a[i]-a[i+1])<=1){ // If adjacent elements differ by at most 1
                return 0; // Already beautiful
            }
        }
        
        // Determine if array is strictly increasing or decreasing
        boolean f = false; // true if there's a decrease
        boolean g = false; // true if there's an increase
        for(int i = 0;i<n-1;i++){
            if(a[i]>a[i+1])f = true; // Found a decrease
            else g = true; // Found an increase
        }
        
        // If both increasing and decreasing trends exist, one operation is sufficient
        if(f && g) return 1;
        else return -1; // Only one trend means impossible to make beautiful
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        for(int i =0;i<t;i++){
            int n = sc.nextInt();
            int[] a = new int[n];
            for(int j = 0;j<n;j++){
                a[j] = sc.nextInt();
            }
            System.out.println(solve(n, a));
        }
    }
}


// https://github.com/VaHiX/CodeForces/
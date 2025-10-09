// Problem: CF 2110 A - Fashionable Array
// https://codeforces.com/contest/2110/problem/A

/*
 * Problem: A. Fashionable Array
 * 
 * Purpose: 
 *   Given an array of integers, determine the minimum number of operations (removing elements)
 *   required to make the array "fashionable". An array is fashionable if the sum of its
 *   minimum and maximum elements is even.
 * 
 * Algorithm:
 *   - Sort the array to easily access min and max values.
 *   - For each subarray formed by removing elements from both ends, check if the sum
 *     of the first and last elements (min and max of that subarray) is even.
 *   - Keep track of the minimum operations needed to achieve this condition.
 * 
 * Time Complexity: O(n^2)
 * Space Complexity: O(1) (not counting input storage)
 */

import java.util.Arrays;
import java.util.Scanner;

public class A_Fashionable_Array {
    public static void solve(Scanner sc) {
        int n = sc.nextInt();
        int[] v = new int[n];
        for (int i = 0; i < n; i++) {
            v[i] = sc.nextInt();
        }
        Arrays.sort(v); // Sort the array to easily access min and max
        int min = n; // Initialize with maximum possible operations (removing all elements)
        for(int i = 0; i < n; i++) {
            for(int j = i; j < n; j++) {
                if((v[i] + v[j]) % 2 == 0) { // Check if sum of min and max is even
                    int op = i + (n - 1 - j); // Calculate operations needed to get this subarray
                    min = Math.min(min, op); // Keep track of minimum operations
                }
            }
        }
        System.out.println(min);
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            solve(sc);
        }
        sc.close();
    }
}


// https://github.com/VaHiX/CodeForces/
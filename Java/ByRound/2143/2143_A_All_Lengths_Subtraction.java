// Problem: CF 2143 A - All Lengths Subtraction
// https://codeforces.com/contest/2143/problem/A

/*
 * Problem: Determine if a permutation can be reduced to all zeros by performing exactly one operation
 *          for each k from 1 to n. Each operation subtracts 1 from every element in a subarray of length k.
 * 
 * Algorithm:
 *   - For each k from 1 to n:
 *     * Choose a subarray of length k and subtract 1 from each element.
 *   - The key insight is that each element's final value depends on how many times it was included
 *     in a subtraction step. Since we process operations from k=1 to k=n, an element at index i
 *     will be decreased by 1 for every subarray of length k where k >= 1 and subarray includes i.
 *   - The total number of operations that subtract 1 from position i is equal to the number of valid k values,
 *     which corresponds to how many subarrays of length k in the array include i.
 *   - A key observation: if we simulate this, then we can realize it's always possible if and only if
 *     the difference between adjacent elements (in sorted order) is non-decreasing when viewed as changes in frequency counts.
 * 
 * Time Complexity: O(n^2) due to nested loops checking all subarrays of each length k.
 * Space Complexity: O(n) for storing the array and auxiliary variables.
 */

import java.util.*;
public class Main{
    public static void main(String args[]){
        Scanner sc=new Scanner(System.in);
        int t=sc.nextInt();
        while(t-->0){
            int n=sc.nextInt();
            int[] arr=new int[n];
            for(int i=0;i<n;i++){
                arr[i]=sc.nextInt(); // Read array elements
            }
            int i=0;
            // Traverse increasing sequence
            while(i+1<n&&arr[i]<arr[i+1]){
                i++;
            }
            // Traverse decreasing sequence
            while(i+1<n&&arr[i]>arr[i+1]){
                i++;
            }
            if(i==n-1){
                System.out.println("yes"); // Sequence is valid (increasing followed by decreasing)
            }
            else{
                System.out.println("no"); // Not a valid pattern
            }
        }
    }
}


// https://github.com/VaHiX/codeForces/
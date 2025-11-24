// Problem: CF 2107 A - LRC and VIP
// https://codeforces.com/contest/2107/problem/A

/*
 * Problem: A. LRC and VIP
 * 
 * Purpose: Given an array of integers, partition it into two non-empty sequences such that the GCDs of the two sequences are different.
 * 
 * Algorithm/Techniques:
 * - For each test case:
 *   1. Find the minimum and maximum elements in the array.
 *   2. If all elements are equal, it's impossible to split into two groups with different GCDs → output "No".
 *   3. Otherwise, assign all elements with value equal to max to sequence B (group 1), others to sequence C (group 2).
 *      This ensures that one group will have a large number and the other will not, leading to different GCDs.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the array
 */

import java.util.Scanner;
public class A_LRC_and_VIP{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t =sc.nextInt(); // Read number of test cases
        while(t-->0){
            int n = sc.nextInt(); // Read size of array
            int[] arr = new int[n];
            for(int i=0;i<n;i++)arr[i]=sc.nextInt(); // Read array elements
            int min = Integer.MAX_VALUE,max=Integer.MIN_VALUE;
            for(int i:arr){
                max = Math.max(max, i); // Find maximum element
                min = Math.min(min,i); // Find minimum element
            }
            if(min==max){ // If all elements are same, impossible to split
                System.out.println("No");continue;
            }
            System.out.println("Yes");
            for (int i = 0; i < n; i++) {
                // Assign element to group 2 if it equals max, otherwise 1
                System.out.print((1 + (arr[i] == max ? 1 : 0)) + (i + 1 == n ? "\n" : " "));
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/
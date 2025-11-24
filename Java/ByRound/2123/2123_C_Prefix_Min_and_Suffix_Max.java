// Problem: CF 2123 C - Prefix Min and Suffix Max
// https://codeforces.com/contest/2123/problem/C

/*
C. Prefix Min and Suffix Max
Algorithm: 
    - For each element a[i], determine if it's possible to reduce the array to just [a[i]] 
      using operations: replace prefix with its minimum or suffix with its maximum.
    
    - Key Insight:
        * An element a[i] can be the final element if:
            1. It is the minimum in some prefix ending at i (i.e., it's a "prefix min")
            2. It is the maximum in some suffix starting from i (i.e., it's a "suffix max")

    - Approach:
        * Precompute for each index i:
            - b[i] = 1 if a[i] is a prefix minimum up to that point.
            - b[i] = 1 if a[i] is a suffix maximum from that point onwards.

        * To do this:
            - First pass (left to right): mark all positions where a[i] is the minimum seen so far.
            - Second pass (right to left): mark all positions where a[i] is the maximum seen so far.

    - Time Complexity: O(n)
    - Space Complexity: O(1) extra space (excluding input/output arrays)

*/

import java.util.*;

public class C_Prefix_Min_and_Suffix_Max {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while(t-->0){
            int n = sc.nextInt();
            int a[] = new int[n];
            int b[] = new int[n]; // Stores 1 if a[i] can be final element, 0 otherwise
            int max=0; // Tracks maximum from right to left
            int min=0; // Tracks minimum from left to right
            
            // Left to right pass: mark prefix mins
            for(int i=0; i<n; i++) {
                a[i] = sc.nextInt();
                if(a[i]<min || i==0){  // If current element is smaller than seen min or first element, it's new min
                    min = a[i];
                    b[i] = 1;  // Mark that current element is prefix min
                }
            }
            
            // Right to left pass: mark suffix maxs
            for(int i=n-1; i>=0; i--) {
                if(a[i]>max || i==n-1) {  // If current element is larger than seen max or last element, it's new max
                    max = a[i];
                    b[i] = 1;  // Mark that current element is suffix max   
                }
            }
            
            for(int i=0; i<n; i++) {
                System.out.print(b[i]);
            }
            System.out.println();
        }
    }
}


// https://github.com/VaHiX/CodeForces/
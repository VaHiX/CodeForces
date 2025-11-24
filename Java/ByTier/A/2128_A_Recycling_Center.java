// Problem: CF 2128 A - Recycling Center
// https://codeforces.com/contest/2128/problem/A

/*
 * Problem: Recycling Center
 * 
 * Purpose:
 *   Given n trash bags with weights, we must destroy all of them. Each second,
 *   we choose one bag to destroy (costing 1 coin if weight > c, 0 otherwise),
 *   then all remaining bags' weights are doubled.
 *   
 *   Goal: Find the minimum number of coins needed to destroy all bags.
 *   
 * Algorithm:
 *   Greedy approach:
 *     - Sort bags in ascending order.
 *     - Process from largest to smallest (reverse iteration).
 *     - For each bag, if its current weight (after doubling) is <= c, we can
 *       destroy it for free; otherwise, we must pay 1 coin.
 *     - We maintain a counter 'doube' which represents how many times the bag's
 *       weight was doubled before processing it.
 * 
 * Time Complexity: O(n log n) per test case due to sorting.
 * Space Complexity: O(n) for the array storage.
 */

import java.util.*;
public class Main {
    public static void main(String[] args) {
       Scanner sc=new Scanner(System.in);
       int t=sc.nextInt();
       while(t-->0)
       {
         int n=sc.nextInt();        // Read number of bags
         int c=sc.nextInt();        // Read threshold weight
         int arr[]=new int[n];      // Array to store weights
         for(int i=0;i<n;i++)
         {
           arr[i]=sc.nextInt();     // Read each bag's weight
         }
         Arrays.sort(arr);          // Sort in ascending order
         int doube=0;               // Counter for number of doublings
         for(int i=n-1;i>=0;i--)    // Process from largest to smallest
         {
           if(arr[i]*(1<<doube)<=c) // Check if bag can be destroyed for free
           {
             doube++;               // Increment doubling count
           }
         }
         System.out.println(n-doube); // Print coins spent = total bags - free bags
       }
  }
}


// https://github.com/VaHiX/CodeForces/
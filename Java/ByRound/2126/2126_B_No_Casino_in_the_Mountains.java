// Problem: CF 2126 B - No Casino in the Mountains
// https://codeforces.com/contest/2126/problem/B

/*
 * Problem: B. No Casino in the Mountains
 * 
 * Purpose: Given an array of n days where each element represents weather (0 = good, 1 = rain),
 *          find the maximum number of k-day hikes Jean can take such that:
 *          - Each hike takes exactly k consecutive good days (0s)
 *          - After each hike, there must be at least one break day (1 or end of array)
 * 
 * Algorithm: Sliding window approach
 *            - Scan the array for valid k-length windows of 0s
 *            - When a valid window is found, increment count and skip the next day as break
 *            - Continue until the end of the array
 * 
 * Time Complexity: O(n) where n is the size of the input array (each element visited once)
 * Space Complexity: O(1) excluding input storage, only using a few variables
 */

import java.util.*;
public class Main {
    public static void main(String[] args) {
      Scanner sc=new Scanner(System.in);
      int t=sc.nextInt();
      for(int i=0;i<t;i++){
        int n=sc.nextInt();
        int k=sc.nextInt();
        int[] arr=new int[n];
        for(int j=0;j<n;j++){
          arr[j]=sc.nextInt();
        }
        int count=0;
        int k1=0; // counter for consecutive good days
        for(int j=0;j<n;j++){
          if(arr[j]==0){ // if current day is good weather
            k1++; // increment consecutive good day counter
            if(k1==k){ // when we have k consecutive good days
              count++; // we can start a hike
              k1=0; // reset counter
              j+=1; // skip the next day (mandatory break)
            }
          }
          else{ // if current day is bad weather (rain)
            k1=0; // reset consecutive good day counter
          }
        }
        System.out.println(count);
      }
  }
}


// https://github.com/VaHiX/CodeForces/
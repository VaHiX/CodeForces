// Problem: CF 2159 D1 - Inverse Minimum Partition (Easy Version)
// https://codeforces.com/contest/2159/problem/D1

/*
 * Problem: D1. Inverse Minimum Partition (Easy Version)
 * Purpose: Given a sequence of positive integers, compute the minimum total cost to partition the sequence into subsequences,
 *          where the cost of each subsequence is defined as ceil(k / min_element) where k is the length of the subsequence.
 * Algorithms/Techniques:
 *   - Dynamic Programming with Binary Search
 *   - Preprocessing to maintain a decreasing sequence
 * Time Complexity: O(n log n) per test case
 * Space Complexity: O(n) for storing arrays and lists
 */
import java.io.*;
import java.util.*;
public class D1058{
   public static void main(String[] args)throws IOException{
      BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
      PrintWriter out = new PrintWriter(System.out);
      int t = Integer.parseInt(f.readLine());
      for(int q = 1; q <= t; q++){
         int n = Integer.parseInt(f.readLine());
         StringTokenizer st = new StringTokenizer(f.readLine());
         long[] array = new long[n];
         for(int k = 0; k < n; k++){
            array[k] = Long.parseLong(st.nextToken());
         }
         // Build a decreasing sequence from the end to optimize dynamic programming states
         ArrayList<Long> alist = new ArrayList<Long>();
         alist.add(array[n-1]);
         for(int k = n-2; k >= 0; k--){
            if(array[k] < alist.get(alist.size()-1)){
               alist.add(array[k]);
            }
         }
         // Add a sentinel zero to the list for easier handling of edge cases
         alist.add(0L);        
         Collections.reverse(alist);
         int dn = alist.size();
         int[] dp = new int[dn];
         dp[0] = 0;
         dp[1] = 1;
         int l,r,ans;
         // Dynamic programming loop to compute minimum cost for each prefix
         for(int k = 2; k < dn; k++){
            // Default case: extend previous partition (add 1 to cost)
            dp[k] = dp[k-1] + 1;
            // Binary search for the best previous state when using factor of 2
            int i2 = bs(alist,k,2L);
            dp[k] = Math.min(dp[k],dp[i2] + 2);
            // Binary search for the best previous state when using factor of 3
            int i3 = bs(alist,k,3L);
            dp[k] = Math.min(dp[k],dp[i3] + 3);
         }
         // Output result for current test case
         out.println(dp[dn-1]);
      }
      out.close();
   }
   // Binary search helper function to find best previous index based on threshold
   public static int bs(ArrayList<Long> alist, int i, long thresh){
      long x = alist.get(i);
      int l = 1;
      int r = i-1;
      int ans = 0;
      while(l <= r){
         int mid = l + (r-l)/2;
         // Check if current element multiplied by threshold is less than target
         if(alist.get(mid) * thresh < x){
            ans = mid;
            l = mid+1;
         } else {
            r = mid-1;
         }
      }
      return ans;
   }
}


// https://github.com/VaHiX/CodeForces/
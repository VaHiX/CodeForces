// Problem: CF 2143 B - Discounts
// https://codeforces.com/contest/2143/problem/B

/*
B. Discounts
Approach:
- Greedy algorithm using sorting and prefix sums.
- Sort product prices in descending order to maximize savings from discounts.
- Sort discount voucher sizes in ascending order to apply smaller groups first (greedy).
- Use a prefix sum array for efficient range sum queries.
- For each group of products, we pay for all but the cheapest one in that group.
- If a group size exceeds remaining products, stop.
Time Complexity: O(n log n + k log k) due to sorting and linear traversal
Space Complexity: O(n + k) for arrays storing prices, vouchers, and prefix sums

Algorithms/Techniques:
- Sorting (descending for prices, ascending for voucher sizes)
- Prefix Sum Array for fast range sum calculation
- Greedy strategy: apply smaller discount groups first to avoid large unused discounts
*/

import java.util.*;
import java.lang.*;
import java.io.*;
public class Discount
{
	public static void main (String[] args) throws java.lang.Exception
	{
       BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine());
        while (T-- > 0) {
            String[] s = br.readLine().split(" ");
            int n = Integer.parseInt(s[0]), k = Integer.parseInt(s[1]);
            Long[] a = Arrays.stream(br.readLine().split(" ")).map(Long::parseLong).toArray(Long[]::new);
            Long[] b = Arrays.stream(br.readLine().split(" ")).map(Long::parseLong).toArray(Long[]::new);
            
            // Sort prices in descending order to get maximum savings with discounts
            Arrays.sort(a, Collections.reverseOrder());
            
            // Sort vouchers in ascending order to apply smaller groups first (greedy)
            Arrays.sort(b);
            
            // Build prefix sum array for efficient range sum queries
            long[] pre = new long[n+1]; 
            for (int i=0;i<n;i++) 
                pre[i+1]=pre[i]+a[i];
                
            long ans=0; 
            int p=0;
            
            // Process each discount voucher
            for(long v:b){
                int sz=(int)v;
                
                // If not enough products left, break
                if(p+sz>n) 
                    break;
                    
                // Add the sum of all elements except the smallest (which is free)
                ans += pre[p+sz] - pre[p] - a[p+sz-1];
                
                // Move pointer to next unprocessed product
                p += sz;
            }
            
            // Pay for remaining products not covered by any discount
            ans += pre[n] - pre[p];
            
            System.out.println(ans);
        }
	}
}


// https://github.com/VaHiX/codeForces/
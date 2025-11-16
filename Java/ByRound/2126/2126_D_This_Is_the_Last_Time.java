// Problem: CF 2126 D - This Is the Last Time
// https://codeforces.com/contest/2126/problem/D

/*
 * Problem: D. This Is the Last Time
 * 
 * Purpose: Given n casinos, each with a range of coins required to play and a reward,
 *          find the maximum number of coins achievable starting with k coins.
 *          
 * Algorithm: 
 *   - Sort all casinos by their minimum required coins (l_i) in ascending order.
 *   - Iterate through sorted casinos, and for each casino, if current coins are within
 *     the range [l_i, r_i], then update coins to max(coins, real_i).
 *   - This greedy approach works because we process casinos in increasing order of
 *     required coins, ensuring optimal choices at each step.
 *   
 * Time Complexity: O(n log n) due to sorting; the traversal is O(n), so overall is O(n log n).
 * Space Complexity: O(1) if we don't count input storage; otherwise O(n) for the 2D array.
 */

import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
          int n=sc.nextInt();
          int coins=sc.nextInt();
          int[][] arr=new int[n][3];
        for(int i=0;i<n;i++){
           for(int j=0;j<3;j++){
            arr[i][j]=sc.nextInt();
           }
        }
        // Sort casinos by the minimum required coins (l_i)
        Arrays.sort(arr,(a,b)->Integer.compare(a[0],b[0]));
        int idx=0;
         while(idx<n){
                // Check if current coins are within the range of the casino
                if(coins>=arr[idx][0] && coins<=arr[idx][1]){
                    // Update coins to maximum of current and reward
                    coins=Math.max(coins,arr[idx][2]);
                }
            idx++;
         }
        System.out.println(coins);
        }   
        sc.close();
    }
}


// https://github.com/VaHiX/CodeForces/
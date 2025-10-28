// Problem: CF 2133 B - Villagers
// https://codeforces.com/contest/2133/problem/B

/*
B. Villagers
Algorithm: Greedy approach with sorting
Approach:
- To minimize total emeralds spent, we want to pair villagers optimally such that each operation contributes the least possible cost.
- Sort the grumpiness values in ascending order.
- For a connected graph of n nodes (villagers), we need exactly n - 1 edges (friendships).
- The optimal strategy is to always combine the two smallest remaining grumpiness values to minimize cost.
- This can be achieved by taking elements at even indices (0, 2, 4, ...) from the sorted array.
Time Complexity: O(n log n) due to sorting; processing takes O(n)
Space Complexity: O(n) for the array storing grumpiness values

*/

import java.util.*;
public class s6{
    public static void main(String args[]){
        Scanner sc=new Scanner(System.in);
        int t=sc.nextInt();
        for(int j=0;j<t;j++){
            int n=sc.nextInt();
            long[] g=new long[n];
            for(int i=0;i<n;i++)g[i]=sc.nextLong();
            Arrays.sort(g); // Sort grumpiness values
            long ans=0;
            int s=(n%2==1)?0:1; // Start index based on whether n is odd or even
            for(int i=s;i<n;i+=2)ans+=g[i]; // Add elements at even indices to minimize total emeralds
            System.out.println(ans);
        }
        sc.close();
    }
}


// https://github.com/VaHiX/codeForces/
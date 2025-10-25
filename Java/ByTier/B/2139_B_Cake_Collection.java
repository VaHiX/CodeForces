// Problem: CF 2139 B - Cake Collection
// https://codeforces.com/contest/2139/problem/B

/*
B. Cake Collection
Algorithms/Techniques: Greedy approach with sorting
Time Complexity: O(n log n + n) per test case due to sorting and single pass
Space Complexity: O(1) excluding input storage

Problem Summary:
Maple has n ovens, each baking a[i] cakes per second. She can collect cakes from any oven at the end of each second.
She wants to maximize total cakes collected in m seconds.

Approach:
- Sort the ovens by cake production rate (ascending).
- For each second from the end (m-1 down to 0), we decide which oven to visit.
- To maximize, at each step, choose the oven with highest remaining capacity.
- Since after m seconds all ovens will have baked a[i]*m cakes,
  but we only collect once per oven, use greedy selection in reverse:
    - Visit ovens with highest rates first.
    - Accumulate result by multiplying rate with time left.

*/

import java.util.*;
public class B_Cake_Collection {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while(t-- > 0) {
            int n = sc.nextInt(), m = sc.nextInt();
            int[] a = new int[n];
            for(int i=0; i<n; i++) a[i] = sc.nextInt();
            Arrays.sort(a); // Sort ovens by rate (ascending)
            long result = 0;
            // Traverse from highest rate oven to lowest
            for(int i=n-1; i>=0; i--) {
                // Calculate how many seconds left to use this oven (from m down to current position)
                int timeLeft = m - (n - 1 - i); 
                if(timeLeft > 0) {
                    result += (long) a[i] * timeLeft;
                }
            }
            System.out.println(result);
        }
        sc.close();
    }
}


// https://github.com/VaHiX/codeForces/
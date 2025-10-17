// Problem: CF 2122 B - Pile Shuffling
// https://codeforces.com/contest/2122/problem/B

/*
B. Pile Shuffling

Purpose:
This program calculates the minimum number of operations required to transform n binary piles from their initial state to a target state. Each pile has a certain number of zeros on top (a_i) and ones on bottom (b_i), and the goal is to make them match the target configuration (c_i zeros on top, d_i ones on bottom).

Approach:
We analyze each pile independently. For each pile i:
1. We compute how many elements need to be moved from the "one" part of the original pile to the "zero" part of the target pile ('one' = d_i - b_i).
2. We compute how many elements need to be moved from the "zero" part of the original pile to the "one" part of the target pile ('zero' = c_i - a_i).

If 'one' is negative, it means we have more ones than required in the target (need to move some ones down). If 'zero' is positive, it means we have fewer zeros than needed in the target (need to move some zeros up).

The total operations required are:
- If one < 0: We must move |one| elements downward (from ones to zeros) AND also move min(c_i, a_i) elements.
- If zero > 0: We must move zero elements upward.

Time Complexity: O(n), where n is the number of piles. Each pile is processed once.
Space Complexity: O(1), constant extra space used.

*/

import java.io.*;
import java.util.*;
public class Solution {
    public static void main(String args[]) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine());
        while (t-- > 0) {
            int n = Integer.parseInt(br.readLine());
            long ans = 0;
            for (int i = 0; i < n; i++) {
                StringTokenizer st = new StringTokenizer(br.readLine());
                long a = Long.parseLong(st.nextToken()); // original zeros
                long b = Long.parseLong(st.nextToken()); // original ones
                long c = Long.parseLong(st.nextToken()); // target zeros
                long d = Long.parseLong(st.nextToken()); // target ones
                
                long one = d - b;   // how many ones to move from current pile
                long zero = c - a;  // how many zeros to move from current pile
                
                if (one < 0) {
                    // Need to move some ones down, and possibly add extra moves based on overlap
                    ans += Math.abs(one) + Math.min(c, a);
                }
                if (zero > 0) {
                    // Need to move some zeros up
                    ans += zero;
                }
            }
            System.out.println(ans);
        }
    }
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 2148 C - Pacer
// https://codeforces.com/contest/2148/problem/C

/*
 * Problem: C. Pacer
 * 
 * Description:
 * Farmer John is running the FitnessGram Pacer Test. He can choose to run or stay in place at
 * the start of each minute, gaining one point for each run. He must meet specific requirements
 * that specify where he should be at certain times.
 * 
 * Algorithm:
 * - Greedily optimize the number of points FJ can gain by choosing the best route to meet
 *   requirements while maximizing runs.
 * - At each requirement, decide whether to move (and gain a point) if necessary to reach the
 *   correct side at that time.
 * - The key idea is to analyze the time gaps between consecutive requirements and determine
 *   how many optimal moves can be made within those gaps.
 * 
 * Time Complexity: O(n) per test case, where n is the number of requirements.
 * Space Complexity: O(1), only using a few variables for computation.
 */

import java.util.Scanner;

public class C_Pacer {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            int n = sc.nextInt();
            long m = sc.nextLong();
            long prevTime = 0;
            int prevSide = 0;
            long ans = 0;

            // Process each requirement
            for (int i = 0; i < n; i++) {
                long a = sc.nextLong(); // Time when requirement occurs
                int b = sc.nextInt();   // Required side at time a

                long d = a - prevTime;  // Time difference from previous requirement
                int need = prevSide ^ b; // XOR tells us if we must move (1) or not (0)

                // If we need to move and the time allows, we gain at least one point
                // If d is odd and need is 1, we can get exactly d points.
                // If d is even and need is 1, we must reduce by 1 to avoid overcounting.
                ans += (d % 2 == need) ? d : d - 1;

                prevTime = a;
                prevSide = b;
            }

            // Handle the final interval from last requirement to m
            ans += m - prevTime;
            System.out.println(ans);
        }
    }
}


// https://github.com/VaHiX/codeForces/
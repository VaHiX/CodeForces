// Problem: CF 2135 B - For the Champion
// https://codeforces.com/contest/2135/problem/B

/*
 * Problem: B. For the Champion
 *
 * Purpose: This code finds the initial coordinates (X, Y) of a robot on an infinite 2D plane,
 *          given n anchor points and the ability to move in four directions (up, down, left, right)
 *          with queries returning the minimum Manhattan distance to any anchor point.
 *
 * Algorithm:
 * - First, determine the bounds of possible coordinates by querying the robot's position
 *   with large movements in each direction to estimate min/max x and y.
 * - Then use a binary search-like logic to deduce the exact coordinates using Manhattan distances.
 *
 * Time Complexity: O(n) per test case for reading input and processing one query, plus
 *                  O(1) operations for each move, but with up to 10 moves total. Overall:
 *                  O(n) + O(1)*10 = O(n) for a single test case.
 *
 * Space Complexity: O(1), only using fixed-size variables and no additional data structures
 *                   beyond input reading (which is not counted in space complexity).
 */

import java.util.*;
public class boilerplate {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {
        int t = sc.nextInt();  
        while (t-- > 0) {
            int n = sc.nextInt();
            long min=Integer.MAX_VALUE;
            long max=Integer.MIN_VALUE;
            for(int i=0;i<n;i++){
                long x=sc.nextLong();
                long y=sc.nextLong();
                min=Math.min(y-x,min); // Compute min of (y - x) for all anchors
                max=Math.max(max,x+y); // Compute max of (x + y) for all anchors
            }
            long k = 1_000_000_000L; // Large value to move robot far away from anchors
            
            // Query moves with large k in different directions to get bounds on Manhattan distances
            long d1=sendAndGet("? U "+k); // Move up
            d1=sendAndGet("? U "+k);
            d1=sendAndGet("? R "+k); // Move right
            d1=sendAndGet("? R "+k);
            
            long d2=sendAndGet("? D "+k); // Move down
            d2=sendAndGet("? D "+k);
            d2=sendAndGet("? D "+k);
            d2=sendAndGet("? D "+k);
            
            // Using mathematical relation derived from coordinate bounds:
            long a=((d1+d2)-(8*k)+(max-min))/2; // Compute x-coordinate
            long b = d1 - 4*k + max - a;         // Compute y-coordinate
            
            System.out.println("! "+a+" "+b);
            System.out.flush();
        }
        sc.close();
    }
    
    // Static method to send query and receive distance response
    static long sendAndGet(String query) {
        System.out.println(query);
        System.out.flush();
        try {
            long res = sc.nextLong(); 
            if (res == -1) {
                System.exit(0);
            }
            return res;
        } catch (NoSuchElementException e) {
            System.exit(0);
            return -1; 
        }
    }
}


// https://github.com/VaHiX/CodeForces/
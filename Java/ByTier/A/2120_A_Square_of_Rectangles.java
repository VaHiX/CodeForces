// Problem: CF 2120 A - Square of Rectangles
// https://codeforces.com/contest/2120/problem/A

/*
 * Problem: Arrange three rectangles to form a square
 * 
 * Algorithm/Techniques:
 * - Check all possible valid arrangements of 3 rectangles to form a square
 * - Given l1 >= l2 >= l3 and b1 >= b2 >= b3
 * - For each arrangement, verify that the total area matches square area and dimensions align
 * 
 * Time Complexity: O(1) - constant number of checks (4 conditions)
 * Space Complexity: O(1) - only using a few variables
 */

import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner ob = new Scanner(System.in);
        int t = ob.nextInt(); // Read number of test cases
        while (t-- > 0) { // Process each test case
                int l1 = ob.nextInt(); // Length of first rectangle
                int b1 = ob.nextInt(); // Breadth of first rectangle
                int l2 = ob.nextInt(); // Length of second rectangle
                int b2 = ob.nextInt(); // Breadth of second rectangle
                int l3 = ob.nextInt(); // Length of third rectangle
                int b3 = ob.nextInt(); // Breadth of third rectangle
                
                // Check all valid arrangements that could form a square
                if((l1 == l2+l3 && b2==b3 && b1+b2 == l1) || // Case 1: First rect aligned horizontally with others stacked vertically
                   (l1==l2 && l1==l3 &&b1+b2+b3 == l1 ) ||   // Case 2: All aligned horizontally, stacked vertically
                   (b1==b2 && b1==b3 && l1+l2+l3 == b1) ||   // Case 3: All aligned vertically, stacked horizontally
                   (l2 == l3 && b1==b2+b3 && l1+l2 == b1))   // Case 4: Two smaller rectangles aligned horizontally with one vertical
                {
                    System.out.println("YES"); // Valid arrangement found
                    continue;
                }
                System.out.println("NO"); // No valid arrangement
        }
    }
}


// https://github.com/VaHiX/CodeForces/
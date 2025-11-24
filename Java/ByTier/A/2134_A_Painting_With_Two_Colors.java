// Problem: CF 2134 A - Painting With Two Colors
// https://codeforces.com/contest/2134/problem/A

/*
 * Problem: Painting With Two Colors
 * 
 * Algorithm/Techniques: Mathematical analysis and symmetry check
 * 
 * Approach:
 * - A coloring is symmetric if for every cell i, the color of cell i equals the color of cell (n+1-i).
 * - After painting a red section [x, x+a-1] and a blue section [y, y+b-1], we analyze the symmetry condition.
 * - We check conditions based on relative sizes of 'a' and 'b', determining valid combinations of x and y that lead to symmetric coloring.
 * 
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

import java.util.*;
public class Main{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while(t-->0){
            int n = sc.nextInt();   // Total number of cells
            int a = sc.nextInt();   // Length of red segment
            int b = sc.nextInt();   // Length of blue segment
            
            if(a<=b) 
                // If 'a' is smaller or equal to 'b', check if parity of n matches parity of b
                System.out.println(n%2==b%2 ? "YES" : "NO");
            else 
                // If 'a' is larger than 'b', both n and a must have same parity as b for symmetric result
                System.out.println(n%2==a%2 && n%2==b%2 ? "YES" : "NO");
        }
    }
}


// https://github.com/VaHiX/codeForces/
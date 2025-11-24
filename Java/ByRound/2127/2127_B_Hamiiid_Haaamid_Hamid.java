// Problem: CF 2127 B - Hamiiid, Haaamid... Hamid?
// https://codeforces.com/contest/2127/problem/B

/*
 * Problem: B. Hamiiid, Haaamid... Hamid?
 * Purpose: Determine the number of days Hamid needs to escape a 1×n grid,
 *          where Mani builds walls and Hamid moves/destroys walls optimally.
 * 
 * Algorithms/Techniques:
 *   - Two-pointers to find the nearest walls on both sides of Hamid's position.
 *   - Greedy optimization: for each direction, calculate the number of days
 *     it would take to escape if that direction is chosen.
 *   
 * Time Complexity: O(n) per test case, where n is the grid size.
 * Space Complexity: O(1), excluding input storage.
 */

import java.io.*;
import java.util.*;
public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);
        int t = Integer.parseInt(br.readLine());
        while (t-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());       // Grid size
            int x = Integer.parseInt(st.nextToken()) - 1;   // Hamid's initial position (0-indexed)
            String s = br.readLine();                       // Initial state of the grid
            
            int l = x, r = x;                               // Pointers to expand left and right from Hamid's position
            
            // Expand left while cells are empty ('.') to find leftmost wall
            while (l >= 0 && s.charAt(l) == '.') {
                l--;
            }
            
            // Expand right while cells are empty ('.') to find rightmost wall
            while (r < n && s.charAt(r) == '.') {
                r++;
            }
            
            // Calculate the minimum number of moves required to escape 
            // by going left or right, considering the optimal placement of walls by Mani.
            
            // Left option: Hamid moves left towards nearest wall and destroys it,
            // and then needs to cross that wall to escape.  
            int leftOption  = Math.min(x, n - r);
            
            // Right option: Hamid moves right towards nearest wall and destroys it,
            // and then needs to cross that wall to escape.
            int rightOption = Math.min(l + 1, n - x - 1);
            
            // The answer is the maximum of left and right options plus one day for Hamid's action
            int ans = Math.max(leftOption, rightOption) + 1;
            pw.println(ans);
        }
        pw.flush();
    }
}


// https://github.com/VaHiX/CodeForces/
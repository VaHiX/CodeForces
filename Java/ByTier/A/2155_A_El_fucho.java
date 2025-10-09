// Problem: CF 2155 A - El fucho
// https://codeforces.com/contest/2155/problem/A

/*
 * Problem: Tournament Matches Count
 * 
 * Description:
 * In a modified double-elimination football tournament with n teams, we need to determine
 * the total number of matches played until a single winner emerges.
 * 
 * Algorithm/Techniques:
 * - Simulates tournament rounds where teams are split into winners and losers groups.
 * - Each match eliminates exactly one team from the competition.
 * - The key insight is that in any valid elimination tournament structure, exactly (n-1) teams
 *   must be eliminated, hence (n-1) matches are needed to determine a single winner.
 * 
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(1), constant extra space used.
 * 
 * Example:
 * For n=2: 2 matches
 * For n=3: 4 matches
 */

import java.util.Scanner;
public class Div2 {
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        int t=sc.nextInt(); // Read number of test cases
        while(t-->0){ // Process each test case
            int n=sc.nextInt(); // Read number of teams
            System.out.println(2*(n-1)); // Output total matches (derived from logic above)
        }
    }
}


// https://github.com/VaHiX/CodeForces/
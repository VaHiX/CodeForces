// Problem: CF 2109 A - It's Time To Duel
// https://codeforces.com/contest/2109/problem/A

/*
 * Problem: It's Time To Duel
 * 
 * Purpose:
 *   Given n players in a tournament where each player reports whether they won at least one duel (1) or none (0),
 *   determine if the reports are consistent with the structure of a tournament where every adjacent pair duels.
 * 
 * Algorithm:
 *   - For each test case, we simulate the tournament by checking consistency of the reports.
 *   - The key insight is that in any sequence of duels between consecutive players, there must be at least one winner per match.
 *   - If two adjacent players both report 0 (no wins), it's impossible since one must win.
 *   - If a player reports 1 but no subsequent player reports 0 (meaning they never lost), then their report is valid only if they're not at the end.
 * 
 * Time Complexity:
 *   O(n) per test case, where n is the number of players. We iterate through the array once to process each player's report.
 * 
 * Space Complexity:
 *   O(1) extra space (excluding input/output). The string s is temporary and reused; no additional data structures scaling with input size.
 * 
 * Techniques:
 *   - Linear scan through the reports
 *   - Checking for adjacent zero-zero pairs which indicate a contradiction
 *   - Simplified logic using string concatenation for convenience in input processing (though inefficient)
 */

import java.util.Scanner;
public class Its_Time_To_Duel {
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        int t=sc.nextInt(); // Read number of test cases
        while (t-->0){
            int n=sc.nextInt(); // Read the number of players
            String s=""; // Initialize an empty string to store reports as a sequence
            for (int i=0;i<n;i++)s+=sc.next(); // Concatenate all player reports into one string
            if(s.contains("00")||!s.contains("0")) System.out.println("YES"); // If there is a "00" or no "0" at all, then contradiction exists => someone must be lying
            else System.out.println("NO"); // Otherwise, all reports are consistent
        }
    }
}


// https://github.com/VaHiX/CodeForces/
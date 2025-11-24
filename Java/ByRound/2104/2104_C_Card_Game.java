// Problem: CF 2104 C - Card Game
// https://codeforces.com/contest/2104/problem/C

/*
 * Problem: Card Game
 * 
 * Description:
 * Alice and Bob play a game with n cards where each card has a value from 1 to n.
 * Card i beats card j if and only if i > j, except for the special case where card 1 beats card n.
 * Players take turns, each playing one of their cards. The player whose card beats the opponent's card wins both.
 * The goal is to determine who wins with optimal play.
 * 
 * Approach:
 * - For any string of cards (A/B), we simulate or analyze based on first and last characters,
 *   along with certain edge conditions involving the existence of specific cards.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) due to input string storage
 */

import java.util.*;
import java.lang.*;
import java.io.*;

public class Codechef {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int ts = Integer.parseInt(br.readLine());
        for(int t=0; t<ts; t++) {
            int n = Integer.parseInt(br.readLine());
            String s = br.readLine();
            char f = s.charAt(0);
            char l = s.charAt(n - 1);
            
            // If first and last card are same, the winner is determined directly
            if (f == l) System.out.println(f == 'A' ? "Alice" : "Bob");
            else if (l == 'B') 
                // If last character is B, check if only one B exists to decide the outcome
                System.out.println(s.indexOf('B') == s.lastIndexOf('B') ? "Alice" : "Bob");
            else 
                // Otherwise, look at second-to-last character to determine winner
                System.out.println(s.charAt(n - 2) == 'A' ? "Alice" : "Bob");
        }
    }
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 2143 E - Make Good
// https://codeforces.com/contest/2143/problem/E

/**
 * E. Make Good
 * 
 * Problem Description:
 * Given a bracket string s of length n, we can perform two types of operations:
 * 1. Replace "((" with "))" 
 * 2. Replace "))" with "((" 
 * Goal: Transform the string into a valid (regular) bracket sequence, or return -1 if impossible.
 * 
 * Algorithm:
 * - For a valid bracket sequence, total '(' must equal total ')', and at no point should ')' exceed '(' while scanning left to right.
 * - The operations allow us to change adjacent pairs of brackets.
 * - So we check if it's possible to rearrange the brackets into a valid pattern.
 * 
 * Key Observations:
 * - If length n is odd, it can never form a valid bracket sequence → return "-1"
 * - Count how many '(' are at odd positions (1-indexed) and even positions (1-indexed)
 *   These represent possible adjustments to balance parentheses
 * - Calculate target number of '(' at even/odd positions needed for valid matching
 * - Reconstruct the string with these targets ensuring balance at all times
 * 
 * Time Complexity: O(n), where n is length of string. Each character is processed once.
 * Space Complexity: O(n), for storing intermediate string and StringBuilder output.
 */
import java.util.*;
import java.io.*;
public class E_Make_Good {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine());
        StringBuilder out = new StringBuilder();
        while (t-- > 0) {
            int n = Integer.parseInt(br.readLine());
            StringTokenizer st = new StringTokenizer(br.readLine());
            String s = st.nextToken();
            out.append(solve(n, s)).append("\n");
        }
        System.out.print(out);
    }
    
    private static String solve(int n, String s) {
        if (n % 2 != 0) return "-1"; // If length is odd, it's impossible to form a balanced bracket sequence
        
        int oddOpen = 0, evenOpen = 0;
        for (int i = 0; i < n; i++) {
            if (s.charAt(i) == '(') {
                if ((i + 1) % 2 != 0) oddOpen++; // Count '(' at odd positions (1-indexed)
                else evenOpen++; // Count '(' at even positions (1-indexed)
            }
        }
        
        int d = oddOpen - evenOpen; // Difference in counts to understand imbalance
        // Check if we can distribute such that a valid bracket sequence is possible
        if ((n / 2 + d) % 2 != 0 || (n / 2 - d) % 2 != 0) return "-1";
        
        int targetOddOpen = (n / 2 + d) / 2; // Target number of '(' at odd positions
        int targetEvenOpen = (n / 2 - d) / 2; // Target number of '(' at even positions
        
        if (targetOddOpen < 0 || targetEvenOpen < 0 ||
            targetOddOpen > n / 2 || targetEvenOpen > n / 2) return "-1";
        
        StringBuilder tStr = new StringBuilder(n);
        for (int i = 0; i < n; i++) {
            if ((i + 1) % 2 != 0) { // Odd position
                if (targetOddOpen > 0) {
                    tStr.append('(');
                    targetOddOpen--;
                } else {
                    tStr.append(')');
                }
            } else { // Even position
                if (targetEvenOpen > 0) {
                    tStr.append('(');
                    targetEvenOpen--;
                } else {
                    tStr.append(')');
                }
            }
        }
        
        int balance = 0;
        for (int i = 0; i < n; i++) {
            if (tStr.charAt(i) == '(') balance++;
            else balance--;
            if (balance < 0) return "-1"; // Invalid at any point
        }
        return tStr.toString();
    }
}


// https://github.com/VaHiX/codeForces/
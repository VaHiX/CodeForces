// Problem: CF 2110 B - Down with Brackets
// https://codeforces.com/contest/2110/problem/B

/*
 * Problem: B. Down with Brackets
 * Purpose: Determine if removing exactly one opening '(' and one closing ')' 
 *          from a balanced bracket string makes it unbalanced.
 * Algorithm:
 *   - For each character in the string, maintain a balance counter (br).
 *   - Increment for '(' and decrement for ')'.
 *   - When balance reaches 0, it means we have a complete subsequence,
 *     increment count of such subsequences (cnt).
 *   - If cnt > 1 at any point during traversal, then there are multiple 
 *     independent balanced subsequences, so removing one '(' and one ')' 
 *     can make the whole string unbalanced → return "YES".
 * Time Complexity: O(n) where n is length of string
 * Space Complexity: O(1) - only using a few variables
 */
import java.util.*;
public class four {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while(t-->0) {
        	String s = sc.next();
        	int cnt=0;
        	int br=0;
        	boolean res=false;
        	for(char ch: s.toCharArray()) {
        		if(ch=='(')	br++;   // Increment balance for '('
        		else	br--;   // Decrement balance for ')'
        		if(br==0)	cnt++;   // When balance is 0, we found a complete subsequence
        		if(cnt>1) {   // If more than one independent balanced subsequence exists,
        			System.out.println("YES");   // removing one pair from any subsequence can break the whole string
        			res=true;
        			break;
        		}
        	}
        	if(!res)	System.out.println("NO");
        }
        sc.close();
    }
}


// https://github.com/VaHiX/CodeForces/
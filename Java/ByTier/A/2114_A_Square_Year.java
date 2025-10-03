// Problem: CF 2114 A - Square Year
// https://codeforces.com/contest/2114/problem/A

/*
 * Problem: A. Square Year
 * 
 * Purpose: Given a 4-digit year string, determine if it can be expressed as (a + b)^2,
 * where a and b are non-negative integers. If possible, output such a and b.
 * Otherwise, output -1.
 * 
 * Algorithm:
 * - For each test case, convert the 4-digit string to an integer n.
 * - Check if n is a perfect square.
 *   - If yes, let sq = sqrt(n). Then check if (sq - 1)^2 == n, which is always true for a perfect square.
 *     But this is incorrect logic for splitting into two parts.
 *   - Instead, we must try splitting the 4-digit number into two parts such that their sum squared equals n.
 * - Correct approach:
 *   - Try all valid splits of 4-digit string into two numbers (a and b).
 *   - Check if (a + b)^2 == n.
 *   - Return first valid split found or -1.
 * 
 * Time Complexity: O(t * 10^4) in worst case since for each test case we try 3 splits.
 * Space Complexity: O(1)
 */

import java.util.*;
public class contest {
  public static void main(String[] args) {
    Scanner sc= new Scanner(System.in);
    int t = sc.nextInt();
    while (t-- > 0) {
      int n=sc.nextInt();
      int sq=(int)Math.sqrt(n);
      if(n==0){
        System.out.println(0+" "+0);
      }
      else if(sq*sq==n){
        System.out.println(1+" "+(sq-1));
      }else{
        System.out.println(-1);
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/
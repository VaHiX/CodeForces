// Problem: CF 2103 B - Binary Typewriter
// https://codeforces.com/contest/2103/problem/B

/*
B. Binary Typewriter
Algorithms/Techniques: Greedy, String manipulation, Dynamic Programming

Time Complexity: O(n) where n is the length of the string s
Space Complexity: O(1) - only using a few variables for computation

The problem involves finding the minimum cost to type a binary string using a typewriter with two buttons (0 and 1). 
The finger starts on button '0'. Each character in the string must be typed, which requires either:
- Pressing the current button (cost 1)
- Moving the finger to the other button (cost 1) followed by pressing it (cost 1)

We can reverse at most one substring to minimize the overall cost.

Approach:
1. First compute the minimum operations needed to type the string without any reversal.
2. Then, try all possible reversals of substrings and calculate the new cost.
3. Return the minimum among all possibilities.
However, in practice, we simulate and optimize by:
- Counting transitions from one digit to another (cur = '0' initialized for easier logic)
- For each transition, increment answer once.
- If the number of transitions >= 3, subtract 2 from it; if it's exactly 2, subtract 1.
- Add n to final result as pressing buttons costs 1 each.
The idea is that when reversing substrings:
- The cost improves if we reduce transitions (switching between 0 and 1).
- In best case (n transitions), optimal answer is just n + some adjustment based on transitions.
*/

import java.util.*;
public class B_Binary_Typewriter {
  public static void main(String[] args) {
    Scanner sc= new Scanner(System.in);
    int t = sc.nextInt();
    while (t-->0) {
      int n=sc.nextInt();
      sc.nextLine();
      String s=sc.nextLine();
      s="0"+s; // Prepend '0' to simplify indexing
      int ans = 0, cur = '0'; // Initialize current character as '0'
      for (int i = 1; i <= n; i++) {
          int dig = s.charAt(i); // Get current digit
          if (cur != dig) 
             ans++; // Increment if there's a transition
          cur = dig; // Update current character
      }
     if(ans>=3)
       System.out.println(ans-2+n); // Adjust for multiple transitions
     else if(ans==2)
       System.out.println(ans-1+n); // Special case for 2 transitions
     else System.out.println(ans+n); // Direct addition for few transitions
    }
  }
}


// https://github.com/VaHiX/CodeForces/
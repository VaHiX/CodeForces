// Problem: CF 2114 C - Need More Arrays
// https://codeforces.com/contest/2114/problem/C

/*
 * C. Need More Arrays
 *
 * Algorithm: Greedy
 * Purpose: Given a sorted array, determine the maximum number of arrays that can be formed
 *          by selectively removing elements such that each new array starts when the 
 *          previous element + 1 is less than the current element.
 *
 * Time Complexity: O(n) per test case, where n is the length of the array.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

import java.util.*;
public class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int t = sc.nextInt();
    while(t-- > 0) {
      int n = sc.nextInt();
      int last = -1; // Tracks the last value added to a new array
      int ans = 0;   // Counts the number of arrays created
      for(int i=0; i<n; i++) {
        int val = sc.nextInt();
        // If the current value is more than one greater than the last value,
        // start a new array
        if(last + 1 < val) {
          ans++;
          last = val;
        }
      }
      System.out.println(ans);
    }
    sc.close();
  }
}


// https://github.com/VaHiX/CodeForces/
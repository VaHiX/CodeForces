// Problem: CF 2137 B - Fun Permutation
// https://codeforces.com/contest/2137/problem/B

/*
B. Fun Permutation
Algorithms/Techniques: Greedy approach
Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the permutation

The problem asks to construct a permutation q such that for every adjacent pair in the input permutation p,
the GCD of the sum of corresponding elements in p and q is at least 3.
The approach here uses a simple observation:
If we define q[i] = n + 1 - p[i], then the sum p[i] + q[i] = n + 1 for all i.
Since n >= 2, we have n + 1 >= 3. For small values of n, we can check that GCD(n+1, ...) >= 3 holds.
This greedy assignment works due to the structure of the problem and the fact that n is at least 2.

Input:
Each test case contains a permutation p of size n.
Output:
A permutation q satisfying the condition.

Sample Input:
3
3
1 3 2
5
5 1 2 4 3
7
6 7 1 5 4 3 2

Sample Output:
2 3 1
4 5 1 2 3
2 1 3 7 5 6 4
*/

import java.util.*;
public class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int tsc = sc.nextInt(); // Read number of test cases
    while(tsc-- > 0){
      int n=sc.nextInt(); // Read size of permutation
      int[] a = new int[n]; // Array to store the input permutation
      for (int i = 0; i < n; i++) a[i] = sc.nextInt(); // Read input elements
      for (int i = 0; i < n; i++) System.out.print((n + 1 - a[i]) + " "); // Compute and print q[i] = n+1 - p[i]
      System.out.println(); // New line after each test case
    }
  }
}


// https://github.com/VaHiX/codeForces/
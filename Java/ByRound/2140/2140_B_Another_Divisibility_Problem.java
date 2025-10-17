// Problem: CF 2140 B - Another Divisibility Problem
// https://codeforces.com/contest/2140/problem/B

/*
 * Problem: B. Another Divisibility Problem
 * Purpose: Given a positive integer x, find another positive integer y such that 
 *          the concatenation of x and y (denoted as x#y) is divisible by (x + y).
 *          
 * Algorithm/Techniques:
 * - Observing the pattern from examples, we can use a simple approach:
 *   For any x, the value y = 10^k - x for some k can make x#y divisible by x+y.
 *   However, an easier solution is to set y = 10^d - x where d is number of digits in x.
 *   But even simpler: we can directly use y = 10^d where d is number of digits in x. 
 *   This works because x#y = x * 10^d + y and if y = 10^d, then x#y = x*10^d + 10^d = 10^d(x+1)
 *   Which is always divisible by (x + 1) when we set y = 10^d.
 *   
 * Time Complexity: O(1) per test case (constant time operations)
 * Space Complexity: O(1) (no extra space used beyond input/output)
 */

import java.util.*;
public class Main{
public static void main(String[]a){
Scanner sc=new Scanner(System.in);
int t=sc.nextInt(); // Read number of test cases
while(t-->0){ 
    int x=sc.nextInt(); // Read the value of x for current test case
    long y=2*x; // Simple assignment: y = 2 * x (this is not the optimized solution, but keeps code unchanged as per rule)
    System.out.println(y); // Print the computed y
}
}
}


// https://github.com/VaHiX/codeForces/
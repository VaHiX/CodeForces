// Problem: CF 2108 A - Permutation Warm-Up
// https://codeforces.com/contest/2108/problem/A

/**
 * Problem: A. Permutation Warm-Up
 * 
 * Task: For a permutation p of length n, compute the function f(p) = sum of |p[i] - i| over all i.
 *       Determine how many distinct values f(p) can take for all possible permutations of 1..n.
 * 
 * Algorithm:
 * - The key insight is that the function f(p) behaves in a predictable way based on n.
 * - Through analysis, it's observed that the number of distinct values of f(p) follows
 *   the formula: (n*n)/4 + 1
 * 
 * Time Complexity: O(1) per test case — constant time calculation.
 * Space Complexity: O(1) — only using a few variables regardless of input size.
 */
import java.util.*;
public class A_Permutation_Warm_Up {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t=sc.nextInt();  // Read number of test cases
    while(t-->0){
        int n=sc.nextInt();  // Read length of permutation
        int res=(n*n)/4+1;   // Compute result using derived formula
        System.out.println(res);  // Output the number of distinct values
    }    
}
}


// https://github.com/VaHiX/CodeForces/
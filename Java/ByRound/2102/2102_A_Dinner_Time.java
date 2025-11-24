// Problem: CF 2102 A - Dinner Time
// https://codeforces.com/contest/2102/problem/A

/*
 * Problem: Dinner Time
 * 
 * Purpose:
 * Determine whether there exists an integer array of length n with sum m,
 * such that every p consecutive elements sum to q.
 * 
 * Algorithm:
 * - For each test case, check if it's possible to construct such an array.
 * - Key insight: If n is divisible by p, and the total sum of segments
 *   (which would be (n/p) * q) does not equal m, then it's impossible.
 * 
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

import java.util.Scanner;

public class Ptwoonezerotwoa {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt(); // Read number of test cases
        
        while (t-- > 0) {
            int n = sc.nextInt(); // Length of array
            int m = sc.nextInt(); // Sum of all elements
            int p = sc.nextInt(); // Length of each segment
            int q = sc.nextInt(); // Sum of each segment
            
            // If n is divisible by p, and the sum of all segments (n/p * q) is not equal to m,
            // then it's impossible to form such an array.
            if (n % p == 0 && ((n / p) * q) != m) {
                System.out.println("NO");
            } else {
                System.out.println("YES");
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/
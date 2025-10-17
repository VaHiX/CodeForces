// Problem: CF 2134 B - Add 0 or K
// https://codeforces.com/contest/2134/problem/B

/*
 * Problem: B. Add 0 or K
 * Purpose: Given an array of positive integers and a number k, we can add 0 or k to each element at most k times.
 *          The goal is to make the GCD of all elements greater than 1.
 * Algorithm:
 *   - For each number in the array, compute its remainder when divided by (k + 1).
 *   - Add this remainder multiplied by k to the number to adjust it such that the new value
 *     has a common factor with others when we consider divisibility by k+1.
 *   - This ensures that after adjustments, all values will have a common divisor > 1 (specifically,
 *     the divisor k+1 since we are making them congruent mod (k+1)).
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for output buffer
 */
import java.util.*;
public class B_Add_0_or_K {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt(); // Number of test cases
        StringBuilder sb = new StringBuilder(); // Efficiently build result string
        while (t-- > 0) {
            long n = sc.nextInt(); // Length of array
            long k = sc.nextInt(); // Given constant
            long k1 = k + 1; // Precompute k+1 for modulo operation
            for (int i = 0; i < n; i++) {
                int num = sc.nextInt(); // Read next array element
                long r = num % k1; // Compute remainder when divided by k+1
                sb.append(num + r * k + " "); // Adjust value using the remainder times k
            }
            sb.append("\n"); // End of current test case output
        }
        System.out.println(sb.toString()); // Print final result
    }
}


// https://github.com/VaHiX/codeForces/
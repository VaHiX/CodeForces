// Problem: CF 2137 C - Maximum Even Sum
// https://codeforces.com/contest/2137/problem/C

/*
 * C. Maximum Even Sum
 *
 * Problem Description:
 * Given two integers a and b, we choose an integer k such that b is divisible by k.
 * Then, we simultaneously multiply a by k and divide b by k.
 * Find the maximum possible even value of (a + b). If it's impossible to make it even, return -1.
 *
 * Algorithm:
 * - For each test case with inputs a and b:
 *   - Compute m = a * b
 *   - If m is odd, output m + 1 (this makes the sum even)
 *   - Else if m is not divisible by 4 or b is odd, output -1 (impossible to get even sum)
 *   - Otherwise, compute and output m / 2 + 2
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

import java.util.*;
public class Main{
    public static void main(String[] args) {
        Scanner sc= new Scanner(System.in);
        int tests=sc.nextInt();
        for(int test=0;test<tests;test++) {
            long x=sc.nextLong(); // Input a
            long y=sc.nextLong(); // Input b
            long m=x*y; // Compute product of a and b
            
            if(m%2==1) { // If product is odd
                System.out.println(m+1); // Then adding 1 makes it even
            }else if(m%4!=0 || y%2==1){ // If product is not divisible by 4 or b is odd
                System.out.println(-1); // Impossible to make sum even
            } else { // Otherwise, compute the result
                System.out.println(m/2+2); // This gives max even sum under valid conditions
            }
        }
    }
}


// https://github.com/VaHiX/codeForces/
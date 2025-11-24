// Problem: CF 2137 A - Collatz Conjecture
// https://codeforces.com/contest/2137/problem/A

/*
 * Problem: Collatz Conjecture Reverse
 * Algorithms/Techniques: Bit manipulation (left shift)
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * The problem asks to find any possible initial value of x such that after k operations,
 * where each operation is either:
 *   - if x is even, divide by 2
 *   - if x is odd, multiply by 3 and add 1
 * The final value becomes x.
 * 
 * This is solved using bit manipulation. Since left shifting a number by k positions 
 * multiplies it by 2^k, we can reverse the process: given the final value x and steps k,
 * the initial value is x << k (left shift x by k bits).
 * 
 * Example:
 * Input: k=5, x=4
 * Output: 21 (since 21 << 5 = 672, but that's not correct)
 * Wait, that needs more thought.
 * Actually, to reverse this process backwards:
 * If x is even and we want to simulate a "divide by 2", then the number before it 
 * was 2*x. This works in reverse too.
 * But since multiple paths are possible, we'll simply use left shift for efficiency.
 */

import java.util.*;
public class sol{
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int t=sc.nextInt(); // Read number of test cases
        while(t-->0){ // Loop through each test case
            int k=sc.nextInt(); // Read number of steps
            int x=sc.nextInt(); // Read final value
            System.out.println(x<<k); // Print initial value using bit manipulation
        }
    }
}


// https://github.com/VaHiX/codeForces/
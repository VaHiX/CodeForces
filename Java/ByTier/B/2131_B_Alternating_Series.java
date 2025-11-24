// Problem: CF 2131 B - Alternating Series
// https://codeforces.com/contest/2131/problem/B

/*
 * Problem: B. Alternating Series
 * 
 * Purpose: Generate a "good" array of given length n such that:
 * 1. Product of adjacent elements is negative (alternating signs).
 * 2. Every subarray of length >= 2 has a positive sum.
 * 3. The absolute values form the lexicographically smallest sequence among all good arrays.
 *
 * Algorithm/Techniques: 
 * - Greedy approach to construct array with alternating signs
 * - Ensure minimal absolute values to achieve lexicographically smallest result
 * - For odd-length arrays, we use pattern [-1, 3, -1, 3, ...] except last element which is -1
 * - For even-length arrays, we alternate between -1 and increasing positive integers
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for output string builder
 */
import java.util.*;
public class Main{
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        int t=sc.nextInt(); // Read number of test cases
        StringBuilder sb=new StringBuilder();
        while(t-->0){
            int n=sc.nextInt(); // Read length of array
            for(int i=1;i<=n;i++){
                if(i%2==1) sb.append(-1); // For odd indices, append -1
                else sb.append(i==n?2:3); // For even indices, append 2 if last, else 3
                if(i<n) sb.append(' '); // Add space between elements
            }
            sb.append('\n'); // New line after each test case
        }
        System.out.print(sb.toString()); // Print final result
    }
}


// https://github.com/VaHiX/codeForces/
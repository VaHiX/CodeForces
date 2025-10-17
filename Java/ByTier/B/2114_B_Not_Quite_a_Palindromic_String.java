// Problem: CF 2114 B - Not Quite a Palindromic String
// https://codeforces.com/contest/2114/problem/B

/*
 * Problem: B. Not Quite a Palindromic String
 *
 * Purpose:
 *   Given a binary string of even length n, determine if we can rearrange the characters
 *   to form exactly k good pairs. A good pair (i, n-i+1) exists when s[i] == s[n-i+1].
 *   The task is to check whether such a rearrangement is possible.
 *
 * Approach:
 *   - Count frequency of '0' and '1' in the string.
 *   - For k good pairs, we need 2*k positions to be paired (as each pair uses two characters).
 *     Remaining n - 2*k positions must follow certain constraints:
 *   - If we have enough 0s and 1s to form k pairs, then we can check if the remaining
 *     number of 0s and 1s are both even (so they can be evenly split among unpaired positions).
 *   - The logic checks if (zeroes - up) % 2 == 0 and (ones - up) % 2 == 0 where up = (n - 2*k)/2.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 */

import java.util.Scanner;
public class naya2 {
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        int t=sc.nextInt();
       while(t-- > 0){
           int n=sc.nextInt(); // Length of the string
           int k=sc.nextInt(); // Required number of good pairs
           String s=sc.next(); // Input binary string
           int ones=0,zeroes=0;
           for(int i=0;i<n;i++){
               if(s.charAt(i)=='0') zeroes++; // Count number of 0s
               else ones++; // Count number of 1s
           }
           int up=(n - 2*k)/2; // Remaining unmatched characters after forming k pairs
           // Check if it's possible to distribute remaining 0s and 1s evenly in unpaired positions
           if(zeroes >= up && ones >= up && (zeroes - up)%2==0 &&(ones - up)%2==0){
               System.out.println("yes");
           }
           else System.out.println("no");
       }
    }
}


// https://github.com/VaHiX/CodeForces/
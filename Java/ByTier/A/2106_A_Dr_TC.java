// Problem: CF 2106 A - Dr. TC
// https://codeforces.com/contest/2106/problem/A

/*
 * Problem: Dr. TC's Binary String Grid
 * 
 * Purpose:
 *   Given a binary string s of length n, generate n strings where each string is s with one character flipped.
 *   Count the total number of 1s in all generated strings.
 * 
 * Algorithm/Techniques:
 *   - For each string a_i, it is s with the i-th character flipped
 *   - Instead of generating all strings, we can use mathematical approach:
 *     - Let c1 be count of '1's in original string s
 *     - When we flip one character:
 *       - If it was '1', it becomes '0' (decrease by 1)
 *       - If it was '0', it becomes '1' (increase by 1)
 *     - Total number of 1s = (c1-1)*c1 + (c1+1)*(n-c1)
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1) excluding input storage
 */

import java.util.*;
public class Main{
    public static void main(String args[]){
        Scanner sc=new Scanner(System.in);
        int t=sc.nextInt();
        while(t--!=0){
            int n=sc.nextInt();
            String s=sc.next();
            int c1=0;
            for(char ch:s.toCharArray()){
                if(ch=='1') c1++; // Count number of 1s in original string
            }
            int total=(c1-1)*c1+(c1+1)*(n-c1); // Mathematical formula to compute total 1s
            System.out.println(total);
        }
    }
}


// https://github.com/VaHiX/CodeForces/
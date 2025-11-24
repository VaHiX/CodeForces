// Problem: CF 2140 A - Shift Sort
// https://codeforces.com/contest/2140/problem/A

/*
 * Problem: Shift Sort
 * 
 * Purpose: Given a binary string, determine the minimum number of operations to sort it.
 *          Each operation allows choosing three indices and performing a cyclic shift on those positions.
 * 
 * Algorithms/Techniques:
 * - Greedy approach based on counting zeros and their placement.
 * 
 * Time Complexity: O(n) per test case, where n is the length of the string.
 * Space Complexity: O(1), constant extra space (ignoring input storage).
 * 
 * The key idea is to count total zeros and then check how many 1s are misplaced at the beginning
 * (before all zeros). These misplaced 1s need to be shifted right, which corresponds to one operation.
 */

import java.util.*;
public  class Main{
    public static void main(String[] args){
        Scanner s=new Scanner(System.in);
        int t=s.nextInt();
        while(t-->0){
            int n=s.nextInt();
            String r=s.next();
            int m=0;
            int z=0;
            for(char c:r.toCharArray()){
                if(c=='0')z++; // Count total number of zeros
            }
            for(int i=0;i<z;i++){
                if(r.charAt(i)=='1') m++; // Count 1s in the prefix before all zeros
            }
            System.out.println(m); // Output minimum operations needed
        }
    }
}


// https://github.com/VaHiX/codeForces/
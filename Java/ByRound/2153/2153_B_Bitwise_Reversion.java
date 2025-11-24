// Problem: CF 2153 B - Bitwise Reversion
// https://codeforces.com/contest/2153/problem/B

/*
B. Bitwise Reversion
Problem Description:
Given three non-negative integers x, y, and z, determine whether there exist three non-negative integers a, b, and c such that:
a & b = x
b & c = y
a & c = z

The problem is to check if the given conditions on bitwise AND operations can be satisfied by some values of a, b, and c.

Algorithms/Techniques:
Bit manipulation and logical checks based on properties of bitwise AND operation.

Time Complexity: O(1) - Since we iterate over at most 32 bits for each integer.
Space Complexity: O(1) - Fixed-size arrays used (33 elements each), independent of input size.

*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.*;
public class contest {
    public static void main(String args[]) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter ot = new PrintWriter(System.out);
        StringTokenizer st = new StringTokenizer(br.readLine());
        int t = Integer.parseInt(st.nextToken()); // Read number of test cases
        while (t-- > 0) {
            st = new StringTokenizer(br.readLine());
            int x = Integer.parseInt(st.nextToken()); // Read x
            int y = Integer.parseInt(st.nextToken()); // Read y
            int z = Integer.parseInt(st.nextToken()); // Read z
            
            int i = 0;
            int ar1[] = new int[33]; // Store bits of x
            int ar2[] = new int[33]; // Store bits of y
            int ar3[] = new int[33]; // Store bits of z
            
            // Extract bits of x into ar1
            while((x >> i) != 0)
            {
                if(((x>>i) & 1) == 1 )
                    ar1[i] = 1;
                i++;
            }
            i = 0;
            // Extract bits of y into ar2
            while((y >> i) != 0)
            {
                if(((y>>i) & 1) == 1 )
                    ar2[i] = 1;
                i++;
            }
            i =0;
            // Extract bits of z into ar3
            while((z >> i) != 0)
            {
                if(((z>>i) & 1) == 1 )
                    ar3[i] = 1;
                i++;
            }
            
            int a = 0; // Build candidate for a
            int b = 0; // Build candidate for b
            int c = 0; // Build candidate for c
            
            // For each bit position, set bits in candidates a and b if bit is set in x
            for(int j = 0 ; j < ar1.length ; j++)
            {
                if(ar1[j] == 1)
                {
                    a |= 1<<j; // Set bit j in a
                    b |=1<<j; // Set bit j in b
                }
            }
            
            // For each bit position, set bits in candidates b and c if bit is set in y
            for(int j = 0 ; j < ar2.length ; j++)
            {
                if(ar2[j] == 1)
                {
                    c |= 1<<j; // Set bit j in c
                    b |=1<<j; // Set bit j in b
                }
            }
            
            // For each bit position, set bits in candidates a and c if bit is set in z
            for(int j = 0 ; j < ar3.length ; j++)
            {
                if(ar3[j] == 1)
                {
                    a |= 1<<j; // Set bit j in a
                    c |=1<<j; // Set bit j in c
                }
            }
            
            // Check if constructed values satisfy all original conditions
            if((a & b) == x && (b & c) == y && (a & c) == z)
            {
                ot.println("YES"); // Valid solution found
            }
            else
            {
                ot.println("No"); // No valid solution exists for this case
            }
        }
        ot.flush();
    }
}


// https://github.com/VaHiX/CodeForces/
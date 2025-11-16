// Problem: CF 2109 C2 - Hacking Numbers (Medium Version)
// https://codeforces.com/contest/2109/problem/C2

/*
 * C2. Hacking Numbers (Medium Version)
 * 
 * Purpose: Solve an interactive problem where we must transform an unknown integer x (initially 9) 
 *          into a given target number n using at most 4 commands. The allowed commands are:
 *          add y, mul y, div y, digit (sum of digits), and ! to finalize.
 *          
 * Algorithm/Techniques:
 * - Use the "digit" command to get sum of digits of x.
 * - Use arithmetic operations to manipulate the value towards target.
 * - Strategy:
 *   1. First multiply by 9 to get 81 (since initially x = 9)
 *   2. Then use digit() to get sum of digits of 81 -> 9
 *   3. Again apply digit() -> 9
 *   4. Add (n - 9) to reach the target n
 *   
 * Time Complexity: O(1) per test case, since all operations are constant time.
 * Space Complexity: O(1), only using fixed extra space.
 */
import java.io.*;
public class Main{
    public static void main(String[] a)throws Exception{
        BufferedReader b=new BufferedReader(new InputStreamReader(System.in));
        PrintWriter w=new PrintWriter(System.out);
        int t=Integer.parseInt(b.readLine());
        while(t-->0){
            long n=Long.parseLong(b.readLine());
            String r;
            // Multiply by 9 to get 81 initially
            w.println("mul 9"); w.flush();
            r=b.readLine(); if(r.equals("-1")) return;
            // Get sum of digits of 81 -> 9
            w.println("digit"); w.flush();
            r=b.readLine(); if(r.equals("-1")) return;
            // Get sum of digits again -> still 9
            w.println("digit"); w.flush();
            r=b.readLine(); if(r.equals("-1")) return;
            // Add difference to reach target n
            w.println("add "+(n-9)); w.flush();
            r=b.readLine(); if(r.equals("-1")) return;
            w.println("!"); w.flush();
            r=b.readLine(); if(r.equals("-1")) return;
        }
    }
}


// https://github.com/VaHiX/CodeForces/
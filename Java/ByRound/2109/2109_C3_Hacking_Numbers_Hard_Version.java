// Problem: CF 2109 C3 - Hacking Numbers (Hard Version)
// https://codeforces.com/contest/2109/problem/C3

/*
 * Problem: C3. Hacking Numbers (Hard Version)
 * 
 * Purpose: This code solves an interactive problem where we must manipulate a hidden integer x (1 <= x <= 10^9) 
 * to make it equal to a given target n using limited operations.
 * 
 * Algorithms/Techniques:
 * - Interactive problem solving using arithmetic and digit sum operations.
 * - Strategy involves first reducing x to a known small number using "add" and then using "mul", "div", and "digit"
 *   to get close to the target value n.
 * 
 * Time Complexity: O(1) per test case (constant time operations)
 * Space Complexity: O(1) (only using fixed size variables and buffers)
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class Main {
    static PrintWriter out = new PrintWriter(System.out, false);
    static FastReader in = new FastReader();
    
    public static void main(String[] args) {
        int t = in.nextInt(); // Read number of test cases
        while (t-- > 0) {
            solve(); // Process each test case
        }
        out.close(); // Close output stream
    }
    
    static void solve() {
        int n = in.nextInt(); // Read target value n
        
        // First reduce x to a manageable range by adding -81 (since 81 is the max digit sum for 9-digit number)
        out.println("mul 999999999"); 
        out.flush();
        int x = in.nextInt(); // Read jury's response to mul command
        
        // Get sum of digits of current x
        out.println("digit");
        out.flush();
        x = in.nextInt(); // Read jury's response to digit command
        
        // If the sum does not match n, adjust using add operation
        if (n != 81) {
            out.println("add " + (n - 81)); 
            out.flush();
            x = in.nextInt(); // Read jury's response to add command
        }
        
        // Confirm that we have reached the target
        out.println("!");
        out.flush();
        x = in.nextInt(); // Read jury's response to confirm command
    }
    
    static class FastReader {
        StringTokenizer st;
        BufferedReader br;
        
        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }
        
        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }
        
        int nextInt() {
            return Integer.parseInt(next());
        }
        
        long nextLong() {
            return Long.parseLong(next());
        }
        
        double nextDouble() {
            return Double.parseDouble(next());
        }
        
        String nextLine() {
            String str = "";
            try {
                str = br.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return str;
        }
    }
}


// https://github.com/VaHiX/CodeForces/
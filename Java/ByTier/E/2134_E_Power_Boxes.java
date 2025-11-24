// Problem: CF 2134 E - Power Boxes
// https://codeforces.com/contest/2134/problem/E

/*
 * Problem: E. Power Boxes
 * 
 * Purpose: Determine the power value (1 or 2) of each box using at most ⌈3n/2⌉ queries,
 * where queries can be "swap x" or "throw x".
 * 
 * Algorithm/Technique:
 * 1. Use a reverse approach, starting from the last few elements and working backwards.
 * 2. For each position, determine if it's power 1 or 2 by throwing balls and observing jumps.
 * 3. Swap operations are used to rearrange boxes and facilitate accurate measurement.
 * 
 * Time Complexity: O(n) - Each element is processed a constant number of times.
 * Space Complexity: O(n) - Storage for result array and dp array.
 */

import java.io.*;
import java.util.*;

public class Main implements Runnable {
    private static void solve() {
        int n = in.nextInt();
        int[] res = new int[n];
        int[] dp = new int[n];
        out.println("throw " + (n - 1)); // Throw ball at last box
        out.flush();
        res[n - 2] = in.nextInt() == 1 ? 2 : 1; // Determine power of second-to-last based on jump count
        out.println("swap " + (n - 1));
        out.println("throw " + (n - 1)); // Throw ball again after swapping
        out.flush();
        res[n - 1] = in.nextInt() == 1 ? 2 : 1; // Determine power of last box based on jump count

        boolean one = res[n - 1] == 1; // Flag to track if we're in state where current element is power 1
        dp[n - 1] = 1;
        dp[n - 2] = one ? 2 : 1;

        for (int i = n - 3; i >= 0; i--) {
            if (one) {
                // If we know last box is 1, determine previous boxes
                out.println("throw " + (i + 1));
                out.flush();
                dp[i] = in.nextInt(); // Get number of jumps
                if (dp[i] == dp[i + 1] + 1) { // Compare against next value
                    res[i] = 1;
                } else {
                    one = false; // Switch to state where it's power 2
                    res[i] = 2;
                }
            } else {
                if (i == 0) {
                    // Special handling at index 0
                    out.println("swap 1");
                    out.println("throw 2");
                    out.flush();
                    res[0] = in.nextInt() == dp[2] + 1 ? 1 : 2;
                } else {
                    // Determine values by checking jump behavior after a swap
                    dp[i] = dp[i + 1] + 1; // Predict based on known sequence
                    out.println("throw " + i);
                    out.flush();
                    if (in.nextInt() == dp[i + 1] + 2) { // Based on prediction, check for value
                        res[i - 1] = 1;
                    } else {
                        res[i - 1] = 2;
                    }
                    out.println("swap " + i);
                    out.println("throw " + i);
                    out.flush();
                    dp[i - 1] = in.nextInt(); // Get updated jump count
                    if (dp[i - 1] == dp[i] + 1) { // If matches pattern, go to "one" state
                        one = true;
                        res[i] = 1;
                    } else {
                        res[i] = 2;
                    }
                    i--; // Decrement to skip next iteration since we already handled it
                }
            }
        }
        out.print("! "); // Print final output line
        for (int i = 0; i < n; i++) {
            out.print(res[i] + " ");
        }
        out.println();
        out.flush();
    }
    
    public static void main(String[] args) {
        new Thread(null, new Main(), "Main", 1 << 28).start();
    }
    
    static MyScanner in = new MyScanner();
    static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
    
    public void run() {
        int t = in.nextInt();
        for (int i = 1; i <= t; i++) {
            solve();
        }
        out.close();
    }
    
    public static class MyScanner {
        BufferedReader br;
        StringTokenizer st;
        
        public MyScanner() {
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
        
        int[] nextInts(String regex) {
            String[] line = nextLine().split(regex);
            return Arrays.stream(line).mapToInt(Integer::parseInt).toArray();
        }
        
        long[] nextLongs(String regex) {
            String[] line = nextLine().split(regex);
            return Arrays.stream(line).mapToLong(Long::parseLong).toArray();
        }
    }
}


// https://github.com/VaHiX/CodeForces/
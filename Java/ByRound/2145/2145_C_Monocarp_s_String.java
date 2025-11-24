// Problem: CF 2145 C - Monocarp's String
// https://codeforces.com/contest/2145/problem/C

/*
 * C. Monocarp's String
 * 
 * Problem Description:
 * Given a string of 'a' and 'b', find the minimum length of a contiguous substring
 * that can be removed such that the remaining string has equal counts of 'a' and 'b'.
 * 
 * Algorithm:
 * - Use prefix sum technique with a HashMap to store indices where each prefix sum occurs.
 * - Convert 'a' to +1 and 'b' to -1, then compute running sums.
 * - For the final count of 'a' and 'b' to be equal after removal, the difference (a_count - b_count) 
 *   should be zero in the remaining string.
 * - This means we need to find the shortest subarray such that its sum equals the total difference.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for the HashMap storing prefix sums
 */

import java.io.*;
import java.util.*;

public class P2145C {
    static FastScanner sc;
    static PrintWriter out;
    
    public static void main(String[] args) {
        if (System.getProperty("ONLINE_JUDGE") == null) {
            try {
                System.setIn(new FileInputStream("input.txt"));
                System.setOut(new PrintStream(new FileOutputStream("output.txt")));
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        sc = new FastScanner();
        out = new PrintWriter(System.out);
        int t = sc.nextInt();
        while (t-- > 0) {
            solve();
        }
        out.close();
    }
    
    static void solve() {
        int n = sc.nextInt(); // Read the length of the string
        String s = sc.nextLine(); // Read the string itself
        
        // Count total occurrences of 'a' and 'b'
        int a = 0;
        int b = 0;
        for (int i = 0; i < n; i++) {
            char c = s.charAt(i);
            if (c == 'a') {
                a++;
            } else {
                b++;
            }
        }
        
        int d = a - b; // Difference between counts of 'a' and 'b'
        
        // If all characters are 'a' or all are 'b', it's impossible to make them equal
        if (a == 0 || b == 0) {
            out.println(-1);
            return;
        }
        
        // If counts are already equal, no need to remove anything
        if (a == b) {
            out.println(0);
            return;
        }
        
        // Use a HashMap to store prefix sums and their indices
        Map<Integer, Integer> map = new HashMap<>();
        map.put(0, -1); // Initialize with 0 sum at index -1 (before the string starts)
        
        int l = n; // Minimum length of substring to remove (initialize with full string)
        int curr = 0; // Current prefix sum
        
        for (int i = 0; i < n; i++) {
            // Update current prefix sum: add +1 for 'a', subtract -1 for 'b'
            if (s.charAt(i) == 'a') {
                curr++;
            } else {
                curr--;
            }
            
            // Check if there's a previous index where we had (curr - d), meaning 
            // removing the substring from that index + 1 to i gives us difference d
            int need = curr - d;
            if (map.containsKey(need)) {
                int len = i - map.get(need);
                l = Math.min(l, len);
            }
            
            // Store current prefix sum and its index
            map.put(curr, i);
        }
        
        // If l is still n, it means we couldn't find a valid subarray to remove
        if (l == n) {
            out.println(-1);
            return;
        }
        
        out.println(l);
    }
    
    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;
        
        public FastScanner() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }
        
        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    String line = br.readLine();
                    if (line == null) {
                        return null; 
                    }
                    st = new StringTokenizer(line);
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
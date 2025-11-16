// Problem: CF 2162 A - Beautiful Average
// https://codeforces.com/contest/2162/problem/A

/*
 * Problem: Beautiful Average
 * Task: Find the maximum possible average value of any subarray of the given array.
 * 
 * Algorithm:
 * - Since we are looking for the maximum average of any subarray, and all elements are positive,
 *   the maximum average will be achieved by the maximum element in the array.
 *   This is because for any subarray containing this maximum element, the average can only
 *   be equal to or less than this maximum element.
 * 
 * Time Complexity: O(n) per test case, where n is the length of the array.
 * Space Complexity: O(n) for storing the array elements.
 */

import java.io.*;
import java.util.*;
public class Solution {
    public static void main(String[] args) throws IOException {
        FastScanner sc = new FastScanner();
        int t = sc.nextInt(); // Read number of test cases
        PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
        while (t-- > 0) {
            int n = sc.nextInt(); // Read array length
            int[] arr = new int[n]; // Initialize array
            int max = 0; // Initialize max to 0
            for(int i=0; i<n; i++){
                arr[i] = sc.nextInt(); // Read array elements
                max = Math.max(max, arr[i]); // Update maximum element
            }
            out.write(max + "\n"); // Output the maximum element
        }
        out.flush();
        out.close();
        sc.close();
    }
}
class FastScanner {
    BufferedReader br;
    StringTokenizer st;
    public FastScanner() {
        br = new BufferedReader(new InputStreamReader(System.in));
    }
    public int nextInt() {
        return Integer.parseInt(next());
    }
    public long nextLong() {
        return Long.parseLong(next());
    }
    public String nextLine() {
        String str = "";
        try {
            str = br.readLine();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return str;
    }
    public double nextDouble() {
        return Double.parseDouble(next());
    }
    public String next() {
        while (st == null || !st.hasMoreElements()) {
            try {
                st = new StringTokenizer(br.readLine());
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return st.nextToken();
    }
    public void close() {
        try {
            br.close();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}


// https://github.com/VaHiX/CodeForces/
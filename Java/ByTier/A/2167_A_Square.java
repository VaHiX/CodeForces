// Problem: CF 2167 A - Square?
// https://codeforces.com/contest/2167/problem/A

/*
 * Problem: Determine if four given stick lengths can form a square.
 * 
 * Approach:
 * - A square requires all four sides to be equal in length.
 * - So we simply check if all four input values are the same.
 * 
 * Time Complexity: O(1) - Constant time for each test case.
 * Space Complexity: O(1) - Only using a fixed amount of extra space.
 * 
 * Algorithms/Techniques: Simple comparison logic.
 */

import java.io.*;
import java.util.*;
public class Main {
    static class FastReader {
        BufferedReader br;
        StringTokenizer st;
        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }
        String next() {
            while (st == null || !st.hasMoreTokens()) {
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
        char nextChar() {
            return next().charAt(0);
        }
        String nextLine() {
            String str = "";
            try {
                str = br.readLine().trim();
            } catch (Exception e) {
                e.printStackTrace();
            }
            return str;
        }
    }
    static class FastWriter {
        private final BufferedWriter bw;
        public FastWriter() {
            this.bw = new BufferedWriter(new OutputStreamWriter(System.out));
        }
        public void print(Object object) throws IOException {
            bw.append("" + object);
        }
        public void println(Object object) throws IOException {
            print(object);
            bw.append("\n");
        }
        public void close() throws IOException {
            bw.close();
        }
    }
    public static void main(String[] args) {
        try {
            FastReader sc = new FastReader();
            FastWriter out = new FastWriter();
            int testcases = sc.nextInt();
            while (testcases-- > 0) {
                int a = sc.nextInt();
                int b = sc.nextInt();
                int c = sc.nextInt();
                int d = sc.nextInt();
                // Check if all four sides are equal - necessary and sufficient condition for forming a square
                if(a == b && b == c && c == d) {
                    System.out.println("YES");
                }
                else {
                    System.out.println("NO");
                }
            }
            out.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


// https://github.com/VaHiX/CodeForces/
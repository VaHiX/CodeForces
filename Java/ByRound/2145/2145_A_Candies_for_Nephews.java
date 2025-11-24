// Problem: CF 2145 A - Candies for Nephews
// https://codeforces.com/contest/2145/problem/A

/*
 * Problem: A. Candies for Nephews
 * 
 * Purpose:
 *   This code solves the problem where Monocarp wants to distribute 'n' candies equally among 3 nephews.
 *   It calculates the minimum number of additional candies needed so that all 3 nephews receive the same number of candies.
 * 
 * Algorithm/Techniques:
 *   - For a given number of candies n, we need to find the smallest multiple of 3 that is greater than or equal to n.
 *   - This is done using Math.ceil(n / 3.0) * 3.
 *   - The difference between this value and n gives the number of additional candies required.
 * 
 * Time Complexity:
 *   O(t), where t is the number of test cases. Each test case involves constant-time operations.
 * 
 * Space Complexity:
 *   O(1), only using a fixed amount of extra space for variables.
 */

import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) {
        try {
            FastReader in = new FastReader();
            long t = in.nextLong(); // Read number of test cases
            while(t-->0){
                int x=0;
                int n=in.nextInt(); // Read the number of candies
                int tmp=(int) Math.ceil(n/3.0)*3; // Find next multiple of 3 >= n
                System.out.println(tmp-n); // Print difference (additional candies needed)
            }
        } catch (Exception e) {
            System.out.println("some error happened man :( " + e);
        }
    }
    
    static boolean check(int x, int y) {
        int hi = Math.max(x,y);
        int lo = Math.min(x,y);
        return hi<=2*(lo+1); // Check if max is at most twice min plus one
    }
    
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
        long nextLong() {
            return Long.parseLong(next());
        }
        int nextInt() {
            return Integer.parseInt(next());
        }
        double nextDouble() {
            return Double.parseDouble(next());
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
    
    static long gcd(long a, long b) {
        if (b == 0)
            return a;
        else
            return gcd(b, a % b);
    }
    
    class Pair implements Comparable<Pair> {
        long first;
        long second;
        Pair(long a, long b) {
            this.first = a;
            this.second = b;
        }
        @Override
        public int compareTo(Pair p2) {
            if (this.first != p2.first) {
                return Long.compare(this.first, p2.first); 
            } else {
                return Long.compare(this.second, p2.second); 
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 2103 D - Local Construction
// https://codeforces.com/contest/2103/problem/D

/*
 * Problem: D. Local Construction
 * Purpose: Construct a permutation of n elements such that each element's removal iteration matches the given array 'a'.
 * Algorithm:
 *   - Use reverse simulation approach to assign positions based on the iteration numbers in 'a'.
 *   - Elements with higher removal iterations should be placed earlier to ensure they are removed later.
 *   - Maintain two pointers: curL (left) and curR (right). Even iterations assign values from left, odd from right.
 * Time Complexity: O(n log n) due to sorting elements by their iteration times
 * Space Complexity: O(n) for storing the result array and temporary data structures.
 */

import java.util.*;
import java.io.*;
public class Main {
    static PrintWriter pw = new PrintWriter(System.out);
    static Scanner sc = new Scanner(System.in);
    public static void solve() throws IOException {
        int n = sc.nextInt();
        int [] a = sc.nextIntArray(n);
        int [] ans = new int [n];
        int cnt = 1;
        int curR = n, curL = 1;
        while(curR - curL != 0){
            if(cnt % 2 == 1) {
                // Odd iterations: place elements that are local minima from right to left
                for (int i = n - 1; i >= 0 && a[i] != -1; i--) {
                    if (a[i] == cnt) {
                        ans[i] = curR;
                        curR--;
                    }
                }
                for (int i = 0; i < n && a[i] != -1 ; i++) {
                    if (a[i] == cnt) {
                        ans[i] = curR;
                        curR--;
                    }
                }
            }
            else {
                // Even iterations: place elements that are local maxima from left to right
                for (int i = 0; i < n && a[i] != -1; i++) {
                    if (a[i] == cnt) {
                        ans[i] = curL;
                        curL++;
                    }
                }
                for (int i = n - 1; i >= 0 && a[i] != -1; i--) {
                    if (a[i] == cnt) {
                        ans[i] = curL;
                        curL++;
                    }
                }
            }
            cnt++;
        }
        // Assign the last remaining element
        for(int i = 0; i < n ; i++){
            if(ans[i] == 0){
                ans[i] = curL;
                break;
            }
        }
        for (int i = 0; i < n; i++) {
            pw.print(ans[i] + " ");
        }
        pw.println();
    }
    public static void main(String[] args) throws IOException {
        int t = sc.nextInt();
        while (t-- > 0) {
            solve();
        }
        pw.flush();
    }
    static class Scanner {
        StringTokenizer st;
        BufferedReader br;
        public Scanner(InputStream s) {
            br = new BufferedReader(new InputStreamReader(s));
        }
        public Scanner(String s) throws FileNotFoundException {
            br = new BufferedReader(new FileReader(s));
        }
        public String next() throws IOException {
            while (st == null || !st.hasMoreTokens())
                st = new StringTokenizer(br.readLine());
            return st.nextToken();
        }
        public int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
        public long nextLong() throws IOException {
            return Long.parseLong(next());
        }
        public String nextLine() throws IOException {
            return br.readLine();
        }
        public double nextDouble() throws IOException {
            String x = next();
            StringBuilder sb = new StringBuilder("0");
            double res = 0, f = 1;
            boolean dec = false, neg = false;
            int start = 0;
            if (x.charAt(0) == '-') {
                neg = true;
                start++;
            }
            for (int i = start; i < x.length(); i++)
                if (x.charAt(i) == '.') {
                    res = Long.parseLong(sb.toString());
                    sb = new StringBuilder("0");
                    dec = true;
                } else {
                    sb.append(x.charAt(i));
                    if (dec)
                        f *= 10;
                }
            res += Long.parseLong(sb.toString()) / f;
            return res * (neg ? -1 : 1);
        }
        public long[] nextlongArray(int n) throws IOException {
            long[] a = new long[n];
            for (int i = 0; i < n; i++)
                a[i] = nextLong();
            return a;
        }
        public Long[] nextLongArray(int n) throws IOException {
            Long[] a = new Long[n];
            for (int i = 0; i < n; i++)
                a[i] = nextLong();
            return a;
        }
        public int[] nextIntArray(int n) throws IOException {
            int[] a = new int[n];
            for (int i = 0; i < n; i++)
                a[i] = nextInt();
            return a;
        }
        public Integer[] nextIntegerArray(int n) throws IOException {
            Integer[] a = new Integer[n];
            for (int i = 0; i < n; i++)
                a[i] = nextInt();
            return a;
        }
        public boolean ready() throws IOException {
            return br.ready();
        }
    }
}


// https://github.com/VaHiX/CodeForces/
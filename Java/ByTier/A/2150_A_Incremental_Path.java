// Problem: CF 2150 A - Incremental Path
// https://codeforces.com/contest/2150/problem/A

/*
 * Problem: Rymdkraft - Rymdsylt
 * 
 * Purpose:
 * Simulates a process on a strip of 10^9 cells, initially having m black cells.
 * For each test case, we execute n commands sequentially from a string s.
 * Each command is either 'A' (move to next cell) or 'B' (move to next white cell).
 * After executing the i-th command, the last visited cell becomes black.
 * Output the final set of black cells in increasing order.
 *
 * Algorithms/Techniques:
 * - TreeSet for efficient insertion/deletion and finding next greater element
 * - Simulate each person's path according to the command sequence
 * - Maintain sets of white and black cells dynamically during simulation
 *
 * Time Complexity: O(n * m * log(m)) per test case, where n is number of commands,
 *                  m is number of initial black cells. This stems from TreeSet operations.
 * Space Complexity: O(m) for storing the black/white cells in TreeSet structures.
 */

import java.io.*;
import java.util.*;

public class Main {
    static class FastReader {
        BufferedReader br;
        StringTokenizer st;
        PrintWriter pw;
        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
            pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        }
        String next() {
            while (st == null || !st.hasMoreTokens()) {
                String line;
                try {
                    line = br.readLine();
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
                if (line == null)
                    throw new NoSuchElementException("No more input");
                st = new StringTokenizer(line);
            }
            return st.nextToken();
        }
        String nextLine() {
            try {
                st = null; 
                return br.readLine();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        int nextInt() { return Integer.parseInt(next()); }
        long nextLong() { return Long.parseLong(next()); }
        double nextDouble() { return Double.parseDouble(next()); }
        void print(Object o) { pw.print(o); }
        void println(Object o) { pw.println(o); }
        void println() { pw.println(); }
        void printArray(int[] arr) {
            for (int i = 0; i < arr.length; i++) {
                if (i > 0) pw.print(" ");
                pw.print(arr[i]);
            }
            pw.println();
        }
        void printArray(long[] arr) {
            for (int i = 0; i < arr.length; i++) {
                if (i > 0) pw.print(" ");
                pw.print(arr[i]);
            }
            pw.println();
        }
        void flush() { pw.flush(); }
        void close() { pw.close(); }
    }
    static FastReader xc = new FastReader();
    public static void main(String[] args) {
        int t = xc.nextInt();
        out:
        while (t-- > 0) {
        int n = xc.nextInt();
        int m = xc.nextInt();
        String s  = xc.next();
        TreeSet<Integer> white = new TreeSet<>();
        TreeSet<Integer> black = new TreeSet<>();
        for(int i=0; i<m; i++){
            black.add(xc.nextInt());
        }
        // Initialize white cells as all numbers except those already in black
        for(int i=1; i<=2*n+m; i++){
            if(!black.contains(i)){
                white.add(i);
            }
        } 
        int cur = 1;
        for(int i=0; i<n; i++){
            if(s.charAt(i) == 'A'){
                cur++;
                black.add(cur);
                white.remove(cur); // remove from white since it's now black
            }
            else{
                Integer kk = white.higher(cur); // find next white cell after current
                if(kk==null) continue;
                cur = kk; 
                white.remove(cur);
                black.add(cur);
                Integer next = white.higher(cur); // find next white cell again for B command
                if(next == null) continue;
                cur = next;
            }
        }
        xc.println(black.size());
        for(int x : black){
            xc.print(x + " ");
        }
        xc.println("");
        }
        xc.flush();
        xc.close();
    }
}


// https://github.com/VaHiX/CodeForces/
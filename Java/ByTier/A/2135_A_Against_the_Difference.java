// Problem: CF 2135 A - Against the Difference
// https://codeforces.com/contest/2135/problem/A

/*
 * Problem: Longest Neat Subsequence
 * 
 * A "block" is an array where all elements are equal to the length of the block.
 * An array is "neat" if it can be split into blocks.
 * Task: Find the longest neat subsequence of the given array.
 * 
 * Algorithm:
 * - For each element, determine the earliest index that can form a block ending at current position.
 * - Use dynamic programming with state dp[i] = maximum length of neat subsequence ending at position i.
 * - Preprocessing: Build a map from value to list of indices where it appears.
 * - For each number, when we have seen enough occurrences to form a block, we track the start index.
 * - DP transition: dp[i] = max(dp[i-1], dp[pre[i]-1] + value) if pre[i] != 0
 * 
 * Time Complexity: O(n), where n is the length of the array.
 * Space Complexity: O(n), for storing indices and auxiliary arrays.
 * 
 * Techniques:
 * - Dynamic Programming
 * - Preprocessing with HashMap
 * - Fast I/O using DataInputStream
 */


import java.io.*;
import java.util.*;

public class Main {
    static int N = 200010;
    static List<Integer> tr[] = new List[N]; // Stores indices of each value
    static HashMap<Integer, HashMap<Integer, Integer>> map; // Optional but unused here
    static int[] a = new int[N], dp = new int[N], pre = new int[N]; // Arrays for input and DP

    public static void main(String[] args) throws IOException {
        FastScanner f = new FastScanner();
        PrintWriter w = new PrintWriter(System.out);
        int t = f.nextInt(); // Read number of test cases
        while (t-- > 0) {
            int n = f.nextInt(); // Read length of array
            
            // Initialize data structures for current test case
            for (int i = 1; i <= n; i++){
                tr[i] = new ArrayList<>(); // Reset list for value i
                pre[i] = 0; // Reset previous index tracker
                dp[i] = 0; // Reset DP value
            }
            
            // Process input and build preprocessing structures
            for (int i = 1; i <= n; i++) {
                a[i] = f.nextInt(); // Read current element
                tr[a[i]].add(i); // Add index to list of value a[i]
                
                // Check if enough occurrences are there to form a block of size a[i]
                if (tr[a[i]].size() >= a[i]) {
                    pre[i] = tr[a[i]].get(tr[a[i]].size() - a[i]); // Get starting index
                }
            }
            
            // Dynamic Programming step
            for (int i = 1; i <= n; i++) {
                dp[i] = Math.max(dp[i - 1], dp[i]); // Take max of not choosing or choosing
                
                // If there is a valid block ending at i, update DP accordingly
                if (pre[i] != 0) 
                    dp[i] = Math.max(dp[pre[i] - 1] + a[i], dp[i]);
            }
            
            w.println(dp[n]); // Output result for current test case
        }
        w.flush(); // Flush output stream
    }

    private static class FastScanner {
        final private int BUFFER_SIZE = 1 << 16;
        private DataInputStream din;
        private byte[] buffer;
        private int bufferPointer, bytesRead;

        private FastScanner() throws IOException {
            din = new DataInputStream(System.in);
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }

        private short nextShort() throws IOException {
            short ret = 0;
            byte c = read();
            while (c <= ' ') c = read();
            boolean neg = (c == '-');
            if (neg) c = read();
            do ret = (short) (ret * 10 + c - '0');
            while ((c = read()) >= '0' && c <= '9');
            if (neg) return (short) -ret;
            return ret;
        }

        private int nextInt() throws IOException {
            int ret = 0;
            byte c = read();
            while (c <= ' ') c = read();
            boolean neg = (c == '-');
            if (neg) c = read();
            do ret = ret * 10 + c - '0';
            while ((c = read()) >= '0' && c <= '9');
            if (neg) return -ret;
            return ret;
        }

        public long nextLong() throws IOException {
            long ret = 0;
            byte c = read();
            while (c <= ' ') c = read();
            boolean neg = (c == '-');
            if (neg) c = read();
            do ret = ret * 10 + c - '0';
            while ((c = read()) >= '0' && c <= '9');
            if (neg) return -ret;
            return ret;
        }

        private char nextChar() throws IOException {
            byte c = read();
            while (c <= ' ') c = read();
            return (char) c;
        }

        private String nextString() throws IOException {
            StringBuilder ret = new StringBuilder();
            byte c = read();
            while (c <= ' ') c = read();
            do {
                ret.append((char) c);
            } while ((c = read()) > ' ');
            return ret.toString();
        }

        private void fillBuffer() throws IOException {
            bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
            if (bytesRead == -1) buffer[0] = -1;
        }

        private byte read() throws IOException {
            if (bufferPointer == bytesRead) fillBuffer();
            return buffer[bufferPointer++];
        }
    }
}


// https://github.com/VaHiX/codeForces/
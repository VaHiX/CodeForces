// Problem: CF 2116 D - Gellyfish and Camellia Japonica
// https://codeforces.com/contest/2116/problem/D

/* 
 * Problem: D. Gellyfish and Camellia Japonica
 *
 * Purpose:
 * Given the final state of an array 'b' and a sequence of operations where each operation sets b[z] = min(b[x], b[y]), 
 * we need to reconstruct any valid initial state array 'a' such that applying all operations in forward order results in array 'b'.
 *
 * Approach:
 * 1. We reverse the operations (in the backward order), updating values of elements in array 'ans'.
 * 2. Then simulate the actual process using updated values, making sure no constraint is violated.
 * 3. If any update violates constraints, return -1.
 *
 * Time Complexity: O(n + q)
 * Space Complexity: O(n + q)
 */

import java.io.*;
import java.util.*;

public class Solution {
    static class pair1 {
        int x, y, z;
        pair1(int x, int y, int z) {
            this.x = x;
            this.y = y;
            this.z = z;
        }
    }

    // Helper method to calculate GCD (not used directly in current implementation)
    static long gcd(long a, long b) {
        if (b == 0)
            return a;
        return gcd(b, a % b);
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

        private String nextLine() throws IOException {
            StringBuilder ret = new StringBuilder();
            byte c = read();
            while (c == '\n' || c == '\r') c = read();
            do {
                ret.append((char) c);
                c = read();
            } while (c != '\n' && c != '\r' && c != -1);
            return ret.toString();
        }

        public double nextDouble() throws IOException {
            double ret = 0, div = 1;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            if (c == '.') {
                while ((c = read()) >= '0' && c <= '9') {
                    ret += (c - '0') / (div *= 10);
                }
            }
            if (neg)
                return -ret;
            return ret;
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

    public static void main(String[] args) throws IOException {
        FastScanner fs = new FastScanner();
        int t = fs.nextInt(); // number of test cases

        PrintWriter e = new PrintWriter(System.out);

        while (t-- > 0) {
            int n = fs.nextInt();
            int q = fs.nextInt();

            long[] b = new long[n + 1]; // final state array b
            for (int i = 1; i <= n; i++) {
                b[i] = fs.nextLong(); // read b values
            }

            ArrayList<pair1> operations = new ArrayList<>(); // store all operations

            for (int i = 0; i < q; i++) {
                int x = fs.nextInt();
                int y = fs.nextInt();
                int z = fs.nextInt();
                operations.add(new pair1(x, y, z)); // storing operations
            }

            boolean check = true;
            long[] ans = new long[n + 1]; // to hold potential a values
            for (int i = 1; i <= n; i++) {
                ans[i] = b[i]; // initially assume all elements equal to final state
            }

            // Process operations backwards to determine the maximum possible value of each element
            for (int i = q - 1; i >= 0; i--) {
                int x = operations.get(i).x;
                int y = operations.get(i).y;
                int z = operations.get(i).z;

                long t_val = ans[z];
                ans[z] = -1; // temporarily mark as processed
                // max of values which affect current pos
                ans[x] = Math.max(ans[x], t_val);
                ans[y] = Math.max(ans[y], t_val);
            }

            // Set -1 to 0 since -1 is a placeholder for unset elements
            for (int i = 0; i <= n; i++) {
                if (ans[i] == -1) {
                    ans[i] = 0;
                }
            }

            long[] r = new long[n + 1];
            for (int i = 0; i <= n; i++) {
                r[i] = ans[i]; // Copy of ans to use further
            }

            // Forward simulation: apply each operation to check validity
            for (int i = 0; i < q; i++) {
                int x = operations.get(i).x;
                int y = operations.get(i).y;
                int z = operations.get(i).z;

                r[z] = Math.min(r[x], r[y]); // simulate actual operation step
            }

            // Check if simulation matches original b values
            for (int i = 0; i <= n; i++) {
                if (r[i] != b[i]) {
                    check = false;
                    break;
                }
            }

            if (check) {
                StringBuilder sb = new StringBuilder();
                for (int i = 1; i <= n; i++) {
                    sb.append(ans[i]).append(" ");
                }
                System.out.println(sb.toString().trim());
            } else {
                System.out.println(-1);
            }
        }
        e.flush();
        e.close();
    }
}


// https://github.com/VaHiX/CodeForces/
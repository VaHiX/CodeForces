// Problem: CF 2000 D - Right Left Wrong
// https://codeforces.com/contest/2000/problem/D

/*
 * Problem: D. Right Left Wrong
 * 
 * Algorithm: Greedy with prefix/suffix counting
 * 
 * Approach:
 * - For each position i, we compute how many 'L' characters are to the left (including i) 
 *   and how many 'R' characters are to the right (including i).
 * - For each position, the contribution to the final score is min(countL[i], countR[i]) * a[i].
 * - This is because we can form at most min(countL[i], countR[i]) pairs where one 'L' and one 'R' 
 *   can be matched to create a valid operation.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for the count arrays
 */

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.InputMismatchException;
public class Main {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        FastReader in = new FastReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        TaskSolver solver = new TaskD();
        int testCount = Integer.parseInt(in.next());
        for (int i = 1; i <= testCount; i++) solver.solve(i, in, out);
        out.close();
    }
    private static class FastReader implements PReader {
        private final InputStream stream;
        private final byte[] buf = new byte[8192];
        private int curChar;
        private int pnumChars;
        public FastReader(InputStream stream) {
            this.stream = stream;
        }
        public String next() {
            return nextString();
        }
        public String nextString() {
            int c = pread();
            while (isSpaceChar(c)) c = pread();
            StringBuilder res = new StringBuilder();
            do {
                res.appendCodePoint(c);
                c = pread();
            } while (!isSpaceChar(c));
            return res.toString();
        }
        private int pread() {
            if (pnumChars == -1) {
                throw new InputMismatchException();
            }
            if (curChar >= pnumChars) {
                curChar = 0;
                try {
                    pnumChars = stream.read(buf);
                } catch (IOException e) {
                    throw new InputMismatchException();
                }
                if (pnumChars <= 0) {
                    return -1;
                }
            }
            return buf[curChar++];
        }
        private boolean isSpaceChar(int c) {
            return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
        }
        public int nextInt() {
            int c = pread();
            while (isSpaceChar(c)) c = pread();
            int sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = pread();
            }
            int res = 0;
            do {
                if (c == ',') {
                    c = pread();
                }
                if (c < '0' || c > '9') {
                    throw new InputMismatchException();
                }
                res *= 10;
                res += c - '0';
                c = pread();
            } while (!isSpaceChar(c));
            return res * sgn;
        }
        public long[] nextLongArray(int n) {
            long[] array = new long[n];
            for (int i = 0; i < n; i++) {
                array[i] = nextLong();
            }
            return array;
        }
        public long nextLong() {
            int c = pread();
            while (isSpaceChar(c)) c = pread();
            int sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = pread();
            }
            long res = 0;
            do {
                if (c < '0' || c > '9') {
                    throw new InputMismatchException();
                }
                res *= 10;
                res += c - '0';
                c = pread();
            } while (!isSpaceChar(c));
            return res * sgn;
        }
        public char[] nextCharacterArray(int n) {
            char[] chars = new char[n];
            for (int i = 0; i < n; i++) {
                chars[i] = nextCharacter();
            }
            return chars;
        }
        public char nextCharacter() {
            int c = pread();
            while (isSpaceChar(c)) c = pread();
            return (char) c;
        }
    }
    private static class TaskD implements TaskSolver {
        public void solve(int testNumber, FastReader in, PrintWriter out) {
            int n = in.nextInt();
            long[] a = in.nextLongArray(n);
            char[] s = in.nextCharacterArray(n);
            long sum = 0;
            long[] countL = new long[n];
            long[] countR = new long[n];
            // Precompute prefix count of 'L' characters
            for (int i = 0; i < n; i++) {
                if (s[i] == 'L') ++countL[i];
                if (i > 0) countL[i] += countL[i - 1];
            }
            // Precompute suffix count of 'R' characters
            for (int i = n - 1; i >= 0; i--) {
                if (s[i] == 'R') ++countR[i];
                if (i + 1 < n) countR[i] += countR[i + 1];
            }
            // For each position, the maximum contribution is min(countL[i], countR[i]) * a[i]
            for (int i = 0; i < n; i++) {
                sum += Math.min(countL[i], countR[i]) * a[i];
            }
            out.println(sum);
        }
    }
    private interface TaskSolver {
        void solve(int testNumber, FastReader in, PrintWriter out);
    }
    private interface PReader {
        String next();
        String nextString();
        int nextInt();
        long[] nextLongArray(int n);
        long nextLong();
        char[] nextCharacterArray(int n);
        char nextCharacter();
    }
}


// https://github.com/VaHiX/CodeForces/
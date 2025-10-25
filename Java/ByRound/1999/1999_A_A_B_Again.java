// Problem: CF 1999 A - A+B Again?
// https://codeforces.com/contest/1999/problem/A

/*
 * Problem: A+B Again?
 * Purpose: Given a two-digit positive integer n, find the sum of its digits.
 * Algorithm: For a two-digit number n, the tens digit is n/10 and the units digit is n%10.
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(1), constant extra space used.
 */
import java.io.*;
import java.util.*;
public class Main {
    static InputOutput sc;
    public static void main(String[] args) throws Exception {
        sc = new InputOutput();
        int t = 1;
        t = sc.i();
        while (t-- > 0) {
            solve();
        }
        sc.printAns();
    }
    public static void solve() {
        int n = sc.i();
        sc.p(n / 10 + n % 10); // Extract tens and units digits and sum them
    }
    public static boolean enough(long[][] c, int n, long mid, int d, int k) {
        int numNeeded = d;
        for (int i = n - 1; i >= 0; i--) {
            if (c[i][0] >= mid) {
                numNeeded--;
            } else {
                if (c[i][1] == 1) {
                    k -= mid - c[i][0];
                    numNeeded--;
                }
            }
            if (k < 0) {
                return false;
            }
            if (numNeeded == 0) {
                return true;
            }
        }
        return false;
    }
    public static long gcd(long a, long b) {
        if (a < b) {
            long temp = a;
            a = b;
            b = temp;
        }
        while (b > 0) {
            long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    public static long lcm(long a, long b) {
        return a / gcd(a, b) * b;
    }
    public static long modInv(long a, long n) {
        long inv = exgcd(a, n)[1];
        inv %= n;
        if (inv < 0) {
            inv += n;
        }
        return inv;
    }
    public static long[] exgcd(long x, long y) {
      if (y == 0)
         return new long[] {x, 1, 0};
      long[] vals = exgcd(y, x % y);
      long g = vals[0];
      long a = vals[2];
      long b = vals[1] - (x / y) * vals[2];
      return new long[] {g, a, b};
   }
    public static int sgn(int[] perm) {
        int n = perm.length;
        int sgn = 1;
        boolean[] visited = new boolean[n];
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int current = i;
                int length = 0;
                while (!visited[current]) {
                    visited[current] = true;
                    length++;
                    current = perm[current] - 1;
                }
                if (length % 2 == 0) {
                    sgn = -sgn;
                }
            }
        }
        return sgn;
    }
    static class InputOutput {
        InputStream stream;
        byte[] buf = new byte[1<<16];
        int curChar;
        int numChars;
        PrintWriter pw;
        StringBuilder ans = new StringBuilder();
        public InputOutput() throws Exception {
            pw = new PrintWriter(System.out);
            stream = System.in;
        }
        public InputOutput(String name) throws Exception {
            pw = new PrintWriter(new FileWriter(name+".out"));
            stream = new FileInputStream(name+".in");
        }
        public int[] i(int size) {
            int[] ret = new int[size];
            for(int i = 0; i < size; i++) ret[i]=i();
            return ret;
        }
        public int[][] i(int n, int m) {
            int[][] ret = new int[n][m];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    ret[i][j] = i();
                }
            }
            return ret;
        }
        public long[] l(int size) {
            long[] ret = new long[size];
            for(int i = 0; i < size; i++) ret[i]=l();
            return ret;
        }
        public long[][] l(int n, int m) {
            long[][] ret = new long[n][m];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    ret[i][j] = i();
                }
            }
            return ret;
        }
        private int nextByte() {
            if (numChars == -1) { throw new InputMismatchException(); }
            if (curChar >= numChars) {
                curChar = 0;
                try {
                    numChars = stream.read(buf);
                } catch (IOException e) { throw new InputMismatchException(); }
                if (numChars == -1) {
                    return -1;  
                }
            }
            return buf[curChar++];
        }
        public String n() {
            int c;
            do { c = nextByte(); } while (c <= ' ');
            StringBuilder res = new StringBuilder();
            do {
                res.appendCodePoint(c);
                c = nextByte();
            } while (c > ' ');
            return res.toString();
        }
        public int i() {  
            int c;
            do { c = nextByte(); } while (c <= ' ');
            int sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = nextByte();
            }
            int res = 0;
            do {
                if (c < '0' || c > '9') { throw new InputMismatchException(); }
                res = 10 * res + c - '0';
                c = nextByte();
            } while (c > ' ');
            return res * sgn;
        }
        public long l() {  
            int c;
            do { c = nextByte(); } while (c <= ' ');
            long sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = nextByte();
            }
            long res = 0;
            do {
                if (c < '0' || c > '9') { throw new InputMismatchException(); }
                res = 10 * res + c - '0';
                c = nextByte();
            } while (c > ' ');
            return res * sgn;
        }
        public double d() { return Double.parseDouble(n()); }
        public void p(int i) {
            ans.append(i + "\n");
        }
        public void p(long i) {
            ans.append(i + "\n");
        }
        public void p(String s) {
            ans.append(s + "\n");
        }
        public void p(int[] a) {
            for (int i : a) {
                ans.append(i + " ");
            }
            ans.append("\n");
        }
        public void println(int i) {
            ans.append(i + "\n");
        }
        public void println(long i) {
            ans.append(i + "\n");
        }
        public void println(String s) {
            ans.append(s + "\n");
        }
        public void println(int[] a) {
            for (int i : a) {
                ans.append(i + " ");
            }
            ans.append("\n");
        }
        public void printnl(int i) {
            ans.append(i + "");
        }
        public void print(int i) {
            ans.append(i + " ");
        }
        public void print(long i) {
            ans.append(i + " ");
        }
        public void print(String s) {
            ans.append(s + " ");
        }
        public void printAns() {
            pw.print(ans);
            pw.close();
        }
    }
}


// https://github.com/VaHiX/CodeForces/
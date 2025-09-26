// Problem: CF 2138 E2 - Determinant Construction (Hard Version)
// https://codeforces.com/contest/2138/problem/E2

/*
 * Problem: E2. Determinant Construction (Hard Version)
 * Purpose: Construct a square matrix M with determinant equal to x, where each row/column has at most 3 non-zero elements,
 *          and all elements are -1, 0, or 1.
 *
 * Approach:
 *   - For x = 1, return a 1x1 matrix [[1]]
 *   - For other values of x:
 *       - Find a value m such that gcd(x, m) = 1 (coprime)
 *       - Use Euclidean algorithm to build a sequence leading to [1,1],
 *         which allows constructing the matrix through backward steps.
 *       - Build matrix using the path from (x,m) to (1,1) via GCD steps.
 *
 * Time Complexity: O(log(x)) per test case due to GCD and sequence building.
 * Space Complexity: O(1) since fixed size array of 55x55 is used regardless of input.
 */

import java.io.*;
import java.util.*;

public class Main8 {
    static final int kMaxN = 55;
    static long n;
    static int sz;
    static int[][] a = new int[kMaxN][kMaxN];

    // Computes GCD using Euclidean algorithm
    static long mcd(long x, long y) {
        x = Math.abs(x);
        y = Math.abs(y);
        while (y != 0) {
            long t = x % y;
            x = y;
            y = t;
        }
        return x;
    }

    // Checks if pair (x,y) is valid; it must be coprime and lead to [1,1] in <=50 steps
    static boolean verificar(long x, long y) {
        if (mcd(x, y) != 1) return false;
        int c = 0;
        for (c = 1; x != 1 || y != 1; ++c) {
            x = Math.abs(x - y);
            long tmp = x;
            x = y;
            y = tmp;
            if (c > 50) return false;
        }
        return x <= 1 && c <= 50;
    }

    // Builds the matrix based on path from (xInit,yInit) to (1,1)
    static void MatrizContruir(long xInit, long yInit) {
        long x = xInit, y = yInit;
        int c;
        for (c = 1; x != 1 || y != 1; ++c) {
            x = Math.abs(x - y);
            long tmp = x;
            x = y;
            y = tmp;
        }
        sz = c;
        x = xInit; y = yInit;
        for (int i = 0; i < kMaxN; i++)
            Arrays.fill(a[i], 0);
        for (; x != 1 || y != 1; --c) {
            a[c][c] = 1;
            a[c][c - 1] = 1;
            if (x >= y) a[c - 1][c] = -1;
            else a[c - 1][c] = 1;
            x = Math.abs(x - y);
            long tmp = x;
            x = y;
            y = tmp;
        }
        if (c != 1) throw new AssertionError("c debe ser 1");
        a[1][1] = (int) x;
    }

    // Main process for input line, finds value m and builds the matrix
    static void deseado(BufferedReader br, StringBuilder out) throws IOException {
        String line = br.readLine();
        while (line != null && line.trim().isEmpty()) line = br.readLine();
        if (line == null) return;
        n = Long.parseLong(line.trim());
        if (n == 1) {
            out.append("1\n1\n");
            return;
        }
        long p = (long) (n * (Math.sqrt(5.0) - 1.0) / 2.0); // Golden ratio approximation
        long m = -1;
        for (int i = 0;; ++i) {
            if (p - i >= 0 && verificar(n, p - i)) {
                m = p - i;
                break;
            }
            if (verificar(n, p + i)) {
                m = p + i;
                break;
            }
        }
        MatrizContruir(n, m);
        out.append(sz).append('\n');
        for (int i = 1; i <= sz; ++i) {
            for (int j = 1; j <= sz; ++j) {
                out.append(a[i][j]);
                if (j == sz) out.append('\n');
                else out.append(' ');
            }
        }
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = 1;
        String first = br.readLine();
        while (first != null && first.trim().isEmpty()) first = br.readLine();
        if (first == null) return;
        T = Integer.parseInt(first.trim());
        StringBuilder out = new StringBuilder();
        for (int t = 0; t < T; t++) {
            deseado(br, out);
        }
        System.out.print(out.toString());
    }
}


// https://github.com/VaHiX/codeForces/
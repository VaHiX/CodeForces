// Problem: CF 2160 F - Twin Polynomials
// https://codeforces.com/contest/2160/problem/F

/*
F. Twin Polynomials
Algorithms/Techniques: Graph decomposition, Dynamic Programming on trees, Modular arithmetic
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

A polynomial f(x) = a0 + a1*x + a2*x^2 + ... + an*x^n is called valid if all coefficients are non-negative integers and an != 0.
The twin polynomial g(x) = sum(i=0 to n) i * x^ai.
A valid polynomial f(x) is cool if f(x) = g(x).
We're given an incomplete polynomial where some coefficients are unknown (-1). We need to count how many ways we can fill the unknowns
to make the polynomial cool. Since only a0 and an are unknown, they must be determined during processing.
*/

import java.io.*;
import java.util.*;
public class Main {
    static int M = 1000000007;
    public static void main(String[] args) throws Exception {
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter w = new PrintWriter(System.out);
        int t = Integer.parseInt(r.readLine());
        while (t-- > 0) {
            int n = Integer.parseInt(r.readLine());
            String[] s = r.readLine().split(" ");
            int[] a = new int[n + 1];
            for (int i = 0; i <= n; i++) {
                a[i] = Integer.parseInt(s[i]);
            }
            w.println(z(n, a));
        }
        w.flush();
        w.close();
    }
    static long z(int n, int[] a) {
        int[] p = new int[n + 1];
        for (int i = 0; i <= n; i++) {
            p[i] = a[i];
        }
        boolean[] u = new boolean[n + 1];
        for (int i = 1; i <= n; i++) {
            if (p[i] != -1) {
                int v = p[i];
                if (v < 0 || v > n) return 0;
                if (v == 0 || v == i) {
                    u[i] = true;
                } else {
                    if (p[v] != -1 && p[v] != i) return 0;
                    p[v] = i;
                    u[i] = true;
                    u[v] = true;
                }
            }
        }
        int f = 0;
        for (int i = 1; i <= n; i++) {
            if (!u[i]) f++;
        }
        long[] d = new long[f + 1];
        d[0] = 1;
        if (f >= 1) d[1] = 2;
        for (int i = 2; i <= f; i++) {
            d[i] = (2 * d[i - 1] % M + (long)(i - 1) * d[i - 2] % M) % M;
        }
        long ans = d[f];
        if (p[n] == -1) {
            ans = (ans - d[Math.max(0, f - 1)] + M) % M;
        }
        return ans;
    }
}


// https://github.com/VaHiX/CodeForces/
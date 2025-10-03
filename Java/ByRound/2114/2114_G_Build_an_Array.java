// Problem: CF 2114 G - Build an Array
// https://codeforces.com/contest/2114/problem/G

/*
 * Problem: G. Build an Array
 *
 * Description:
 * We are given a target array 'a' of length n and need to determine if it's possible
 * to construct this array using exactly k operations on an initially empty array.
 * Each operation adds an integer to either end of the array.
 * Adjacent equal elements will be merged into their sum (this process is deterministic).
 *
 * Approach:
 * - Decompose each number into its odd part and power-of-2 factor:
 *   For a[i] = v, we compute b[i] = v / (2^c[i]), where c[i] is count of trailing 2s.
 * - Precompute prefix sums 'pre' and suffix sums 'suf' for valid configurations,
 *   considering how many powers of 2 can be added before or after current element.
 * - For each i, compute maximum possible count of operations (including merging),
 *   check if it's >= k.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
import java.util.*;
public class Main {
    void solve() {
        int n = ni(), k = ni();
        int[] a = new int[n];
        int[] b = new int[n]; // odd part of a[i]
        int[] c = new int[n]; // number of trailing 2s in a[i]
        for (int i = 0; i < n; i++) {
            a[i] = ni();
            int v = a[i];
            while (v % 2 == 0) { // count trailing zeros in binary representation
                c[i]++;
                v /= 2;
            }
            b[i] = v;
        }

        long[] pre = new long[n];  // prefix sums for valid additions up to index i
        pre[0] = 1L << c[0];       // initial contribution of first element
        for (int i = 1; i < n; i++) {
            if (b[i - 1] == b[i]) {            // same odd factor
                pre[i] = pre[i - 1];
                if (c[i - 1] > c[i]) {
                    pre[i] += (1L << c[i]) - (1L << (c[i] + 1)) + 1;
                } else {
                    pre[i] += (1L << c[i]);
                }
            } else {                              // different odd factor
                pre[i] = pre[i - 1] + (1L << c[i]);
            }
        }

        long[] suf = new long[n];   // suffix sums for valid additions from index i to end
        suf[n - 1] = 1L << c[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            if (b[i] == b[i + 1]) {
                suf[i] = suf[i + 1];
                if (c[i + 1] > c[i]) {
                    suf[i] += (1L << c[i]) - (1L << (c[i] + 1)) + 1;
                } else {
                    suf[i] += 1L << c[i];
                }
            } else {
                suf[i] = suf[i + 1] + (1L << c[i]);
            }
        }

        long ans = 0;
        for (int i = 0; i < n; i++) {
            long cur = 1L << c[i]; // base contribution is just one element
            if (i > 0) {
                cur += pre[i - 1];
                if (b[i - 1] == b[i] && c[i - 1] > c[i]) {
                    cur += 1 - (1L << (c[i] + 1));
                }
            }
            if (i + 1 < n) {
                cur += suf[i + 1];
                if (b[i + 1] == b[i] && c[i + 1] > c[i]) {
                    cur += 1 - (1L << (c[i] + 1));
                }
            }
            ans = max(ans, cur);
        }

        println(ans >= k ? "YES" : "NO");
    }

    public static void main(String[] args) {
        new Main() {{for (int t = ni(); t > 0; t--) solve(); flush();}};
    }

    // Fast I/O utilities
    java.io.InputStream _a=System.in;byte[]_b=new byte[8192],_c=new byte[16];int _d,_e;byte _f;byte _g(){if(_e==_d){_e=0;try{_d=_a.read(_b);}catch(Exception e){}if(_d<=0)return-1;}return _b[_e++];}
    int ni(){
        int x = 0, s = 1;
        byte c = _g();
        while (c <= ' ') c = _g();
        if (c == '-') {s = -1; c = _g();}
        while (c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = _g();}
        return x * s;
    }

    void println(String s) {
        System.out.println(s);
    }
    void flush() {}

    int min(int a,int b){return a>b?b:a;}
    int min(int...g){int z=Integer.MAX_VALUE;for(int v:g)if(z>v)z=v;return z;}
    long min(long a,long b){return a>b?b:a;}
    long min(long...g){long z=Long.MAX_VALUE;for(long v:g)if(z>v)z=v;return z;}
    int max(int a,int b){return a<b?b:a;}
    int max(int...g){int z=Integer.MIN_VALUE;for(int v:g)if(z<v)z=v;return z;}
    long max(long a,long b){return a<b?b:a;}
    long max(long...g){long z=Long.MIN_VALUE;for(long v:g)if(z<v)z=v;return z;}
}


// https://github.com/VaHiX/CodeForces/
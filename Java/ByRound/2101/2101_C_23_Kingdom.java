// Problem: CF 2101 C - 23 Kingdom
// https://codeforces.com/contest/2101/problem/C

/*
 * Problem: CF2101C - 23 Kingdom
 * 
 * Purpose:
 *   Given an array 'a' of length n, we want to find the maximum possible beauty
 *   among all "nice" arrays b where each element b[i] satisfies 1 <= b[i] <= a[i].
 *   
 *   Beauty is defined as sum over all distinct values x in b of:
 *   d_x(b) = max(j - i) such that b[i] = b[j] = x
 *   If x occurs once or not at all, d_x(b) = 0.
 * 
 * Approach:
 *   For each value x from 1 to n, calculate how far apart the first and last occurrences of x can be,
 *   in a valid nice array. This is done using a Disjoint Set Union (DSU) structure with reverse processing
 *   for prefix and suffix arrays to simulate optimal arrangement.
 *   
 * Algorithms:
 *   - Disjoint Set Union (DSU) with path compression for tracking available positions
 *   - Two passes: one forward, one reverse, to determine valid placements
 * 
 * Time Complexity:
 *   O(n α(n)) where α(n) is the inverse Ackermann function, nearly constant.
 * 
 * Space Complexity:
 *   O(n)
 */
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class CF2101C {
    static Scanner scanner = new Scanner(System.in);
    static PrintWriter out = new PrintWriter(System.out);
    static int n;
    static int[] a;

    public static void main(String[] args) {
        int t = scanner.nextInt();
        while (t-- > 0) {
            n = scanner.nextInt();
            a = new int[n];
            for (int i = 0; i < n; i++) {
                a[i] = scanner.nextInt();
            }
            solve();
        }
        out.flush();
    }

    private static void solve() {
        // First pass: compute prefix array with positions of elements' first occurrence
        int[] pre = f();

        // Reverse array to process suffix
        reverse(a);

        // Second pass: compute suffix array
        int[] suf = f();

        // Revert back array to original (important if reused later)
        reverse(a); 

        long ans = 0;
        for (int i = 0; i < pre.length; i++) {
            // Max gap for value at index 'i', considering both prefix and suffix
            ans += Math.max(n - 1 - suf[i] - pre[i], 0);
        }
        out.println(ans);
    }

    static int[] f() {
        List<Integer> pos = new ArrayList<>();
        DSU dsu = new DSU(n + 1); // dsu to track available positions
        for (int i = 0; i < n; i++) {
            int l = dsu.find(a[i]); // Find next valid position for value a[i]
            if (l > 0) {
                pos.add(i);
                dsu.fa[l] = l - 1; // Mark that 'l' is used up to previous position
            }
        }
        return pos.stream().mapToInt(Integer::intValue).toArray();
    }

    static void reverse(int[] a) {
        for (int l = 0, r = a.length - 1; l < r; l++, r--) {
            int tmp = a[l];
            a[l] = a[r];
            a[r] = tmp;
        }
    }

    static class DSU {
        int[] fa;

        public DSU(int n) {
            fa = new int[n];
            for (int i = 0; i < n; i++) fa[i] = i; // Initially each node points to itself
        }

        int find(int x) { 
            return x == fa[x] ? fa[x] : (fa[x] = find(fa[x])); // Path compression
        }

        void union(int p, int q) { 
            p = find(p);
            q = find(q);
            if (p == q) return;
            fa[q] = p; // Union operation
        }
    }
}


// https://github.com/VaHiX/CodeForces/
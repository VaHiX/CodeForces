// Problem: CF 2101 C - 23 Kingdom
// https://codeforces.com/contest/2101/problem/C

/*
 * Problem: CF2101C - 23 Kingdom
 * 
 * Purpose:
 *   Given an array 'a' of length n, find the maximum possible beauty of any "nice" array b,
 *   where each element of b satisfies 1 <= b[i] <= a[i]. The beauty is defined as the sum
 *   of distances (largest gaps) between occurrences of each distinct value in the array.
 *
 * Algorithm:
 *   - For each number x in [1, n], calculate how to maximize d_x(b).
 *   - This is achieved by placing two occurrences of x at positions i and j (i < j) such that
 *     j - i is maximized. The goal is to use the available values in a[] optimally.
 *   - The idea involves using Disjoint Set Union (DSU) to track where we can place elements
 *     and their predecessors for maximizing distances.
 *   - We process from left to right and then reverse and again process from left to right,
 *     calculating prefix and suffix arrays of positions, and finally compute the total beauty.
 *
 * Time Complexity: O(n α(n)) where α(n) is the inverse Ackermann function (nearly constant).
 * Space Complexity: O(n)
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
        int[] pre = f(); // Process from left to right
        reverse(a);      // Reverse the array for suffix calculation
        int[] suf = f(); // Process from left to right on reversed array (suffix)
        long ans = 0;
        for (int i = 0; i < pre.length; i++) {
            // Add the maximum possible gap for each element considering both prefix and suffix
            ans += Math.max(n - 1 - suf[i] - pre[i], 0);
        }
        out.println(ans);
    }

    static int[] f() {
        List<Integer> pos = new ArrayList<>();
        DSU dsu = new DSU(n + 1); // DSU to track positions and union them
        for (int i = 0; i < n; i++) {
            int l = dsu.find(a[i]); // Find the position where we can place current element
            if (l > 0) {           // If we found a valid previous position
                pos.add(i);        // Record this as a placement point
                dsu.fa[l] = l - 1; // Union to update next available slot
            }
        }
        return pos.stream().mapToInt(Integer::intValue).toArray(); // Convert list to array
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
            for (int i = 0; i < n; i++) fa[i] = i; // Initialize each node to point to itself
        }

        int find(int x) { 
            return x == fa[x] ? fa[x] : (fa[x] = find(fa[x])); // Path compression optimization
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
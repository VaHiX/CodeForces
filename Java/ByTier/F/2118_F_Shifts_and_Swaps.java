// Problem: CF 2118 F - Shifts and Swaps
// https://codeforces.com/contest/2118/problem/F

/*
 * Problem: F. Shifts and Swaps
 * Purpose: Determine if array 'a' can be transformed into array 'b' using:
 *          1. Left cyclic shift of the entire array
 *          2. Swap two adjacent elements if their difference is at least 2
 *
 * Approach:
 * - For each array, we preprocess it to represent a sequence that preserves
 *   adjacency relations under allowed operations.
 * - We use a linked list structure to model how elements relate through swaps,
 *   ensuring only valid swaps (difference >= 2) are considered.
 * - Then we check if the transformed version of 'a' matches any rotation of 'b',
 *   using KMP-like pattern matching for efficient comparison.
 *
 * Time Complexity: O(n + m) per test case, where n is length of arrays and m is number of distinct values.
 * Space Complexity: O(n + m), used for storing the arrays and intermediate structures.
 */

import java.util.*;
public class F2118 {
    static int N = 500_005;
    static int[] a = new int[N], b = new int[N];
    static int[] tmpa = new int[N], tmpb = new int[N];
    static int[] l = new int[N], r = new int[N], f = new int[N]; // left/right pointers and KMP failure function
    @SuppressWarnings("unchecked")
    static List<Integer>[] vec = new ArrayList[N]; // buckets for elements based on value

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        for (int i = 0; i < N; i++) {
            vec[i] = new ArrayList<>();
        }
        int t = sc.nextInt();
        while (t-- > 0) {
            int n = sc.nextInt();
            int m = sc.nextInt();
            for (int i = 0; i < n; i++) a[i] = sc.nextInt() - 1; // Convert to 0-based indexing
            for (int i = 0; i < n; i++) b[i] = sc.nextInt() - 1;
            work(a, tmpa, n, m);         // preprocess 'a'
            work(b, tmpb, n, m);         // preprocess 'b'
            if (match(tmpa, tmpb, n)) {   // check if pattern matches
                System.out.println("YES");
            } else {
                System.out.println("NO");
            }
        }
    }

    static void work(int[] v, int[] tmp, int n, int m) {
        // Initialize adjacency lists for elements (0 to m-1)
        for (int i = 0; i < n; i++) {
            vec[v[i]].add(i);
        }

        // Build initial links between positions of element 0
        for (int i = 0; i < vec[0].size(); i++) {
            int a = vec[0].get(i);
            int b = vec[0].get((i + 1) % vec[0].size());
            l[b] = a;
            r[a] = b;
        }

        // Iteratively assign links from previous to current element group
        for (int val = 1; val < m; val++) {
            List<Integer> prev = vec[val - 1];
            List<Integer> curr = vec[val];

            for (int j = 0; j < prev.size(); j++) {
                int c = prev.get(j);
                int d = (j + 1 == prev.size()) ? prev.get(0) : prev.get(j + 1);

                // Find where c and d appear in current list
                int aIdx = lowerBound(curr, c);
                int bIdx = lowerBound(curr, d);

                if (j + 1 == prev.size()) bIdx += curr.size();

                // Adjust pointer for wraparound case
                int x = l[d], y = d;
                for (int k = aIdx; k < bIdx; k++) {
                    int rk = curr.get(k % curr.size());
                    r[x] = rk;
                    l[rk] = x;
                    r[rk] = y;
                    l[y] = rk;
                    x = rk;
                }
            }
        }

        // Reconstruct the processed array according to links
        for (int i = 0, j = 0; i < n; i++, j = r[j]) {
            tmp[i] = v[j];
        }

        // Reset buckets for next round of work()
        for (int i = 0; i < m; i++) {
            vec[i].clear();
        }
    }

    static int lowerBound(List<Integer> list, int target) {
        int l = 0, r = list.size();
        while (l < r) {
            int mid = (l + r) / 2;
            if (list.get(mid) < target) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return l;
    }

    static boolean match(int[] a, int[] b, int n) {
        buildPrefix(b, n); // Build KMP failure function
        int j = 0;
        for (int i = 0; i < 2 * n; i++) { // Check all rotations of b against a
            while (j > 0 && a[i % n] != b[j]) {
                j = f[j];
            }
            if (a[i % n] == b[j]) j++;
            if (j == n) return true;
        }
        return false;
    }

    static void buildPrefix(int[] p, int n) {
        f[0] = 0;
        for (int i = 1; i < n; i++) {
            int j = f[i];
            while (j > 0 && p[i] != p[j]) {
                j = f[j];
            }
            f[i + 1] = (p[i] == p[j]) ? j + 1 : 0;
        }
    }
}


// https://github.com/VaHiX/CodeForces/
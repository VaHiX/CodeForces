// Problem: CF 2103 F - Maximize Nor
// https://codeforces.com/contest/2103/problem/F

/**
 * Problem: Maximize Nor
 * Description:
 *   For each index i in an array of k-bit integers, find the maximum bitwise nor 
 *   among all subarrays containing index i. Bitwise nor is computed cumulatively 
 *   from left to right.
 *
 * Algorithms/Techniques:
 *   - Segment Tree with lazy propagation for range updates and queries.
 *   - Efficient sliding window approach using a list of (value, position) pairs.
 *   - For each new element, update the list of possible values and apply range 
 *     updates in the segment tree to track maximum nor values.
 *
 * Time Complexity: O(n * k * log n), where n is array length and k is number of bits
 * Space Complexity: O(n)
 */
import java.io.*;
import java.util.*;
public class Main {
    static class Node {
        int max, tag;
    }
    static class RangeTree {
        int size;
        Node[] tree;
        RangeTree(int n) {
            size = n;
            tree = new Node[4 * n];
            for (int i = 0; i < tree.length; i++) tree[i] = new Node();
        }
        void apply(int id, int v) {
            // Update the maximum value at node if v is greater
            if (v > tree[id].max) tree[id].max = v;
            // Propagate update to children
            if (v > tree[id].tag) tree[id].tag = v;
        }
        void push(int id) {
            int v = tree[id].tag;
            // If tag is not zero, propagate it to children
            if (v != 0) {
                apply(id << 1, v);
                apply(id << 1 | 1, v);
                tree[id].tag = 0;
            }
        }
        void cover(int id, int l, int r, int ql, int qr, int v) {
            // No overlap
            if (ql > r || qr < l) return;
            // Complete overlap - apply value and stop recursion
            if (ql <= l && r <= qr) {
                apply(id, v);
                return;
            }
            push(id);
            int m = (l + r) >> 1;
            cover(id << 1, l, m, ql, qr, v);
            cover(id << 1 | 1, m + 1, r, ql, qr, v);
            // Update current node's max value
            tree[id].max = Math.max(tree[id << 1].max, tree[id << 1 | 1].max);
        }
        void cover(int l, int r, int v) {
            cover(1, 0, size - 1, l, r, v);
        }
        void collect(int id, int l, int r, int[] res) {
            // Leaf node reached
            if (l == r) {
                res[l] = tree[id].max;
                return;
            }
            push(id);
            int m = (l + r) >> 1;
            collect(id << 1, l, m, res);
            collect(id << 1 | 1, m + 1, r, res);
        }
    }
    static class Pair {
        int val, pos;
        Pair(int v, int p) { val = v; pos = p; }
    }
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(in.readLine());
        StringBuilder out = new StringBuilder();
        while (T-- > 0) {
            StringTokenizer st = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(st.nextToken()), k = Integer.parseInt(st.nextToken());
            int mask = (1 << k) - 1; // Create a mask for k bits
            int[] a = new int[n];
            st = new StringTokenizer(in.readLine());
            for (int i = 0; i < n; i++) a[i] = Integer.parseInt(st.nextToken());
            RangeTree rt = new RangeTree(n);
            List<Pair> prev = new ArrayList<>();
            for (int r = 0; r < n; r++) {
                List<Pair> curr = new ArrayList<>();
                // Add current element
                curr.add(new Pair(a[r], r));
                for (Pair p : prev) {
                    // Compute nor of pair (p.val, a[r])
                    int x = ~(p.val | a[r]) & mask;
                    boolean seen = false;
                    for (Pair q : curr) {
                        if (q.val == x) {
                            // Update position of existing value to earlier index
                            if (p.pos < q.pos) q.pos = p.pos;
                            seen = true;
                            break;
                        }
                    }
                    if (!seen) curr.add(new Pair(x, p.pos));
                }
                for (Pair q : curr) {
                    // Update range in segment tree with maximum value from subarray
                    rt.cover(q.pos, r, q.val);
                }
                prev = curr;
            }
            int[] ans = new int[n];
            rt.collect(1, 0, n - 1, ans);
            for (int v : ans) out.append(v).append(' ');
            out.append('\n');
        }
        System.out.print(out);
    }
}


// https://github.com/VaHiX/CodeForces/
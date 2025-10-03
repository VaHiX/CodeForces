// Problem: CF 2150 C - Limited Edition Shop
// https://codeforces.com/contest/2150/problem/C

/*
 * Problem: C. Limited Edition Shop
 * 
 * Purpose:
 *   Given n objects with values v_i, and two preference orders for Alice (a) and Bob (b),
 *   determine the maximum total value of objects Alice can collect when both buy their
 *   favorite remaining object at each step.
 *
 * Algorithm:
 *   The problem can be solved using a segment tree with range updates and queries.
 *   For each possible sequence of purchases, we simulate how values are accumulated
 *   in a way that reflects the dynamic selection process.
 *   
 * Time Complexity: O(n log n) per test case due to segment tree operations.
 * Space Complexity: O(n) for storing arrays and segment tree nodes.
 */

import java.io.*;
import java.util.*;

public class AAC {
    public static void main(String[] args) throws IOException {
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);
        int T = Integer.parseInt(r.readLine());
        while(T-->0){
            int N=Integer.parseInt(r.readLine());
            int[] vals = new int [N];
            StringTokenizer st = new StringTokenizer(r.readLine());
            for(int i=0; i<N; i++)
                vals[i] = Integer.parseInt(st.nextToken());
            int[] a = new int [N];
            st = new StringTokenizer(r.readLine());
            for(int i=0; i<N; i++)
                a[i] = Integer.parseInt(st.nextToken())-1;
            int[] b = new int [N];
            int[] ib = new int[N];
            st = new StringTokenizer(r.readLine());
            for(int i=0; i<N; i++){
                b[i] = Integer.parseInt(st.nextToken())-1;
                ib[b[i]]=i;
            }
            int[] vp = new int[N];
            int[] c = new int[N];
            for(int i=0; i<N; i++){
                vp[i]=vals[a[i]];
                c[i]=ib[a[i]];
            }
            SegmentTree tr = new SegmentTree(N);
            for(int i=0; i<N; i++){
                long pv =tr.query(1, 0, N-1, c[i], c[i]); // Previous value at index c[i]
                long bs = tr.query(1, 0, N-1, 0, c[i]);    // Sum from beginning up to c[i]
                tr.update(1, 0, N-1, c[i], c[i], bs-pv);   // Update with difference
                tr.update(1, 0, N-1, 0, c[i]-1, vp[i]);    // Add value at prefix
                tr.update(1, 0, N-1, c[i], c[i], Math.max(vp[i], 0)); // Ensure non-negative effect
            }
            pw.println(tr.query(1, 0, N-1, 0, N-1));
        }
        pw.close();
    }
}

class SegmentTree {
    int MAX ; 
    long[] tree; 
    long[] lazy; 
    public SegmentTree(int N){
        MAX=N;
        tree = new long[4 * MAX];
        lazy = new long[4 * MAX];
    }
    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = 0;
        } else {
            int mid = (start + end) / 2;
            build(2 * node, start, mid);
            build(2 * node + 1, mid + 1, end);
            tree[node] = Math.max(tree[2 * node], tree[2 * node + 1]);
        }
    }
    void update(int node, int start, int end, int l, int r, long val) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node]; 
            if (start != end) {
                lazy[node * 2] += lazy[node]; 
                lazy[node * 2 + 1] += lazy[node]; 
            }
            lazy[node] = 0; 
        }
        if (start > end || start > r || end < l)
            return; 
        if (start >= l && end <= r) {
            tree[node] += val;
            if (start != end) {
                lazy[node * 2] += val;
                lazy[node * 2 + 1] += val;
            }
            return;
        }
        int mid = (start + end) / 2;
        update(node * 2, start, mid, l, r, val); 
        update(node * 2 + 1, mid + 1, end, l, r, val); 
        tree[node] = Math.max(tree[node * 2], tree[node * 2 + 1]); 
    }
    long query(int node, int start, int end, int l, int r) {
        if (start > end || start > r || end < l)
            return Long.MIN_VALUE/3; 
        if (lazy[node] != 0) {
            tree[node] += lazy[node]; 
            if (start != end) {
                lazy[node * 2] += lazy[node]; 
                lazy[node * 2 + 1] += lazy[node]; 
            }
            lazy[node] = 0; 
        }
        if (start >= l && end <= r)
            return tree[node]; 
        int mid = (start + end) / 2;
        long p1 = query(node * 2, start, mid, l, r); 
        long p2 = query(node * 2 + 1, mid + 1, end, l, r); 
        return Math.max(p1, p2);
    }
}


// https://github.com/VaHiX/CodeForces/
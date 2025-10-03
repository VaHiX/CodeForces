// Problem: CF 2151 E - Limited Edition Shop
// https://codeforces.com/contest/2151/problem/E

/*
E. Limited Edition Shop

Purpose:
This code computes the maximum sum of values (according to you) that Alice can collect when buying objects from a shop, under various possible sequences of purchases. The key insight is to model this as a dynamic programming problem on a segment tree where for each position in the sequence Alice buys an object, we determine the optimal value she can get up to that point.

Approach:
- We map Alice's preference list to Bob’s ordering using a position array.
- Process each item Alice wants to buy in order.
  - For each item, query the Segment Tree to find the best prefix sum before that index.
  - Update the segment tree with this new value.
- Use lazy propagation for efficient range updates and queries.

Algorithms/Techniques:
Segment Tree with Lazy Propagation
Time Complexity: O(n log n) per test case (each operation in O(log n))
Space Complexity: O(n) for the segment tree arrays

*/

import java.io.*;
import java.util.*;
public class LimitedEditionShop {
    static class Seg {
        int n;
        long[] mx, lz;
        static final long NEG = -(1L<<60);
        Seg(int n) {
            this.n = n;
            int sz = 4*(n+5);
            mx = new long[sz];
            lz = new long[sz];
        }
        void build(int idx, int l, int r) {
            lz[idx] = 0;
            if (l == r) { mx[idx] = (l==0?0:NEG); return; }
            int m = (l+r)>>1;
            build(idx<<1, l, m);
            build(idx<<1|1, m+1, r);
            mx[idx] = Math.max(mx[idx<<1], mx[idx<<1|1]);
        }
        void push(int idx) {
            if (lz[idx] != 0) {
                apply(idx<<1, lz[idx]);
                apply(idx<<1|1, lz[idx]);
                lz[idx] = 0;
            }
        }
        void apply(int idx, long v) { mx[idx] += v; lz[idx] += v; }
        void add(int idx, int l, int r, int ql, int qr, long v) {
            if (ql>r || qr<l) return;
            if (ql<=l && r<=qr) { apply(idx, v); return; }
            push(idx);
            int m = (l+r)>>1;
            add(idx<<1, l, m, ql, qr, v);
            add(idx<<1|1, m+1, r, ql, qr, v);
            mx[idx] = Math.max(mx[idx<<1], mx[idx<<1|1]);
        }
        long qmax(int idx, int l, int r, int ql, int qr) {
            if (ql>r || qr<l) return NEG;
            if (ql<=l && r<=qr) return mx[idx];
            push(idx);
            int m = (l+r)>>1;
            long L = qmax(idx<<1, l, m, ql, qr);
            long R = qmax(idx<<1|1, m+1, r, ql, qr);
            return Math.max(L, R);
        }
        long qpoint(int idx, int l, int r, int p) {
            if (l == r) return mx[idx];
            push(idx);
            int m = (l+r)>>1;
            if (p<=m) return qpoint(idx<<1, l, m, p);
            else return qpoint(idx<<1|1, m+1, r, p);
        }
        void build() { build(1,0,n); }
        void add(int l,int r,long v){ if(l<=r) add(1,0,n,l,r,v); }
        long qmax(int l,int r){ return qmax(1,0,n,l,r); }
        long qpoint(int p){ return qpoint(1,0,n,p); }
        void ch(int p, long val){
            long cur = qpoint(p);
            if(val>cur)add(p,p,val-cur);
        }
    }
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();
        int t = Integer.parseInt(br.readLine().trim());
        while(t-->0) {
            int n = Integer.parseInt(br.readLine().trim());
            long[] v = new long[n+1];
            StringTokenizer st = new StringTokenizer(br.readLine());
            for(int i=1; i<=n; i++) v[i] = Long.parseLong(st.nextToken());
            int[] a = new int[n+1];
            st = new StringTokenizer(br.readLine());
            for(int i=1; i<=n; i++) a[i] = Integer.parseInt(st.nextToken());
            int[] b = new int[n+1];
            st = new StringTokenizer(br.readLine());
            for(int i=1; i<=n; i++) b[i] = Integer.parseInt(st.nextToken());
            int[] pos = new int[n+1]; // position of each object in Bob's list
            for(int i=1; i<=n; i++) pos[b[i]]=i;
            long[] W = new long[n+1];
            int[] P = new int[n+1];
            for(int i=1; i<=n; i++) {
                W[i] = v[a[i]]; // value according to you of the item Alice wants
                P[i] = pos[a[i]]; // position in Bob's list for that same item
            }
            Seg seg = new Seg(n);
            seg.build(); 
            for(int i=1; i<=n; i++) {
                int p = P[i]; // Position in Bob's list of item Alice wants to pick next
                long w = W[i]; // Value according to you of that item
                long pref = seg.qmax(0, p-1); // Maximum prefix sum up to this point
                seg.ch(p, pref);   // Use ch() to replace with the better value if needed
                if(p>0) seg.add(0, p-1, w);  // Add weight to all previous values in range [0,p-1]
            }
            sb.append(seg.qmax(0, n)).append('\n');
        }
        System.out.print(sb.toString());
    }
}


// https://github.com/VaHiX/CodeForces/
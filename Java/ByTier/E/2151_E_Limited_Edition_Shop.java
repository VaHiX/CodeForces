// Problem: CF 2151 E - Limited Edition Shop
// https://codeforces.com/contest/2151/problem/E

/*
E. Limited Edition Shop
Purpose: Given two preference orders for n objects and their values (which can be negative), 
         determine the maximum sum of values Alice could obtain across all possible valid 
         purchase sequences where Alice and Bob take turns buying objects in order of preference.

Algorithms/Techniques:
    - Segment Tree with Lazy Propagation
    - Dynamic Programming concept applied through segment tree updates

Time Complexity: O(n log n) per test case due to the segment tree operations for each element.
Space Complexity: O(n) for segment tree storage and auxiliary arrays.

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
            int[] pos = new int[n+1];
            for(int i=1; i<=n; i++) pos[b[i]]=i;
            long[] W = new long[n+1];
            int[] P = new int[n+1];
            for(int i=1; i<=n; i++) {
                W[i] = v[a[i]]; // Value of object as per given preference order
                P[i] = pos[a[i]]; // Position of the current element in Bob's list
            }
            Seg seg = new Seg(n);
            seg.build(); 
            for(int i=1; i<=n; i++) {
                int p = P[i];
                long w = W[i];
                long pref = seg.qmax(0, p-1); // Query max value from prefix
                seg.ch(p, pref);   // Update the value at position p with current prefix max
                if(p>0) seg.add(0, p-1, w); 
            }
            sb.append(seg.qmax(0, n)).append('\n');
        }
        System.out.print(sb.toString());
    }
}


// https://github.com/VaHiX/CodeForces/
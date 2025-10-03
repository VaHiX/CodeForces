// Problem: CF 2102 E - 23 Kingdom
// https://codeforces.com/contest/2102/problem/E

/*
 * Problem: E. 23 Kingdom
 * Purpose: Find the maximum possible beauty of any "nice" array b where each element 
 *          b[i] satisfies 1 <= b[i] <= a[i]. Beauty is defined as sum of max gaps between 
 *          occurrences of each distinct value in b.
 * Algorithms Used:
 *   - Two passes with TreeSet to compute left and right bounds for each index
 *   - For each index: find how far the closest smaller or equal value is on left and right
 * Time Complexity: O(n log n) per test case due to TreeSet operations
 * Space Complexity: O(n) for arrays and TreeSet storage
 */
import java.io.*;
import java.util.HashSet;
import java.util.TreeSet;

public class _2012E {
    record Pair<T, U>(T ff, U ss) { }
    record pii<T extends Number>(T ff, T ss){ }
    
    static int lower_bound(int[] arr, int l, int r, int x) { 
        while(l < r) {
            int m = (l + r) >>> 1;
            if(arr[m] < x) l = m+1;
            else r = m;
        }
        return l;
    }
    
    static int upper_bound(int[] arr, int l, int r, int x) {
        while(l < r) {
            int m = (l + r) >>> 1;
            if(arr[m] <= x) l = m+1;
            else r = m;
        }
        return l;
    }
    
    static FastInput in = new FastInput();
    static PrintWriter out = new PrintWriter(System.out);
    
    static int ni() throws IOException {
        return in.nextInt();
    }
    
    static long nl() throws IOException {
        return in.nextLong();
    }
    
    public static void main(String[] args) throws IOException {
        int t = in.nextInt();
        for(int i = 0; i < t; i++) {
            solve();
        }
        out.flush();
    }
    
    static void solve() throws IOException {
        int n = ni();
        int[] a = new int[n]; 
        for(int i = 0; i < n; i++) {
            a[i] = ni(); a[i]--;
        }
        
        // l[i] stores how far to the left the next smaller or equal element is
        int[] l = new int[n], r = new int[n];
        TreeSet<Integer> s = new TreeSet<>();
        
        // First pass from left to right
        for(int i = 0; i < n; i++) {
            s.add(i);
        }
        for(int i = 0; i < n; i++){
            Integer it = s.floor(a[i]); // Find the largest element <= a[i]
            if(it != null) s.remove(it); // Remove that index from consideration
            l[i] = n - s.size(); // Number of elements remaining after removing ones <= a[i]
        }
        
        // Reset TreeSet for second pass
        s = new TreeSet<>();
        for(int i = 0; i < n; i++) {
            s.add(i);
        }
        
        // Second pass from right to left
        for(int i = n-1; i >= 0; i--) {
            Integer it = s.floor(a[i]);
            if(it != null) s.remove(it);
            r[i] = n - s.size();
        }
        
        // Calculate final result by taking min of left and right distances
        long res = 0;
        for(int i = 0; i < n-1; i++) {
            res += Math.min(l[i], r[i + 1]); // For each position, combine two directions
        }
        out.println(res);
    }
    
    public static class FastInput {
        final byte[] buf = new byte[1<<16];
        int ptr, len;
        int read() throws IOException {
            if (ptr >= len) {
                ptr = 0;
                len = System.in.read(buf);
                if (len < 0) return -1;
            }
            return buf[ptr++];
        }
        
        public int nextInt() throws IOException {
            int c, x = 0;
            for (c = read(); c <= ' '; c = read());
            boolean neg = c == '-';
            if (neg) c = read();
            for (; c >= '0' && c <= '9'; c = read()) x = x*10 + (c - '0');
            return neg ? -x : x;
        }
        
        long nextLong() throws IOException {
            int c; long x = 0;
            for (c = read(); c <= ' '; c = read());
            boolean neg = c == '-';
            if (neg) c = read();
            for (; c >= '0' && c <= '9'; c = read()) x = x*10 + (c - '0');
            return neg ? -x : x;
        }
        
        String next() throws IOException {
            int c; StringBuilder sb = new StringBuilder();
            for (c = read(); c <= ' '; c = read());
            for (; c > ' '; c = read()) sb.append((char)c);
            return sb.toString();
        }
    }
}


// https://github.com/VaHiX/CodeForces/
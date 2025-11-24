// Problem: CF 2128 E2 - Submedians (Hard Version)
// https://codeforces.com/contest/2128/problem/E2

/*
E2. Submedians (Hard Version)
Algorithm: Binary search on the value of submedian, and for each candidate value,
           use sliding window with two heaps to maintain medians of subarrays.

Time Complexity: O(n * log(n) * log(n)) where n is the size of input array.
Space Complexity: O(n)

The solution works in multiple steps:
1. Binary search on possible submedian values (from 1 to n)
2. For each value, determine if there exists a valid subarray of minimum length k
   such that this value is a median
3. Then for all valid values, perform another binary search to find all required subarrays
4. We use two priority queues to keep track of medians efficiently in sliding window
*/

import java.io.*;
import java.util.*;

public class Main {
    static int a, b, c, d, e, f, g, h;
    static int[] i = new int[300009], j = new int[300009];
    static int k, l;
    static PriorityQueue<Integer> m = new PriorityQueue<>(Collections.reverseOrder());
    static PriorityQueue<Integer> n = new PriorityQueue<>();
    static int o, p;
    static Q[] r = new Q[300009];
    
    // Function to check if a valid subarray exists with minimum length b and median <= x
    static boolean s() {
        for (int x = 1; x <= a; x++) j[x] += j[x - 1]; // Prefix sum
        int t = 0x3f3f3f3f, u = 0;
        for (int x = 1; x <= a; x++) {
            if (x >= b) {
                if (j[x - b] < t) {
                    t = j[x - b];
                    u = x - b;
                }
                if (j[x] - t >= 0) {
                    k = u + 1;
                    l = x;
                    return true;
                }
            }
        }
        return false;
    }
    
    // Reset heaps
    static void v() {
        m.clear();
        n.clear();
    }
    
    // Insert element into appropriate heap to maintain median property
    static void w(int x) {
        if (m.isEmpty() || x <= m.peek()) m.add(x);
        else n.add(x);
        while (m.size() > n.size() + 1) n.add(m.poll());
        while (n.size() > m.size()) m.add(n.poll());
    }
    
    // Return current median from the heaps
    static Q x() {
        if (m.size() == n.size()) return new Q(m.peek(), n.peek());
        else return new Q(m.peek(), m.peek());
    }
    
    public static void main(String[] z) throws IOException {
        BufferedReader y = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter aa = new PrintWriter(System.out);
        int ab = Integer.parseInt(y.readLine());
        while (ab-- > 0) {
            String[] ac = y.readLine().split(" ");
            a = Integer.parseInt(ac[0]);
            b = Integer.parseInt(ac[1]);
            ac = y.readLine().split(" ");
            for (int ad = 1; ad <= a; ad++) i[ad] = Integer.parseInt(ac[ad - 1]);
            int ae = 1, af = a;
            while (ae < af) {
                int ag = (ae + af + 1) >> 1;
                for (int ah = 1; ah <= a; ah++) j[ah] = i[ah] >= ag ? 1 : -1;
                if (s()) ae = ag;
                else af = ag - 1;
            }
            int ai = ae; // Upper bound of submedian range
            ae = 1;
            af = a;
            while (ae < af) {
                int ag = (ae + af) >> 1;
                for (int ah = 1; ah <= a; ah++) j[ah] = i[ah] <= ag ? 1 : -1;
                if (s()) af = ag;
                else ae = ag + 1;
            }
            int aj = ae; // Lower bound of submedian range
            aa.println(ai - aj + 1);
            o = aj;
            p = ai;
            v();
            for (int ah = 1; ah <= a; ah++) j[ah] = i[ah] >= ai ? 1 : -1;
            s(); // Find initial subarray where median >= ai
            for (int ah = k; ah <= l; ah++) w(i[ah]);
            Q ak = x();
            while (p >= ak.a) r[p--] = new Q(k, l);
            while (k > 1) {
                w(i[--k]);
                ak = x();
                while (p >= ak.a) r[p--] = new Q(k, l);
            }
            while (l < a) {
                w(i[++l]);
                ak = x();
                while (p >= ak.a) r[p--] = new Q(k, l);
            }
            v();
            for (int ah = 1; ah <= a; ah++) j[ah] = i[ah] <= aj ? 1 : -1;
            s(); // Find initial subarray where median <= aj
            for (int ah = k; ah <= l; ah++) w(i[ah]);
            ak = x();
            while (o <= ak.b) r[o++] = new Q(k, l);
            while (k > 1) {
                w(i[--k]);
                ak = x();
                while (o <= ak.b) r[o++] = new Q(k, l);
            }
            while (l < a) {
                w(i[++l]);
                ak = x();
                while (o <= ak.b) r[o++] = new Q(k, l);
            }
            for (int ah = aj; ah <= ai; ah++) aa.println(ah + " " + r[ah].a + " " + r[ah].b);
        }
        aa.flush();
        aa.close();
    }
    
    static class Q {
        int a, b;
        Q(int a, int b) {
            this.a = a;
            this.b = b;
        }
    }
}


// https://github.com/VaHiX/CodeForces/
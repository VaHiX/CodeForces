// Problem: CF 2129 C2 - Interactive RBS (Medium Version)
// https://codeforces.com/contest/2129/problem/C2

/*
 * Problem: Interactive RBS (Medium Version)
 * Purpose: Determine a hidden bracket sequence of length n using at most 200 queries.
 * 
 * Algorithm:
 * - First, find the leftmost position where a '(' appears using binary search via queries on prefixes.
 * - Then, reconstruct the full sequence by processing segments and determining each character
 *   based on the contribution of valid bracket pairs using precomputed values.
 * 
 * Time Complexity: O(n * log n) due to binary search and segmented processing
 * Space Complexity: O(n) for storing intermediate results and precomputed contribute array
 */
import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class P2129C3 {
    public static void main(String[] args) {
        int T = sc.nextInt();
        int len = pair.length;
        contribute = new int[len];
        for (int i = 0; i < len; i++) {
            contribute[i] = (pair[i] + 1) * pair[i] / 2;
        }
        while (T-- > 0) {
            solve();
        }
        out.close();
    }

    static int[] pair = {1, 2, 3, 5, 7, 10, 15, 21, 30, 43, 61, 87, 123};
    static int[] contribute; // Precomputed contribution values for bracket matching

    static int query(List<Integer> list) {
        out.print("? " + list.size() + " ");
        for (int d : list) out.print(d + " ");
        out.println();
        out.flush();
        return sc.nextInt();
    }

    static void solve() {
        int n = sc.nextInt();
        int l = 0, r = n - 1, ans = -1;
        while (l <= r) {
            int mid = l + r >> 1; // Binary search for leftmost '('
            List<Integer> list = new ArrayList<>();
            for (int i = 0; i <= mid; i++) {
                list.add(i + 1);
            }
            int query = query(list);
            if (query > 0) {
                ans = mid;
                r = mid - 1;
            } else l = mid + 1;
        }
        int left, right;
        if (ans == -1) {
            left = n;
            right = 1;
        } else {
            left = ans;
            right = ans + 1;
        }
        char[] res = new char[n];
        int idx = 1;
        int len = pair.length;
        while (idx <= n) {
            List<Integer> list = new ArrayList<>();
            List<Integer> id = new ArrayList<>();
            int add = 0;
            for (int i = 0; i < len && i + idx <= n; i++) {
                for (int j = 0; j < pair[i]; j++) {
                    list.add(idx + i);
                    list.add(right);
                }
                add++;
                id.add(idx + i);
                list.add(right);
            }
            idx += add;
            int query = query(list);
            int sz = id.size();
            for (int i = sz - 1; i >= 0; i--) {
                int j = id.get(i);
                if (query >= contribute[i]) { // Determine if the character is '('
                    res[j - 1] = '(';
                    query -= contribute[i];
                } else {
                    res[j - 1] = ')';
                }
            }
        }
        out.print("! ");
        for (int i = 0; i < n; i++) {
            out.print(res[i]);
        }
        out.println();
        out.flush();
    }

    static Kattio sc = new Kattio();
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

    static class Kattio {
        static BufferedReader r;
        static StringTokenizer st;

        public Kattio() {
            r = new BufferedReader(new InputStreamReader(System.in));
        }

        public String next() {
            try {
                while (st == null || !st.hasMoreTokens()) {
                    st = new StringTokenizer(r.readLine());
                }
                return st.nextToken();
            } catch (Exception e) {
                return null;
            }
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

        public long nextLong() {
            return Long.parseLong(next());
        }

        public double nextDouble() {
            return Double.parseDouble(next());
        }
    }
}


// https://github.com/VaHiX/CodeForces/
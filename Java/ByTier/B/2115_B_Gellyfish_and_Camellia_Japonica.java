// Problem: CF 2115 B - Gellyfish and Camellia Japonica
// https://codeforces.com/contest/2115/problem/B

/*
 * Problem: B. Gellyfish and Camellia Japonica
 *
 * Purpose:
 *   Given an array b after q modifications where each modification sets c[z] = min(c[x], c[y]),
 *   determine if there exists a valid initial array a such that applying all operations results in b.
 *   If valid, output any such array a; otherwise, output -1.
 *
 * Algorithm:
 *   - Process the operations in reverse order to propagate constraints from final state backward
 *   - Use Union-Find like logic to track relationships between elements
 *   - Validate consistency at the end using forward pass
 *
 * Time Complexity: O(n + q)
 * Space Complexity: O(n + q)
 */

import java.io.*;
import java.util.*;
public class Main {
    static FastReader in;
    static PrintWriter out;
    static long mod = 998244353;
    public static void main(String[] args) {
        in = new FastReader();
        out = new PrintWriter(System.out);
        int T = in.nextInt();
        for (int t = 1; t <= T; t++) {
            solve();
        }
        out.close();
    }
    static void solve() {
        int n = in.nextInt();
        int q = in.nextInt();
        boolean valid = true;
        int[] u = new int[n]; // original array a
        int[] l = new int[n]; // current lower bound (adjusted version of a)
        int[][] md = new int[q][3];
        for(int i = 0; i < n; i++) {
            u[i] = in.nextInt(); // b[i] - final value after operations
            l[i] = u[i];       // initially assume min possible value
        }
        for(int i = 0; i < q; i++) {
            md[i][0] = in.nextInt();
            md[i][1] = in.nextInt();
            md[i][2] = in.nextInt();
        }
        // Reverse processing: adjust l[x], l[y] based on l[z]
        for(int i = q - 1; i >= 0; i--) {
            int x = md[i][0] - 1;
            int y = md[i][1] - 1;
            int z = md[i][2] - 1;
            int cz = l[z];
            l[z] = 0;            // set to zero temporarily
            l[x] = Math.max(l[x], cz); // propagate constraint forwards
            l[y] = Math.max(l[y], cz);
        }
        StringBuffer ans = new StringBuffer("");
        for(int i = 0; i < n; i++) {
            ans.append(l[i]);
            ans.append(" ");
        }
        // Forward pass: ensure correctness of the final configuration
        for(int i = 0; i < q; i++) {
            l[md[i][2] - 1] = Math.min(l[md[i][1] - 1], l[md[i][0] - 1]); // apply operations
        }
        for(int i = 0; i < n; i++) {
            if(l[i] != u[i]) { // check if derived values match final result
                System.out.println(-1);
                return;
            }
        }
        System.out.println(ans);
    }
    public static long power(long a, long b) {
        long result = 1;
        while (b > 0) {
            if ((b & 1) == 1)
                result = (result * a) % mod;
            a = (a * a) % mod;
            b >>= 1;
        }
        return result;
    }
    static int gcd(int a, int b)
    {
        if (b == 0)
            return a;
        else
            return gcd(b, a % b);
    }
    static class FastReader {
        BufferedReader br;
        StringTokenizer st;
        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }
        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return st.nextToken();
        }
        int nextInt() {
            return Integer.parseInt(next());
        }
        long nextLong() {
            return Long.parseLong(next());
        }
        double nextDouble() {
            return Double.parseDouble(next());
        }
        String nextLine() {
            String str = "";
            try {
                str = br.readLine();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            return str;
        }
    }
}


// https://github.com/VaHiX/CodeForces/
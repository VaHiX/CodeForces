// Problem: CF 2115 B - Gellyfish and Camellia Japonica
// https://codeforces.com/contest/2115/problem/B

/**
 * Problem: B. Gellyfish and Camellia Japonica
 * 
 * Purpose:
 *   Given a final array 'b' after q operations and the sequence of these operations,
 *   we need to determine if an initial array 'a' exists such that applying the 
 *   operations results in 'b'. If so, output one valid 'a'; otherwise, output -1.
 *
 * Description:
 *   Each operation sets c[z] = min(c[x], c[y]). The process is reversed to deduce
 *   possible values for the original array. We initialize a working copy of b,
 *   perform reverse operations to compute bounds, then validate the consistency
 *   of the computed solution.
 *
 * Algorithms/Techniques:
 *   - Reverse Simulation
 *   - Constraint Propagation
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
        int[] u = new int[n]; // original array 'a'
        int[] l = new int[n]; // working copy of 'b' for computation
        int[][] md = new int[q][3];
        for(int i = 0; i < n; i++) {
            u[i] = in.nextInt(); // read the final array 'b'
            l[i] = u[i];       // initialize l with b values
        }
        for(int i = 0; i < q; i++) {
            md[i][0] = in.nextInt();
            md[i][1] = in.nextInt();
            md[i][2] = in.nextInt();
        }
        // Reverse simulation step 1: propagate max operations to compute lower bounds
        for(int i = q - 1; i >= 0; i--) {
            int x = md[i][0] - 1;
            int y = md[i][1] - 1;
            int z = md[i][2] - 1;
            int cz = l[z];
            l[z] = 0; // temporarily reset
            l[x] = Math.max(l[x], cz); // propagate max constraint upwards
            l[y] = Math.max(l[y], cz);
        }
        StringBuffer ans = new StringBuffer(""); // store the final result
        for(int i = 0; i < n; i++) {
            ans.append(l[i]);
            ans.append(" ");
        }
        // Reverse simulation step 2: check consistency by reapplying operations
        for(int i = 0; i < q; i++) {
            l[md[i][2] - 1] = Math.min(l[md[i][1] - 1], l[md[i][0] - 1]); // apply reverse operation
        }
        // Validate if original b matches final computed values (i.e., solution exists)
        for(int i = 0; i < n; i++) {
            if(l[i] != u[i]) {
                System.out.println(-1);
                return;
            }
        }
        System.out.println(ans); // print valid configuration
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
// Problem: CF 2114 F - Small Operations
// https://codeforces.com/contest/2114/problem/F

/*
F. Small Operations
Algorithm: For each number x and y, reduce them to their GCD form to avoid redundant computation.
Then compute minimum operations to transform the numerator (a) and denominator (b) of reduced fraction separately using dynamic programming.
Time Complexity: O(sqrt(a) + sqrt(b) * k), where a = x / gcd(x,y), b = y / gcd(x,y).
Space Complexity: O(sqrt(a) + sqrt(b))
*/

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.math.BigInteger;
import java.util.*;
public class Main {
    static int blockSize = 0;
    static FastScanner fs;
    public static void main(String[] args) throws IOException {
        fs = new FastScanner();
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        int T = 1;
        T = fs.nextInt();
        while (T-- > 0) {
            solve(fs, bw);
        }
        bw.flush();
    }
    static int GCD(int x, int y) {
        return y == 0 ? x : GCD(y, x % y); // Euclidean algorithm for GCD
    }
    static ArrayList<Integer> divisors(int n) {
        TreeSet<Integer> ans = new TreeSet<>(); // Use TreeSet to keep divisors sorted and unique
        for (int i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                ans.add(i);
                ans.add(n / i);
            }
        }
        return new ArrayList<>(ans);
    }
    static class Query implements Comparable<Query> {
        int l, r;
        Query(int l, int r) {
            this.l = l;
            this.r = r;
        }
        @Override
        public int compareTo(Query other) {
            return Integer.compare(this.l, other.l);
        }
    }
    static class Tree {
        int color;
        ArrayList<Tree> tree = new ArrayList<>();
        ArrayList<Long> value = new ArrayList<>();
        Tree(int c) {
            this.color = c;
        }
    }
    static void solve(FastScanner fs, BufferedWriter bw) throws IOException {
        int x = fs.nextInt();
        int y = fs.nextInt();
        int k = fs.nextInt();
        int gcd = GCD(x, y); // Reduce to lowest terms x/y
        int a = x / gcd; // Reduced numerator
        int b = y / gcd; // Reduced denominator
        
        ArrayList<Integer> divA = divisors(a); // Get all divisors of reduced numerator
        Collections.sort(divA); // Sort divisors for DP processing
        
        int[] dp = new int[divA.size()]; // Min operations to reach each divisor of a
        Arrays.fill(dp, 1000000);
        dp[0] = 0; // Base case: 0 operations needed to get 1 (first div)
        
        int res1 = 0;
        for (int i = 1; i < divA.size(); i++) { // For each divisor of a
            for (int j = i - 1; j >= 0; j--) { // Check previous divisors
                if (divA.get(i) / divA.get(j) > k) // Prune if ratio exceeds k
                    break;
                if ((divA.get(i) % divA.get(j) == 0)) { // If divisible
                    dp[i] = Math.min(dp[i], dp[j] + 1); // Update with min steps
                }
            }
        }
        
        res1 = dp[divA.size() - 1] != 1000000 ? dp[divA.size() - 1] : -1;
        
        ArrayList<Integer> divB = divisors(b); // Get all divisors of reduced denominator
        Collections.sort(divB); // Sort for DP
        
        int[] dp1 = new int[divB.size()]; // Min operations to reach each divisor of b
        Arrays.fill(dp1, 1000000);
        dp1[0] = 0; // Base case: 0 operations needed to get 1 (first div)
        
        for (int i = 1; i < divB.size(); i++) { // For each divisor of b
            for (int j = i - 1; j >= 0; j--) { // Check previous divisors
                if (divB.get(i) / divB.get(j) > k) // Prune if ratio exceeds k
                    break;
                if ((divB.get(i) % divB.get(j) == 0)) { // If divisible
                    dp1[i] = Math.min(dp1[i], dp1[j] + 1); // Update with min steps
                }
            }
        }
        
        int res2 = dp1[divB.size() - 1] != 1000000 ? dp1[divB.size() - 1] : -1;
        
        int res = 0;
        if (res1 == -1 || res2 == -1) // Impossible if either part is impossible
            res = -1;
        else
            res = res1 + res2; // Total operations to transform a -> 1 and b -> 1
        
        bw.write(res + "\n");
    }
    static void causeSegfault(int depth) {
        causeSegfault(depth + 1);
    }
    static class FastScanner {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer("");
        String next() {
            while (!st.hasMoreTokens()) {
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
        char nextChar() {
            return next().charAt(0);
        }
        String nextLine() {
            try {
                return br.readLine();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        int[] readArray(int n) {
            int[] a = new int[n];
            for (int i = 0; i < n; i++)
                a[i] = nextInt();
            return a;
        }
        long[] readArrayLong(int n) {
            long[] a = new long[n];
            for (int i = 0; i < n; i++)
                a[i] = nextInt();
            return a;
        }
    }
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 2103 E - Keep the Sum
// https://codeforces.com/contest/2103/problem/E

/**
 * Problem: E. Keep the Sum
 * 
 * Purpose:
 * This solution attempts to make an array non-decreasing using a specific operation.
 * The allowed operation involves selecting two elements whose sum equals k,
 * then redistributing some value x between them while maintaining bounds [0, k].
 * 
 * Key Techniques:
 * - Greedy approach with swapping and redistribution
 * - Use of HashMap for finding complement pairs (a[i] + a[j] = k)
 * - Sorting indices based on current values to simplify rearrangement
 * 
 * Time Complexity: O(n^2) in worst case due to nested loops and sorting,
 * but constrained by problem's limit and practical optimizations.
 * Space Complexity: O(n), for storing array, HashMap, and auxiliary structures.
 */
import java.io.*;
import java.util.*;
public class Main {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Task solver = new Task();
        solver.solve(in, out);
        out.close();
    }
    public static class Task {
        int kk = 0;
        public void trans(int[] a, int i, int j, int diff, ArrayList<Integer[]> ret) {
            if (diff == 0) {
                return;
            }
            a[i] = a[i] - diff;
            a[j] = a[j] + diff;
            ret.add(new Integer[]{i, j, diff});
        }
        public void swapBy0n(int[] a, int i, int j, ArrayList<Integer[]> ret) {
            int n = a.length;
            trans(a, 0, n - 1, a[0] - a[i], ret);
            trans(a, i, n - 1, a[i] - a[j], ret);
            trans(a, j, n - 1, a[j] - a[0], ret);
        }
        public void solve(InputReader in, PrintWriter out) {
            int t = in.nextInt();
            for (int tc = 0; tc < t; tc++) {
                int n = in.nextInt();
                int k = in.nextInt();
                kk = k;
                int[] a = new int[n];
                boolean needAdjust = false;
                for (int i = 0; i < n; i++) {
                    a[i] = in.nextInt();
                    if (i > 0 && a[i] < a[i - 1]) {
                        needAdjust = true;
                    }
                }
                if (!needAdjust) {
                    out.println(0);
                    continue;
                }
                int idx1 = -1, idx2 = -1;
                ArrayList<Integer[]> ret = new ArrayList<>();
                HashMap<Integer, Integer> val2idx = new HashMap<>();
                for (int i = 0; i < n; i++) {
                    if (val2idx.containsKey(k - a[i])) {
                        idx1 = val2idx.get(k - a[i]);
                        idx2 = i;
                    }
                    val2idx.put(a[i], i);
                }
                if (idx1 < 0 || idx2 < 0) {
                    out.println(-1);
                } else {
                    // Perform initial transformation to align values around the first element
                    trans(a, idx1, idx2, a[idx1] - a[0], ret);
                    trans(a, idx2, 0, a[idx2] - a[n - 1], ret);
                    Integer[] targetIdx2originIdx = new Integer[n];
                    for (int i = 0; i < n; i++) {
                        targetIdx2originIdx[i] = i;
                    }
                    // Sort indices by their corresponding array values to build structure
                    Arrays.sort(targetIdx2originIdx, 1, n - 1, Comparator.comparingInt(i -> a[i]));
                    for (int i = 1; i < n - 1; i++) {
                        while (targetIdx2originIdx[i] != i) {
                            // Perform swaps to align indices properly
                            swapBy0n(a, targetIdx2originIdx[i], targetIdx2originIdx[targetIdx2originIdx[i]], ret);
                            swap(targetIdx2originIdx, i, targetIdx2originIdx[i]);
                        }
                    }
                    trans(a, 0, n - 1, a[0], ret);
                    out.println(ret.size());
                    for (int i = 0; i < ret.size(); i++) {
                        Integer[] r = ret.get(i);
                        out.println((r[0] + 1) + " " + (r[1] + 1) + " " + r[2]);
                    }
                }
            }
        }
    }
    public static void swap(Integer[] a, int i, int j) {
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
    public static long MOD = 998244353L;
    public static long factorial(int n) {
        return factorialTable[n];
    }
    public static long reciprocalFactorial(int n) {
        return reciprocalFactorialTable[n];
    }
    public static long[] reciprocalFactorialTable;
    public static long[] factorialTable;
    public static void initTables(int MAX_NUM) {
        reciprocalFactorialTable = new long[MAX_NUM + 1];
        factorialTable = new long[MAX_NUM + 1];
        factorialTable[0] = 1;
        for (int i = 1; i < factorialTable.length; i++) {
            factorialTable[i] = mul(i, factorialTable[i - 1]);
        }
        reciprocalFactorialTable[MAX_NUM] = pow(factorialTable[MAX_NUM], MOD - 2);
        for (int i = MAX_NUM - 1; i >= 0; i--) {
            reciprocalFactorialTable[i] = mul(reciprocalFactorialTable[i + 1], (i + 1));
        }
    }
    public static long pow(long a, long n) {
        if (n > Integer.MAX_VALUE) {
            throw new IllegalArgumentException("n忒大了");
        }
        long ret = 1;
        while (n > 0) {
            if (n % 2 == 1) {
                ret = ret * a % MOD;
            }
            a = a * a % MOD;
            n /= 2;
        }
        return ret;
    }
    public static long mul(long a, long b) {
        return a * b % MOD;
    }
    public static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;

        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }

        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }
    }
}


// https://github.com/VaHiX/CodeForces/
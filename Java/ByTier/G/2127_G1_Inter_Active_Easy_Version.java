// Problem: CF 2127 G1 - Inter Active (Easy Version)
// https://codeforces.com/contest/2127/problem/G1

/*
 * Problem: Inter Active (Easy Version)
 * Purpose: Find a hidden permutation p of length n using at most 15*n queries.
 * Algorithm:
 *   - Select k = (n+1)/4 + 1 as a constant.
 *   - For each position i in the result:
 *     - Build a query permutation q where q[k] = i.
 *     - Partition remaining positions into left and right parts.
 *     - Query using this partition and use the response to narrow down the search.
 *     - Repeat until the correct position is found.
 *   - Time Complexity: O(n^2 * log n)
 *   - Space Complexity: O(n)
 */

import java.io.*;
import java.util.*;

public class Main {
    static final int MXN = 1003;
    static int n, k;
    static int[] p = new int[MXN];
    static int[] q = new int[MXN];
    static boolean[] mark = new boolean[MXN];
    static BufferedReader br;
    static PrintWriter out;

    // Ask the jury for the number of valid pairs
    static int ask() throws IOException {
        out.print("? ");
        for (int i = 1; i <= n; i++) {
            out.print(q[i]);
            if (i < n) out.print(' ');
        }
        out.println();
        out.flush();
        String line = br.readLine();
        if (line == null) System.exit(0);
        line = line.trim();
        if (line.equals("-1")) System.exit(0); 
        return Integer.parseInt(line);
    }

    // Output the final permutation
    static void ans() {
        out.print("! ");
        for (int i = 1; i <= n; i++) {
            if (i > 1) out.print(' ');
            out.print(p[i]);
        }
        out.println();
        out.flush();
    }

    // Build query permutation q for a given value at position k
    static void build(int valI, ArrayList<Integer> opt, ArrayList<Integer> optbad) {
        Arrays.fill(mark, false);
        Arrays.fill(q, 0);
        q[k] = valI;
        mark[valI] = true;
        
        // Assign elements to positions [1..k-1]
        for (int j = 1; j < k && !opt.isEmpty(); j++) {
            int x = opt.remove(opt.size() - 1);
            q[j] = x;
            mark[x] = true;
        }

        // Assign remaining elements in reverse manner to [n down to k+1]
        for (int j = n; !opt.isEmpty(); j--) {
            int x = opt.remove(opt.size() - 1);
            q[j] = x;
            mark[x] = true;
        }

        // Assign elements from bad list
        for (int j = k + 1; !optbad.isEmpty(); j++) {
            int x = optbad.remove(optbad.size() - 1);
            q[j] = x;
            mark[x] = true;
        }

        // Fill remaining zeros with unused elements
        ArrayList<Integer> remaining = new ArrayList<>();
        for (int j = 1; j <= n; j++) {
            if (!mark[j]) remaining.add(j);
        }
        for (int j = 1; j <= n; j++) {
            if (q[j] == 0) {
                q[j] = remaining.remove(remaining.size() - 1);
            }
        }
    }

    // Reverse query array
    static void rev() {
        ArrayList<Integer> vec = new ArrayList<>();
        for (int i = 1; i <= n; i++) {
            if (i != k) vec.add(q[i]);
        }
        for (int i = 1; i <= n; i++) {
            if (i == k) continue;
            q[i] = vec.remove(vec.size() - 1);
        }
    }

    static void solveCase() throws IOException {
        n = Integer.parseInt(br.readLine().trim());
        k = (n + 1) / 4 + 1;
        out.println(k);
        out.flush();

        // For each index i, find where it should be placed in the permutation
        for (int i = 1; i <= n; i++) {
            ArrayList<Integer> opt = new ArrayList<>();
            for (int j = 1; j <= n; j++) {
                if (j != i) opt.add(j);
            }

            // Binary search to determine correct element at position i
            while (opt.size() > 1) {
                int sz = opt.size() - Math.min((opt.size() + 1) / 2, n - (2 * k - 1));
                if (sz < 0) sz = 0;
                if (sz > opt.size()) sz = opt.size();

                ArrayList<Integer> left = new ArrayList<>(opt.subList(0, sz));
                ArrayList<Integer> right = new ArrayList<>(opt.subList(sz, opt.size()));

                build(i, new ArrayList<>(left), new ArrayList<>(right));
                int val = ask();
                
                rev(); // Reverse the query and make another call
                val += ask();

                if (val == n - 1) {
                    opt = left;
                } else {
                    opt = right;
                }
            }
            
            // Once the element is determined, map it to its correct position
            int pos = opt.get(0);
            p[pos] = i;
        }
        ans();
    }

    public static void main(String[] args) throws Exception {
        br = new BufferedReader(new InputStreamReader(System.in));
        out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        String first = br.readLine();
        if (first == null) return;
        first = first.trim();
        int tc;
        try {
            tc = Integer.parseInt(first);
        } catch (NumberFormatException e) {
            return;
        }
        for (int t = 0; t < tc; t++) {
            solveCase();
        }
        out.close();
    }
}


// https://github.com/VaHiX/CodeForces/
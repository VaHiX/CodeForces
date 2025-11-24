// Problem: CF 2140 D - A Cruel Segment's Thesis
// https://codeforces.com/contest/2140/problem/D

/*
 * Problem: D. A Cruel Segment's Thesis
 * 
 * Purpose: Given n segments on a number line, repeatedly merge two unmarked segments 
 * into one new segment by choosing appropriate endpoints, maximizing the total length 
 * of all marked segments.
 *
 * Algorithm: 
 * - Each segment is represented as [l, r], and we compute sum = l + r for sorting.
 * - Sort segments based on their sum to optimize selection for merges.
 * - Use prefix sums to help quickly calculate sums of subsets.
 * - For even n, the best merge is to take the first half of sorted segments' right values 
 *   minus the sum of first half of sums (to minimize cost).
 * - For odd n, iterate over each possible segment and compute best merge that leaves one 
 *   segment unmerged, again minimizing the cost.
 *   
 * Time Complexity: O(n log n) per test case due to sorting; overall is O(n log n) assuming total n is bounded.
 * Space Complexity: O(n) for storing segment data, prefix sums, and auxiliary arrays.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) {
        FastReader fs = new FastReader();
        PrintWriter out = new PrintWriter(System.out);
        int t = fs.nextInt();
        while (t-- > 0) {
            solve(fs, out);
        }
        out.flush();
    }

    static class Segment implements Comparable<Segment> {
        long l, r, sum;
        public Segment(long l, long r) {
            this.l = l;
            this.r = r;
            this.sum = l + r;
        }
        @Override
        public int compareTo(Segment other) {
            return Long.compare(this.sum, other.sum);
        }
    }

    static void solve(FastReader fs, PrintWriter out) {
        int n = fs.nextInt();
        if (n == 0) {
            out.println(0);
            return;
        }
        Segment[] seg = new Segment[n];
        long base = 0;
        for (int i = 0; i < n; i++) {
            long l = fs.nextLong();
            long r = fs.nextLong();
            base += (r - l); // accumulate base total length
            seg[i] = new Segment(l, r);
        }
        Arrays.sort(seg); // Sort segments by sum = l + r

        long[] As = new long[n]; // Stores the sums (l + r) of sorted segments
        long[] Rs = new long[n]; // Stores right bounds of sorted segments
        long totalR = 0;
        for (int i = 0; i < n; i++) {
            As[i] = seg[i].sum;
            Rs[i] = seg[i].r;
            totalR += Rs[i];
        }

        long[] prefA = new long[n]; // Prefix sum array of As
        prefA[0] = As[0];
        for (int i = 1; i < n; i++) {
            prefA[i] = prefA[i - 1] + As[i];
        }

        long bestAdded = Long.MIN_VALUE;
        if (n % 2 == 0) {
            // Even number of segments: merge all except the last half to minimize cost
            int m = n / 2;
            long sumSmall = (m > 0) ? prefA[m - 1] : 0;
            bestAdded = totalR - sumSmall;
        } else {
            // Odd number of segments: try every element as unmerged, compute optimal merge
            int m = (n - 1) / 2;
            for (int k = 0; k < n; k++) {
                long sumRRem = totalR - Rs[k]; // Remaining right sums after removing k-th segment
                long sumSmall = 0;
                if (m > 0) {
                    if (k >= m) {
                        // Take prefix up to m-1
                        sumSmall = prefA[m - 1];
                    } else {
                        // Remove k from suffix sum of first m elements
                        sumSmall = prefA[m] - As[k];
                    }
                }
                bestAdded = Math.max(bestAdded, sumRRem - sumSmall);
            }
        }

        long answer = base + Math.max(0, bestAdded); // Add positive gain to base
        out.println(answer);
    }

    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
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
    }
}


// https://github.com/VaHiX/CodeForces/
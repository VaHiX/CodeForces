// Problem: CF 2108 D - Needle in a Numstack
// https://codeforces.com/contest/2108/problem/D

/*
 * Task: D. Needle in a Numstack
 * 
 * Purpose:
 *   Given a concatenated array C of two arrays A and B, where both A and B have length at least k,
 *   and each has all k consecutive elements distinct, find the lengths of A and B.
 *   The arrays consist only of numbers from 1 to k.
 * 
 * Approach:
 *   - We use a binary search strategy to identify the boundary between arrays A and B.
 *   - Query the first K and last K elements to gather initial information about A and B.
 *   - Perform binary search on possible positions where the transition from A to B may occur.
 * 
 * Time Complexity:
 *   O(log N * K) per test case due to binary search and limited queries (250).
 * 
 * Space Complexity:
 *   O(K) for storing arrays A and B of size K.
 */

import java.io.*;
import java.util.*;

public class D {
    static InputReader r = new InputReader(System.in);
    static PrintWriter pw = new PrintWriter(System.out);

    public static void main(String[] args) {
        int T = r.nextInt(); // Read number of test cases
        for (int star = 0; star < T; star++) {
            int N = r.nextInt(); // Length of concatenated array C
            int K = r.nextInt(); // Minimum length constraint for A and B
            int[] A = new int[N]; // Store first K elements from the array C
            for (int i = 1; i <= K; i++) {
                pw.println("? " + i); // Query first K elements of C
                pw.flush();
                A[i - 1] = r.nextInt();
            }
            int[] B = new int[K]; // Store last K elements from the array C
            for (int i = N; i > N - K; i--) {
                pw.println("? " + i); // Query last K elements of C
                pw.flush();
                B[(i - 1) % K] = r.nextInt(); // Reverse indexing to store in array format
            }

            int good_query = -1;
            if (N == 2 * K) { // Special case where both A and B are exactly of size K
                pw.println("! " + K + " " + K);
                pw.flush();
                continue;
            }

            for (int i = 0; i < K; i++) {
                if (A[i] != B[i]) { // Find the first element where A and B differ
                    good_query = i;
                    break;
                }
            }

            if (good_query == -1) { // All elements match, not enough info
                pw.println("! -1");
                pw.flush();
                continue;
            }

            int L = K; // Left boundary for binary search
            int R = N - K - 1; // Right boundary for binary search

            while (R - L > K) {
                int mid = (L + (R - L) / 2); // Midpoint for binary search
                int now_try_query = -1;
                // Search in a window around mid to find a difference
                for (int i = mid + K / 2; i >= mid - K / 2; i--) {
                    if (A[i % K] != B[i % K]) {
                        now_try_query = i;
                        break;
                    }
                }
                if (now_try_query == -1) {
                    System.out.println("FUCK"); // Not expected but kept for debugging
                }

                int one_indexed_now_try_query = now_try_query + 1;
                pw.println("? " + one_indexed_now_try_query); // Query that point
                pw.flush();
                int response = r.nextInt();
                if (response == A[now_try_query % K]) {
                    L = now_try_query + 1; // Response indicates A’s pattern holds, move left forward
                } else {
                    R = now_try_query; // Response indicates B’s pattern holds, keep moving right
                }
            }

            boolean unknown = false;
            boolean found = false;
            for (int i = L; i <= R; i++) {
                int i_one_indexed = i + 1;
                pw.println("? " + i_one_indexed); // Query candidate transition point
                pw.flush();
                int response = r.nextInt();

                if (response == A[i % K] && response == B[i % K]) {
                    unknown = true; // Ambiguous case; might be boundary point
                } else if (response == A[i % K]) {
                    unknown = false; // Confirms A's presence
                } else if (response == B[i % K]) {
                    if (unknown) {
                        pw.println("! -1");
                        pw.flush();
                        found = true;
                        break;
                    } else {
                        int Alen = i; // Current length of array A
                        int Blen = N - i; // Remaining length for array B
                        pw.println("! " + Alen + " " + Blen);
                        pw.flush();
                        found = true;
                        break;
                    }
                }
            }

            if (!found) {
                if (unknown) {
                    pw.println("! -1");
                    pw.flush();
                    continue;
                }
                int Alen = N - K; // Default assuming A goes up to N-K
                int Blen = K; // B covers last K elements
                pw.println("! " + Alen + " " + Blen);
                pw.flush();
            }
        }
        pw.close(); // Close PrintWriter
    }

    static class InputReader {
        BufferedReader reader;
        StringTokenizer tokenizer;

        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }

        String next() { 
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

        public long nextLong() {
            return Long.parseLong(next()); 
        }

        public double nextDouble() {
            return Double.parseDouble(next());
        }
    }
}


// https://github.com/VaHiX/CodeForces/
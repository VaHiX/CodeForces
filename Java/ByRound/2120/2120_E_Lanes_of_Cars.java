// Problem: CF 2120 E - Lanes of Cars
// https://codeforces.com/contest/2120/problem/E

/*
E. Lanes of Cars

Purpose:
This code solves the problem of minimizing the total angriness of cars in a toll plaza with n lanes,
where each car's angriness is based on how long it waits before passing through the toll, and switching lanes adds k extra angriness.
The goal is to optimally rearrange cars between lanes to minimize total angriness.

Algorithm:
- Binary search on the answer (the minimal possible total angriness)
- For each candidate value, check feasibility using a greedy simulation approach
- Adjust lanes to minimize congestion and compute the minimum total angriness

Time Complexity:
O(sum(n) * log(max(a[i]))) where sum(n) is the total number of elements across all test cases.
Space Complexity:
O(n) for storing arrays and intermediate data.

Techniques:
- Binary search over the solution space
- Greedy simulation to verify feasibility
- Mathematical formula for sum of arithmetic sequence
 */

import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter    pw = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(br.readLine().trim());
        while (T-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            long k = Long.parseLong(st.nextToken());
            long[] a = new long[n];
            st = new StringTokenizer(br.readLine());
            long S = 0, maxA = 0;
            for (int i = 0; i < n; i++) {
                a[i] = Long.parseLong(st.nextToken());
                S += a[i];
                if (a[i] > maxA) maxA = a[i];
            }
            long lo = 1, hi = maxA;
            while (lo < hi) {
                long mid = (lo + hi) >>> 1; // Use unsigned right shift for safe mid calculation
                long cnt = 0;
                for (int i = 0; i < n; i++) {
                    cnt += Math.min(a[i], mid); // Only count up to 'mid' cars from lane i
                    long extra = mid - k - a[i]; // How many additional cars can be moved here
                    if (extra > 0) cnt += extra; // Add those extra cars if any
                    if (cnt >= S) break; // Early termination if enough cars counted
                }
                if (cnt >= S) hi = mid; // If we can handle all cars with this 'mid', try smaller value
                else            lo = mid + 1; // Otherwise, increase lower bound
            }
            long T0 = lo; // The minimum time to serve all cars
            long took = 0;
            long total = 0;
            for (int i = 0; i < n; i++) {
                long ai = a[i];
                long use0 = Math.min(ai, T0); // How many cars are served in this lane at time T0
                took  += use0;
                total += use0 * (use0 + 1) / 2; // Sum of first 'use0' natural numbers for contribution
                long extra = T0 - k - ai; // Extra cars that could come from other lanes due to lane changing
                if (extra > 0) {
                    took  += extra;
                    total += extra * (ai + k); // Additional cost due to lane change
                    total += extra * (extra + 1) / 2; // Additional angriness from these cars
                }
            }
            long excess = took - S; // Excess cars in final assignment
            total -= excess * T0; // Adjust for overcounted contribution
            pw.println(total);
        }
        pw.flush();
    }
}


// https://github.com/VaHiX/CodeForces/
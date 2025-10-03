// Problem: CF 2120 E - Lanes of Cars
// https://codeforces.com/contest/2120/problem/E

/*
E. Lanes of Cars

Algorithm: Binary search on the answer + Greedy optimization.
Time Complexity: O(n * log(max_a)) where max_a is the maximum element in array a.
Space Complexity: O(1) excluding input storage.

The problem involves minimizing total angriness of cars in lanes, where:
- Each car waits 1 second per position in queue to pass the toll
- Cars can be moved between lanes at extra cost k (angriness increase due to confusion)
- Goal: Minimize sum of all angriness values

Approach:
1. Binary search on the optimal time T when cars arrive at toll booth.
2. For a given T, check if it's possible to distribute cars such that total waiting time is <= S (sum of all cars).
   This uses greedy idea to assign cars optimally to each lane.
3. After determining optimal T, compute final result using arithmetic progression formula and adjustments.

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
            // Binary search on the answer
            long lo = 1, hi = maxA;
            while (lo < hi) {
                long mid = (lo + hi) >>> 1; // Right shift for unsigned division
                long cnt = 0;
                for (int i = 0; i < n; i++) {
                    cnt += Math.min(a[i], mid);
                    long extra = mid - k - a[i];
                    if (extra > 0) cnt += extra;
                    if (cnt >= S) break; // Early termination condition
                }
                if (cnt >= S) hi = mid;
                else            lo = mid + 1;
            }
            long T0 = lo;
            long took = 0;
            long total = 0;
            for (int i = 0; i < n; i++) {
                long ai = a[i];
                long use0 = Math.min(ai, T0);
                took  += use0;
                total += use0 * (use0 + 1) / 2; // Sum of first 'use0' integers
                long extra = T0 - k - ai;
                if (extra > 0) {
                    took  += extra;
                    total += extra * (ai + k);      // Additional angriness from lane change
                    total += extra * (extra + 1) / 2; // Sum of extra integers after lane change
                }
            }
            long excess = took - S;
            total -= excess * T0; // Adjust for overcounting due to excess cars processed beyond sum S
            pw.println(total);
        }
        pw.flush();
    }
}


// https://github.com/VaHiX/CodeForces/
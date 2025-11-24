// Problem: CF 2121 F - Yamakasi
// https://codeforces.com/contest/2121/problem/F

/*
F. Yamakasi
Algorithms/Techniques: Prefix Sum, HashMap, Sliding Window with Reset on Threshold

Time Complexity: O(n) average per test case, where n is the length of the array.
Space Complexity: O(n) for the hash maps storing prefix sums.

The solution uses a two-map approach to track valid subsegments ending at each position:
- cntAll tracks all prefix sums encountered so far (including those with elements > x)
- cntNoX tracks prefix sums excluding elements that are greater than x

When we encounter an element > x, we reset both hashmaps since the subsegment can't continue
with values exceeding x. For every valid element (<= x), we count how many previous prefix sums
can form a valid subsegment with sum s and max value x using these maps.

Key observations:
- Elements larger than x break potential subsegments
- We use two counters to handle inclusion/exclusion of x appropriately
- All valid subsegments must have their maximum element exactly equal to x

*/

import java.util.*;
public class Main {
    static void solve(Scanner in) {
        int n = in.nextInt();
        long s = in.nextLong();
        int x = in.nextInt();
        long ans = 0L;
        long pref = 0L;
        HashMap<Long, Long> cntAll = new HashMap<>(); // All prefix sums including >x elements
        HashMap<Long, Long> cntNoX = new HashMap<>(); // Prefix sums excluding >x elements, but allowing x itself
        cntAll.put(0L, 1L);
        cntNoX.put(0L, 1L);
        for (int i = 0; i < n; i++) {
            int a = in.nextInt();
            if (a > x) {
                // Reset counters when encountering element > x
                pref = 0L;
                cntAll.clear();
                cntNoX.clear();
                cntAll.put(0L, 1L);
                cntNoX.put(0L, 1L);
            } else {
                pref += (long) a; // Add current element to prefix sum
                long need = pref - s; // What prefix sum would be needed for a subsegment of sum s
                
                // Get count of previous prefix sums giving us a valid segment sum s (any element)
                long addAll = 0L;
                Long vAll = cntAll.get(need);
                if (vAll != null) {
                    addAll = vAll;
                }
                
                // Get count of previous prefix sums not counting 'x' elements (but allowing x itself)
                long addNoX = 0L;
                if (a == x) {
                    addNoX = 0L; // We're at x, so it's always included in noX
                } else {
                    Long vNoX = cntNoX.get(need);
                    if (vNoX != null) {
                        addNoX = vNoX;
                    }
                }
                
                // Difference gives us valid sequences not containing the value x directly in it.
                ans += (addAll - addNoX); // Accumulate answer from this position
                
                // Update maps for future prefix sums
                Long pAll = cntAll.get(pref);
                if (pAll == null) {
                    cntAll.put(pref, 1L);
                } else {
                    cntAll.put(pref, pAll + 1L);
                }
                
                if (a == x) {
                    // If current element is x, reset noX map with updated prefix
                    cntNoX.clear();
                    cntNoX.put(pref, 1L);
                } else {
                    Long pNoX = cntNoX.get(pref);
                    if (pNoX == null) {
                        cntNoX.put(pref, 1L);
                    } else {
                        cntNoX.put(pref, pNoX + 1L);
                    }
                }
            }
        }
        System.out.println(ans);
    }
    
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int t = in.nextInt(); if (false) { }
        while (t-- > 0) {
            solve(in);
        }
        in.close();
    }
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 2137 D - Replace with Occurrences
// https://codeforces.com/contest/2137/problem/D

/**
 * Problem: D. Replace with Occurrences
 * 
 * Purpose:
 * Given an array b of size n, determine if there exists an array a of size n such that
 * for each element a[i], the count of occurrences of a[i] in a equals b[i].
 * If such an array exists, construct it.
 * 
 * Algorithm:
 * 1. For each unique value v in b, collect all indices where b[i] = v.
 * 2. Check whether total occurrences (size of list) is divisible by v.
 *    If not, it's impossible to assign values correctly → return -1.
 * 3. Otherwise, assign labels in groups: for each value v occurring at k positions,
 *    we need to assign v numbers (each appearing exactly v times) over those k positions.
 *    Use a label counter to cycle through different values and distribute accordingly.
 * 
 * Time Complexity: O(n log n) due to HashMap operations and sorting implicit in computeIfAbsent
 * Space Complexity: O(n) for storing the map, result array, and auxiliary data structures
 */

import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int t = s.nextInt();
        while (t-- > 0) {
            int n = s.nextInt();
            int[] b = new int[n], a = new int[n];
            for (int i = 0; i < n; i++) b[i] = s.nextInt();

            // Map each value in b to the list of indices where it appears
            Map<Integer, List<Integer>> m = new HashMap<>();
            for (int i = 0; i < n; i++)
                m.computeIfAbsent(b[i], x -> new ArrayList<>()).add(i);

            boolean ok = true;
            // Check if for each value v in b, the count of occurrences is divisible by v
            for (var e : m.entrySet())
                if (e.getValue().size() % e.getKey() != 0) {
                    ok = false;
                    break;
                }

            if (!ok) {
                System.out.println(-1);
                continue;
            }

            int lbl = 1; // start labeling from 1
            // Process each group of indices corresponding to same value in b
            for (var e : m.entrySet()) {
                int v = e.getKey();         // value we're handling
                int sz = e.getValue().size(); // number of occurrences needed for this value
                List<Integer> idxs = e.getValue(); // indices where this value occurs
                for (int i = 0; i < sz;) {
                    // Assign 'v' elements with the same label
                    for (int j = 0; j < v; j++)
                        a[idxs.get(i++)] = lbl;
                    lbl++; // move to next unique label
                }
            }

            StringBuilder out = new StringBuilder();
            for (int i = 0; i < n; i++)
                out.append(a[i]).append(i == n - 1 ? "\n" : " ");
            System.out.print(out);
        }
    }
}


// https://github.com/VaHiX/codeForces/
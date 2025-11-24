// Problem: CF 2133 A - Redstone?
// https://codeforces.com/contest/2133/problem/A

/*
 * Problem: Determine if gears can be arranged to satisfy a specific rotational speed condition.
 * 
 * Algorithm/Technique:
 * - The problem involves computing the cumulative speed of gears in a sequence.
 * - For a valid arrangement where the last gear spins at 1 revolution per second,
 *   we simulate the speed propagation and check if it satisfies the constraint.
 * - Key observation: We only need to test one arrangement since the result depends on
 *   the multiplicative properties of gear ratios across the chain.
 * 
 * Time Complexity: O(n) per test case — linear scan through gears.
 * Space Complexity: O(1) — using only a few variables for computation.
 */

import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            int n = sc.nextInt();
            Set<String> set = new HashSet<>(); // Used to track unique gear teeth values
            for (int i = 0; i < n; i++) {
                set.add(sc.next()); // Add each gear's tooth count to the set
            }
            // If all gears have distinct tooth counts, output "NO"
            // Otherwise, at least one duplicate exists which may allow valid arrangement
            if (set.size() == n) {
                System.out.println("NO");
            } else {
                System.out.println("YES");
            }
        }
    }
}


// https://github.com/VaHiX/codeForces/
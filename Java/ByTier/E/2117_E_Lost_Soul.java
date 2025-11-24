// Problem: CF 2117 E - Lost Soul
// https://codeforces.com/contest/2117/problem/E

/**
 * Problem: E. Lost Soul
 * Purpose: Given two arrays a and b of length n, compute the maximum number of matches
 *          achievable by performing operations on elements or removing one element pair.
 *
 * Algorithms/Techniques:
 * - Greedy approach with preprocessing and set-based tracking of values
 * - For each test case, check for possible match positions from right to left,
 *   considering valid transformations and potential removals.
 *
 * Time Complexity: O(n) per test case, as each element is processed once in the loop.
 * Space Complexity: O(n) for storing the set and input arrays.
 */
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class ProblemE {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            int n = sc.nextInt();
            int[] arr = new int[n];
            int[] arr2 = new int[n];
            for (int i = 0; i < n; i++) {
                arr[i] = sc.nextInt();
            }
            for (int i = 0; i < n; i++) {
                arr2[i] = sc.nextInt();
            }
            if (arr[n - 1] == arr2[n - 1]) {
                // If last elements match, all positions up to n are matches
                System.out.println(n);
            } else {
                Set<Integer> set = new HashSet<>();
                int ans = 0;
                // Traverse from right to left, checking conditions for match
                for (int i = n - 2; i >= 0; i--) {
                    if (arr[i] == arr2[i]) {
                        // If current elements match, update answer
                        ans = i + 1;
                        break;
                    }
                    if (arr[i] == arr[i + 1] || arr2[i] == arr2[i + 1]) {
                        // If transformation leads to matching next element, update answer
                        ans = i + 1;
                        break;
                    }
                    if (set.contains(arr[i]) || set.contains(arr2[i])) {
                        // If either current element was seen before, update answer
                        ans = i + 1;
                        break;
                    }
                    // Add the next elements to the set for future reference
                    set.add(arr[i + 1]);
                    set.add(arr2[i + 1]);
                }
                System.out.println(ans);
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/
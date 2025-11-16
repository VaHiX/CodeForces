// Problem: CF 2110 C - Racing
// https://codeforces.com/contest/2110/problem/C

/*
 * Problem: Racing
 * 
 * Purpose: Given a drone flight program with some unknown values (-1), determine how to replace
 *          those -1s with 0 or 1 such that the drone passes through all obstacles. Obstacles
 *          define valid height ranges [l_i, r_i] at each step.
 *
 * Algorithm:
 *   - Forward pass: Compute minimum and maximum possible heights at each point using prefix logic.
 *   - Backward pass: Compute actual values for the drone height array h.
 *   - Reconstruct d from h differences.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for arrays mins, maxs, h
 */

import java.util.Scanner;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int t = sc.nextInt();
    for (int tc = 0; tc < t; ++tc) {
      int n = sc.nextInt();
      int[] d = new int[n];
      for (int i = 0; i < d.length; ++i) {
        d[i] = sc.nextInt();
      }
      int[] l = new int[n];
      int[] r = new int[n];
      for (int i = 0; i < n; ++i) {
        l[i] = sc.nextInt();
        r[i] = sc.nextInt();
      }
      System.out.println(solve(d, l, r));
    }
    sc.close();
  }

  static String solve(int[] d, int[] l, int[] r) {
    int n = d.length;
    int[] mins = new int[n + 1]; // Minimum possible height at index i
    int[] maxs = new int[n + 1]; // Maximum possible height at index i

    // Forward pass: Determine bounds on height at each obstacle
    for (int i = 1; i <= n; ++i) {
      if (d[i - 1] == 0) {
        // No change in height
        mins[i] = mins[i - 1];
        maxs[i] = maxs[i - 1];
      } else if (d[i - 1] == 1) {
        // Drone rises by 1
        mins[i] = mins[i - 1] + 1;
        maxs[i] = maxs[i - 1] + 1;
      } else {
        // d[i-1] == -1, unknown value: can rise (1) or stay (0), so:
        mins[i] = mins[i - 1];         // Min height if we choose not to rise
        maxs[i] = maxs[i - 1] + 1;     // Max height if we rise
      }

      // Impose constraints imposed by current obstacle range [l[i-1], r[i-1]]
      mins[i] = Math.max(mins[i], l[i - 1]);
      maxs[i] = Math.min(maxs[i], r[i - 1]);

      // Check if valid range exists
      if (mins[i] > maxs[i]) {
        return "-1";
      }
    }

    int[] h = new int[n + 1]; // Final computed height array
    h[n] = mins[n]; // Start from the minimum allowed final height

    // Backward pass: Fill in actual heights for each obstacle
    for (int i = n - 1; i >= 1; --i) {
      if (d[i] == -1) {
        // Unknown direction, choose to keep consistent with prior choice if possible
        if (h[i + 1] >= mins[i] && h[i + 1] <= maxs[i]) {
          h[i] = h[i + 1];
        } else {
          h[i] = h[i + 1] - 1;
        }
      } else {
        // Known transition: use the difference to backtrack
        h[i] = h[i + 1] - d[i];
      }
    }

    // Build output array by computing differences between consecutive heights
    return IntStream.range(1, h.length)
        .map(i -> h[i] - h[i - 1])
        .mapToObj(String::valueOf)
        .collect(Collectors.joining(" "));
  }
}


// https://github.com/VaHiX/CodeForces/
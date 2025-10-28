// Problem: CF 2107 C - Maximum Subarray Sum
// https://codeforces.com/contest/2107/problem/C

/*
 * Problem: C. Maximum Subarray Sum
 *
 * Purpose:
 *   Given a partially filled array with some elements marked as "missing" (indicated by 0 in string s),
 *   fill the missing positions with values up to 10^18 such that the maximum subarray sum equals exactly k.
 *
 * Algorithms/Techniques:
 *   - Kadane's Algorithm for finding maximum subarray sum
 *   - Greedy approach to assign value to the last missing element, adjusting left and right segments
 *
 * Time Complexity:
 *   O(n) per test case due to single passes through the array
 *
 * Space Complexity:
 *   O(n) for storing the array and intermediate results
 */

import java.util.*;

public class Main {
    // Kadane's algorithm to compute maximum subarray sum
    static long max_subarray_sum(long arr[]) {
        int n = arr.length;
        long curr = 0, max = Long.MIN_VALUE;
        for (int i = 0; i < n; i++) {
            curr += arr[i];
            if (curr < 0)
                curr = 0;
            max = Math.max(curr, max);
        }
        return max;
    }

    static void solve(Scanner in) {
        int n = in.nextInt();
        long k = in.nextLong();
        String s = in.next();
        long[] a = new long[n];
        final long INF = Integer.MAX_VALUE; // A large value used to mark missing elements
        int last = -1; // index of the last missing element

        // Initialize array: set missing elements to -INF so they are ignored in max subarray calculation
        for (int i = 0; i < n; i++) {
            a[i] = in.nextLong();
            if (s.charAt(i) == '0') {
                a[i] = -INF;
                last = i;
            }
        }

        // Check if maximum possible subarray sum is already greater than k
        if (max_subarray_sum(a) > k) {
            System.out.println("No");
            return;
        }

        // If current max sum equals k, we're done
        if (max_subarray_sum(a) == k) {
            System.out.println("Yes");
            for (long v : a)
                System.out.print(v + " ");
            System.out.println();
            return;
        }

        // If there are no missing elements, it's impossible to adjust
        if (last == -1) {
            System.out.println("No");
            return;
        }

        // Reset the last missing element to 0 before calculating left/right max subarrays
        a[last] = 0;

        // Calculate maximum subarray sum on the left side of the last missing element
        long left_max = 0, right_max = 0;
        long sum = 0;
        for (int i = last - 1; i >= 0; i--) {
            sum += a[i];
            left_max = Math.max(left_max, sum);
        }

        // Reset and calculate maximum subarray sum on the right side of the last missing element
        sum = 0;
        for (int i = last + 1; i < n; i++) {
            sum += a[i];
            right_max = Math.max(right_max, sum);
        }

        // Assign value to the last missing position such that overall max subarray = k
        a[last] = k - left_max - right_max;
        System.out.println("Yes");
        for (long v : a)
            System.out.print(v + " ");
        System.out.println();
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int t = in.nextInt();
        while (t-- > 0)
            solve(in);
        in.close();
    }
}


// https://github.com/VaHiX/CodeForces/
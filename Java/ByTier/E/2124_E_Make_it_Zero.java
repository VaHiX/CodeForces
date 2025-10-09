// Problem: CF 2124 E - Make it Zero
// https://codeforces.com/contest/2124/problem/E

/*
E. Make it Zero

Purpose:
This code solves the problem where we are given an array of positive integers and must determine 
the minimum number of operations to reduce all elements to zero using a specific operation:
- Choose an array b such that the prefix sum equals the suffix sum at some index.
- Subtract b[i] from a[i] for each i.

Approach:
1. First check if it's possible to make all elements zero:
   - Total sum must be even (since we split total into two equal parts)
   - Maximum element must not exceed half of total sum (otherwise impossible to balance)

2. If possible:
   - Try to find a prefix whose sum equals half the total sum.
   - If found, one operation suffices (subtract whole array).
   - Otherwise, construct two arrays that split the work in a way that both sums are equal.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the array and intermediate result arrays

Algorithms/Techniques:
- Prefix sum calculation
- Greedy assignment
- Two-pointer-like logic for balancing sums
*/

import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine());
        for (int test = 1; test <= T; test++) {
            int n = Integer.parseInt(br.readLine());
            long[] a = new long[n];
            StringTokenizer st = new StringTokenizer(br.readLine());
            for (int i = 0; i < n; i++) {
                a[i] = Long.parseLong(st.nextToken());
            }
            long sum = 0;
            for (long num : a) {
                sum += num;
            }
            if (sum % 2 != 0) { // If total sum is odd, impossible to split equally
                System.out.println(-1);
                continue;
            }
            long maxVal = 0;
            for (long num : a) {
                maxVal = Math.max(maxVal, num);
            }
            if (maxVal * 2 > sum) { // If any single element is more than half of the total, impossible
                System.out.println(-1);
                continue;
            }
            long target = sum / 2;
            long currentSum = 0;
            int index = 0;
            for (; index < n; index++) {
                if (currentSum + a[index] > target) {
                    index--; // Backtrack so we include this element in our prefix
                    break;
                }
                currentSum += a[index];
            }
            if (currentSum == target) { // Found exact partition
                System.out.println(1);
                for (int i = 0; i < n; i++) {
                    System.out.print(a[i] + " ");
                }
                System.out.println();
            } else { // Need to split into two operations
                System.out.println(2);
                long[] aa = new long[n]; // Second array to be constructed
                long extra = sum - 2 * currentSum; // Difference between total and 2*currentSum
                aa[index + 1] = extra / 2; // Assign half of difference to next element in second array
                a[index + 1] -= aa[index + 1]; // Adjust first array accordingly
                extra /= 2;
                for (int i = n - 1; i > index + 1 && extra > 0; i--) { // Distribute remaining to back elements
                    if (a[i] >= extra) {
                        aa[i] = extra;
                        a[i] -= extra;
                        extra = 0;
                    } else {
                        aa[i] = a[i];
                        extra -= a[i];
                        a[i] = 0;
                    }
                }
                for (int i = 0; i < n; i++) {
                    System.out.print(a[i] + " ");
                }
                System.out.println();
                for (int i = 0; i < n; i++) {
                    System.out.print(aa[i] + " ");
                }
                System.out.println();
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 2106 E - Wolf
// https://codeforces.com/contest/2106/problem/E

/*
 * Problem: Wolf and Binary Search
 * 
 * Purpose:
 *   This program solves a problem where we perform binary search on a permutation of integers
 *   to find a target value k. However, the permutation may not be sorted, so we can reorder
 *   some elements in a given range [l,r] to make the binary search successful.
 *
 * Algorithm:
 *   For each query (l, r, k):
 *     1. Find the position of k in the permutation.
 *     2. Simulate the binary search process on subarray [l,r].
 *     3. Count "bad" comparisons where the pivot element is misordered relative to k.
 *     4. Compute minimum number of swaps (d) needed to fix these inconsistencies.
 *
 * Time Complexity: O(n + q * log n)
 * Space Complexity: O(n)
 */
import java.util.*;
public class Main {
    static void solve(Scanner sc) {
        int n = sc.nextInt();
        int q = sc.nextInt();
        int[] perm = new int[n + 1];
        int[] pos = new int[n + 1];
        for (int i = 1; i <= n; i++) {
            perm[i] = sc.nextInt();
            pos[perm[i]] = i;
        }
        while (q-- > 0) {
            int l = sc.nextInt();
            int r = sc.nextInt();
            int x = sc.nextInt();
            int px = pos[x];
            if (px < l || px > r) {
                System.out.print("-1 ");
                continue;
            }
            int left = l, right = r;
            int badLeft = 0, badRight = 0;
            int midLess = 0, midGreater = 0;
            while (true) {
                int mid = (left + right) / 2;
                if (mid == px) break;
                if (mid < px) {
                    if (perm[mid] > x) {
                        badLeft++;
                        midGreater++;
                    } else {
                        midLess++;
                    }
                    left = mid + 1;
                } else {
                    if (perm[mid] < x) {
                        badRight++;
                        midLess++;
                    } else {
                        midGreater++;
                    }
                    right = mid - 1;
                }
            }
            int availableLess = x - 1 - midLess;
            int availableGreater = n - x - midGreater;
            int fixLeft = Math.max(0, badLeft - badRight);
            int fixRight = Math.max(0, badRight - badLeft);
            if (fixLeft > availableLess || fixRight > availableGreater) {
                System.out.print("-1 ");
            } else {
                int moves = 2 * Math.max(badLeft, badRight);
                System.out.print(moves + " ");
            }
        }
        System.out.println();
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            solve(sc);
        }
        sc.close();
    }
}


// https://github.com/VaHiX/CodeForces/
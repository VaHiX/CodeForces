// Problem: CF 2108 C - Neo's Escape
// https://codeforces.com/contest/2108/problem/C

// Problem: C. Neo's Escape
// Purpose: Determine the minimum number of clones needed to press all buttons in a non-increasing order of weights.
// Algorithm: 
//   - Group consecutive elements with same value.
//   - For each group, check if it can be a "peak" (i.e., it's greater than its neighbors).
//   - The number of such peaks corresponds to the number of clones needed.
// Time Complexity: O(n) for each test case, where n is the number of buttons.
// Space Complexity: O(1) excluding input storage.

import java.util.Scanner;
public class C3 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            int n = sc.nextInt();
            int[] arr = new int[n];
            for (int i = 0; i < n; i++) {
                arr[i] = sc.nextInt();
            }
            int ans = 0;
            int i = 0;
            while (i < n) {
                int j = i;
                // Find the end of the current group of identical elements
                while (j + 1 < n && arr[j + 1] == arr[i]) {
                    j++;
                }
                int v = arr[i];
                // Check if this group can be a peak on the left
                boolean leftOk = (i == 0) || (arr[i - 1] < v);
                // Check if this group can be a peak on the right
                boolean rightOk = (j == n - 1) || (arr[j + 1] < v);
                // If both conditions are satisfied, it's a valid peak and needs one clone
                if (leftOk && rightOk) {
                    ans++;
                }
                i = j + 1;
            }
            System.out.println(ans);
        }
        sc.close();
    }
}


// https://github.com/VaHiX/CodeForces/
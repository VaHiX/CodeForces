// Problem: CF 2152 C - Triple Removal
// https://codeforces.com/contest/2152/problem/C

/*
C. Triple Removal
Algorithms/Techniques: Prefix sums, range queries, greedy approach with preprocessing.

Time Complexity: O(n + q) per test case, where n is the size of the array and q is the number of queries.
Space Complexity: O(n) per test case for storing prefix arrays.

The problem is about finding the minimum cost to make a binary subarray empty by removing triplets of identical elements.
We preprocess the array to support efficient range queries on:
- Number of 0s and 1s in any subarray
- Number of adjacent equal elements

For each query, we compute:
- Count of 0s (o) and 1s (z)
- Count of adjacent equal pairs (ea)
Then use a greedy strategy to determine the minimum cost, handling cases where total count is divisible by 3.

The key idea:
- If total number of 0s and 1s are both divisible by 3, we can remove triplets.
- Else it's impossible. Otherwise, the minimal operations needed is (o/3 + z/3)
- If there are adjacent equal pairs, one move might allow us to combine operations
*/

import java.util.*;
public class C_Triple_Removal {
    static Scanner sc = new Scanner(System.in);
    static int[] rd(int n) {
        int[] a = new int[n + 1]; // 1-indexed array for easier prefix handling
        for (int i = 1; i <= n; i++) a[i] = sc.nextInt();
        return a;
    }
    static int[] pre1(int[] a, int n) {
        int[] p = new int[n + 1]; // prefix sum of 1s
        for (int i = 1; i <= n; i++) p[i] = p[i - 1] + a[i];
        return p;
    }
    static int[] pre0(int[] a, int n) {
        int[] p = new int[n + 1]; // prefix sum of 0s
        for (int i = 1; i <= n; i++) p[i] = p[i - 1] + (1 - a[i]); // convert 1 to 0 and vice versa
        return p;
    }
    static int[] preE(int[] a, int n) {
        int[] p = new int[n + 1]; // prefix sum of adjacent equal pairs
        for (int i = 1; i < n; i++) {
            p[i] = p[i - 1];
            if (a[i] == a[i + 1]) p[i]++; // increment only if current and next are equal
        }
        p[n] = p[n - 1]; // duplicate last value for consistent indexing
        return p;
    }
    static int calc(int o, int z, int ea) {
        // If not divisible by 3, cannot form valid triplets for all elements, return -1
        if (o % 3 != 0 || z % 3 != 0) return -1;
        int b = o / 3 + z / 3; // Minimum operations needed without considering adjacent pairs
        // If there are adjacent equal pairs, one extra operation may not be needed
        return ea > 0 ? b : b + 1;
    }
    static void solv() {
        int n = sc.nextInt(), q = sc.nextInt();
        int[] a = rd(n);
        int[] po = pre1(a, n); // prefix sum of 1s
        int[] pz = pre0(a, n); // prefix sum of 0s
        int[] pe = preE(a, n); // prefix sum of adjacent equal elements
        while (q-- > 0) {
            int l = sc.nextInt(), r = sc.nextInt();
            int o = po[r] - po[l - 1]; // count of 1s in range [l, r]
            int z = pz[r] - pz[l - 1]; // count of 0s in range [l, r]
            int ea = pe[r - 1] - pe[l - 1]; // count of adjacent equal pairs in range [l, r]
            System.out.println(calc(o, z, ea));
        }
    }
    public static void main(String[] args) {
        int t = sc.nextInt();
        while (t-- > 0) 
            solv();
    }
}


// https://github.com/VaHiX/CodeForces/
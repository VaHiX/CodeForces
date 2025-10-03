// Problem: CF 2115 A - Gellyfish and Flaming Peony
// https://codeforces.com/contest/2115/problem/A

/**
 * Problem: Gellyfish and Flaming Peony
 * 
 * Purpose:
 * This program solves the problem of finding the minimum number of operations
 * required to make all elements of an array equal by replacing one element with
 * the GCD of that element and another element in the array.
 * 
 * Algorithm:
 * - Precompute GCD values for all pairs up to 5000 using Euclidean algorithm.
 * - Reduce the array elements by their overall GCD so that we can work with a normalized array.
 * - Use dynamic programming to find the minimum operations needed to reduce each element to 1,
 *   then account for any elements remaining greater than 1.
 * 
 * Time Complexity:
 * O(N^2 + M*N) where N is max element (5000), M is number of elements in array.
 * Preprocessing GCD table takes O(N^2). For each test case, the DP step takes O(M*N).
 * 
 * Space Complexity:
 * O(N^2) for storing precomputed GCD values and auxiliary arrays.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Main {
    static final int N = 5004;
    static int[][] gcd = new int[N][N];
    
    // Initialize GCD table using Euclidean algorithm
    static {
        for (int i = 0; i < N; i++) {
            gcd[i][0] = gcd[0][i] = gcd[i][i] = i;
        }
        for (int x = 1; x < N; x++) {
            for (int y = 1; y < x; y++) {
                gcd[x][y] = gcd[y][x] = gcd[y][x % y]; // Compute GCD using Euclidean method
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(bf.readLine());
        while (t-- > 0) {
            int size = Integer.parseInt(bf.readLine());
            String[] arrStr = bf.readLine().split(" ");
            int[] lst = new int[size];
            for (int i = 0; i < size; i++) lst[i] = Integer.parseInt(arrStr[i]);
            System.out.println(solve(size, lst));
        }
    }

    static int solve(int n, int[] arr) {
        int k = 0;
        int m = 0;
        int[] f = new int[N];
        Arrays.fill(f, N*N); // Initialize dp array with large value
        
        // Find overall GCD of all elements in the array
        for (int num : arr) {
            k = gcd[k][num];
        }
        
        // Normalize array by dividing each element by overall GCD and build max 'm'
        for (int i = 0; i < n; i++) {
            arr[i] /= k;
            m = Math.max(m, arr[i]);
            f[arr[i]] = 0; // Mark starting positions as 0 operations
        }
        
        // DP step: compute minimum number of steps to reduce each number to 1
        for (int a = m; a >= 1; a--) {
            for (int b : arr) {
                int g = gcd[a][b]; // Compute GCD between current value and array element
                f[g] = Math.min(f[g], f[a] + 1); // Update dp if shorter path found
            }
        }
        
        // Count how many elements are not already 1 (they require additional operations)
        int ans = Math.max(f[1] - 1, 0);
        for (int num : arr) {
            if (num > 1) ans++;
        }
        return ans;
    }
}


// https://github.com/VaHiX/CodeForces/
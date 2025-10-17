// Problem: CF 2143 D2 - Inversion Graph Coloring (Hard Version)
// https://codeforces.com/contest/2143/problem/D2

/*
 * Problem: D2. Inversion Graph Coloring (Hard Version)
 * 
 * Purpose:
 *   This solution counts the number of "good" subsequences in a given array,
 *   where a good subsequence can be colored with red/blue such that for every
 *   pair of indices i < j with b_i > b_j, they have different colors.
 *   This is equivalent to counting how many subsequences avoid having an inversion
 *   that would create a conflict in coloring. The problem is solved using dynamic programming
 *   with Fenwick Trees (Binary Indexed Tree) to efficiently track valid colorings.
 * 
 * Algorithm:
 *   - Use coordinate compression on the input values.
 *   - For each element, update a 2D DP table `magic[i][j]` tracking the number of
 *     ways to form a good subsequence ending at position i with last element having index j in
 *     compressed coordinates.
 *   - Two Fenwick Trees (colFenw and rowFenw) are used:
 *     colFenw[i][j] tracks sum along columns for row i up to index j.
 *     rowFenw[i][j] tracks sum along rows for column i up to index j.
 *   - Transition based on valid inversion checking (i.e., how to extend a subsequence
 *     such that no two elements that violate coloring property are adjacent).
 * 
 * Time Complexity:
 *   O(n^2 * log n) per test case due to Fenwick Tree operations and nested loops.
 * Space Complexity:
 *   O(n^2) for storing the DP table and Fenwick Trees.
 */

import java.io.*;
import java.util.*;

public class Main {
    static final int MOD = 1_000_000_007;
    
    // Modular addition to prevent overflow
    static int addmod(int a, int b) {
        a += b;
        if (a >= MOD) a -= MOD;
        return a;
    }
    
    // Fenwick Tree update: adds value 'val' at index 'idx'
    static void fenwAdd(int[] bit, int idx, int val, int SZ) {
        int i = idx + 1;
        while (i <= SZ) {
            bit[i] = addmod(bit[i], val);
            i += i & -i; // Move to parent in BIT
        }
    }
    
    // Fenwick Tree prefix sum: returns sum from index 0 to idx
    static int fenwSum(int[] bit, int idx) {
        if (idx < 0) return 0;
        int i = idx + 1;
        int res = 0;
        while (i > 0) {
            res = addmod(res, bit[i]);
            i -= i & -i; // Move to parent in BIT
        }
        return res;
    }
    
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        int T = Integer.parseInt(br.readLine().trim());
        while (T-- > 0) {
            int n = Integer.parseInt(br.readLine().trim());
            int[] snacks = new int[n];
            st = new StringTokenizer(br.readLine());
            for (int i = 0; i < n; i++) snacks[i] = Integer.parseInt(st.nextToken());
            
            // Coordinate compression
            int[] vals = Arrays.copyOf(snacks, n);
            Arrays.sort(vals);
            vals = Arrays.stream(vals).distinct().toArray();
            int M = vals.length;
            for (int i = 0; i < n; i++) {
                snacks[i] = Arrays.binarySearch(vals, snacks[i]);
            }
            
            int SZ = M + 1; // Size of Fenwick Trees
            int[][] magic = new int[SZ][SZ]; // DP table: number of good subsequences ending at pos i with last element val j
            magic[0][0] = 1; // Base case
            
            // Initialize Fenwick Trees for column-wise and row-wise sums
            int[][] colFenw = new int[SZ][SZ + 1];
            int[][] rowFenw = new int[SZ][SZ + 1];
            
            fenwAdd(colFenw[0], 0, 1, SZ); // Initialize with base state in columns
            fenwAdd(rowFenw[0], 0, 1, SZ); // Initialize with base state in rows
            
            // Iterate through each element of the sequence
            for (int snack : snacks) {
                int snackIdx = snack + 1; // Convert to 1-based indexing
                
                // Update columns based on previous valid states
                for (int lb = 0; lb <= M; lb++) {
                    int S1 = fenwSum(colFenw[lb], snackIdx);
                    if (S1 != 0) {
                        magic[snackIdx][lb] = addmod(magic[snackIdx][lb], S1);
                        fenwAdd(colFenw[lb], snackIdx, S1, SZ); // Update BIT for column lb
                        fenwAdd(rowFenw[snackIdx], lb, S1, SZ); // Update BIT for row snackIdx
                    }
                }
                
                // Update rows based on previous valid states
                for (int la = snackIdx + 1; la <= M; la++) {
                    int S2 = fenwSum(rowFenw[la], snackIdx);
                    if (S2 != 0) {
                        magic[la][snackIdx] = addmod(magic[la][snackIdx], S2);
                        fenwAdd(colFenw[snackIdx], la, S2, SZ); // Update BIT for column snackIdx
                        fenwAdd(rowFenw[la], snackIdx, S2, SZ); // Update BIT for row la
                    }
                }
            }
            
            // Calculate final result by summing all possibilities in magic table
            int ans = 0;
            for (int i = 0; i <= M; i++)
                for (int j = 0; j <= M; j++)
                    ans = addmod(ans, magic[i][j]);
            System.out.println(ans);
        }
    }
}


// https://github.com/VaHiX/codeForces/
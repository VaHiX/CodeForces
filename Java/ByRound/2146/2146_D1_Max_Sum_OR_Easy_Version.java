// Problem: CF 2146 D1 - Max Sum OR (Easy Version)
// https://codeforces.com/contest/2146/problem/D1

/*
 * Problem: D1. Max Sum OR (Easy Version)
 * 
 * Purpose: Given integers l and r (where l = 0), we need to create two arrays 'a' and 'b'
 *          such that b is [l, l+1, ..., r] and a is a permutation of the same elements.
 *          We want to maximize the sum of bitwise ORs between corresponding elements:
 *          sum(a[i] | b[i]) for i = 0 to n-1.
 *
 * Algorithm:
 *   - The strategy builds a specific permutation using recursive bit manipulation logic.
 *   - For each bit position, it determines how to assign values to maximize the OR result.
 *   - A recursive function 'buildPairs' generates the optimal arrangement of bits.
 *   - The time complexity is O(r) due to generating permutations for all numbers from 0 to r.
 *   - The space complexity is O(r) because we store a permutation array of size n = r + 1.
 *
 * Time Complexity: O(r)
 * Space Complexity: O(r)
 */
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter writer = new PrintWriter(System.out);
        int t = Integer.parseInt(reader.readLine());
        while (t-- > 0) {
            solve(reader, writer);
        }
        writer.flush();
        writer.close();
        reader.close();
    }

    private static void solve(BufferedReader reader, PrintWriter writer) throws IOException {
        StringTokenizer st = new StringTokenizer(reader.readLine());
        st.nextToken(); // Skip the first token (l)
        int r = Integer.parseInt(st.nextToken()); // Get r
        int n = r + 1; // Length of arrays
        int[] permutation = new int[n]; // This will hold the rearranged array
        buildPairs(r, permutation); // Build optimal arrangement
        long maxSum = computeSum(permutation); // Compute final sum
        writer.println(maxSum);
        printArray(permutation, writer); // Print the resulting array
    }

    private static void buildPairs(int r, int[] p) {
        if (r < 0) return;
        int k = 0;
        while ((1 << k) <= r) k++; // Find smallest k such that 2^k > r
        int mask = (1 << k) - 1; // Create a mask with k bits set to 1
        int pivot = mask - r; // Determine the pivot point based on current r and mask

        // Fill in the range [pivot, r] in reverse order using bit manipulation
        for (int i = pivot; i <= r; i++) {
            p[i] = mask - i;
        }

        // Recursively process the left half of the sequence
        buildPairs(pivot - 1, p);
    }

    private static long computeSum(int[] p) {
        long sum = 0;
        for (int i = 0; i < p.length; i++) {
            sum += (long) i | p[i]; // OR each element of original array with permuted array
        }
        return sum;
    }

    private static void printArray(int[] arr, PrintWriter writer) {
        for (int i = 0; i < arr.length; i++) {
            writer.print(arr[i]);
            if (i < arr.length - 1) writer.print(" ");
        }
        writer.println();
    }
}


// https://github.com/VaHiX/CodeForces/
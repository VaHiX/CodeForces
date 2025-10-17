// Problem: CF 2130 D - Stay or Mirror
// https://codeforces.com/contest/2130/problem/D

/*
D. Stay or Mirror
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

You are given a permutation p_1, p_2, ..., p_n of length n.
You have to build an array a_1, a_2, ..., a_n in the following way:
 for each 1 <= i <= n, set either a_i = p_i or a_i = 2n - p_i.
Find the minimum possible number of inversions in the array a_1, a_2, ..., a_n.
An inversion in the array a_1, a_2, ..., a_n is a pair of indices (i, j) such that 1 <= i < j <= n and a_i > a_j.

Algorithm:
- For each element in the permutation, we decide whether to keep it as p[i] or use 2*n - p[i].
- The key idea is to use a greedy approach with simulation.
- Try to place elements in order from 1 to n (as if we were building a sorted array).
- For each number:
    - Find its current position in the list (after previous removals)
    - Determine cost of moving it left or right to reach target index
    - Remove that element from list
- This mimics a greedy assignment strategy to minimize inversions.

Time Complexity: O(n^2) due to repeated indexOf and remove operations.
Space Complexity: O(n) for storing the arraylist.
*/

import java.io.*;
import java.util.*;
public class Main {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static StringTokenizer st;
    public static String next() throws IOException {
        while (st == null || !st.hasMoreTokens())
            st = new StringTokenizer(br.readLine());
        return st.nextToken();
    }
    public static int nextInt() throws IOException {
        return Integer.parseInt(next());
    }
    public static long nextLong() throws IOException {
        return Long.parseLong(next());
    }
    public static void main(String[] args) throws IOException {
        int t = nextInt();
        while (t-- > 0) {
            Nish();
        }
    }
    static void Nish() throws IOException {
        int n= nextInt(); // Read size of permutation
        ArrayList<Integer>  res = new ArrayList<>(); // Store current elements in order
        for(int i = 0;i<n;i++){
            int num = nextInt(); // Read permutation element
            res.add(num);
        }
        int ans = 0; // Initialize inversion count
        for(int i = 1;i<=n;i++){ // For each number from 1 to n
            int pos = res.indexOf(i); // Find position of current number in remaining list
            ans += Math.min(pos, res.size() - pos-1); // Calculate minimum steps needed to move it
            res.remove(pos); // Remove the number after processing
        }
        System.out.println(ans); // Output result
    }
}


// https://github.com/VaHiX/codeForces/
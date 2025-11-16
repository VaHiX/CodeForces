// Problem: CF 2115 D - Gellyfish and Forget-Me-Not
// https://codeforces.com/contest/2115/problem/D

/*
 * Problem: D. Gellyfish and Forget-Me-Not
 * 
 * Purpose:
 * This code solves a game theory problem where two players (Gellyfish and Flower) take turns choosing
 * to XOR either array 'a' or 'b' elements with a running value x, aiming to minimize or maximize the final result.
 * The choice is determined by a binary string c. Players play optimally.
 * 
 * Algorithm:
 * - Uses a basis vector approach (linear algebra over GF(2)) to compute optimal XOR combinations.
 * - For each element from right to left, processes whether it can be represented in the current basis.
 * - Based on player turns and the basis representation, computes final minimal/maximal value accordingly.
 * 
 * Time Complexity: O(n * L), where L = 60 (number of bits)
 * Space Complexity: O(L)
 */
import java.io.*;
import java.util.*;
public class Main {
    static final int L = 60;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int T = Integer.parseInt(br.readLine());
        while (T-- > 0) {
            int n = Integer.parseInt(br.readLine());
            long[] a = new long[n];
            long[] b = new long[n];
            StringTokenizer st = new StringTokenizer(br.readLine());
            for (int i = 0; i < n; i++) {
                a[i] = Long.parseLong(st.nextToken());
            }
            st = new StringTokenizer(br.readLine());
            for (int i = 0; i < n; i++) {
                b[i] = Long.parseLong(st.nextToken()) ^ a[i]; // XOR difference between b[i] and a[i]
            }
            String str = br.readLine();
            long[] bas = new long[L]; // Basis vectors to represent the space
            int[] bel = new int[L];   // Belongs to which player (1: Flower, 0: Gellyfish, -1: unassigned)
            Arrays.fill(bel, -1);
            long all = 0;             // XOR of all a values
            for (long num : a) {
                all ^= num;
            }
            for (int i = n - 1; i >= 0; i--) {
                long x = b[i];        // Difference for current element
                int col = str.charAt(i) - '0'; // Player: 0 for Gellyfish, 1 for Flower
                for (int j = L - 1; j >= 0; j--) {
                    if ((x >> j & 1) == 1) { // If bit j is set in x
                        if (bas[j] != 0) {
                            x ^= bas[j]; // Reduce using existing basis vector
                        } else {
                            // Find a new pivot and update the basis
                            for (int k = j - 1; k >= 0; k--) {
                                if ((x >> k & 1) == 1) {
                                    x ^= bas[k];
                                }
                            }
                            bas[j] = x;
                            for (int k = L - 1; k > j; k--) {
                                if ((bas[k] >> j & 1) == 1) {
                                    bas[k] ^= bas[j];
                                }
                            }
                            bel[j] = col;
                            break;
                        }
                    }
                }
            }

            // Determine minimum xor value using basis
            for (int j = L - 1; j >= 0; j--) {
                if ((all >> j & 1) == 1) {
                    all ^= bas[j];
                }
            }
            
            long ans = 0;
            for (int j = 0; j < L; j++) {
                if (bel[j] == 1) {    // If the basis vector belongs to Flower, include it
                    ans ^= bas[j];
                }
            }
            out.println(all ^ ans);
        }
        out.close();
    }
}


// https://github.com/VaHiX/CodeForces/
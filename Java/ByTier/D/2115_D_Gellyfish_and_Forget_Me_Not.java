// Problem: CF 2115 D - Gellyfish and Forget-Me-Not
// https://codeforces.com/contest/2115/problem/D

/*
 * Problem: D. Gellyfish and Forget-Me-Not
 * 
 * Algorithm: This problem uses a greedy approach with Gaussian elimination
 *            to compute optimal XOR values in a two-player game.
 * 
 * Approach:
 *   - For each bit position, we determine whether it can be set by the operations.
 *   - We process the rounds in reverse order, building a basis for the vectors.
 *   - The key idea is to simulate a greedy selection where Gellyfish minimizes
 *     and Flower maximizes the outcome, using linear algebra principles over GF(2).
 * 
 * Time Complexity: O(n * L), where L = 60 is the number of bits (constant)
 * Space Complexity: O(L), for storing basis vectors and column information
 * 
 * Techniques Used:
 *   - Gaussian elimination on binary vectors
 *   - Greedy selection based on player roles (0 for Gellyfish, 1 for Flower)
 *   - XOR properties in bit manipulation
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
                b[i] = Long.parseLong(st.nextToken()) ^ a[i]; // Compute delta (b[i] XOR a[i])
            }
            String str = br.readLine();
            long[] bas = new long[L]; // Basis vectors
            int[] bel = new int[L];   // Belongs to which player's choice in bit position
            Arrays.fill(bel, -1);
            long all = 0;
            for (long num : a) {
                all ^= num; // XOR all a[i] values as initial x
            }
            // Process rounds from last to first to build basis
            for (int i = n - 1; i >= 0; i--) {
                long x = b[i]; // Current delta value
                int col = str.charAt(i) - '0'; // Determine current active player (0 or 1)
                for (int j = L - 1; j >= 0; j--) {
                    if ((x >> j & 1) == 1) { // If this bit is set
                        if (bas[j] != 0) {
                            x ^= bas[j]; // Reduce x using existing basis vector
                        } else {
                            // First time we see a vector with this bit as MSB
                            for (int k = j - 1; k >= 0; k--) { // Ensure no smaller bit is set in reduced x
                                if ((x >> k & 1) == 1) {
                                    x ^= bas[k];
                                }
                            }
                            bas[j] = x; // Add x to basis at position j
                            for (int k = L - 1; k > j; k--) { // Update dependent basis vectors
                                if ((bas[k] >> j & 1) == 1) {
                                    bas[k] ^= bas[j];
                                }
                            }
                            bel[j] = col; // Mark that this bit represents decision by player 'col'
                            break;
                        }
                    }
                }
            }
            // Reduce all to remove redundant components
            for (int j = L - 1; j >= 0; j--) {
                if ((all >> j & 1) == 1) {
                    all ^= bas[j];
                }
            }
            long ans = 0;
            for (int j = 0; j < L; j++) {
                if (bel[j] == 1) { // If this bit was chosen by Flower (player 1)
                    ans ^= bas[j];  // Add contribution from this basis to final result
                }
            }
            out.println(all ^ ans); // Final answer considering optimal choices
        }
        out.close();
    }
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 2153 A - Circle of Apple Trees
// https://codeforces.com/contest/2153/problem/A

/*
 * Problem: A. Circle of Apple Trees
 * 
 * Algorithm: Greedy approach withHashSet for tracking unique values.
 * 
 * Key Idea:
 * - Traverse the circle of trees and greedily eat apples with beauty greater 
 *   than the last eaten apple's beauty.
 * - Use a HashSet to track unique beauties that have been eaten so far to avoid 
 *   counting duplicates.
 * 
 * Time Complexity: O(n) per test case, where n is the number of trees.
 * Space Complexity: O(n) for storing the HashSet of unique beauties.
 * 
 * Techniques: 
 * - Greedy selection
 * - HashSet for uniqueness tracking
 * - Circular traversal simulation
 */

import java.io.*;
import java.util.*;
public class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder ans = new StringBuilder();
        int taama = Integer.parseInt(br.readLine().trim()); // Read number of test cases
        while (taama-- > 0) {
            int naama = Integer.parseInt(br.readLine().trim()); // Read number of trees
            StringTokenizer st = new StringTokenizer(br.readLine()); // Read beauties
            HashSet<Integer> paama = new HashSet<>(); // Set to store unique beauties eaten
            for (int i = 0; i < naama; i++) {
                int daama = Integer.parseInt(st.nextToken()); // Read current beauty
                paama.add(daama); // Add beauty to set
            }
            ans.append(paama.size()).append('\n'); // Output size of set (unique beauties)
        }
        System.out.print(ans.toString()); // Print all results
    }
}


// https://github.com/VaHiX/CodeForces/
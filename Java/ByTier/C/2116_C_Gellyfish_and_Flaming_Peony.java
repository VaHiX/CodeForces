// Problem: CF 2116 C - Gellyfish and Flaming Peony
// https://codeforces.com/contest/2116/problem/C

/*
 * Problem: C. Gellyfish and Flaming Peony
 * 
 * Purpose:
 *   Given an array of positive integers, we need to make all elements equal by repeatedly replacing one element with the GCD of itself and another element.
 *   This problem can be solved using BFS on GCD values to find minimum operations required to reduce the array to a single value.
 *   
 * Algorithms:
 *   - BFS traversal on GCD values to simulate possible operations
 *   - Precompute GCDs to avoid recomputation
 *   - Use BFS with a queue and HashMap to track minimal steps to reach a certain GCD value
 *   
 * Time Complexity:
 *   O(n * sqrt(max_value) + U * log(U)) where U is the number of unique elements.
 *   In worst case, it's about O(n * sqrt(5000) * n) = O(n^2 * sqrt(5000)).
 *   
 * Space Complexity:
 *   O(U * log(U) + n) where U is the number of unique elements and n is array size.
 *   The space is used for map storing GCDs and queue.
 */


import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine());
        while (t-- > 0) {
            int n = Integer.parseInt(br.readLine());
            int[] arr = new int[n];
            int g = 0;
            StringTokenizer st = new StringTokenizer(br.readLine());
            Set<Integer> unique = new HashSet<>();
            for (int i = 0; i < n; i++) {
                arr[i] = Integer.parseInt(st.nextToken()); // Read each element
                g = gcd(g, arr[i]); // Compute GCD of all elements
                unique.add(arr[i]); // Store unique values in a set
            }
            
            int countNotG = 0, countG = 0;
            for (int i = 0; i < n; i++) {
                if (arr[i] == g) countG++; // Count how many elements are equal to final GCD
                else countNotG++; // Count elements not equal to final GCD
            }
            
            if (countG > 0) {
                System.out.println(countNotG); // If already all elements are same as g, just return number of operations needed to reach that value
                continue;
            }

            Map<Integer, Integer> dis = new HashMap<>(); // Distance map to store minimum steps to get a GCD value
            Queue<Integer> q = new LinkedList<>();
            
            for (int i = 0; i < n; i++) {
                dis.put(arr[i], 0); // Put each starting element into the map with distance 0
                q.add(arr[i]); // Add to BFS queue
            }
            
            while (!q.isEmpty()) {
                int curr = q.poll(); // Current GCD value being processed
                for (int val : unique) { // For all unique values in original array
                    int currgcd = gcd(curr, val); // Calculate new GCD
                    if (!dis.containsKey(currgcd)) { // Only process if not seen before
                        dis.put(currgcd, dis.get(curr) + 1); // Mark distance as previous distance + 1
                        q.add(currgcd); // Add to queue for further exploration
                    }
                }
            }
            
            System.out.println((n - 1) + dis.getOrDefault(g, 0)); // Total operations = n-1 (to reduce to one element) + steps to reach desired GCD
        }
    }
    
    public static int gcd(int a, int b) { // Standard implementation of GCD using Euclidean algorithm
        while (b != 0) {
            int t = b;
            b = a % b;
            a = t;
        }
        return a;
    }
}


// https://github.com/VaHiX/CodeForces/
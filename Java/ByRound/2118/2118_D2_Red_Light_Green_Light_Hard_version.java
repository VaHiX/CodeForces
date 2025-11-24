// Problem: CF 2118 D2 - Red Light, Green Light (Hard version)
// https://codeforces.com/contest/2118/problem/D2

/*
 * Problem: D2. Red Light, Green Light (Hard version)
 *
 * Purpose: This code determines whether a person starting at different positions on a strip will eventually leave the strip within 10^100 seconds, based on traffic light behavior.
 *
 * Algorithm/Approach:
 * 1. Build a graph representing dependencies between positions where lights affect movement.
 * 2. Use DFS to detect cycles in this graph (which indicate the person gets stuck).
 * 3. For each query position, check if it leads to a cycle using binary search and precomputed mappings.
 *
 * Time Complexity: O(n log n + q log n)
 * Space Complexity: O(n)
 *
 * Techniques Used:
 * - Graph construction with cycle detection via DFS
 * - Binary search for efficient querying
 * - Modular arithmetic and hashing for grouping positions by light phases
 */

import java.util.*;
import java.lang.*;
import java.io.*;

public class Codechef {
    static Scanner s = new Scanner(System.in);
    static long[] p, d; // p: positions, d: delays
    static int n, k, mod = 998244353;
    
    public static void main(String[] args) {
        int tt = s.nextInt();
        while (tt-- > 0) {
            solve();
        }
        s.close();
    }
    
    public static void solve() {
        n = s.nextInt();
        long k = s.nextLong();
        p = new long[n];
        d = new long[n];
        for (int i = 0; i < n; i++) p[i] = s.nextLong(); // read positions
        for (int i = 0; i < n; i++) d[i] = s.nextLong(); // read delays
        int q = s.nextInt();
        
        // Adjacency list to represent the dependency graph
        ArrayList<Integer>[] arr = new ArrayList[2 * n];
        for (int i = 0; i < 2 * n; i++) arr[i] = new ArrayList<>();
        
        // Map to group positions by their phase (p[i] + d[i]) % k
        HashMap<Long, ArrayList<Integer>> map = new HashMap<>();
        for (int i = 0; i < n; i++) {
            long temp = (p[i] + d[i]) % k;
            if (!map.containsKey(temp)) map.put(temp, new ArrayList<>());
            if (map.get(temp).size() > 0) {
                int prev = map.get(temp).get(map.get(temp).size() - 1);
                arr[i].add(prev + n); // Add a link from current to previous light's mirror
            }
            map.get(temp).add(i);
        }
        
        // Clear the map and reuse for second phase (p[i] - d[i]) % k
        map = new HashMap<>();
        for (int i = 0; i < n; i++) {
            long temp = (p[i] - d[i] + k) % k;
            if (!map.containsKey(temp)) map.put(temp, new ArrayList<>());
            if (map.get(temp).size() > 0) {
                int prev = map.get(temp).get(map.get(temp).size() - 1);
                arr[prev + n].add(i); // Add link from previous mirror to current
            }
            map.get(temp).add(i);
        }
        
        // DFS for cycle detection
        int[] visited = new int[2 * n]; // 0: unvisited, 1: processed, 2: visiting (for detecting cycles)
        for (int i = 0; i < visited.length; i++) {
            if (visited[i] == 0) dfs(arr, i, visited);
        }
        
        // Process queries
        while (q-- > 0) {
            long c = s.nextLong();
            boolean t = true;
            long temp = (c) % k;
            if (map.containsKey(temp)) {
                ArrayList<Integer> al = map.get(temp);
                int ind = lowerBoundByValue(al, c, p);
                if (ind != -1 && visited[al.get(ind)] == 2) t = false; // If in a cycle
            }
            System.out.println(t ? "YES" : "NO");
        }
    }
    
    public static boolean dfs(ArrayList<Integer>[] arr, int i, int[] visited) {
        visited[i] = 2; // Mark as visiting
        for (int nei : arr[i]) {
            if (visited[nei] == 2) return true; // Cycle detected
            if (visited[nei] == 0) {
                if (dfs(arr, nei, visited)) return true;
            }
        }
        visited[i] = 1; // Mark as processed
        return false;
    }
    
    public static int lowerBoundByValue(ArrayList<Integer> list, long target, long[] dis) {
        int low = 0, high = list.size() - 1;
        int ans = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (dis[list.get(mid)] >= target) {
                ans = mid;       
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans; 
    }
}


// https://github.com/VaHiX/CodeForces/
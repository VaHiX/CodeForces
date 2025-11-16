// Problem: CF 2131 D - Arboris Contractio
// https://codeforces.com/contest/2131/problem/D

/*
 * Problem: D. Arboris Contractio
 * Purpose: Given a tree, determine the minimum number of operations to reduce its diameter to the smallest possible value.
 * Algorithm:
 *   - The key idea is that we want to minimize the diameter by "contracting" paths.
 *   - We find all leaf nodes (degree 1), and for each, we compute how many edges
 *     are connected to them from their neighbors.
 *   - Then we count the number of leaves and subtract the maximum number of leaves 
 *     connected to any single node (which represents the most "effective" contraction).
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing adjacency list and counters
 */

import java.io.*;
import java.util.*;

public class Main{
	public static void main(String[] args) throws IOException{
	    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	    PrintWriter out = new PrintWriter(System.out);
        StringTokenizer st;
        int t = Integer.parseInt(in.readLine());
        while(t-- > 0){
            int n = Integer.parseInt(in.readLine());
            ArrayList<Integer>[] adj = new ArrayList[n];
            for(int i = 0; i < n; i++) adj[i] = new ArrayList(); // Build adjacency list
            int[] cnts = new int[n];
            for(int i = 1; i < n; i++){
                st = new StringTokenizer(in.readLine());
                int u = Integer.parseInt(st.nextToken()) - 1;
                int v = Integer.parseInt(st.nextToken()) - 1;
                adj[u].add(v);
                adj[v].add(u);
                cnts[u]++;
                cnts[v]++;
            }
            int ans = 0;
            int[] cnts2 = new int[n]; // Count how many leaves are connected to each node
            for(int i = 0; i < n; i++){
                if(cnts[i] == 1){ // If the node is a leaf
                    ans++; // Increment total leaf count
                    cnts2[adj[i].get(0)]++; // Increment neighbor's counter (the parent of this leaf)
                }
            }
            int max = 0;
            for(int i : cnts2) max = Math.max(max, i); // Find maximum number of leaves connected to a node
            out.println(n == 2 ? 0 : ans - max); // Special case for n=2, otherwise compute operations needed
        }
	  	out.close();
	}
}


// https://github.com/VaHiX/codeForces/
// Problem: CF 2120 C - Divine Tree
// https://codeforces.com/contest/2120/problem/C

/*
C. Divine Tree
Purpose: Construct a rooted tree with n nodes such that the sum of divineness (smallest label on path from root to node) equals m.
Algorithm:
- For a tree rooted at r, the divine value d(v) for node v is the smallest label on the path from root r to v.
- Try to construct a tree by placing nodes in specific order so that their contribution adds up to m.
- The minimum possible sum occurs when we have a path: 1 -> 2 -> 3 -> ... -> n (rooted at 1), which gives sum = 1 + 2 + ... + n = n*(n+1)/2.
- If m is less than this, impossible. If more, not solvable directly with path structure.

Key Idea:
- Build a "chain" of nodes starting from the desired root node
- When we run out of chain capacity (i.e., remaining x < n - 1), we place what's left in valid position

Time Complexity: O(n) per test case due to iterative construction and traversal.
Space Complexity: O(n) for storing intermediate arrays and sets.

*/
import java.io.*;
import java.util.*;
public class Main {
  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter out = new PrintWriter(System.out);
    int t = Integer.parseInt(br.readLine());
    while (t-- > 0) {
      String[] input = br.readLine().split(" ");
      long n = Long.parseLong(input[0]);
      long m = Long.parseLong(input[1]);
      if (m < n) { // Minimum possible sum is n (all nodes are root themselves)
        out.println(-1);
        continue;
      }
      long x = m - n; // Extra amount to distribute beyond the base sum from 1..n
      long y = (n * (n + 1)) / 2; // Sum of first n natural numbers
      if (m > y) { // If exceeds maximum possible sum
        out.println(-1);
        continue;
      }
      ArrayList<Long> ans = new ArrayList<>();
      HashSet<Long> set = new HashSet<>();
      while (x >= n - 1 && n > 0) { 
        // While we can add full chain contribution and still have nodes left
        ans.add(n); // Add node to the result list
        set.add(n); // Mark this node as used
        x = x - (n - 1); // Deduct the contribution for adding n, which adds a path length of (n-1)
        n--; // Move backward in label
      }
      if (x > 0 && !set.contains(x + 1)) {
        ans.add(x + 1); // Place the remaining x+1 if not already placed
        set.add(x + 1);
      }
      for (long i = 1; i <= n; i++) {
        // Fill all unused nodes from 1 to n
        if (!set.contains(i)) {
          ans.add(i);
          set.add(i);
        }
      }
      out.println(ans.get(0)); // Root will be first element of list
      for (int i = 0; i < ans.size() - 1; i++) {
        out.println(ans.get(i) + " " + ans.get(i + 1)); // Output edges in form u v where u is parent of v
      }
    }
    out.flush();
    out.close();
  }
}


// https://github.com/VaHiX/CodeForces/
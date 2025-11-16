// Problem: CF 2120 C - Divine Tree
// https://codeforces.com/contest/2120/problem/C

/*
C. Divine Tree
Algorithm: Greedy Construction
Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the result and set

The task is to construct a rooted tree with n nodes such that the sum of 
divineness (minimum node label on the path from root to each node) equals m.
We build a tree greedily by assigning smaller labels to deeper levels,
and ensuring that total divineness matches m.

Approach:
- For n=1, impossible if m != 1
- Start with the largest possible values in lower layers (greedy)
- Use a set to track already added nodes
- Adjust leftover difference optimally into the tree structure
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
      if (m < n) { // If m is less than n, it's impossible since each node contributes at least 1
        out.println(-1);
        continue;
      }
      long x = m - n; // The extra contribution we need beyond minimum sum
      long y = (n * (n + 1)) / 2; // Maximum possible value for divineness (i.e., 1+2+...+n)
      if (m > y) { // If we exceed maximum possible sum, impossible
        out.println(-1);
        continue;
      }
      ArrayList<Long> ans = new ArrayList<>();
      HashSet<Long> set = new HashSet<>();
      while (x >= n - 1 && n > 0) {
        ans.add(n); // Add node with label n (greedy step)
        set.add(n);
        x = x - (n - 1); // Deduct contribution of this node as child
        n--; // Move to a smaller number
      }
      if (x > 0 && !set.contains(x + 1)) { // Handle leftover difference optimally
        ans.add(x + 1);
        set.add(x + 1);
      }
      for (long i = 1; i <= n; i++) { // Fill in remaining nodes not yet added
        if (!set.contains(i)) {
          ans.add(i);
          set.add(i);
        }
      }
      out.println(ans.get(0)); // Root is the first element
      for (int i = 0; i < ans.size() - 1; i++) { // Output edges of the tree in form u v
        out.println(ans.get(i) + " " + ans.get(i + 1));
      }
    }
    out.flush();
    out.close();
  }
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 2133 E - I Yearned For The Mines
// https://codeforces.com/contest/2133/problem/E

/* 
E. I Yearned For The Mines
Purpose: Solve a game on a tree where Steve (the player) must catch Herobrine (the enemy) by performing checks or destroying edges.
Algorithms:
  - Tree DFS traversal with level tracking
  - Greedy strategy to reduce the number of nodes where Herobrine might be
  - Use of hierarchical checking based on node degrees

Time Complexity: O(n) per test case, where n is the number of nodes. DFS traversal and processing are linear.

Space Complexity: O(n), for storing adjacency lists, level info, parent array, and result list.
*/

using System.Text;
namespace IYearnedForTheMines;
class Program {
  static void Solve() {
    int n = Next();
    nn = new HashSet<int>[n];
    for (int i = 0; i < n; i++)
      nn[i] = new(); // Initialize adjacency list
    for (int i = 1; i < n; i++) { // Read edges and build tree
      int a = Next() - 1;
      int b = Next() - 1;
      nn[a].Add(b);
      nn[b].Add(a);
    }
    lev = new(int v, int i)[n]; // Store level and node index for sorting by depth
    par = new int[n]; // Parent array for DFS traversal
    lev[0] = (-1, 0); // Root has level -1 (to distinguish from children)
    Dfs(0, 0); // Perform DFS to determine levels and parents
    Array.Sort(lev); 
    Array.Reverse(lev); // Sort nodes in descending order of depth
    ans = new(); // Result sequence of operations
    f = new bool[n]; // Boolean array to mark checked nodes
    foreach (var (_, i) in lev) { // Process from leaves up to root
      int cnt = nn[i].Count + 1; // Count adjacent nodes + 1 for current node
      if (cnt < 4) {
        foreach (var j in nn[i]) // If the node has less than 4 nodes around it, increase count
          cnt += nn[j].Count;
      }
      if (cnt > 3) {
        Remove(i); // If too many connections, remove this node
      }
    }
    Array.Reverse(lev); // Re-sort for the final traversal
    foreach (var (_, i) in lev) { // Final checking phase
      if (f[i]) // Skip already processed
        continue;
      if (nn[i].Count == 2) { // If node has degree 2, check each adjacent one
        var w = nn[i].ToArray();
        Check(w[0]);
        Check(i);
        Check(w[1]);
      } else if (nn[i].Count == 1) { // If single neighbor, trace entire chain
        int j = i;
        while (true) {
          Check(j);
          if (nn[j].Count == 0)
            break;
          j = nn[j].First();
        }
      } else { // For nodes with degree >= 3, just check them
        Check(i);
      }
    }
    writer.WriteLine(ans.Count); // Output all operations
    foreach (var (op, i) in ans) {
      writer.WriteLine($"{op} {i + 1}");
    }
  }
  static void Check(int i) {
    f[i] = true; // Mark node as checked
    ans.Add((1, i)); // Add check operation to result
  }
  static void Remove(int i) {
    Check(i); // Mark for checking
    ans.Add((2, i)); // Add destroy operation to result
    nn[par[i]].Remove(i); // Remove from parent's adjacency list (cutting the edge)
  }
  static bool[] f;
  static List<(int op, int i)> ans;
  static HashSet<int>[] nn;
  static (int v, int i)[] lev;
  static int[] par;
  static void Dfs(int to, int from) {
    lev[to] = (1 + lev[from].v, to); // Set level for current node
    par[to] = from; // Store parent
    nn[to].Remove(from); // Remove parent since tree is undirected
    foreach (var j in nn[to]) { // Go to children
      Dfs(j, to);
    }
  }
  static void Main(string[] args) {
    long t = Next(); // Read number of test cases
    for (int i = 0; i < t; i++)
      Solve(); // Process each case
    writer.Flush(); // Flush output buffer
  }
  static int Next() {
    int c;
    int m = 1;
    int res = 0;
    do {
      c = reader.Read();
      if (c == '-')
        m = -1;
    } while (c < '0' || c > '9');
    res = c - '0';
    while (true) {
      c = reader.Read();
      if (c < '0' || c > '9')
        return m * res; // Return final integer
      res *= 10;
      res += c - '0';
    }
  }
  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/codeForces/
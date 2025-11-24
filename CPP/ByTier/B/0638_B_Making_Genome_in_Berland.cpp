// Problem: CF 638 B - Making Genome in Berland
// https://codeforces.com/contest/638/problem/B

/*
 * Problem: B. Making Genome in Berland
 * 
 * Purpose: Given a set of DNA fragments (substrings), reconstruct the shortest
 *          possible genome string that contains all the fragments as substrings.
 *          The genome string must consist of distinct characters (nucleotides).
 * 
 * Approach:
 *   1. Build a directed graph from the fragments where an edge from 'a' to 'b'
 *      means 'a' is immediately followed by 'b' in some fragment.
 *   2. Find all "start" nodes (characters that are never right-hand side of edges).
 *   3. Follow each path in the graph from a start node to reconstruct fragments.
 *   4. Output all these fragments concatenated to form the final genome.
 * 
 * Time Complexity: O(N * M + K), where N is number of fragments, M is average fragment length,
 *                  and K is total number of distinct characters (at most 26).
 * Space Complexity: O(K^2), for storing the graph and sets (at most 26 characters).
 * 
 * Algorithms/Techniques:
 *   - Graph construction using adjacency list (map)
 *   - Topological traversal to find paths
 *   - Set-based deduplication and storage
 */

#include <iostream>
#include <map>
#include <set>
#include <string>

int main() {
  const long N = 26;
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::map<char, char> left, right;  // 'right' maps each char to the char that follows it
  std::set<char> present;            // store all characters that appear in fragments
  std::set<std::string> snippets;    // store paths (fragments) in the graph
  std::set<char> done;               // characters that are not starting points (they are on RHS of edges)
  
  for (long p = 0; p < n; p++) {
    std::string s;
    std::cin >> s;
    for (long u = 0; u < s.size(); u++) {
      present.insert(s[u]);  // mark character as present
    }
    for (long u = 0; u + 1 < s.size(); u++) {
      right[s[u]] = s[u + 1];  // create an edge from s[u] to s[u+1]
      done.insert(s[u + 1]);   // mark s[u+1] as being a follower (not a start)
    }
  }
  
  // Find all start characters (those not in 'done')
  for (long p = 0; p < N; p++) {
    char c = 'a' + p;
    if (!present.count(c) || done.count(c)) {
      continue;
    }
    std::string s("");
    s += c;
    // Traverse the path from start character c
    while (right.count(c)) {
      c = right[c];
      s += c;
    }
    snippets.insert(s);
  }
  
  // Output all reconstructed fragments
  for (std::set<std::string>::iterator it = snippets.begin();
       it != snippets.end(); it++) {
    std::cout << (*it);
  }
  std::cout << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/
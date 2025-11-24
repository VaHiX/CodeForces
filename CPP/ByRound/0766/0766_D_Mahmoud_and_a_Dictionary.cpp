// Problem: CF 766 D - Mahmoud and a Dictionary
// https://codeforces.com/contest/766/problem/D

/*
 * Problem: Mahmoud and a Dictionary
 * 
 * Purpose: 
 *   This code implements a dynamic connectivity system with two types of relations (synonymy and antonymy)
 *   using Union-Find with path compression and edge marking. It handles insertion of new relations,
 *   detects contradictions, and answers queries about relationships between words.
 * 
 * Techniques used:
 *   - Union-Find with path compression
 *   - Edge marking (boolean flag to track if a relation is synonym (0) or antonym (1))
 *   - Disjoint Set Union (DSU) with logical operations to maintain consistency
 * 
 * Time Complexity:
 *   - For union operations: O(log N) amortized (with path compression)
 *   - For find operations: O(log N) amortized (with path compression)
 *   - Overall for M relations and Q queries: O((M + Q) * log N)
 * 
 * Space Complexity:
 *   - O(N) for DSU structure and hash map
 * 
 * Algorithms:
 *   - DSU with logic tracking of relation types
 *   - Path compression in find operation
 *   - Logical XOR to maintain consistency of relationships
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

using namespace std;
#define f first
#define s second
typedef long long ll;
typedef pair<int, bool> pi;
const int N = 1e5 + 1;
int n, m, q;
pi dsu[N]; // DSU array storing parent and boolean indicating relation type (true = antonym, false = synonym)
unordered_map<string, int> mp; // Map from word to index in DSU

// Find function with path compression
// Returns parent index and logical value of path from node to root
pi find(int a) {
  if (dsu[a].f != a) {
    pi t = find(dsu[a].f); // Recursively find root
    dsu[a] = {t.f, t.s ^ dsu[a].s}; // Path compression with XOR
  }
  return dsu[a];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m >> q;
  
  // Initialize DSU and mapping
  for (int i = 1; i <= n; i++) {
    string s;
    cin >> s;
    mp[s] = i;
    dsu[i] = {i, 0}; // Initially, each node is its own parent with no relation
  }
  
  // Process all input relations
  while (m--) {
    int parity; // 0 for synonymy, 1 for antonymy
    cin >> parity;
    parity--; // Convert to 0 or 1
    string a, b;
    cin >> a >> b;
    
    pi c = find(mp[a]); // Find root of a
    pi d = find(mp[b]); // Find root of b
    
    // If both nodes are already in same set
    if (c.f == d.f) {
      // Check consistency: if relation between a and b conflicts with existing
      if ((c.s ^ d.s) == (bool)parity)
        cout << "YES\n"; // Consistent relation
      else
        cout << "NO\n"; // Inconsistent relation - contradiction
    } else {
      // Union operation: merge sets
      cout << "YES\n"; // Valid union
      dsu[c.f] = {d.f, parity ^ c.s ^ d.s}; // Update root with proper relation type
    }
  }
  
  // Process queries
  while (q--) {
    string a, b;
    cin >> a >> b;
    
    pi c = find(mp[a]); // Find root of a
    pi d = find(mp[b]); // Find root of b
    
    // If roots are different, no relation exists
    if (c.f != d.f)
      cout << "3\n";
    else {
      // If logical value is same, words are synonyms (same meaning)
      if (c.s == d.s)
        cout << "1\n";
      else
        // If logical value differs, words are antonyms (opposite meaning)
        cout << "2\n";
    }
  }
}


// https://github.com/VaHiX/CodeForces/
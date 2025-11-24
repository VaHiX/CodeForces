// Problem: CF 1987 D - World is Mine
// https://codeforces.com/contest/1987/problem/D

/*
 * Problem: D. World is Mine
 * 
 * Purpose:
 *   This code determines the maximum number of cakes Alice can eat in a game
 *   against Bob, where Alice starts first and both play optimally. 
 *   Alice eats cakes with tastiness strictly greater than any she's eaten before,
 *   while Bob eats any remaining cake. The goal is to maximize (for Alice) or 
 *   minimize (for Bob) the number of cakes Alice eats.
 * 
 * Algorithm:
 *   - Count frequency of each tastiness value.
 *   - Create a list of frequencies in ascending order of tastiness values.
 *   - Use a greedy approach with a priority queue (max heap) to track the 
 *     largest frequency that can be "replaced" to maintain optimal selection.
 *   - Iterate through the list of frequencies and simulate the game:
 *     * If placing the current frequency doesn't exceed the current max,
 *       add it to the heap.
 *     * Otherwise, if we can replace the largest frequency in the heap with the current,
 *       update the heap and total count.
 *   - The number of distinct max tastiness values Alice can achieve is the answer.
 * 
 * Time Complexity: O(n log n) - due to sorting and priority queue operations.
 * Space Complexity: O(n) - for frequency array and vector storage.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#define ll long long
#define ull unsigned ll
#define vs vector<string>
#define dd int
#define ii pair<dd, dd>
#define vi vector<dd>
#define vii vector<ii>
#define vvi vector<vi>
#define vvii vector<vii>
#define umap unordered_map
#define uset unordered_set
using namespace std;

const int N = 5e3 + 2;
int freq[N];

void solve() {
  int n;
  cin >> n;
  fill(freq, freq + n + 1, 0); // Initialize frequency array to 0
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    freq[a]++; // Count occurrences of each tastiness value
  }
  
  vi a; // Will store frequencies of each tastiness value (in increasing order)
  for (int i = 1; i <= n; i++) {
    if (freq[i])
      a.push_back(freq[i]); // Only include values that actually exist
  }
  
  int m = a.size(); // Number of unique tastiness values
  priority_queue<int> pq; // Max heap to store current frequencies in play
  int cnt = 0; // Total number of cakes selected so far
  int i = 0; // Index for iterating over frequencies
  int mv = 0; // Number of distinct tastiness values Alice can eat

  while (i < m) {
    if (cnt + a[i] <= mv) {
      // If including this frequency doesn't exceed maximum,
      // we can safely include this category of cakes
      pq.push(a[i]);
      cnt += a[i];
    } else {
      // Else check if we can replace a previous selection with better value
      if (pq.size() && pq.top() > a[i]) {
        cnt -= pq.top(); // Remove the largest selected frequency
        pq.pop();
        cnt += a[i]; // Add new frequency
        pq.push(a[i]); // Push updated entry
      }
      mv++; // Increment the maximum tastiness Alice can eat
    }
    i++; // Move to next unique tastiness value
  }
  
  cout << mv << endl; // Output the maximum number of cakes Alice can eat
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/
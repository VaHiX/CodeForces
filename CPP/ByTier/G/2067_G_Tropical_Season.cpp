// Problem: CF 2067 G - Tropical Season
// https://codeforces.com/contest/2067/problem/G

/*
G. Tropical Season

This code solves a problem involving identifying a single poisonous barrel among many,
using a system of comparisons and pouring operations. It simulates a scenario where each
barrel's weight can be compared to another, and water can be poured between barrels to
help distinguish which one is poisoned (assuming exactly one contains poison with mass 0.179kg).
The key insight is that in order to reliably identify the poisonous barrel, we must be able to
distinguish it from all others through comparison or merging operations.

Algorithm:
- Each barrel is grouped based on its weight's bit representation (using highest set bit).
- We maintain groups of barrels and gaps between consecutive weights within a group.
- When inserting or removing a barrel, we update these structures.
- Using the gap information, we determine if the current system allows us to identify
  exactly one poisonous barrel by checking conditions based on whether certain combinations
  of weights can be merged or distinguished.

Time Complexity: O(n log n + q * log^2 n) where n is number of barrels and q is number of queries
Space Complexity: O(n)

*/
#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

using namespace std;
const int NUM_GROUPS = 20; // Number of bit groups for weights
vector<multiset<int>> groups(NUM_GROUPS); // Groups barrel weights by their highest set bit
vector<multiset<int>> gaps(NUM_GROUPS);   // Gaps between consecutive elements in same group
vector<long long> groupSum(NUM_GROUPS, 0); // Sum of elements in each group

// Returns the index of the most significant set bit in x
inline int getGroup(int x) { return 31 - __builtin_clz(x); }

// Inserts a barrel into appropriate group and updates data structures
void insertBarrel(int x) {
  int grp = getGroup(x); // Determine which bit-group this weight belongs to
  auto it = groups[grp].insert(x); // Insert the new barrel weight
  groupSum[grp] += x; // Add to the group sum

  // Check if we have a previous element in the group
  if (it != groups[grp].begin()) {
    auto prevIt = it;
    prevIt--; // Iterator to previous element
    gaps[grp].insert(x - *prevIt); // Insert gap between current and previous elements
  }

  // Check next element in the group
  auto nxtIt = it;
  nxtIt++; // Move to next element or end()
  if (nxtIt != groups[grp].end()) {
    gaps[grp].insert(*nxtIt - x); // Insert gap from current to next in group

    if (it != groups[grp].begin()) { // If not first in group
      auto prevIt = it;
      prevIt--; // Previous element
      auto gapIt = gaps[grp].find(*nxtIt - *prevIt);
      if (gapIt != gaps[grp].end())
        gaps[grp].erase(gapIt); // Remove the old gap before insertion
    }
  }
}

// Removes a barrel from its group and updates data structures
void removeBarrel(int x) {
  int grp = getGroup(x);
  auto it = groups[grp].find(x); // Find the element to be removed
  if (it == groups[grp].end()) // If not found, do nothing
    return;

  // Remove gap with preceding element
  if (it != groups[grp].begin()) {
    auto prevIt = it;
    prevIt--; // Previous element iterator
    auto gapIt = gaps[grp].find(x - *prevIt);
    if (gapIt != gaps[grp].end())
      gaps[grp].erase(gapIt);
  }

  // Check next element for gap update
  auto nxtIt = it;
  nxtIt++; // Next iterator
  if (nxtIt != groups[grp].end()) {
    auto gapIt = gaps[grp].find(*nxtIt - x);
    if (gapIt != gaps[grp].end())
      gaps[grp].erase(gapIt);

    if (it != groups[grp].begin()) {
      auto prevIt = it;
      prevIt--; // Previous element
      gaps[grp].insert(*nxtIt - *prevIt); // Add new gap between next and previous
    }
  }

  groupSum[grp] -= x; // Decrease sum
  groups[grp].erase(it); // Remove the barrel from its group
}

// Determines if it's possible to identify the poisonous barrel with certainty
bool canIdentifyPoison() {
  int total = 0;
  for (int i = 0; i < NUM_GROUPS; i++) {
    total += groups[i].size();
  }

  if (total == 1) // If only one barrel, it must be the poison
    return true;

  int dupGroup = -1;
  // Find a group where there is at least one gap and that gap contains zero
  for (int i = NUM_GROUPS - 1; i >= 0; i--) {
    if (!groups[i].empty() && !gaps[i].empty() && (*gaps[i].begin() == 0)) {
      dupGroup = i;
      break;
    }
  }

  if (dupGroup == -1)
    return false;

  long long safeWater = 0;
  // Sum up group sums up to and including the identified duplicate group
  for (int i = 0; i <= dupGroup; i++) {
    safeWater += groupSum[i];
  }

  long long lastVal = 0, candidateSum = 0;
  int candidateCount = 0;

  // Process higher groups to determine merging capability
  for (int i = dupGroup + 1; i < NUM_GROUPS; i++) {
    if (!groups[i].empty()) {
      int minVal = *groups[i].begin();   // Minimum value in group
      bool mergeable = false;

      if (!gaps[i].empty()) {
        int minGap = *gaps[i].begin();
        if (safeWater >= minGap)
          mergeable = true;
      }

      if (safeWater + lastVal >= minVal)
        mergeable = true;

      if (mergeable) {
        // If a group can be merged with safe_water, merge it
        safeWater += candidateSum + groupSum[i];
        lastVal = 0;
        candidateSum = 0;
        candidateCount = 0;
      } else {
        // Otherwise accumulate this group into candidate set
        candidateCount += groups[i].size();
        lastVal = *groups[i].rbegin(); // Max value in group
        candidateSum += groupSum[i];   // Sum of values in group
      }
    }
  }

  return (candidateCount <= 1); // Can identify only one or zero candidates left
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;

  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    insertBarrel(x);
  }

  cout << (canIdentifyPoison() ? "Yes" : "No") << "\n";

  for (int i = 0; i < q; i++) {
    char op;
    int x;
    cin >> op >> x;

    if (op == '+') {
      insertBarrel(x);
    } else {
      removeBarrel(x);
    }

    cout << (canIdentifyPoison() ? "Yes" : "No") << "\n";
  }

  return 0;
}


// https://github.com/VaHiX/codeForces/
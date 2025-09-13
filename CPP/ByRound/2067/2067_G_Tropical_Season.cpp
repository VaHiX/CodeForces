/*
 * Problem URL : https://codeforces.com/problemset/problem/2067/G
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;

const int NUM_GROUPS = 20;

vector<multiset<int>> groups(NUM_GROUPS);
vector<multiset<int>> gaps(NUM_GROUPS);
vector<long long> groupSum(NUM_GROUPS, 0);

inline int getGroup(int x) { return 31 - __builtin_clz(x); }

void insertBarrel(int x) {
  int grp = getGroup(x);
  auto it = groups[grp].insert(x);
  groupSum[grp] += x;

  if (it != groups[grp].begin()) {
    auto prevIt = it;
    prevIt--;
    gaps[grp].insert(x - *prevIt);
  }
  auto nxtIt = it;
  nxtIt++;
  if (nxtIt != groups[grp].end()) {
    gaps[grp].insert(*nxtIt - x);
    if (it != groups[grp].begin()) {
      auto prevIt = it;
      prevIt--;
      auto gapIt = gaps[grp].find(*nxtIt - *prevIt);
      if (gapIt != gaps[grp].end())
        gaps[grp].erase(gapIt);
    }
  }
}

void removeBarrel(int x) {
  int grp = getGroup(x);
  auto it = groups[grp].find(x);
  if (it == groups[grp].end())
    return;

  if (it != groups[grp].begin()) {
    auto prevIt = it;
    prevIt--;
    auto gapIt = gaps[grp].find(x - *prevIt);
    if (gapIt != gaps[grp].end())
      gaps[grp].erase(gapIt);
  }
  auto nxtIt = it;
  nxtIt++;
  if (nxtIt != groups[grp].end()) {
    auto gapIt = gaps[grp].find(*nxtIt - x);
    if (gapIt != gaps[grp].end())
      gaps[grp].erase(gapIt);
    if (it != groups[grp].begin()) {
      auto prevIt = it;
      prevIt--;
      gaps[grp].insert(*nxtIt - *prevIt);
    }
  }
  groupSum[grp] -= x;
  groups[grp].erase(it);
}

bool canIdentifyPoison() {
  int total = 0;
  for (int i = 0; i < NUM_GROUPS; i++) {
    total += groups[i].size();
  }
  if (total == 1)
    return true;

  int dupGroup = -1;
  for (int i = NUM_GROUPS - 1; i >= 0; i--) {
    if (!groups[i].empty() && !gaps[i].empty() && (*gaps[i].begin() == 0)) {
      dupGroup = i;
      break;
    }
  }
  if (dupGroup == -1)
    return false;

  long long safeWater = 0;
  for (int i = 0; i <= dupGroup; i++) {
    safeWater += groupSum[i];
  }

  long long lastVal = 0, candidateSum = 0;
  int candidateCount = 0;
  for (int i = dupGroup + 1; i < NUM_GROUPS; i++) {
    if (!groups[i].empty()) {
      int minVal = *groups[i].begin();
      bool mergeable = false;
      if (!gaps[i].empty()) {
        int minGap = *gaps[i].begin();
        if (safeWater >= minGap)
          mergeable = true;
      }
      if (safeWater + lastVal >= minVal)
        mergeable = true;

      if (mergeable) {
        safeWater += candidateSum + groupSum[i];
        lastVal = 0;
        candidateSum = 0;
        candidateCount = 0;
      } else {
        candidateCount += groups[i].size();
        lastVal = *groups[i].rbegin();
        candidateSum += groupSum[i];
      }
    }
  }
  return (candidateCount <= 1);
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

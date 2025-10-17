/*
 * Problem URL : https://codeforces.com/contest/437/problem/B
 * Submit Date : 2025-09-13
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

long lowBit(long input) {
  long output = 1;
  while (input % 2 == 0) {
    input /= 2;
    output *= 2;
  }
  return output;
}

int main() {

  long sum, limit;
  std::cin >> sum >> limit;
  std::vector<std::pair<long, long>> bitVec(limit + 1);
  for (long p = 1; p <= limit; p++) {
    bitVec[p].first = lowBit(p);
    bitVec[p].second = p;
  }

  sort(bitVec.begin(), bitVec.end());

  long remaining(sum);
  bool possible(1);
  std::vector<long> numberVec;

  for (long p = limit; p > 0; p--) {
    if (bitVec[p].first <= remaining) {
      remaining -= bitVec[p].first;
      numberVec.push_back(bitVec[p].second);
    }
  }

  if (remaining > 0) {
    puts("-1");
  } else {
    printf("%ld\n", numberVec.size());
    for (long p = 0; p < numberVec.size(); p++) {
      printf("%ld ", numberVec[p]);
    };
    puts("");
  }

  return 0;
}

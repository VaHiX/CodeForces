/*
 * Problem URL : https://codeforces.com/contest/367/problem/A
 * Submit Date : 2025-09-05
 */



#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

int main() {

  std::string input;
  getline(std::cin, input);
  std::vector<std::vector<long>> counts(1 + input.size(),
                                        std::vector<long>(3, 0));
  for (long p = 1; p <= input.size(); p++) {
    for (long q = 0; q < 3; q++) {
      counts[p][q] = counts[p - 1][q] + (input[p - 1] == 'x' + q);
    }
  }

  long m(0);
  scanf("%ld", &m);
  while (m--) {
    long start(0), end(0);
    scanf("%ld %ld", &start, &end);
    std::vector<long> dist(3);
    for (int q = 0; q < 3; q++) {
      dist[q] = counts[end][q] - counts[start - 1][q];
    }
    sort(dist.begin(), dist.end());

    if (end - start + 1 < 3 || dist[2] - dist[0] <= 1) {
      puts("YES");
    } else {
      puts("NO");
    }
  }
  return 0;
}

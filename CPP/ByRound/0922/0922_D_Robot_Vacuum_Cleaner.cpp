// Problem: CF 922 D - Robot Vacuum Cleaner
// https://codeforces.com/contest/922/problem/D

/*
Algorithm: Greedy sorting and counting
Techniques: 
  - Preprocessing strings to count 's' and 'h'
  - Sorting using custom comparator based on gain of placing one string before another
  - Computing final noise by processing concatenated strings

Time Complexity: O(n * m + n * log(n) + n * m)
  - O(n * m) for reading and preprocessing all strings
  - O(n * log(n)) for sorting
  - O(n * m) for computing the final noise

Space Complexity: O(n * m)
  - Storing the strings and their 's'/'h' counts
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

typedef long long ll;

struct snippet {
  std::string str;
  ll s, h;
};

// Custom comparator for sorting snippets
// Sorts based on the relative gain of placing A before B
bool snippetSort(snippet A, snippet B) { 
  return A.s * B.h > B.s * A.h; 
}

int main() {
  ll n;
  std::cin >> n;
  std::vector<snippet> v(n);
  
  // Read and preprocess each string
  for (ll p = 0; p < n; p++) {
    std::string x;
    std::cin >> x;
    ll a(0), b(0);
    for (ll p = 0; p < x.size(); p++) {
      a += (x[p] == 's');  // Count 's'
      b += (x[p] == 'h');  // Count 'h'
    }
    v[p].str = x;
    v[p].s = a;
    v[p].h = b;
  }
  
  // Sort the snippets according to custom comparator
  sort(v.begin(), v.end(), snippetSort);
  
  ll cnt(0), ss(0);
  // Compute noise by traversing the sorted snippets
  for (ll p = 0; p < n; p++) {
    for (ll u = 0; u < v[p].str.size(); u++) {
      if (v[p].str[u] == 's') {
        ++ss;  // Increment count of 's' seen so far
      } else {
        cnt += ss;  // Each 'h' contributes to noise equal to previous 's's
      }
    }
  }
  
  std::cout << cnt << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 1965 D - Missing Subarray Sum
// https://codeforces.com/contest/1965/problem/D

/*
Algorithm: 
This solution uses a combination of mathematical reasoning and careful computation of subarray sums to reconstruct a palindrome array from all but one subarray sum. The key insight is that in a palindrome array, many subarray sums will have specific properties:
- Subarrays symmetric around the center will have the same sum
- The sums of subarrays starting from the edges will help determine the values
- By analyzing odd/even occurrences of sums, we can identify which sum is missing

Techniques:
- Palindromic property exploitation
- Subarray sum calculation
- Set operations via sorting and difference
- Mathematical deduction to reconstruct array elements

Time Complexity: O(n^3 + n^2 log n)
- The most expensive operations are the nested loops for generating all subarray sums (O(n^3)) and sorting operations (O(n^2 log n))

Space Complexity: O(n^2)
- Storage for subarray sums and temporary arrays, where the maximum number of subarrays is O(n^2)

*/
#include <assert.h>
#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <vector>

#define mp make_pair
#define pb push_back
using namespace std;
using ll = long long int;
template <typename T> ostream &operator+(ostream &out, const vector<T> &vec) {
  for (const auto &x : vec) {
    out << x << " ";
  }
  out << "\n";
  return out;
}
template <typename T> ostream &operator*(ostream &out, const vector<T> &vec) {
  for (const auto &x : vec) {
    out + x;
  }
  return out;
}
template <typename T> istream &operator>>(istream &in, vector<T> &vec) {
  for (auto &x : vec) {
    in >> x;
  }
  return in;
}
void solve() {
  int n;
  cin >> n;
  int m = n * (n + 1) / 2 - 1;
  vector<int> s(m);
  cin >> s;
  sort(s.begin(), s.end());
  auto get_all_subarray_sum = [&](vector<int> v) {
    vector<int> s;
    for (int i = 0; i < v.size(); i++) {
      int sum = 0;
      for (int j = i; j < v.size(); j++) {
        sum += v[j];
        s.push_back(sum);
      }
    }
    return s;
  };
  auto gen_array = [&](vector<int> &middle_sums) {
    int len = middle_sums.size() * 2 - (n % 2);
    vector<int> a(len);
    a[(len - 1) / 2] = middle_sums[0] / (2 - n % 2);
    a[len / 2] = middle_sums[0] / (2 - n % 2);
    for (int i = 1; i < middle_sums.size(); i++) {
      a[(len / 2) + i] = (middle_sums[i] - middle_sums[i - 1]) / 2;
      a[(len - 1) / 2 - i] = (middle_sums[i] - middle_sums[i - 1]) / 2;
    }
    return a;
  };
  auto keep_odd_occurences = [&](vector<int> &sorted_v) {
    vector<int> v_odd;
    vector<int> &v = sorted_v;
    for (int i = 0; i < v.size(); i++) {
      if (v_odd.size() == 0) {
        v_odd.push_back(v[i]);
        continue;
      }
      if (v_odd.back() == v[i])
        v_odd.pop_back();
      else
        v_odd.push_back(v[i]);
    }
    return v_odd;
  };
  auto vector_sub = [&](vector<int> &sorted_a, vector<int> &sorted_b_subset_a) {
    vector<int> c;
    vector<int> &a = sorted_a;
    vector<int> &b = sorted_b_subset_a;
    while (b.size() > 0) {
      assert(a.size() > 0);
      if (a.back() == b.back()) {
        a.pop_back();
        b.pop_back();
      } else {
        c.push_back(a.back());
        a.pop_back();
      }
    }
    while (a.size() > 0) {
      c.push_back(a.back());
      a.pop_back();
    }
    return c;
  };
  auto find_and_erase = [](vector<int> v, int x) {
    auto it = find(v.begin(), v.end(), x);
    if (it != v.end())
      v.erase(it);
    return v;
  };
  vector<int> b = keep_odd_occurences(s);
  sort(b.begin(), b.end());
  assert(b.size() == (n + 1) / 2 - 1 || b.size() == (n + 1) / 2 + 1);
  if (b.size() == (n + 1) / 2 + 1) {
    int odds = 0;
    int evens = 0;
    for (int i = 0; i < b.size(); i++) {
      if (b[i] % 2 == 0)
        evens++;
      else
        odds++;
    }
    if (odds == 1) {
      auto it = find_if(b.begin(), b.end(), [](int x) { return x % 2 == 1; });
      b.erase(it);
    } else if (evens == 1) {
      auto it = find_if(b.begin(), b.end(), [](int x) { return x % 2 == 0; });
      b.erase(it);
    }
    if (odds == 1 || evens == 1) {
      cout + gen_array(b);
      return;
    }
  }
  if (b.size() == (n + 1) / 2 + 1) {
    vector<int> a_guess = gen_array(b);
    auto subarray_sum = get_all_subarray_sum(a_guess);
    sort(subarray_sum.begin(), subarray_sum.end());
    vector<int> b_c = vector_sub(subarray_sum, s);
    int rem = b.back() - 2 * (b.back() - b_c[0]);
    b = find_and_erase(b, rem);
    cout + gen_array(b);
  }
  if (b.size() == (n + 1) / 2 - 1) {
    if (s.back() > b.back()) {
      b.push_back(b.back() + 2 * (s.back() - b.back()));
      cout + gen_array(b);
      return;
    }
  }
  if (b.size() == (n + 1) / 2 - 1) {
    vector<int> a_guess = gen_array(b);
    auto subarray_sum = get_all_subarray_sum(a_guess);
    sort(subarray_sum.begin(), subarray_sum.end());
    vector<int> b_c = vector_sub(s, subarray_sum);
    int rem = b.back() - 2 * (b.back() - b_c[0]);
    b.push_back(rem);
    sort(b.begin(), b.end());
    cout + gen_array(b);
    return;
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/
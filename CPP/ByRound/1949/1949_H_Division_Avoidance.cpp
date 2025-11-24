// Problem: CF 1949 H - Division Avoidance
// https://codeforces.com/contest/1949/problem/H

/*
 * Problem: H. Division Avoidance
 * Algorithm: Greedy simulation with interval management
 * Time Complexity: O(N log N) per test case, where N is the number of forbidden cells
 * Space Complexity: O(N) per test case
 *
 * Approach:
 * - The organism starts at (0,0) and can only divide in specific ways
 * - Each division splits a cell (a,b) into (a+1,b) and (a,b+1)
 * - Forbidden cells block the organism from occupying them
 * - Key insight: we simulate the process and determine whether it's possible to keep the organism away from all forbidden cells
 * - We maintain intervals of valid y-coordinates for each x-coordinate
 * - We process forbidden cells and update intervals accordingly
 * - If we ever reach a contradiction (e.g., too many cells in a position), we return "NO"
 */

#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

using namespace std;
static struct FastInput {
  static constexpr int BUF_SIZE = 1 << 20;
  char buf[BUF_SIZE];
  size_t chars_read = 0;
  size_t buf_pos = 0;
  FILE *in = stdin;
  char cur = 0;
  inline char get_char() {
    if (buf_pos >= chars_read) {
      chars_read = fread(buf, 1, BUF_SIZE, in);
      buf_pos = 0;
      buf[0] = (chars_read == 0 ? -1 : buf[0]);
    }
    return cur = buf[buf_pos++];
  }
  inline void tie(std::nullptr_t) {}
  inline explicit operator bool() { return cur != -1; }
  inline static bool is_blank(char c) { return c <= ' '; }
  inline bool skip_blanks() {
    while (is_blank(cur) && cur != -1) {
      get_char();
    }
    return cur != -1;
  }
  inline FastInput &operator>>(char &c) {
    skip_blanks();
    c = cur;
    return *this;
  }
  inline FastInput &operator>>(string &s) {
    if (skip_blanks()) {
      s.clear();
      do {
        s += cur;
      } while (!is_blank(get_char()));
    }
    return *this;
  }
  template <typename T> inline FastInput &read_integer(T &n) {
    n = 0;
    if (skip_blanks()) {
      int sign = +1;
      if (cur == '-') {
        sign = -1;
        get_char();
      }
      do {
        n += n + (n << 3) + cur - '0';
      } while (!is_blank(get_char()));
      n *= sign;
    }
    return *this;
  }
  template <typename T>
  inline typename enable_if<is_integral<T>::value, FastInput &>::type
  operator>>(T &n) {
    return read_integer(n);
  }
#if !defined(_WIN32) || defined(_WIN64)
  inline FastInput &operator>>(__int128 &n) { return read_integer(n); }
#endif
  template <typename T>
  inline typename enable_if<is_floating_point<T>::value, FastInput &>::type
  operator>>(T &n) {
    n = 0;
    if (skip_blanks()) {
      string s;
      (*this) >> s;
      sscanf(s.c_str(), "%lf", &n);
    }
    return *this;
  }
} fast_input;
#define cin fast_input
int main() {
  using namespace std;
  ios_base::sync_with_stdio(false), cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;
    std::vector<std::pair<int, int>> cells(N);
    for (auto &[x, y] : cells)
      cin >> x >> y;
    auto solve = [&]() -> bool {
      std::sort(cells.begin(), cells.end());
      auto cell_it = cells.begin();
      std::vector<std::pair<std::pair<int, int>, int>> col;
      col.push_back({{0, 1}, 1});
      std::vector<std::pair<std::pair<int, int>, int>> ncol;
      for (int x = 0; true; x++) {
        if (col.empty()) {
          break;
          if (cell_it == cells.end())
            break;
          x = cell_it->first;
        }
        auto col_it = col.begin();
        ncol.clear();
        int vy = 0;
        for (int y = 0; true; y++) {
          if (vy == 0) {
            if (cell_it != cells.end() && cell_it->first == x) {
              int cell_y = cell_it->second;
              if (col_it != col.end() && col_it->first.first <= cell_y) {
                y = col_it->first.first;
              } else {
                y = cell_y;
              }
            } else if (col_it != col.end()) {
              y = col_it->first.first;
            } else {
              break;
            }
          }
          if (cell_it != cells.end() && cell_it->first == x &&
              cell_it->second == y) {
            vy++;
            ++cell_it;
          }
          if (col_it != col.end() && col_it->first.first == y) {
            if (col_it->second == 1) {
              int yhi = col_it->first.second;
              if (cell_it != cells.end() && cell_it->first == x &&
                  cell_it->second < yhi) {
                yhi = cell_it->second;
                col_it->first.first = yhi;
              } else {
                ++col_it;
              }
              assert(yhi > y);
              if (vy > 0) {
                if (vy == 1) {
                  if (vy == 1 && !ncol.empty() && ncol.back().second == vy &&
                      ncol.back().first.second == y) {
                    ncol.back().first.second = yhi;
                  } else {
                    ncol.push_back({{y, yhi}, vy});
                  }
                } else {
                  assert(vy >= 2);
                  if (vy >= 3)
                    return false;
                  if (yhi - y >= 3) {
                    return false;
                  }
                  for (int a = y; a < yhi; a++) {
                    ncol.push_back({{a, a + 1}, vy});
                  }
                }
              }
              y = yhi - 1;
              continue;
            } else {
              assert(col_it->first.second == y + 1);
              vy += col_it->second;
              ++col_it;
            }
          }
          assert(vy > 0);
          if (vy >= 4)
            return false;
          if (vy > 0) {
            vy--;
          }
          if (vy > 0) {
            if (vy == 1 && !ncol.empty() && ncol.back().second == vy &&
                ncol.back().first.second == y) {
              ncol.back().first.second = y + 1;
            } else {
              if (ncol.size() >= 2 && ncol.end()[-2].first.first == y - 2 &&
                  ncol.end()[-2].second >= 2 && ncol.end()[-1].second >= 2) {
                return false;
              }
              ncol.push_back({{y, y + 1}, vy});
            }
          }
        }
        std::swap(col, ncol);
      }
      return true;
    };
    bool ans = solve();
    cout << (ans ? "YES" : "NO") << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
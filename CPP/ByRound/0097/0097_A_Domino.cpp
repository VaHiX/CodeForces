/*
 * Problem URL : https://codeforces.com/problemset/problem/97/A
 * Submit Date : 2025-08-21
 */

#include <iostream>
#include <stdio.h>
#include <vector>
using ll = long long;
using namespace std;
const int D = 28, C = 31, E = 7, E2 = 2 * E;

int mapping(char k) {
  if (k >= 97)
    return k - 97;
  return k - 65 + 26;
}

int cn(int n, int k) {
  int res = 1, i;
  for (i = n - k + 1; i <= n; i++)
    res *= i;
  for (i = 1; i <= k; i++)
    res /= i;
  return res;
}

vector<vector<std::pair<int, int>>> squares(D);
vector<vector<int>> nr_square(D), squares_dominos(E2);
vector<int> undefined_squares;
string s[C];
int marked[C][C], square[C][C], assignment[C];
bool filled[C], validated[E2][E2];

int official_assignment[C], used[E];
int used_element[E2], last_valid[E2], counter[E];
int main() {
  int n, m, i, j, _x, _y;
  ll res = 0;
  cin >> n >> m;
  for (i = 0; i < n; i++)
    cin >> s[i];

  int last_square = 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      if (marked[i][j] == 0 && s[i][j] != '.') {
        for (_x = i; _x < i + 2; _x++) {
          for (_y = j; _y < j + 2; _y++) {
            marked[_x][_y] = 1;
            square[_x][_y] = last_square;
            squares[last_square].push_back({_x, _y});
          }
        }
        last_square++;
      }
    }
  }

  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      if (s[i][j] == '.')
        continue;
      nr_square[mapping(s[i][j])].push_back(square[i][j]);
    }
  }

  int assigned_elements = 0;
  for (i = 0; i < D; i++) {
    if (nr_square[i][0] == nr_square[i][1]) {
      assignment[nr_square[i][0]] = assigned_elements;
      filled[nr_square[i][0]] = true;
      assigned_elements++;
    } else
      squares_dominos[nr_square[i][1]].push_back(i);
    squares_dominos[nr_square[i][0]].push_back(i);
  }
  for (i = 0; i < E2; i++)
    official_assignment[i] = assignment[i];

  for (i = 0; i < D; i++) {
    if (filled[nr_square[i][0]] == true && filled[nr_square[i][1]] == true) {
      validated[assignment[nr_square[i][0]]][assignment[nr_square[i][1]]] =
          true;
      validated[assignment[nr_square[i][1]]][assignment[nr_square[i][0]]] =
          true;
    }
  }

  for (i = 0; i < E; i++)
    counter[i] = 2;
  for (i = 0; i < E2; i++) {
    if (filled[i] == 1)
      counter[assignment[i]]--;
    else
      undefined_squares.push_back(i);
  }

  int ln = undefined_squares.size();
  int is = 0, c1, c2, exterminated_square, to_remove;
  bool lypa = false;

  while (true) {
    if (is < ln) {
      exterminated_square = undefined_squares[is];
      // printf ("%d %d\n", is, exterminated_square);

      for (i = last_valid[is]; i < E; i++) {
        lypa = false;
        if (counter[i] > 0) {
          for (j = 0; j < E; j++)
            used[j] = 0;
          for (j = 0; j < squares_dominos[exterminated_square].size(); j++) {
            c1 = nr_square[squares_dominos[exterminated_square][j]][1],
            c2 = nr_square[squares_dominos[exterminated_square][j]][0];
            if (c1 == exterminated_square)
              c1 = c2, c2 = exterminated_square;
            if (filled[c1] && validated[assignment[c1]][i])
              lypa = true;
            if (filled[c1])
              used[assignment[c1]]++;
          }
          for (j = 0; j < E; j++) {
            if (used[j] > 1)
              lypa = true;
          }

          // Sprawdzić domino-poprawność - nie-validated -> validate
        } else
          lypa = true;

        if (lypa == false) {
          for (j = 0; j < squares_dominos[exterminated_square].size(); j++) {
            c1 = nr_square[squares_dominos[exterminated_square][j]][1],
            c2 = nr_square[squares_dominos[exterminated_square][j]][0];
            if (c1 == exterminated_square)
              c1 = c2, c2 = exterminated_square;
            if (filled[c1]) {
              validated[assignment[c1]][i] = true;
              validated[i][assignment[c1]] = true;
            }
          }

          used_element[is] = i;
          counter[i]--;
          last_valid[is] = i + 1;
          filled[exterminated_square] = true;
          assignment[exterminated_square] = i;

          is++;
          break;
        }
      }
    }

    if (is >= ln || i == E) {
      // Zdjąć domina ze square'a -> disvalidate
      if (is == ln) {
        res++;
        for (j = 0; j < ln; j++)
          official_assignment[undefined_squares[j]] =
              assignment[undefined_squares[j]];
      }

      if (is == 0)
        break;
      to_remove = undefined_squares[is - 1];
      counter[used_element[is - 1]]++;
      for (j = 0; j < squares_dominos[to_remove].size(); j++) {
        c1 = nr_square[squares_dominos[to_remove][j]][1],
        c2 = nr_square[squares_dominos[to_remove][j]][0];
        if (filled[c1] && filled[c2]) {
          validated[assignment[c2]][assignment[c1]] = false;
          validated[assignment[c1]][assignment[c2]] = false;
        }
      }
      filled[to_remove] = false;
      last_valid[is] = 0;

      is--;
    }
  }

  for (i = 1; i <= assigned_elements; i++)
    res *= i;
  res = res * cn(7, assigned_elements);
  printf("%lld\n", res);

  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      if (s[i][j] == '.')
        printf(".");
      else
        printf("%d", official_assignment[square[i][j]]);
    }
    printf("\n");
  }
  return 0;
}
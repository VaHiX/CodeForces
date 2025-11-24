// Problem: CF 1952 J - Help, what does it mean to be "Based"
// https://codeforces.com/contest/1952/problem/J

/*
 * Code Purpose: BasedInterpreter
 * 
 * This program interprets a "based" programming language that outputs
 * code snippets for different tasks based on the input integer x (1 to 4).
 * 
 * Algorithms/Techniques:
 *   - Task Selection: Simple if-else branching to select predefined code blocks
 *   - Code Generation: Outputs static code strings for different operations:
 *     1. Sum of two integers
 *     2. Absolute value computation
 *     3. Finding maximum element in array
 *     4. Finding k-th largest element in array using partial sorting
 * 
 * Time Complexity: O(1) - The selection of code blocks is constant time.
 * Space Complexity: O(1) - Only a fixed amount of memory is used for input/output.
 */

#include <iomanip>
#include <iostream>
#ifdef GUDEB
#define D(x) cerr << #x << ": " << (x) << '\n';
#define ifdeb if (true)
#else
#define D(x) ;
#define ifdeb if (false)
#endif
#define all(x) begin(x), end(x)
using namespace std;
using ull = unsigned long long;
using ll = long long;

void solve() {
  int x;
  cin >> x;
  if (x == 1) {
    cout << R"( yoink a
yoink b
*slaps a on top of b*
yeet b
go touch some grass
)";
  } else if (x == 2) {
    cout << R"(yoink a
bruh b is lowkey just 0
rip this b fell off by a
vibe check a ratios b
simp for 7
bruh a is lowkey just b
yeet a
go touch some grass
)";
  } else if (x == 3) {
    cout << R"(yoink n
yoink a
bruh m is lowkey just a[0]
bruh i is lowkey just 1
vibe check n ratios i
simp for 9
yeet m
go touch some grass
vibe check a[i] ratios m
bruh m is lowkey just a[i]
*slaps 1 on top of i*
simp for 5
)";
  } else {
    cout << R"(yoink n
yoink a
yoink k
rip this k fell off by 1
bruh i is lowkey just 0
vibe check n ratios i
simp for 10
yeet a[k]
go touch some grass
bruh j is lowkey just i
*slaps 1 on top of j*
vibe check n ratios j
simp for 16
*slaps 1 on top of i*
simp for 6
vibe check a[i] ratios a[j]
simp for 21
bruh t is lowkey just a[i]
bruh a[i] is lowkey just a[j]
bruh a[j] is lowkey just t
*slaps 1 on top of j*
simp for 12)";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << setprecision(20);
  solve();
}


// https://github.com/VaHiX/CodeForces/
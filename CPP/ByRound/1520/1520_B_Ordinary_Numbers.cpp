#include <iostream>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    long long int n, i, j, count = 0;
    cin >> n;
    for (i = 1; i <= n; i = i * 10 + 1) {
      for (j = 1; j <= 9; j++)
        if (i * j <= n)
          count++;
    }
    cout << count << endl;
  }
}
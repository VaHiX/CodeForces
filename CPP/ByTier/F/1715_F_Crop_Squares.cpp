// Problem: CF 1715 F - Crop Squares
// https://codeforces.com/contest/1715/problem/F

#include <iostream>
using namespace std;
int n, m;
long double x, y, s;
int main() {
  cin >> n >> m;
  // First query: vertical strip to determine y-coordinate of poisoned square
  // Polygon is a vertical strip from x=0 to x=n, with height slightly above m
  cout << "? " << n * 2 + 2 << "\n0 " << m + 1 << "\n";
  for (int i = 0; i < n; ++i)
    cout << i << " 0\n" << i + 1 << " " << m << "\n";
  cout << n << " " << m + 1 << endl;
  cin >> s;
  // Calculate y-coordinate using the formula derived from area intersection
  y = m * s - 0.5;
  
  // Second query: horizontal strip to determine x-coordinate of poisoned square
  // Polygon is a horizontal strip from y=0 to y=m, with width slightly above n
  cout << "? " << m * 2 + 2 << "\n" << n + 1 << " 0\n";
  for (int i = 0; i < m; ++i)
    cout << "0 " << i << "\n" << n << " " << i + 1 << "\n";
  cout << n + 1 << " " << m << endl;
  cin >> s;
  // Calculate x-coordinate using the formula derived from area intersection
  x = n * s - 0.5;
  
  // Output the found coordinates of the poisoned square
  cout << "! " << x << " " << y << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/
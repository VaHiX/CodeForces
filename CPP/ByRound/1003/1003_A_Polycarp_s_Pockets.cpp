// Problem: CF 1003 A - Polycarp's Pockets
// https://codeforces.com/contest/1003/problem/A

/*
Code Purpose:
This program determines the minimum number of pockets required to distribute coins such that no two coins with the same value are in the same pocket. 
The approach counts the frequency of each coin value and returns the maximum frequency, as that determines the minimum number of pockets needed.

Algorithms/Techniques:
- Frequency counting using an array to track occurrences of each coin value
- Single pass through input to update frequencies
- Maximum frequency determines minimum pockets needed

Time Complexity: O(n) where n is the number of coins
Space Complexity: O(1) since the array size is fixed (105) regardless of input size
*/
#include <iostream>
#include <algorithm>
#include <iostream>

using namespace std;
int a, p, b[105]; // 'a' stores current coin value, 'p' stores max frequency, 'b' tracks frequency of each coin value
int main() {
  cin >> a; // read number of coins (though not used in logic)
  while (cin >> a) // read each coin value until EOF
    p = max(p, ++b[a]); // increment frequency of current coin and update max frequency
  cout << p; // output the minimum number of pockets needed
}


// https://github.com/VaHiX/CodeForces/
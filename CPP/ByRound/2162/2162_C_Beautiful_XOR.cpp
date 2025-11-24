// Problem: CF 2162 C - Beautiful XOR
// https://codeforces.com/contest/2162/problem/C

#include <iostream>

using namespace std;

// Function to calculate the number of bits in the binary representation of n
int len(int n) {
  int l = 0;
  while (n > 0) {
    n >>= 1; // Right shift to count bits
    l++;
  }
  return l;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int a, b;
    cin >> a >> b;
    
    // If a equals b, no operations needed
    if (a == b) {
      cout << 0 << endl;
      continue;
    }
    
    // If the number of bits in a and b are equal
    if (len(a) == len(b)) {
      int x = a ^ b; // XOR gives the difference in bits
      cout << 1 << endl;
      cout << x << endl;
      continue;
    } 
    // If a has fewer bits than b, it's impossible to make a equal to b
    else if (len(a) < len(b)) {
      cout << -1 << endl;
      continue;
    } 
    // If a has more bits than b
    else {
      cout << 2 << endl;
      int x = a ^ b; // XOR to find difference
      int mask = 1;
      // Find the highest bit position in x
      while (mask <= x) {
        mask <<= 1; // Left shift to find the highest set bit
      }
      mask >>= 1; // Adjust mask to the correct bit position
      int y = x ^ mask; // Get the second operand
      cout << y << " " << mask << endl;
      continue;
    }
  }
}


// https://github.com/VaHiX/CodeForces/
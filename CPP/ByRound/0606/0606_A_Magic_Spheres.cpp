// Problem: CF 606 A - Magic Spheres
// https://codeforces.com/contest/606/problem/A

/*
Purpose: Determine if a magician can transform magic spheres to meet required numbers.
         Transformation rule: Two spheres of same color -> one sphere of any other color.

Algorithms/Techniques: Greedy approach with counting excess and deficit spheres.
                       For each color, calculate how many extra spheres we have (beshi) 
                       and how many we are short of (kom). 
                       The total excess must be sufficient to cover the deficit.

Time Complexity: O(1) - Only a constant number of operations.
Space Complexity: O(1) - Only a few integer variables used.
*/

#include <iostream>

using namespace std;
int main() {
  int a, b, c;       // Initial count of blue, violet, orange spheres
  int x, y, z;       // Required count of blue, violet, orange spheres
  int beshi = 0, kom = 0; // beshi: excess spheres that can be converted, kom: deficit spheres needed
  cin >> a >> b >> c;
  cin >> x >> y >> z;
  
  // Calculate excess or deficit for blue spheres
  if (a > x)
    beshi = beshi + (a - x) / 2;
  else
    kom = kom + x - a;
    
  // Calculate excess or deficit for violet spheres
  if (b > y)
    beshi = beshi + (b - y) / 2;
  else
    kom = kom + y - b;
    
  // Calculate excess or deficit for orange spheres
  if (c > z)
    beshi = beshi + (c - z) / 2;
  else
    kom = kom + z - c;
    
  // If we have enough excess spheres to cover deficits
  if (beshi >= kom)
    cout << "YES";
  else
    cout << "NO";
    
  return 0;
}


// https://github.com/VaHiX/CodeForces/
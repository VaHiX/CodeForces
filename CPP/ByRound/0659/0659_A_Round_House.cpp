// Problem: CF 659 A - Round House
// https://codeforces.com/contest/659/problem/A

/*
Code Purpose:
This program determines the entrance number where Vasya will end his walk around a round building.
The building has entrances numbered from 1 to n, and Vasya starts at entrance `a`. 
He walks `b` entrances in a specific direction (positive for clockwise, negative for counter-clockwise).
The solution uses modular arithmetic to handle the circular nature of the building.

Algorithms/Techniques:
- Modular arithmetic to simulate circular traversal
- Handling negative indices using additive modular inverse

Time Complexity: O(1)
Space Complexity: O(1)
*/

#import <iostream>
using namespace std;
int a, b, n;
int main() {
  cin >> n >> a >> b;
  cout << (100 * n + a + b - 1) % n + 1;  // Adjust for circular indexing and handle negatives
}


// https://github.com/VaHiX/CodeForces/
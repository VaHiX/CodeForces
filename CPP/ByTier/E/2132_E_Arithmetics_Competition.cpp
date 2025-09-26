// Problem: CF 2132 E - Arithmetics Competition
// https://codeforces.com/contest/2132/problem/E

/*
E. Arithmetics Competition
Algorithms/Techniques: Sorting, Prefix Sums, Ternary Search

Time Complexity: O((n + m) * log(max(n, m)) + q * log(max(n, m)))
Space Complexity: O(n + m)

This problem involves selecting cards from two arrays (Vadim's and Kostya's),
such that the total number of chosen cards equals a given value `z`, with
constraints on the maximum number of cards each person can pick (`x` and `y`).
We maximize the sum using ternary search over possible combinations.
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
const int MAX_N = 2e5 + 5;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  
  int testCases;
  cin >> testCases;
  while (testCases--) {
    int sizeA, sizeB, numQueries;
    cin >> sizeA >> sizeB >> numQueries;
    
    // Create vectors for arrays A and B with 1-based indexing
    vector<ll> arrayA(sizeA + 1), arrayB(sizeB + 1);
    
    // Read Vadim's cards
    for (int i = 1; i <= sizeA; i++)
      cin >> arrayA[i];
    
    // Sort Vadim's cards in descending order to get maximum values first
    sort(arrayA.begin() + 1, arrayA.end(), greater<ll>());
    
    // Read Kostya's cards
    for (int i = 1; i <= sizeB; i++)
      cin >> arrayB[i];
    
    // Sort Kostya's cards in descending order to get maximum values first
    sort(arrayB.begin() + 1, arrayB.end(), greater<ll>());
    
    // Compute prefix sums for both arrays to quickly calculate sum of top k elements
    for (int i = 1; i <= sizeA; i++)
      arrayA[i] += arrayA[i - 1];
    for (int i = 1; i <= sizeB; i++)
      arrayB[i] += arrayB[i - 1];
    
    // Process each query
    while (numQueries--) {
      int maxFromA, maxFromB, totalElements;
      cin >> maxFromA >> maxFromB >> totalElements;
      
      // If no cards need to be selected, the sum is 0
      if (totalElements == 0) {
        cout << "0\n";
        continue;
      }
      
      // Determine valid range of cards from array A.
      // We can choose at least `max(0, totalElements - maxFromB)` cards from A,
      // and at most `min(maxFromA, totalElements)` cards from A
      int low = max(0, totalElements - maxFromB);
      int high = min(maxFromA, totalElements);
      
      // Initialize maximum sum
      ll maxSum = 0;
      
      // Use ternary search to find the best number of elements from A to take
      while (high - low > 2) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;
        
        // Calculate sum for two midpoints in ternary search
        ll sum1 = arrayA[mid1] + arrayB[totalElements - mid1];
        ll sum2 = arrayA[mid2] + arrayB[totalElements - mid2];
        
        if (sum1 < sum2) {
          low = mid1 + 1;
        } else if (sum1 > sum2) {
          high = mid2 - 1;
        } else {
          low = mid1;
          high = mid2;
        }
      }
      
      // Final check for all values in the remaining range
      for (int i = low; i <= high; i++) {
        maxSum = max(maxSum, arrayA[i] + arrayB[totalElements - i]);
      }
      
      cout << maxSum << '\n';
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/
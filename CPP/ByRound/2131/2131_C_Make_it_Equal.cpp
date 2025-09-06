/**
 * Problem: CF2131C - Make it Equal
 * 
 * This program determines if two arrays can be made equal by performing operations
 * where each element can be increased or decreased by k any number of times.
 * 
 * Approach:
 * 1. For each element in both arrays, calculate the minimum number of operations needed
 *    to make it congruent to 0 modulo k (either by adding or subtracting multiples of k)
 * 2. Sort both arrays of remainders
 * 3. If the sorted arrays are identical, print "YES", otherwise print "NO"
 * 
 * Time Complexity: O(n log n) per test case (due to sorting)
 * Space Complexity: O(n) for storing the arrays
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * Determines if two arrays can be made equal by adding or subtracting multiples of k
 * @param n Number of elements in each array
 * @param k The modulo value for operations
 * @return true if arrays can be made equal, false otherwise
 */
bool can_make_equal(int n, long long k) {
    vector<long long> arr1(n), arr2(n);
    
    // Read and process first array
    for (int i = 0; i < n; ++i) {
        long long num;
        cin >> num;
        // Calculate minimum operations to make num ≡ 0 mod k
        arr1[i] = min(num % k, k - num % k);
    }
    
    // Read and process second array
    for (int i = 0; i < n; ++i) {
        long long num;
        cin >> num;
        // Calculate minimum operations to make num ≡ 0 mod k
        arr2[i] = min(num % k, k - num % k);
    }
    
    // Sort both arrays for comparison
    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());
    
    // Arrays can be made equal if their sorted remainders match
    return arr1 == arr2;
}

void solve() {
    int n;
    long long k;
    cin >> n >> k;
    
    if (can_make_equal(n, k)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    // Optimize I/O operations
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int test_cases;
    cin >> test_cases;
    
    while (test_cases--) {
        solve();
    }
    
    return 0;
}

// Problem: CF 1915 C - Can I Square?
// https://codeforces.com/contest/1915/problem/C

/*
C. Can I Square?
Purpose: Determine if all wooden squares from given buckets can be arranged to form a perfect square.
Approach:
- Sum all squares from buckets.
- Check if the total sum is a perfect square.
Time Complexity: O(1) per test case (constant time after precomputed prefix sums or direct computation).
Space Complexity: O(1) additional space.

Algorithms/Techniques:
- Mathematical check for perfect square using sqrt function.
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <cmath> // Required for sqrt
#define whatis(x) cerr << #x << " is " << x << endl;
using ll = long long;
using namespace std;

void solve() {
    ll n;
    cin >> n;
    ll sum = 0;
    for (ll i = 0; i < n; ++i) {
        ll a;
        cin >> a;
        sum += a;
    }
    
    // Compute square root of the total number of squares
    ll sqrt_sum = sqrt(sum);
    
    // Check if it's a perfect square by squaring back and comparing
    if (sqrt_sum * sqrt_sum == sum) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}


// https://github.com/VaHiX/codeForces/
/**
 * Problem: CF2131F - Unjust Binary Life
 * 
 * This program solves a problem involving binary strings A and B of length n.
 * It calculates the sum of minimum number of flips needed to make substrings equal
 * for all possible substrings of A and B when they are concatenated in a specific way.
 * 
 * Approach:
 * 1. Precompute prefix sums for both strings to count '0's and '1's efficiently
 * 2. Use a sliding window technique to calculate the minimum flips for each possible alignment
 * 3. Maintain running sums and counts to optimize the calculation
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing prefix sums and helper arrays
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MAX_N = 200005;
const int OFFSET = MAX_N;  // To handle negative indices

// Global arrays
int n;  // Length of strings A and B
char str_a[MAX_N], str_b[MAX_N];  // Input strings
int prefix_a[MAX_N][2];  // prefix_a[i][0] = count of '0's in A[1..i]
int prefix_b[MAX_N][2];  // prefix_b[i][0] = count of '0's in B[1..i]
int diff_count[MAX_N * 2];  // Count of differences at each position

/**
 * Solves a single test case
 */
void solve() {
    // Read input
    scanf("%d%s%s", &n, str_a + 1, str_b + 1);
    
    // Initialize prefix sums
    memset(prefix_a, 0, sizeof(prefix_a));
    memset(prefix_b, 0, sizeof(prefix_b));
    
    // Compute prefix sums for string A
    for (int i = 1; i <= n; i++) {
        int digit = str_a[i] - '0';
        prefix_a[i][digit] = prefix_a[i-1][digit] + 1;
        prefix_a[i][digit ^ 1] = prefix_a[i-1][digit ^ 1];
    }
    
    // Compute prefix sums for string B
    for (int i = 1; i <= n; i++) {
        int digit = str_b[i] - '0';
        prefix_b[i][digit] = prefix_b[i-1][digit] + 1;
        prefix_b[i][digit ^ 1] = prefix_b[i-1][digit ^ 1];
    }
    
    // Initialize difference count array
    memset(diff_count, 0, sizeof(diff_count));
    
    ll total_flips = 0;  // Total flips across all substrings
    ll current_sum = 0;   // Current sum of flips for the current window
    int balance = n;      // Current balance (centered at n to avoid negative indices)
    ll count_less = 0;    // Count of positions where 0s < 1s
    ll count_greater = 0;  // Count of positions where 0s > 1s
    
    // Process first window (A[1..i] + B[1..1])
    for (int i = 1; i <= n; i++) {
        int zeros = prefix_a[i][0] + prefix_b[1][0];
        int ones = prefix_a[i][1] + prefix_b[1][1];
        
        // Update difference count for current balance
        diff_count[balance]++;
        
        // Update counts and total flips based on comparison
        if (zeros < ones) {
            count_less++;
            total_flips += zeros;
        } else if (zeros > ones) {
            count_greater++;
            total_flips += ones;
        } else {
            total_flips += zeros;  // equal, can choose either
        }
    }
    
    current_sum = total_flips;
    
    // Slide the window across B
    for (int i = 2; i <= n; i++) {
        if (str_b[i] == '0') {
            // When moving to next position in B, update counts for balance
            count_greater += diff_count[balance];
            balance--;
            current_sum += count_less;
            count_less -= diff_count[balance];
        } else {
            // When moving to next position in B, update counts for balance
            count_less += diff_count[balance];
            balance++;
            current_sum += count_greater;
            count_greater -= diff_count[balance];
        }
        total_flips += current_sum;
    }
    
    printf("%lld\n", total_flips);
}

int main() {
    // Optimize I/O operations
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int test_cases;
    scanf("%d", &test_cases);
    
    while (test_cases--) {
        solve();
    }
    
    return 0;
}

/**
 * Problem: CF2131A - Lever
 * 
 * This program solves the Lever problem from Codeforces Round 809 (Div. 2).
 * The problem involves calculating the minimum number of operations needed
 * to balance a lever by adjusting weights on either side.
 * 
 * Approach:
 * 1. Read the number of test cases
 * 2. For each test case:
 *    - Read the number of weights (n)
 *    - Read the current weights (a) and target weights (b)
 *    - Calculate the total difference between current and target weights
 *    - The answer is the total difference + 1 (minimum operations needed)
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the weights
 */

#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Read number of test cases
    int num_test_cases;
    cin >> num_test_cases;
    
    while (num_test_cases--) {
        int num_weights;
        cin >> num_weights;
        
        // Vectors to store current and target weights with extra space
        vector<int> current_weights(num_weights + 10);
        vector<int> target_weights(num_weights + 10);
        
        // Read current weights
        for (int i = 1; i <= num_weights; i++) {
            cin >> current_weights[i];
        }
        
        // Read target weights and calculate total difference
        int total_difference = 0;
        for (int i = 1; i <= num_weights; i++) {
            cin >> target_weights[i];
            // Add the difference if current weight is greater than target
            total_difference += max(0, current_weights[i] - target_weights[i]);
        }
        
        // The minimum number of operations is total_difference + 1
        cout << total_difference + 1 << '\n';
    }
    
    return 0;
}
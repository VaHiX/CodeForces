// Problem: CF 2137 A - Collatz Conjecture
// https://codeforces.com/contest/2137/problem/A

/*
 * Problem: Collatz Conjecture
 * Algorithms/Techniques: Bit manipulation (left shift)
 * Time Complexity: O(1) - Each operation involves a fixed number of bits
 * Space Complexity: O(1) - Only using a constant amount of space
 *
 * The task is to find any possible initial value of x such that after k operations,
 * where each operation is either:
 *   - if x is even: x = x / 2
 *   - if x is odd: x = 3*x + 1
 * the final value becomes the given x.
 *
 * Key observation:
 *   If we reverse the process from a final value, it's easier to compute:
 *   - If current value is even, reverse operation gives us left shift (multiply by 2)
 *   - If current value is odd, reverse operation is more complex but not needed in this simplified version
 *
 * However, looking at test cases, pattern indicates simple bit manipulation:
 * For k steps and final x, the original value can be (x << k). This works because
 * each step doubles the number (left shift by 1) if it was even.
 *
 * Example:
 *   Input: k=5, x=4 => Output: 21 (which is 4*3 + 1 = 13 ... no, incorrect interpretation)
 * 
 * Actually, in this variant of the problem, we're told that there's always an answer,
 * and since operations can be reversed via bit manipulation, the solution:
 *   If x is odd, then x << k works for any even number pattern.
 * But looking more carefully at example:
 *   21 -> 64 -> 32 -> 16 -> 8 -> 4
 * We have to work backwards from final result and reverse operations:
 *   Step 5: 4 is even => previous was 4*2 = 8
 *   Step 4: 8 is even => previous was 8*2 = 16
 *   etc.
 * However, for this specific task: given x and k, find one valid initial value,
 * using bit shifts may work under certain assumptions (especially in constraints).
 *
 * Simplified approach: assume the simplest pattern of doubling (i.e., when final value is even),
 * and left shift by k.
 */

#include <iostream>

using namespace std;

int main() {
  int t;
  cin >> t; // Read number of test cases
  while (t--) { // For each test case
    int k, x;
    cin >> k >> x; // Read k (number of steps) and final x (result after k steps)
    cout << (x << k) << endl; // Left shift x by k bits is equivalent to multiplying by 2^k
  }
}


// https://github.com/VaHiX/codeForces/
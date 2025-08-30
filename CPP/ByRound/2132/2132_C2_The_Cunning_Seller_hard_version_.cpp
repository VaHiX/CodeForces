/**
 * Problem: CF2132C2 - The Cunning Seller (Hard Version)
 * 
 * This program solves an advanced version of the problem where we need to find the maximum
 * possible sum of a number's ternary digits after performing exactly k operations. Each operation
 * allows converting a digit '2' to two '1's or a digit '1' to three '0's.
 * 
 * Approach:
 * 1. Precompute the value coefficients for each digit position
 * 2. Convert the number to its ternary representation
 * 3. Distribute the operations to maximize the sum
 * 4. Calculate the final sum using the precomputed coefficients
 * 
 * Time Complexity: O(T * (log₃(n) + 25)) per test case
 *   - T: Number of test cases
 *   - log₃(n): For converting number to base-3
 *   - 25: For processing each digit position (constant time)
 * 
 * Space Complexity: O(1)
 *   - Uses fixed-size arrays regardless of input size
 */

 #include <bits/stdc++.h>
 using namespace std;
 using ll = long long;
 
 const int MAX_DIGITS = 25;
 const int MOD = 1'000'000'007;
 
 // Precompute the value coefficients for each digit position
 vector<ll> precomputeCoefficients() {
	 vector<ll> coefficients(MAX_DIGITS);
	 ll powerOfThree = 3;  // 3^1
	 
	 for (int i = 0; i < MAX_DIGITS; i++) {
		 // The coefficient for digit at position i: 3^(i+1) + (i+1) * 3^(i-1)
		 coefficients[i] = powerOfThree + (i * powerOfThree / 3);
		 powerOfThree *= 3;
	 }
	 return coefficients;
 }
 
 void solve() {
	 ll number, operations;
	 cin >> number >> operations;
	 
	 vector<ll> coefficients = precomputeCoefficients();
	 vector<int> ternaryDigits(MAX_DIGITS, 0);
	 
	 // Convert number to base-3 and count total digits
	 int totalDigits = 0;
	 for (int i = 0; number > 0; i++) {
		 ternaryDigits[i] = number % 3;
		 operations -= ternaryDigits[i];  // Each digit requires at least one operation
		 number /= 3;
		 totalDigits = i + 1;
	 }
	 
	 // If we don't have enough operations, it's impossible
	 if (operations < 0) {
		 cout << "-1\n";
		 return;
	 }
	 
	 // Distribute operations to maximize the sum
	 // Process from highest to lowest digit
	 for (int i = MAX_DIGITS - 1; i > 0 && operations > 0; i--) {
		 // Calculate how many operations we can perform on this digit
		 // Each operation on digit i can be converted to 3 operations on digit i-1
		 int possibleOperations = min(operations / 2, ternaryDigits[i]);
		 ternaryDigits[i] -= possibleOperations;
		 ternaryDigits[i - 1] += possibleOperations * 3;
		 operations -= possibleOperations * 2;
	 }
	 
	 // Calculate the final sum
	 ll result = 0;
	 for (int i = 0; i < MAX_DIGITS; i++) {
		 result += coefficients[i] * ternaryDigits[i];
	 }
	 
	 cout << result % MOD << "\n";
 }
 
 int main() {
	 // Optimize I/O operations
	 ios::sync_with_stdio(false);
	 cin.tie(nullptr);
	 
	 int testCases;
	 cin >> testCases;
	 
	 while (testCases--) {
		 solve();
	 }
	 
	 return 0;
 }
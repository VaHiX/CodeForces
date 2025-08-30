/**
 * Problem: CF2132B - The Secret Number
 * 
 * This program finds all numbers 'x' such that when a digit '1' is inserted between
 * every digit of 'x', the resulting number is divisible by 'x'. For example, if x=123,
 * the resulting number would be 112131.
 * 
 * Approach:
 * 1. For a given n, find all divisors x of n where x < n
 * 2. For each x, construct the number by inserting '1's between its digits
 * 3. Check if the constructed number is divisible by x
 * 
 * Time Complexity: O(T * (√n + k log n))
 *   - T: Number of test cases
 *   - √n: For finding all divisors of n
 *   - k log n: For processing each divisor (k is the number of divisors)
 * 
 * Space Complexity: O(k)
 *   - k: Number of valid divisors (stored in the result array)
 */

 #include <cstdio>
 #include <vector>
 #include <algorithm>
 using namespace std;
 
 const int MAX_RESULTS = 10010;
 
 // Find all valid numbers x where inserting '1's between digits of x divides n
 vector<long long> findValidNumbers(long long n) {
	 vector<long long> results;
	 
	 // Check all possible x that divide n (x < n)
	 for (long long x = 1; x < n; x++) {
		 if (n % x == 0) {
			 // Construct the number with '1's inserted between digits
			 long long num = 0;
			 long long temp = x;
			 long long multiplier = 1;
			 
			 while (temp > 0) {
				 int digit = temp % 10;
				 num = digit * multiplier + num;
				 multiplier *= 10;
				 if (temp >= 10) {
					 num = 1 * multiplier + num;
					 multiplier *= 10;
				 }
				 temp /= 10;
			 }
			 
			 // Check if the constructed number is divisible by x
			 if (num % x == 0) {
				 results.push_back(x);
			 }
		 }
	 }
	 
	 return results;
 }
 
 void solve() {
	 long long n;
	 scanf("%lld", &n);
	 
	 vector<long long> results = findValidNumbers(n);
	 int count = results.size();
	 
	 // Output the results
	 printf("%d\n", count);
	 for (int i = 0; i < count; i++) {
		 printf("%lld%c", results[i], (i == count - 1) ? '\n' : ' ');
	 }
 }
 
 int main() {
	 int testCases;
	 scanf("%d", &testCases);
	 
	 while (testCases--) {
		 solve();
	 }
	 
	 return 0;
 }
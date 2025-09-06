/**
 * Problem: CF2132E - Arithmetics Competition
 * 
 * This program solves a problem where we need to find the maximum sum of elements
 * by selecting a total of 'k' elements from two arrays 'a' and 'b' with constraints
 * on the maximum number of elements that can be taken from each array.
 * 
 * Approach:
 * 1. Sort both arrays in descending order
 * 2. Compute prefix sums for both arrays
 * 3. For each query, use ternary search to find the optimal split between the two arrays
 * 
 * Time Complexity: O(T * (n log n + m log m + q * log(min(x, z))))
 *   - T: Number of test cases
 *   - n: Size of array a
 *   - m: Size of array b
 *   - q: Number of queries
 *   - Sorting: O(n log n + m log m)
 *   - Each query: O(log(min(x, z))) using ternary search
 * 
 * Space Complexity: O(n + m)
 *   - Two prefix sum arrays of size n and m
 */

 #include <bits/stdc++.h>
 using namespace std;
 using ll = long long;
 
 const int MAX_N = 2e5 + 5;
 
 int main() {
	 // Optimize I/O operations
	 ios::sync_with_stdio(false);
	 cin.tie(nullptr);
	 cout.tie(nullptr);
 
	 int testCases;
	 cin >> testCases;
	 
	 while (testCases--) {
		 int sizeA, sizeB, numQueries;
		 cin >> sizeA >> sizeB >> numQueries;
		 
		 vector<ll> arrayA(sizeA + 1), arrayB(sizeB + 1);
		 
		 // Read and sort array A in descending order
		 for (int i = 1; i <= sizeA; i++) cin >> arrayA[i];
		 sort(arrayA.begin() + 1, arrayA.end(), greater<ll>());
		 
		 // Read and sort array B in descending order
		 for (int i = 1; i <= sizeB; i++) cin >> arrayB[i];
		 sort(arrayB.begin() + 1, arrayB.end(), greater<ll>());
		 
		 // Compute prefix sums
		 for (int i = 1; i <= sizeA; i++) arrayA[i] += arrayA[i - 1];
		 for (int i = 1; i <= sizeB; i++) arrayB[i] += arrayB[i - 1];
		 
		 // Process each query
		 while (numQueries--) {
			 int maxFromA, maxFromB, totalElements;
			 cin >> maxFromA >> maxFromB >> totalElements;
			 
			 // If no elements to choose, output 0
			 if (totalElements == 0) {
				 cout << "0\n";
				 continue;
			 }
			 
			 // Define search boundaries
			 int low = max(0, totalElements - maxFromB);
			 int high = min(maxFromA, totalElements);
			 ll maxSum = 0;
			 
			 // Ternary search to find optimal split
			 while (high - low > 2) {
				 int mid1 = low + (high - low) / 3;
				 int mid2 = high - (high - low) / 3;
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
			 
			 // Check remaining candidates
			 for (int i = low; i <= high; i++) {
				 maxSum = max(maxSum, arrayA[i] + arrayB[totalElements - i]);
			 }
			 
			 cout << maxSum << '\n';
		 }
	 }
	 
	 return 0;
 }
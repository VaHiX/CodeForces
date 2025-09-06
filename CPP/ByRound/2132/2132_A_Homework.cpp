/**
 * Problem: CF2132A - Homework
 * 
 * This program processes strings by appending or prepending characters from one string
 * to another based on a sequence of operations. The operations are specified by a third
 * string where 'V' means prepend and any other character means append.
 * 
 * Approach:
 * 1. Read the number of test cases
 * 2. For each test case:
 *    - Read the initial string and its length
 *    - Read the number of operations and the characters to add
 *    - Process each operation to build the result string
 *    - Output the final string
 * 
 * Time Complexity: O(T * m)
 *   - T: Number of test cases
 *   - m: Number of operations (length of string b)
 *   - Each operation takes O(1) time (amortized for string operations)
 * 
 * Space Complexity: O(n + m)
 *   - n: Length of the initial string
 *   - m: Number of operations (length of string b)
 */

 #include <bits/stdc++.h>
 using namespace std;
 
 void processTestCases() {
	 int numTestCases;
	 cin >> numTestCases;
	 
	 while (numTestCases--) {
		 int initialLength;
		 string initialString;
		 cin >> initialLength >> initialString;
		 
		 int numOperations;
		 string charactersToAdd, operations;
		 cin >> numOperations >> charactersToAdd >> operations;
		 
		 // Process each operation
		 for (int i = 0; i < numOperations; i++) {
			 if (operations[i] == 'V') {
				 // Prepend the character
				 initialString = charactersToAdd[i] + initialString;
			 } else {
				 // Append the character
				 initialString += charactersToAdd[i];
			 }
		 }
		 
		 cout << initialString << endl;
	 }
 }
 
 int main() {
	 // Optimize I/O operations
	 ios::sync_with_stdio(false);
	 cin.tie(nullptr);
	 
	 processTestCases();
	 return 0;
 }
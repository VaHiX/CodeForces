// Problem: CF 1095 A - Repeating Cipher
// https://codeforces.com/contest/1095/problem/A

/*
Purpose: Decrypts a string that was encrypted using the "repeating" cipher.
         The cipher works by writing the i-th character i times in sequence.
         This program reverses that process to recover the original string.

Algorithm:
1. Read the length of the encrypted string and the string itself.
2. Iterate through the encrypted string, identifying where each original character begins.
3. For each character in the original string, we determine its position by:
   - Computing the cumulative length of previous characters.
   - The k-th character is located at position k*(k+1)/2 in the encrypted string.
4. Extract and print each original character by taking the character at the correct index.

Time Complexity: O(n^2) - nested loop to compute positions.
Space Complexity: O(n) - for storing the encrypted string.

*/

#include <cstdio>

int c, i, n;
char w[56];
int main() {
  for (scanf("%d%s", &n, w); c + i < n;)  // Loop until all characters processed
    putchar(w[c = i++ * i / 2]);  // Compute index of current character and print it
}


// https://github.com/VaHiX/CodeForces/
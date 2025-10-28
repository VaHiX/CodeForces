// Problem: CF 1095 A - Repeating Cipher
// https://codeforces.com/contest/1095/problem/A

/*
Repeating Cipher Decryption
Algorithm: Reverses the repeating cipher encryption process.
The encryption writes:
- 1st char once,
- 2nd char twice,
- 3rd char thrice,
- and so on...

To decrypt:
- We iterate through the encrypted string
- For each position, we determine which original character it corresponds to
- This is done by tracking cumulative counts: i=1 (1 char), i=2 (1+2=3 chars), i=3 (1+2+3=6 chars), etc.
- When cumulative length (c+i) reaches or exceeds the current position, that means we are at a character from the original string

Time Complexity: O(n^2)
Space Complexity: O(1)

*/

#include <stdio.h>

int c, i, n;        // c: cumulative count, i: loop counter, n: length of input string
char w[56];         // w: input encrypted string

int main() {
  for (scanf("%d%s", &n, w); c + i < n;)    // Read n and w, loop while cumulative count + i < n
    putchar(w[c = i++ * i / 2]);            // Determine position in original string using arithmetic progression formula
}


// https://github.com/VaHiX/codeForces/
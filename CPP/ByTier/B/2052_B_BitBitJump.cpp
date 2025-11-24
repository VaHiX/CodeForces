// Problem: CF 2052 B - BitBitJump
// https://codeforces.com/contest/2052/problem/B

/*
BitBitJump
Algorithms/Techniques: Bit manipulation, instruction pointer simulation, bit comparison
Time complexity: O(1) - fixed size input (16 bits)
Space complexity: O(1) - fixed memory usage (4096 integers)

BitBitJump is a one instruction set computer. Thus, it has only one instruction: bbj a, b, c,
which copies an a-th bit of memory to the b-th bit of memory and then jumps to address c.
Let's consider a 16-bit BitBitJump computer. It has 2^16 bits of memory organized in 2^12 16-bit words.
Words are counted from 0, and bits in a word are counted from the least significant (0-th) bit to the most
significant (15-th) bit.
This computer has a single instruction pointer register (IP), and execution starts with IP = 0. If the
current IP ≥ 2^12 −2, the computer stops. Otherwise, it uses the IP-th word as a, the (IP+1)-th word
as b, the (IP+2)-th word as c, and performs the bbj a, b, c instruction: copies the (a&15)-th bit of
the (a >> 4)-th word to the (b&15)-th bit of the (b >> 4)-th word, and sets IP = c.
For example, the bbj 32, 35, 5 instruction placed at the memory start will be executed as follows:
1. a = 32 and b = 35 are read from the memory.
2. The 0-th bit of the 2-nd word (its value is 5&1 = 1) will be copied to the 3-rd bit of the same word,
so the 2-nd word will have the value of 5+2^3 = 13.
3. Then c = 13 is read from memory, and IP is set to 13.
Let's call the (2^16 −1)-th word (2^16 −16...2^16 −1-th bits of memory) an IO-word. An x-comparator is
a program which checks whether the value of the IO-word is equal to x. It should stop after execution of
no more than 2^12 instructions, leaving the lowest bit of the IO-word equal to 1 if the original value of the
IO-word was equal to x, and 0 otherwise.
Write a program that generates an x-comparator for the given value of x.
Input
The input contains a single decimal integer x (0 ≤ x < 2^16) — the value for which to build the
x-comparator.
Output
The output should contain the x-comparator program dump. Dump consists of values for the first n words
of the memory (1 ≤ n ≤ 2^12−1). All other words, except the IO-word, are filled with zeroes.
For each of the n words, output its value as a four-character hexadecimal number. Values should be
delimited by space or new line characters.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>

using namespace std;
typedef long long ll;
const char chr[] = "0123456789abcdef";
const int I0 = 65520, ZERO = 256 << 4, ONE = 257 << 4, INF = 65535;
int program[4096];

int main() {
  int n;
  scanf("%d", &n);
  // Initialize memory words for zero and one values
  program[256] = 0, program[257] = 65535; // Words 256 and 257 are for constants

  // Construct instructions for comparing each bit of the input 
  for (int a = 0; a < 16; a++) {
    int Z = a * 16;
    // Set up instruction pattern: copy from a-th bit of word Z to bit 6 of same word, jump to Z+6
    program[Z] = I0 + a, program[Z + 1] = (Z + 6) * 16 + 2,
    program[Z + 2] = Z + 4;
    program[Z + 4] = 0, program[Z + 5] = 0, program[Z + 6] = Z + 8;
    program[Z + 8] = 0, program[Z + 9] = 0, program[Z + 10] = Z + 16;
    program[Z + 12] = ZERO, program[Z + 13] = I0, program[Z + 14] = INF;
    
    // Special case for the last bit - uses ONE instead of ZERO as the source
    if (a == 15) {
      program[Z + 8] = ONE, program[Z + 9] = I0, program[Z + 10] = INF;
    }
    
    // Swap instructions to reverse direction based on bit value from input
    int b = (n >> a) & 1;
    if (b)
      for (int c = Z + 8; c < Z + 12; c++)
        swap(program[c], program[c + 4]);
  }

  // Output first 301 words in hexadecimal format
  for (int i = 0; i <= 300; i++) {
    string s;
    int x = program[i];
    for (int turn = 0; turn < 4; turn++)
      s.push_back(chr[x & 15]), x >>= 4;
    reverse(s.begin(), s.end());
    cout << s << ' ';
  }
}


// https://github.com/VaHiX/codeForces/
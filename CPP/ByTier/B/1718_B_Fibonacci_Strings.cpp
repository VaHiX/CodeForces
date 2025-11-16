// Problem: CF 1718 B - Fibonacci Strings
// https://codeforces.com/contest/1718/problem/B

/*
Purpose: Determine if a string composed of given letter frequencies can be rearranged to form a Fibonacci string.
Approach:
- Precompute Fibonacci sequence up to a large enough limit (80 terms).
- For a given set of letter frequencies, check if their total sum equals some Fibonacci number.
- Then try to assign the largest remaining frequencies to blocks of sizes matching the Fibonacci sequence in reverse order.
- If all blocks can be filled accordingly without violating the Fibonacci structure, output "YES", otherwise "NO".

Algorithms/Techniques:
- Fibonacci sequence generation
- Greedy assignment of frequencies to Fibonacci block sizes
- Mathematical validation of rearrangement possibility

Time Complexity: O(k^2) per test case where k is the number of letters in the alphabet.
Space Complexity: O(1) - fixed-size arrays for Fibonacci sequence and other variables.
*/

#include <stdio.h>
#include <iosfwd>

using namespace std;
typedef long long ll;
ll f[80], sum, cur;
int n, a[105], num[105];

void sol() {
  scanf("%d", &n);
  int t = 0;
  cur = 0, sum = 0;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), sum += a[i]; // Read letter counts and compute total

  // Find the smallest Fibonacci number >= sum
  for (t = 0;; t++) {
    cur += f[t];
    if (cur >= sum)
      break;
  }

  // If total sum doesn't match a Fibonacci number, answer is NO
  if (cur != sum) {
    puts("NO");
    return;
  }

  int lst = -1; // Last used letter position
  // Process from largest Fibonacci number down to smallest
  for (t; ~t; t--) {
    int mx = -1, pos = -1;
    // Find the largest available count that is not the previously used letter
    for (int i = 1; i <= n; i++)
      if (a[i] > mx && i != lst)
        mx = a[i], pos = i;
    
    // If the largest available count is less than required Fibonacci block size, return NO
    if (mx < f[t]) {
      puts("NO");
      return;
    }
    
    // Subtract the block size from the selected letter's count
    a[pos] -= f[t];
    lst = pos; // Mark this letter as used
  }
  
  puts("YES");
}

int main() {
  f[0] = f[1] = 1;
  for (int i = 2; i < 80; i++)
    f[i] = f[i - 1] + f[i - 2]; // Generate Fibonacci sequence up to 80 terms
  
  int tc;
  scanf("%d", &tc);
  while (tc--)
    sol();
}


// https://github.com/VaHiX/CodeForces/
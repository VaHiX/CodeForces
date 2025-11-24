// Problem: CF 727 B - Bill Total Value
// https://codeforces.com/contest/727/problem/B

/*
Problem: B. Bill Total Value

Purpose:
This program processes a string representing a store bill where each purchase has a name and a price.
The task is to parse all purchases, sum their prices, and output the total in the same formatted style as input.

Algorithms/Techniques:
- String parsing with state tracking (digit, letter, dot)
- Decimal number construction using base 10 arithmetic
- Formatting with thousand separators (dots every 3 digits from right)
- Handling of cents with leading zero padding

Time Complexity: O(n), where n is the length of the input string.
Space Complexity: O(1), only a few variables are used regardless of input size.

*/

#include <cstdio>
#include <iostream>
#include <string>

typedef long long ll;
int main() {
  std::string s;
  std::cin >> s;
  ll total(0), x(0);
  long dot(-s.size()); // Tracks the position of last dot encountered
  for (long p = 0; p < s.size(); p++) {
    if ('a' <= s[p] && s[p] <= 'z') { // If character is a letter, it marks end of price
      if (p - dot > 3) { // If distance from last dot exceeds 3 digits, multiply by 100 (convert to cents)
        x *= 100;
      }
      total += x; // Add current price to total
      x = 0; // Reset for next price
      dot = -s.size(); // Reset the dot tracker
    } else if (s[p] == '.') { // If character is a dot, record its position
      dot = p;
    } else if ('0' <= s[p] && s[p] <= '9') { // If character is digit, build number
      x = 10 * x + (s[p] - '0');
    }
  }
  if (s.size() - dot > 3) { // Check final price for adjustment before adding to total
    x *= 100;
  }
  total += x; // Add final price to the total

  ll dollars = total / 100; // Convert total cents to dollars
  int cents = total % 100;  // Get remaining cents

  if (dollars == 1000) {
    printf("1.000"); // Special case for thousand dollars
  } else if (dollars == 1000000) {
    printf("1.000.000"); // Special case for million dollars
  } else if (dollars == 1000000000) {
    printf("1.000.000.000"); // Special case for billion dollars
  } else if (dollars > 1000000) { // Handle billions and millions
    printf("%lld.", dollars / 1000000);
    dollars %= 1000000;
    ll thousands = dollars / 1000;
    if (thousands < 100) {
      putchar('0');
    }
    if (thousands < 10) {
      putchar('0');
    }
    printf("%lld.", thousands);
    dollars %= 1000;
    if (dollars < 100) {
      putchar('0');
    }
    if (dollars < 10) {
      putchar('0');
    }
    printf("%lld", dollars);
  } else if (dollars > 1000) { // Handle thousands
    printf("%lld.", dollars / 1000);
    dollars %= 1000;
    if (dollars < 100) {
      putchar('0');
    }
    if (dollars < 10) {
      putchar('0');
    }
    printf("%lld", dollars);
  } else {
    printf("%lld", dollars); // Print plain value
  }

  if (cents > 0) { // If non-zero cents, print them
    putchar('.');
    if (cents < 10) {
      putchar('0'); // Add leading zero if needed
    }
    printf("%d\n", cents);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/
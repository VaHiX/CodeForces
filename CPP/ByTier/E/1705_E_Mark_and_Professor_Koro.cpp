// Problem: CF 1705 E - Mark and Professor Koro
// https://codeforces.com/contest/1705/problem/E

/*
Algorithm/Technique:
  - This code uses a bit manipulation technique with a specialized data
structure to efficiently manage counts of integers and perform operations to
maximize the final value on the board.
  - The approach is based on treating each number's count as a binary
representation in a segmented array (c[]).
  - When updating a number, the old value is removed and the new one is added.
  - The maximum number is computed by converting the highest set bit (in the
segmented representation) back to an integer.

Time Complexity: O((n + q) * log(max_value)) where n is the size of initial
sequence and q is number of queries. Space Complexity: O(log(max_value)) for the
bit-manipulation array (c[]), which is effectively constant since max_value is
bounded by 2*10^5.

The code uses a segmented bit array to maintain counts of elements. Each element
is represented as a series of bits (in groups of S=60 bits each).
*/

#include <stdio.h>

const int N = 2e5 + 7, S = 60; // S is the size of each segment (60 bits)
typedef long long ll;
ll c[5010]; // Segmented bit array to hold counts of numbers
int a[N], n, m, i, j,
    len; // a: original array, c: bit array, others are loop vars/indices

// Function to increment the count of a value x in the bit array (add operation)
void A(int x) {
  int a = x / S, b = x % S; // a is segment index, b is bit index within segment
  c[a] += (1LL << b);       // Add 1 at bit position b in segment a
  // Handle carry propagation if current segment overflows (more than 2^S
  // elements)
  while (c[a] & (1LL << S))
    c[a] ^= (1LL << S),
        c[++a]++; // Propagate carry to next segment and reduce current
  if (a > len)    // Update the maximum segment index used
    len = a;
}

// Function to decrement the count of a value x in the bit array (delete
// operation)
void D(int x) {
  int a = x / S;
  long long b = 1ll << x % S; // Bit to subtract
  // Handle borrow propagation if current segment doesn't have needed bit
  while (c[a] < b) {
    c[a] += (1LL << S) - b; // Add to current segment (borrow from next one)
    a++;                    // Move to next segment
    b = 1; // Reset b to 1 since next segment will be borrowed from
  }
  c[a] -= b; // Subtract the bit
  // Trim trailing zero segments
  while (c[len] == 0)
    len--;
}

// Function to get the maximum possible number (convert segmented bit
// representation to integer)
ll Q() {
  ll ans = len * S; // Start with segment * bits_per_segment
  ll nw = c[len];   // Get the highest segment
  while (nw)        // Count number of bits in the highest segment
    nw /= 2, ans++; // Count total bits to reconstruct number
  return ans - 1;   // Return the maximum number, adjusting for 0-based indexing
}

int main() {
  // Read input n and m
  for (scanf("%d%d", &n, &m), i = 1; i <= n; ++i)
    scanf("%d", a + i), A(a[i]); // Initialize with initial sequence values

  // Process queries
  for (; m--;) {
    scanf("%d%d", &i, &j); // Read k and l (index and new value)
    D(a[i]);               // Remove the old value from the bit array
    A(a[i] = j);           // Update array and add the new value
    printf("%lld\n", Q()); // Print the maximum value after this update
  }
}

// https://github.com/VaHiX/CodeForces/
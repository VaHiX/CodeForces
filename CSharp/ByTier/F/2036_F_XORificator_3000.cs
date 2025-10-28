// Problem: CF 2036 F - XORificator 3000
// https://codeforces.com/contest/2036/problem/F

// *********************************************************************************************************************
// Purpose: This program computes the XOR of all integers in a given range [l, r] that satisfy the condition
//          x ≢ k (mod 2^i). It uses a mathematical approach based on XOR prefix sums and modular arithmetic
//          to efficiently compute results even for large ranges up to 10^18.
//
// Algorithm: 
//   - Uses a helper function XorUpto(n) to compute XOR of all numbers from 0 to n in O(1).
//   - For each query [l, r, i, k], we compute:
//       1. The XOR of all numbers x in [l, r] such that x ≢ k (mod 2^i), 
//       2. This is done by considering how values map under modular arithmetic and shifting.
//   - Time Complexity: O(1) per query after preprocessing
//   - Space Complexity: O(1)
// *********************************************************************************************************************


using System;
class Program {
  // Function to compute XOR from 0 to n efficiently in O(1)
  static ulong XorUpto(ulong n) {
    switch (n % 4) {
    case 0:
      return n;
    case 1:
      return 1;
    case 2:
      return n + 1;
    default:
      return 0;
    }
  }

  static void Main() {
    int t = int.Parse(Console.ReadLine());
    for (int test = 0; test < t; test++) {
      var parts = Console.ReadLine().Split();
      ulong l = ulong.Parse(parts[0]);      // Start of range
      ulong r = ulong.Parse(parts[1]);      // End of range
      ulong i = ulong.Parse(parts[2]);      // Power of 2 used in modulo operation (2^i)
      ulong k = ulong.Parse(parts[3]);      // Value for modular comparison

      ulong step = 1UL << (int)i;           // Step size is 2^i

      // Compute start and end indices for the sequence of representatives
      ulong m_start = l > k ? (l - k + step - 1) / step : 0;    // First index in valid group
      ulong m_end = r >= k ? (r - k) / step : ulong.MaxValue;   // Last index in valid group

      ulong XOR_eq = 0;
      if (m_start <= m_end) {
        ulong count = m_end - m_start + 1;   // Number of valid groups
        ulong m_xor = XorUpto(m_end) ^ XorUpto(m_start - 1);  // XOR of indices
        ulong shifted = m_xor << (int)i;     // Shift left by i bits to get actual XOR of values
        if ((count & 1) == 1) {              // If odd count, XOR with k
          shifted ^= k;
        }
        XOR_eq = shifted;
      }

      // XOR of all numbers in [l, r] using prefix XOR
      ulong XOR_all = XorUpto(r) ^ XorUpto(l - 1);
      
      // Final answer: XOR of all elements minus XOR of elements that satisfy condition
      ulong ans = XOR_all ^ XOR_eq;
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/
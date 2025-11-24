// Problem: CF 1046 F - Splitting money
// https://codeforces.com/contest/1046/problem/F

/*
 * Problem: F. Splitting money
 * Purpose: Calculate the minimum fee Alice needs to pay to split her bitcoins
 *          across multiple addresses such that no address has more than x satoshis.
 *          Each transaction costs f satoshis and is paid from the address being transacted from.
 *          
 * Algorithm:
 *   - For each address with a[i] satoshis, determine how many transactions are necessary
 *     to reduce it to at most x satoshis.
 *   - A transaction can move at most x satoshis from one address (as the transferred amount
 *     gets added to the receiving address, so effectively the sending address can hold up to x).
 *   - The number of moves needed from an address with a[i] satoshis is:
 *     ceil(a[i] / x), but since we pay fee per transaction, and each transaction moves enough
 *     to reduce the sender's satoshi count to at most x, we compute:
 *     ceil((a[i] - x) / (x - f)) = ((a[i] - x) + (x - f - 1)) / (x - f) = (a[i] - f - 1) / (x - f)
 *     However, if a[i] <= x, no transaction is needed.
 *   - A simpler approach considers how many "units" of capacity (x - f) we can fit:
 *     The number of transactions is (a[i] - 1) / (x - f) if a[i] > x, otherwise 0.
 *   - But the expression given in code can also be interpreted as:
 *     ((a[p] + f - 1) / (x + f)), which is effectively a way to simulate how many times
 *     one must split, assuming a new address can take up to x.
 *   - Since f < x, the formula computes the number of transactions required for a single address.
 * 
 * Time Complexity: O(N) - single pass through the input
 * Space Complexity: O(N) - to store the array of addresses
 * 
 * Techniques:
 *   - Ceiling division: (a + b - 1) / b for positive integers
 *   - Vector usage for storing and processing address balances
 *   - Integer arithmetic to avoid floating point operations
*/

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  long n;
  scanf("%ld", &n); // Read number of addresses
  std::vector<ll> a(n); // Create vector to hold satoshi counts
  for (long p = 0; p < n; p++) {
    scanf("%lld", &a[p]); // Read the satoshi count for each address
  }
  ll x, f;
  scanf("%lld %lld", &x, &f); // Read max satoshi per address (x) and fee per transaction (f)
  ll fee(0); // Initialize total fee variable
  for (long p = 0; p < n; p++) {
    // For each address, calculate how many transactions are needed
    // and add corresponding fee (f * number of transactions)
    fee += f * ((a[p] + f - 1) / (x + f)); // Expression for number of transactions needed
  }
  printf("%lld\n", fee); // Output the total fee
  return 0;
}


// https://github.com/VaHiX/CodeForces/
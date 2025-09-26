// Problem: CF 2125 E - Sets of Complementary Sums
// https://codeforces.com/contest/2125/problem/E

/*
E. Sets of Complementary Sums

Algorithm: Dynamic Programming + Mathematical Insight

The problem asks to count the number of distinct sets of complementary sums, where each set:
- Contains exactly n elements,
- Each element is in [1, x],
- The set Q = {s - a_i | 1 <= i <= m} where s is sum of array a.

Key insight: Any such set Q corresponds to an integer partition with specific constraints.
We define s as the total sum of some array, and for each element a_i in that array:
    s - a_i is an element in the complementary set.

This means for any subset S of integers from 1 to x of size n, we can generate its complement set
by choosing elements s - a_i, where s is the total sum.
Thus, it's equivalent to finding valid ways to choose subsets such that all values are in [1,x] and there exists a valid partition of s.

We model it as: suppose we want to form a set Q of n elements from [1, x]. 
If we fix s = sum(a), then for each i,
    s - a[i] = q[i]
So:
    s = q[i] + a[i]
=> Sum over all i: n*s = sum(q) + sum(a)
But since s = sum(a), then:
    n*s = sum(q) + s
=> (n-1)*s = sum(q)

Hence, the sum of elements in set Q must satisfy:
sum(Q) = (n-1)*s / (n-1) if n > 1
=> sum(Q) = s

This implies we look at all possible sums s and count how many sets of size n,
with elements in [1,x], summing to a given s, form valid complementary sets.

We reformulate this using dynamic programming:
Let f[i] = number of ways to make a sum i using values from 1..(n-1) elements.
If the total sum of all elements is `t`, then we are counting subsets such that:
    elements in the subset range [1, x], and their pairwise difference with target s yields valid outputs in range [1,x].

We simplify approach: 
Given an n-element set Q = {q_1, ..., q_n}, where each q_i in [1, x],
The key observation is to realize that there exists a corresponding array a such that
    q_i = s - a_i => sum(q) = n*s - sum(a)
=> sum(q) = n*s - sum(a)
Thus if we fix s:
    sum(q) = n*s - sum(a)
=> sum(a) = n*s - sum(q)

And since each q_i is in [1, x], then sum(a) must be in [n, n*x] to allow each a_i in [1,x].

But given n values from {1,...,x}, we want to count valid complementary sets.
The approach uses DP on sums:
   Define f[i] = number of ways to achieve sum i using at most (n - 1) numbers from 1...n,
   considering the fact that complementing a set Q with total sum s means:
      for s = sum(Q), and elements in Q, we get Q = {s - a_1, ..., s - a_n}
      But also we have:
         each s = max(Q) + min(Q) or more precisely, we look to derive valid (s, set_of_Q)

So instead, think as follows:

If there's a valid complementary sum set Q={q1,...,qn} of n elements from 1..x,
then for each q_i there exists an a_i such that:
   s = q_i + a_i
=> s - q_i = a_i

So the minimum value in Q must be at least 1, and for large enough n, even a small s can give valid result.

Key simplification: For each possible sum s of the complement set (the actual elements of Q),
we compute all valid ways this can happen using DP.
But note the constraint on how many sets we count:
For n distinct elements q1,...,qn in [1,x]:
If the total sum S = q1 + ... + qn,
then for an array a with same number of elements having elements sum to s and q_i = s - a_i,
We are essentially finding the number of valid partitions.

A smarter idea:
We use DP on subsets, but also take into account that we are forming Q such that it results from an
underlying set a with known s (sum of a), so S (total sum of Q) satisfies: 
   S = n * s - sum(a) = 0 => since sum(a) = s.
Thus:
    S = (n - 1) * s

So we iterate over all valid s to calculate possible values for Q.

But in our current DP approach, we simplify:

Let t = x - (1 + 2 + ... + n - 1) = x - (n*(n-1)/2)

This means: if we require sum of elements to be at least t = x - (n*(n-1)/2),
then it's a valid solution, otherwise 0.

Now we compute f[i] = number of ways to achieve sum i.
With DP: 
   for each value v from 1 to n - 1:
       f[j] += f[j - v]

This counts ways to choose subset sums.

Finally, answer is computed as:
    answer = sum over i in [0, len]: (f[i] * (len - i + 1)) % MOD

Time Complexity: O(N*N) where N=max_x
Space Complexity: O(N)

*/

#include <iostream>

#define N 200086
#define fo(a, b, c, d) for (int a = b; a <= c; a += d)
#define ro(a, b, c, d) for (int a = b; a >= c; a -= d)
#define ll long long
#define MOD 998244353ll
using namespace std;
int f[N];

void work() {
  int n, x;
  cin >> n >> x;
  if (n == 1) {
    cout << x << endl; // Only 1-element sets are allowed, so all from 1..x
    return;
  } else if (n == 2) {
    // For n=2, we choose two elements s1,s2 in [1,x] such that there exists array a where s1 = s-a1, s2 = s-a2.
    // => s - a1 + s - a2 = sum of Q
    // => 2*s - (a1+a2) = sum(Q) = s => s = sum(Q)
    // => sum(Q) = sum of elements in Q must be at least n=2 and at most 2*x.
    cout << 1ll * x * (x - 1) / 2 % MOD << endl; // C(x,2)
    return;
  }
  if ((ll)n * (n + 1) / 2 - 1 > x) {
    cout << 0 << endl; // Not enough values to make valid set
    return;
  }

  int len = (x - (n * (n + 1) / 2 - 1)); /* Compute how many "extra" sums we have after fixing minimum sum of n distinct elements */
  fo(i, 0, len, 1) f[i] = 0; // Reset DP array
  f[0] = 1; // Base case: one way to make sum 0

  // Dynamic Programming step: f[j] += f[j - i]
  fo(i, 1, n - 1, 1) { // For each possible size up to n-1
    fo(j, i, len, 1) { f[j] = (f[j] + f[j - i]) % MOD; }
  }

  int ans = 0;
  // Final computation of answer based on contributions from all valid partial sums
  fo(i, 0, len, 1) { ans = (ans + 1ll * f[i] * (len - i + 1) % MOD) % MOD; }
  cout << ans << endl;
  return;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--)
    work();
  return 0;
}


// https://github.com/VaHiX/codeForces/
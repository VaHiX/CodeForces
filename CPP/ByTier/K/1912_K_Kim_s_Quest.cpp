// Problem: CF 1912 K - Kim's Quest
// https://codeforces.com/contest/1912/problem/K

/*
K. Kim's Quest
Algorithms/Techniques: Dynamic Programming with modular arithmetic
Time Complexity: O(n)
Space Complexity: O(1)

In the long-forgotten halls of Kombinatoria's ancient academy, a gifted mathematician named Kim is faced with an unusual challenge. They found an old sequence of integers, which is believed to be a cryptic message from the legendary Kombinatoria's Oracle, and Kim wants to decipher its hidden meaning.

Kim's mission is to find specific patterns within the sequence, known as Harmonious Subsequences. These are extraordinary subsequences where the sum of every three consecutive numbers is even, and each subsequence must be at least three numbers in length.

Given a sequence a_i (1≤i≤n) of length n, its subsequence of length m is equal to a_{b_1}, a_{b_2}, ..., a_{b_m} and is uniquely defined by a set of m indices b_j, such that 1 ≤ b_1 < b_2 < ... < b_m ≤ n. Subsequences given by different sets of indices b_j are considered different.

There's a twist in Kim's quest: the number of these Harmonious Subsequences could be overwhelming. To report the findings effectively, Kim must calculate the total number of these subsequences, presenting the answer as a remainder after dividing by the number 998244353.
*/
#include <stdio.h>
#include <iosfwd>

#define mod (998244353)
using namespace std;
int n, a[200005];
long long cnt[2][2], f[2], cnt1[2]; // cnt[i][j]: count of subsequences ending at position i with last two elements being j and j (mod 2), f: temporary counts, cnt1: count of each element seen so far
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    a[i] %= 2; // reduce elements to binary (0 or 1)
  }
  cnt1[a[1]]++; // initialize count of first element
  for (int i = 2; i <= n; i++) { // iterate from second to last element
    f[0] = f[1] = 0; // reset temporary counts
    
    if (a[i] == 1) {
      f[0] += cnt[1][0]; // accumulate subsequences ending with pair (1,0)
      f[1] += cnt[0][1]; // accumulate subsequences ending with pair (0,1)
    }
    
    if (a[i] == 0) {
      f[0] += cnt[0][0]; // accumulate subsequences ending with pair (0,0)
      f[1] += cnt[1][1]; // accumulate subsequences ending with pair (1,1)
    }
    
    // Update counts of new subsequences
    cnt[0][a[i]] += f[0];
    cnt[1][a[i]] += f[1];
    cnt[1][a[i]] += cnt1[1]; // add count of all previous elements that are 1 (these form valid 2-element combinations with current a[i])
    cnt[0][a[i]] += cnt1[0]; // add count of all previous elements that are 0
    
    cnt[0][a[i]] %= mod; // modular arithmetic for overflow
    cnt[1][a[i]] %= mod;
    
    cnt1[a[i]]++; // increment the count of current element
  }
  
  // Final result: total valid subsequences minus invalid ones, modulo 998244353
  printf("%lld", (cnt[0][0] + cnt[0][1] + cnt[1][0] + cnt[1][1] + mod -
                  ((long long)(n - 1) * n / 2) % mod) %
                     mod);
  return 0;
}


// https://github.com/VaHiX/codeForces/
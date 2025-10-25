// Problem: CF 2130 A - Submission is All You Need
// https://codeforces.com/contest/2130/problem/A

/*
Flowerbox:
Problem: Maximum Score from Multiset Operations

Description:
Given a multiset S of non-negative integers, we can perform two types of operations to maximize our score:
1. Select a subset S′ ⊆ S, add sum(S′) to the score, and remove S′ from S.
2. Select a subset S′ ⊆ S, add mex(S′) to the score, and remove S′ from S.

The goal is to find the maximum possible score.

Approach:
- We use a frequency count array of size 55 (since values are in range [0, 50]).
- For each number i in the multiset:
    - If we can form a subset with elements such that mex = i, then we can add i to the score.
    - Since we prioritize higher values for mex operations first, we handle counts strategically.
- Specifically:
    - We pair up as many 0s and 1s as possible to form sets with mex=2. Each pair contributes 2 to the score.
    - Then, any remaining 0s contribute 1 point each (as mex of a single 0 is 1).
    - For all other i > 1, we directly use them in sum operations contributing i * count(i) to the score.

Time Complexity: O(n + 55) = O(n), which simplifies to O(1) for fixed input size (n <= 50)
Space Complexity: O(1)

Algorithms/Techniques:
- Frequency counting
- Greedy approach with strategic pairing (for handling mex = 2 cases)
- Simple arithmetic operations based on value and frequency

*/

import java.util.*

fun solve(scanner: Scanner) {
    val n = scanner.nextLong()
    val S = LongArray(n.toInt()) { scanner.nextLong() }
    val freq = LongArray(55) { 0L }
    for (x in S) freq[x.toInt()]++  // Count frequency of each number
    var ans = 0L
    val cnt2 = minOf(freq[0], freq[1])  // Pair 0s and 1s to get mex=2, this contributes 2 * cnt2 to score
    ans += cnt2 * 2
    freq[0] -= cnt2  // Remove taken 0s
    freq[1] -= cnt2  // Remove taken 1s
    val cnt1 = freq[0]  // Remaining 0s contribute 1 each (mex becomes 1)
    ans += cnt1
    freq[0] = 0  // All 0s are now used up
    for (i in freq.indices) {
        if (freq[i] > 0) {
            ans += i * freq[i]  // Add all remaining values to score as sum contributions
        }
    }
    println(ans)
}

fun main() {
    val scanner = Scanner(System.`in`)
    val t = scanner.nextInt()
    repeat(t) {
        solve(scanner)
    }
}


// https://github.com/VaHiX/CodeForces/
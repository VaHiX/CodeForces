// Problem: CF 2151 A - Incremental Subarray
// https://codeforces.com/contest/2151/problem/A

/**
 * Code purpose: Given a pattern array `a` and a generated sequence `b` (where b is built by concatenating
 * subsequences [1], [1,2], ..., [1,2,...,n]), this program counts how many times the pattern `a`
 * appears as a subarray in `b`.
 *
 * Algorithm/Techniques: 
 * - Precompute the sequence `b` implicitly using mathematical insight.
 * - For each test case:
 *   1. Parse input values n and m.
 *   2. Read the pattern array `a`.
 *   3. Compute the number of occurrences by checking whether the given subarray can be at the end
 *      of the generated sequence (when it's a full range [1, ..., n]).
 * 
 * Time Complexity: O(m) per test case. The algorithm avoids actually generating or scanning
 *                  the full array `b`, instead analyzing properties of `a` and `n`.
 * Space Complexity: O(m) for storing input array `a`.
 */

fun main() {
    val cin = System.`in`.bufferedReader()
    val cout = System.out.bufferedWriter()
    repeat(cin.readLine().toInt()) {
        val (n, m) = cin.readLine().split(" ").map { it.toInt() }
        val a = cin.readLine().split(" ").map { it.toInt() }
        var ans = 1
        if (a[m-1] - a[0] + 1 == m) {
            // If the range from first to last element of pattern equals its length,
            // then it's a contiguous increasing subsequence that could have started anywhere
            // at the end of the sequence. Count how many such starting positions exist.
            ans = n - a[m-1] + 1
        }
        cout.write("${ans}\n")
    }
    cout.flush()
}


// https://github.com/VaHiX/CodeForces/
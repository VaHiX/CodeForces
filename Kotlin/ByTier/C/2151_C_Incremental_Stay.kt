// Problem: CF 2151 C - Incremental Stay
// https://codeforces.com/contest/2151/problem/C

/*
 * C. Incremental Stay
 *
 * Problem Description:
 * Given a sequence of 2n timestamps when sensors detected activity, determine the maximum total stay time
 * for visitors entering and exiting the museum, considering that at most k people can be inside
 * simultaneously for each k from 1 to n.
 *
 * Algorithms/Techniques:
 * - Greedy approach with preprocessing using dynamic programming techniques
 * - Efficiently compute optimal pairing of enter/exit times under capacity constraints
 *
 * Time Complexity: O(n log n) per test case due to sorting and linear passes
 * Space Complexity: O(n) for storing arrays and auxiliary data structures
 */

fun main() {
    val cin = System.`in`.bufferedReader()
    val cout = System.out.bufferedWriter()
    repeat(cin.readLine().toInt()) {
        val n = cin.readLine().toInt()
        val a = cin.readLine().split(" ").map { it.toLong() }
        val b = Array(n) { LongArray(2) }
        var l = n - 1
        var r = n
        while (l >= 0) {
            // Compute cost of pairing entry at l with exit at r
            b[l][0] = a[r] - a[l]
            // Compute cumulative benefit starting from l
            b[l][1] = a[l + 1] - a[l]
            if (l + 2 < n) b[l][1] += b[l + 2][1]
            if (r - 1 >= n) b[l][1] += a[r] - a[r - 1]
            l--
            r++
        }
        val ans = LongArray(n)
        // Initialize the first element with best possible gain
        ans[0] = b[0][1]
        var sum = 0L
        for (i in 1 until n) {
            // Add previous cost to running sum
            sum += b[i - 1][0]
            // Compute total stay time for current configuration
            ans[i] = sum + b[i][1]
        }
        cout.write("${ans.joinToString(" ")}\n")
    }
    cout.flush()
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 2117 E - Lost Soul
// https://codeforces.com/contest/2117/problem/E

/**
 * Problem: E. Lost Soul
 * 
 * Algorithm: Greedy with preprocessing
 * 
 * Approach:
 * - For each pair of arrays a and b, we want to maximize matches after operations.
 * - We can perform two types of operations:
 *   1. Set a[i] = b[i+1]
 *   2. Set b[i] = a[i+1]
 * - Optionally, we may remove one element from both arrays (at most once).
 * 
 * The function `f` computes the maximum number of matches possible using the following logic:
 * - If last elements match, return n.
 * - Otherwise, iterate backwards to find where best to stop and use a boolean array to track
 *   previously seen values to avoid redundant checks.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for the boolean array used during computation
 */
fun main() {
    val cin = System.`in`.bufferedReader()
    val cout = System.out.bufferedWriter()
    fun f(a: List<Int>, b: List<Int>): Int {
        val n = a.size
        if (a[n - 1] == b[n - 1]) return n // If last elements already match, no need to change
        val f = BooleanArray(n + 1) // Used to track which values have been seen
        for (i in n - 2 downTo 0) {
            if (a[i] == b[i]
                || (a[i] == a[i + 1] || b[i] == b[i + 1]) // Check if current elements or next ones are equal
                || f[a[i]] || f[b[i]] // Check if previously seen values are used to avoid conflicts
            ) {
                return i + 1 // Return the index where we can stop making changes to get maximum matches
            }
            f[a[i + 1]] = true // Mark next element of a as seen
            f[b[i + 1]] = true // Mark next element of b as seen
        }
        return 0
    }
    repeat(cin.readLine().toInt()) {
        val n = cin.readLine().toInt()
        val a = cin.readLine().split(" ").map { it.toInt() }
        val b = cin.readLine().split(" ").map { it.toInt() }
        cout.write("${f(a, b)}")
        cout.newLine()
    }
    cout.flush()
}


// https://github.com/VaHiX/CodeForces/
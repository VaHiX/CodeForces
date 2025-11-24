// Problem: CF 2107 F1 - Cycling (Easy Version)
// https://codeforces.com/contest/2107/problem/F1

/*
 * Problem: Cycling (Easy Version)
 * Algorithm: Dynamic Programming with greedy selection
 * Time Complexity: O(n^3) in worst case due to nested loops and inner search for minimum
 * Space Complexity: O(n) for the dp array and auxiliary arrays
 *
 * Description:
 * Leo wants to move from behind the last cyclist to in front of the first,
 * using two types of operations:
 * 1. Move ahead of a cyclist at cost a[i]
 * 2. Swap elements at positions i and j with cost (j - i)
 *
 * Approach:
 * The solution uses dynamic programming where dp[i] represents the minimum cost
 * to get in front of the first cyclist starting from position i.
 * For each i, we search for the minimum element in range [i, n) to determine
 * how far we can move ahead before needing another swap or move operation.
 * Then we simulate moving ahead step by step and update dp values accordingly.
 */

const val MOD = 1_000_000_007L

fun solve() {
    val n = readInt()
    val a = readLongs()
    var dp = LongArray(n + 1, { Long.MAX_VALUE }) // DP array to store min cost starting from index i
    
    for (i in n - 1 downTo 0) {
        var min_id = i
        var min_val = a[i].toLong()
        // Find the minimum value in subarray [i, n)
        for (j in i..<n) {
            if (a[j] < min_val) {
                min_id = j
                min_val = a[j].toLong()
            }
        }
        val len = min_id - i + 1 // Length of segment from i to min_id
        var cost = min_val * len + len - 1 // Initial cost for moving with min_val repeated 'len' times
        
        // For each position, update the dp[i] with minimum possible cost
        for (idx in min_id until n) {
            dp[i] =
                    minOf(
                            dp[i],
                            cost +
                                    if (idx == (n - 1)) {
                                        0 // If at last element, no further moves needed
                                    } else {
                                        dp[idx + 1] // Add future cost
                                    }
                    )
            cost += min_val + 2 // Increment cost as we simulate moving ahead more
        }
    }
    
    println(dp[0]) // Minimum cost to reach front of first cyclist
}

fun main() {
    val t = readInt()
    repeat(t) { solve() }
}

private fun readInt() = readln().toInt()
private fun readLong() = readln().toLong()
private fun readDouble() = readln().toDouble()
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
private fun readLongs() = readStrings().map { it.toLong() }
private fun readDoubles() = readStrings().map { it.toDouble() }


// https://github.com/VaHiX/CodeForces/
// Problem: CF 2124 F1 - Appending Permutations (Easy Version)
// https://codeforces.com/contest/2124/problem/F1

/*
 * Problem: F1. Appending Permutations (Easy Version)
 * Algorithm/Techniques: Dynamic Programming with State Compression and Transition Checking
 *
 * Time Complexity: O(n^4) per test case due to nested loops checking all valid transitions
 * Space Complexity: O(n^2) for DP table and auxiliary arrays
 */

val MOD = 998244353L

fun solve() {
    val (n, m) = readInts()
    // bad[i][x] marks if value x is forbidden at position i
    var bad = Array(n + 1) { Array(n + 1) { false } }
    repeat(m) {
        val (i, x) = readInts()
        bad[i][x] = true
    }
    
    // dp[i][state]: number of ways to form first i positions with 'state' representing
    // a pattern that ends at position i; state = 0 means no specific ending cycle pattern
    var dp = Array(n + 1) { Array(n + 1) { 0L } }
    dp[0][0] = 1
    
    for (i in 0 until n) {
        val max_rem_len = n - i
        
        // valid_transition[len][start_val]: whether a cycle of length `len` starting with value `start_val`
        // can be appended without violating restrictions
        var valid_transition = Array(max_rem_len + 1) { Array(max_rem_len + 1) { true } }
        
        for (len in 1..max_rem_len) {
            for (start_val in 1..len) {
                var cur = start_val
                // Check if this cycle violates any restriction
                for (idx in i + 1 ..< i + len + 1) {
                    if (bad[idx][cur] == true) {
                        valid_transition[len][start_val] = false
                        break
                    }
                    cur = cur + 1
                    if (cur > len) cur = 1
                }
            }
        }

        for (state in 0..n) {
            if (dp[i][state] == 0L) continue
            
            // Try appending cycles of various lengths and starting values
            for (len in 1..max_rem_len) {
                for (start_val in 1..len) {
                    if (valid_transition[len][start_val] == false) continue
                    
                    // Skip invalid transitions based on current state and cycle properties
                    if (state != 0 && len > state && start_val == len - (len - state) + 1) continue
                    
                    val new_state = if (start_val == 1) len else 0
                    dp[i + len][new_state] = (dp[i + len][new_state] + dp[i][state]) % MOD
                }
            }
        }
    }
    
    var ans = dp[n].fold(0L) { acc, value -> (acc + value) % MOD }
    println(ans)
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
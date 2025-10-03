// Problem: CF 2140 E1 - Prime Gaming (Easy Version)
// https://codeforces.com/contest/2140/problem/E1

/*
 * E1. Prime Gaming (Easy Version)
 * 
 * Problem Summary:
 * - We have `n` piles of stones, each with between 1 and m stones.
 * - There are k "good" indices that can be selected to remove a pile in the game.
 * - Alice goes first and tries to maximize the final pile size; Bob tries to minimize.
 * - The game ends when only one pile remains.
 * - Goal: Compute sum of final pile sizes over all valid configurations modulo 1e9+7.
 *
 * Techniques Used:
 * - Dynamic Programming with Memoization (Bitmask DP)
 * - Game Theory (Minimax, turn-based optimal play)
 * 
 * Time Complexity:
 * - O(2^n * n * k) per test case, where n <= 20. This is due to the exponential bitmask states,
 *   and for each state, we iterate over all good indices.
 *
 * Space Complexity:
 * - O(2^n * n * 2) = O(2^n * n) for DP table, plus some auxiliary space.
 */

const val MOD = (1e9 + 7).toInt()
data class Segment(val l: Int, val r: Int)

fun main() {
    val T = readLine()?.trim()?.toIntOrNull() ?: return
    repeat(T) {
        val nmLine = readLine()?.trim()?.split(" ") ?: return@repeat
        if (nmLine.size < 2) return@repeat
        val n = nmLine[0].toInt()
        val m = nmLine[1].toInt()
        val k = readLine()?.trim()?.toIntOrNull() ?: return@repeat
        val segLine = readLine()?.trim()?.split(" ") ?: return@repeat
        if (segLine.size < k) return@repeat
        
        // Preprocessing segments to mark where good indices are.
        val segments = Array(k) { i ->
            val l = segLine[i].toInt()
            Segment(l, l) 
        }
        
        // Special case when m=1, only one possible value per pile => result always 1
        if (m == 1) {
            println(1)
            return@repeat
        }

        // DP structure: dp[len][mask][turn] stores computed results
        // len: length of current array of piles
        // mask: bitmask of which piles remain (bit i is 1 if pile i+1 exists)
        // turn: 0 = Alice's turn, 1 = Bob's turn
        val dp = Array(n + 1) { len -> Array(1 shl len) { IntArray(2) { -1 } } }

        fun dfs(mask: Int, len: Int, turn: Int): Int {
            // Memoization check
            dp[len][mask][turn].let { if (it != -1) return it }
            
            // Base case: only one pile left
            if (len == 1) return if (mask and 1 != 0) 2 else 1

            val res = if (turn == 0) {
                // Alice's turn - try to maximize the outcome
                var best = 0
                for (seg in segments) if (seg.l <= len) {
                    val pos = seg.l - 1 // Convert to zero-based index
                    // Construct new mask by removing pile at position `pos`
                    val nm = (mask and ((1 shl pos) - 1)) or ((mask shr (pos + 1)) shl pos)
                    val valRes = dfs(nm, len - 1, 1)
                    if (valRes > best) best = valRes
                    if (best == 2) break // Early termination optimization
                }
                best
            } else {
                // Bob's turn - try to minimize the outcome
                var best = 3
                for (seg in segments) if (seg.l <= len) {
                    val pos = seg.l - 1 // Zero-based index
                    // Construct new mask by removing pile at position `pos`
                    val nm = (mask and ((1 shl pos) - 1)) or ((mask shr (pos + 1)) shl pos)
                    val valRes = dfs(nm, len - 1, 0)
                    if (valRes < best) best = valRes
                    if (best == 1) break // Early termination optimization
                }
                best
            }

            dp[len][mask][turn] = res
            return res
        }

        var ans = 0L
        
        // Iterate through all possible masks representing which piles remain
        repeat(1 shl n) { mask ->
            ans = (ans + dfs(mask, n, 0)) % MOD
        }
        
        println(ans)
    }
}


// https://github.com/VaHiX/codeForces/
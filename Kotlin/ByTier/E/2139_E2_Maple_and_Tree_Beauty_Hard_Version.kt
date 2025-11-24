// Problem: CF 2139 E2 - Maple and Tree Beauty (Hard Version)
// https://codeforces.com/contest/2139/problem/E2

/*
 * Problem: E2. Maple and Tree Beauty (Hard Version)
 * Purpose: Find maximum beauty of a tree where each vertex has a binary label,
 *          and beauty is the LCS of all leaf name strings.
 * Approach:
 *   - First compute depth for each node from root.
 *   - For leaves, find the minimum depth + 1 to get an upper bound on LCS.
 *   - Use dynamic programming with bitsets (shift-and-or optimization) to track
 *     valid combinations of labels that sum up to k and compute possible LCS lengths.
 *
 * Time Complexity: O(n * min(k, d) * log(k)), where d is max depth.
 * Space Complexity: O(k / 64), for the bitset DP array.
 */
import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer
import kotlin.math.*
fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val t = br.readLine().trim().toInt()
    val out = StringBuilder()
    repeat(t) {
        val st = StringTokenizer(br.readLine().trim())
        val n = st.nextToken().toInt()
        val k = st.nextToken().toInt()
        val parents = if (n > 1) br.readLine().trim().split(" ").map { it.toInt() - 1 } else emptyList()
        val children = Array(n) { mutableListOf<Int>() }
        for (i in parents.indices) children[parents[i]].add(i + 1)
        val depth = IntArray(n)
        for (i in 1 until n) {
            val p = parents[i - 1]
            depth[i] = depth[p] + 1
        }
        var minLen = Int.MAX_VALUE
        for (i in 0 until n) {
            if (children[i].isEmpty()) {
                minLen = min(minLen, depth[i] + 1)
            }
        }
        if (minLen == Int.MAX_VALUE) minLen = 0
        val s = IntArray(minLen)
        for (i in 0 until n) {
            val d = depth[i]
            if (d < minLen) s[d]++
        }
        if (k == 0) {
            out.append(minLen).append('\n')
            return@repeat
        }
        val W = 64
        val maxBits = k
        val words = (maxBits + W) / W
        val dp = LongArray(words) { 0L }
        dp[0] = 1L
        fun shiftAndOr(dpArr: LongArray, shift: Int, limitBits: Int) {
            if (shift == 0) return
            val wordShift = shift / W
            val bitShift = shift % W
            val newWords = LongArray(words)
            for (i in words - 1 downTo 0) {
                var v = 0L
                val srcIndex = i - wordShift
                if (srcIndex >= 0) {
                    v = dpArr[srcIndex] shl bitShift
                    if (bitShift != 0 && srcIndex - 1 >= 0) {
                        v = v or (dpArr[srcIndex - 1] ushr (W - bitShift))
                    }
                }
                newWords[i] = v
            }
            val maxBit = limitBits
            val lastWord = maxBit / W
            val bitsInLast = (maxBit % W) + 1
            if (lastWord < words) {
                val mask = if (bitsInLast == 64) -1L else (1L shl bitsInLast) - 1
                newWords[lastWord] = newWords[lastWord] and mask
                for (i in lastWord + 1 until words) newWords[i] = 0
            }
            for (i in 0 until words) dpArr[i] = dpArr[i] or newWords[i]
        }
        var total = 0
        var best = 0
        for (L in 1..minLen) {
            total += s[L - 1]
            val limit = min(total, k)
            shiftAndOr(dp, s[L - 1], limit)
            val lower = max(0, total + k - n)
            val upper = min(k, total)
            if (lower <= upper) {
                var ok = false
                for (x in lower..upper) {
                    val w = x / W
                    val b = x % W
                    if (w < words && (dp[w] and (1L shl b)) != 0L) {
                        ok = true
                        break
                    }
                }
                if (ok) best = L
            }
        }
        out.append(best).append('\n')
    }
    print(out.toString())
}


// https://github.com/VaHiX/codeForces/
// Problem: CF 2132 C2 - The Cunning Seller (hard version)
// https://codeforces.com/contest/2132/problem/C2

/*
 * Problem: C2. The Cunning Seller (hard version)
 *
 * Purpose:
 *   Given n watermelons to buy and at most k deals, find the minimum cost to buy exactly n watermelons.
 *   Each deal allows buying 3^x watermelons for 3^(x+1) + x*3^(x-1) coins.
 *   The buyer can only use up to k deals.
 *
 * Algorithms/Techniques:
 *   - Greedy approach with bit manipulation and precomputed powers of 3
 *   - Convert n into base-3 representation and simulate the process of "buying" using optimal deals
 *   - Use a greedy method to maximize the number of high-value deals (i.e., 3^x with larger x)
 *
 * Time Complexity:
 *   O(L * log(n)) where L = 60 is the maximum bit length needed for representing n in base-3.
 *   Since we process up to 60 bits and perform O(1) operations per step.
 *
 * Space Complexity:
 *   O(L) for storing precomputed powers of 3 and count array.
 */
import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer
import kotlin.math.min

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val tLine = br.readLine() ?: return
    var T = tLine.toInt()
    val L = 60
    val pw = ULongArray(L) // Precompute powers of 3 up to 60
    pw[0] = 1uL
    for (i in 1 until L) {
        pw[i] = pw[i - 1] * 3uL
    }
    val out = StringBuilder()
    repeat(T) {
        val st = StringTokenizer(br.readLine())
        val n = st.nextToken().toULong()
        val k = st.nextToken().toULong()
        if (k >= n) { // If deals allowed >= number needed, just take individual deals (3 coins each)
            out.append(3uL * n).append("\n")
            return@repeat
        }
        val cnt = ULongArray(L) // cnt[i] represents how many 3^i deals are active in current calculation
        cnt[0] = n
        var tot = n // total watermelons still to be bought
        var add = 0uL // additional coins needed due to strategic deal selection
        for (i in 0 until L - 1) {
            if (tot <= k) break // If remaining amount is covered by allowed deals, stop
            val g = cnt[i] / 3uL // How many full 3^i deals are left at this level?
            if (g == 0uL) continue // No more deals of this size
            val need = if (tot > k) tot - k else 0uL // How much over-k is there?
            val want = (need + 1uL) / 2uL // Target reduction needed for next level
            val use = min(g, want) // Select the minimal number of moves needed
            cnt[i] -= use * 3uL // Reduce count by consumed deals (in base-3)
            cnt[i + 1] += use // Increase next higher deal size count
            add += use * pw[i] // Add contribution to cost from these deals
            tot -= use * 2uL // Each 3^i deal gives 3^i watermelons but costs 2*3^i (net gain of 3^i)
        }
        if (tot > k) { // After exhausting all possible moves, if we still cannot reach target
            out.append("-1\n")
        } else {
            out.append(3uL * n + add).append("\n") // Total cost = base cost + smart selection
        }
    }
    print(out.toString())
}


// https://github.com/VaHiX/CodeForces/
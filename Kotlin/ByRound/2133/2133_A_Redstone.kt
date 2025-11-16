// Problem: CF 2133 A - Redstone?
// https://codeforces.com/contest/2133/problem/A

/*
 * Problem: Determine if gears can be arranged so that the last gear spins at 1 revolution per second.
 *
 * Algorithm/Technique: 
 * - Simulate the gear speed propagation using the formula: speed[i] = (teeth[i-1] / teeth[i]) * speed[i-1]
 * - For a valid arrangement, we need the final speed to be 1.
 * - Key insight:
 *   Let’s denote the sequence of teeth as [a1, a2, ..., an].
 *   Then the speeds are calculated as:
 *     Speed[0] = 1
 *     Speed[i] = (a[i-1]/a[i]) * Speed[i-1]
 *   After simplifying, we get that final speed = (a1/a2) * (a2/a3) * ... * (a[n-2]/a[n-1]) = a1/a[n-1].
 *   Therefore, for the last gear to have speed 1, we must have a1 == a[n-1].
 * - We only care about whether any arrangement works.
 * - If all gears have same number of teeth (i.e., max frequency >= 2), it is possible.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) due to map storage
 */

fun solve() {
    val n = readLine()!!.toInt()
    val arr = readLine()!!.split(" ").map {
        it.toInt()
    }
    val mp = mutableMapOf<Int, Int>()
    for (i in arr) {
        mp[i] = (mp[i] ?: 0) + 1  // Count frequency of each gear tooth count
    }
    val maxFreq = mp.values.maxOrNull() ?: 0  // Find maximum frequency
    if (maxFreq == 1) {
        println("NO")  // No gear appears more than once, so no valid arrangement exists
    } else {
        println("YES")  // At least one duplicate gear => valid arrangement possible
    }
}

fun main() {
    val t = readLine()!!.toInt()
    repeat(t) {
        solve()
    }
}


// https://github.com/VaHiX/codeForces/
// Problem: CF 2126 C - I Will Definitely Make It
// https://codeforces.com/contest/2126/problem/C

/*
 * Problem: C. I Will Definitely Make It
 *
 * Purpose:
 *   Determine whether it's possible to reach a tower with maximum height 
 *   from the starting tower k, using teleportation and water level rising over time.
 *
 * Algorithm:
 *   - Sort all tower heights to determine the order in which we can reach them.
 *   - Start from the initial tower (k-th element) with water level 1.
 *   - Process the sorted heights in ascending order. 
 *     For each height greater than current water level:
 *       - If it's too high to teleport to (water level + distance > height), set impossible.
 *       - Otherwise, update water level and time spent teleporting.
 *   - Time Complexity: O(n log n) due to sorting per test case.
 *   - Space Complexity: O(n) for storing sorted heights and inputs.
 *
 * Techniques:
 *   - Greedy approach
 *   - Sorting with careful handling of water level constraints
 */

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readStrings() = readLn().split(" ") 
private fun readInts() = readStrings().map { it.toInt() } 
private fun readLongs() = readStrings().map { it.toLong() } 
private fun printInts(a:List<Int>) = run { a.forEach() { print("$it ")}; println() }

private fun main() {
    val t = readInt()
    for (itt in 1..t) {
        val (n, k) = readInts()
        val h = readInts()
        var can = true
        var hh = h[k-1] // Current water level starts from the height of the initial tower.
        val hs = h.sorted() // Sort to process towers in ascending order of heights.
        var w = 1 // Water level starts at 1.
        for (i in 0 until n) {
            if (hs[i] <= hh) {
                continue // If current height is not greater than water level, skip.
            } else if (hs[i] - hh > hh - w + 1) {
                // If the required time to teleport exceeds available time before drowning, impossible.
                can = false
                break
            } else {
                val d = hs[i] - hh // Difference in height between current and previous tower.
                hh += d // Update current water level after teleporting.
                w += d  // Update the accumulated time spent on teleportations.
            }
        }
        println(if (can) "Yes" else "No")
    }
}


// https://github.com/VaHiX/CodeForces/
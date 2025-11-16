// Problem: CF 2126 B - No Casino in the Mountains
// https://codeforces.com/contest/2126/problem/B

/**
 * Problem: B. No Casino in the Mountains
 *
 * Purpose: Given an array of daily weather conditions (0 = good, 1 = rain) and a hike duration k,
 * determine the maximum number of non-overlapping k-day hikes Jean can take.
 *
 * Algorithm:
 * - Traverse the array and track consecutive good days (0s).
 * - When a sequence of k or more good days is found, count it as a valid hike.
 * - After each hike, skip at least one day (mandatory break).
 * - Greedily select hikes to maximize total count.
 *
 * Time Complexity: O(n) per test case, where n is the number of days.
 * Space Complexity: O(1) excluding input storage.
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
        val a = readInts()
        var peaksCnt = 0 // Count of completed hikes
        var dayCnt = 0   // Consecutive good days counter
        for (d in a) {
            if (d == 0) {
                dayCnt ++               // Increment consecutive good days
                if (dayCnt >= k) {      // If we have enough good days for a hike
                    peaksCnt ++         // Count this hike
                    dayCnt = -1         // Reset counter and mark that a hike was taken
                }
            } else {
                dayCnt = 0              // Reset counter on rain day
            }
        }
        println(peaksCnt)
    }
}


// https://github.com/VaHiX/CodeForces/
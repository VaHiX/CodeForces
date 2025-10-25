// Problem: CF 2160 B - Distinct Elements
// https://codeforces.com/contest/2160/problem/B

/*
 * Problem: B. Distinct Elements
 * Algorithm: Reconstruction of array 'a' from prefix sums of distinct elements in subarrays.
 * Approach:
 *   - For each position i, we calculate how many new distinct elements are added to the suffix starting at position i.
 *   - Using the difference between consecutive values in b, we deduce where to place new elements.
 *   - We maintain an array 'a' and build it incrementally using computed differences.
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the result array
 */

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readStrings() = readLn().split(" ") 
private fun readInts() = readStrings().map { it.toInt() } 
private fun readLongs() = readStrings().map { it.toLong() } 
private fun printInts(a:List<Int>) = run { a.forEach() { print("$it ")}; println() }
private fun printLongs(a:List<Long>) = run { a.forEach() { print("$it ")}; println() }

private fun main() {
    val t = readInt()
    for (itt in 1..t) {
        val n = readInt()
        val b = readLongs()
        val a = IntArray(n) { 0 }
        a[0] = 1 // First element is always 1
        var maxa = 1 // Tracks maximum value assigned so far
        for (i in 1 until n) {
            val d = (b[i] - b[i-1] - 1L).toInt() // Calculate the offset based on difference
            if (d == i) {
                // If d equals i, we need a new distinct value
                a[i] = maxa + 1
                maxa++
            } else {
                // Otherwise reuse previous value at index 'i - d - 1'
                a[i] = a[i-d-1]
            }
        }
        printInts(a.asList())
    }
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 2011 D - Among Wolves
// https://codeforces.com/contest/2011/problem/D

/*
D. Among Wolves

Purpose:
This code solves a problem where a sheep is placed on a 2-row grid and must be protected from wolves.
The goal is to determine the minimum cost to ensure no wolf can reach the sheep using two operations:
1. Eradicate a wolf (cost h)
2. Build a trench in an empty cell (cost b)

Approach:
- For each test case, we preprocess the grid to find the sheep position and count wolves.
- Then, we compute three strategies for protecting the sheep:
  1. Clear all wolves in the path (minimum cost = number of wolves * h)
  2. Build trenches at both ends and clear one wolf
  3. Build trenches at both ends and clear the other wolf

Time Complexity: O(n) per test case, where n is the row length.
Space Complexity: O(n) for storing the grid data.

Algorithms/Techniques:
- Greedy approach with precomputation
- Linear iteration with prefix/suffix counters
- Optimization with minimum comparisons
*/

val reader = System.`in`.bufferedReader()
fun readLn() = reader.readLine()
fun readInt() = readLn().toInt()
fun readDouble() = readLn().toDouble()
fun readLong() = readLn().toLong()
fun readStrings() = readLn().split(" ")
fun readInts() = readStrings().map { it.toInt() }
fun readDoubles() = readStrings().map { it.toDouble() }
fun readLongs() = readStrings().map { it.toLong() }

fun runcase() {
    var (n, h, b) = readInts()
    var s = List(2) { readLn() }  // Read the 2-row grid
    var ans: Long = 3L * b  // Default answer if all wolves are cleared
    var pos = -1  // Position of the sheep
    
    // Find the sheep's position
    for (i in 0 until n) {
        if (s[0][i] == 'S' || s[1][i] == 'S') {
            pos = i
            break
        }
    }
    
    assert(pos != -1)  // Ensure sheep was found
    
    var pre = 0L  // Count of wolves before the sheep's position
    var suf = 0L  // Count of wolves after the sheep's position
    
    // Count wolves to the left of the sheep
    for (i in 0 until pos) {
        if (s[0][i] == 'W') {
            pre++
        }
        if (s[1][i] == 'W') {
            pre++
        }
    }
    
    // Count wolves to the right of the sheep
    for (i in n - 1 downTo pos + 1) {
        if (s[0][i] == 'W') {
            suf++
        }
        if (s[1][i] == 'W') {
            suf++
        }
    }
    
    // Evaluate three strategies:
    // 1. Clear all wolves in the path
    ans = minOf(ans, (pre + suf) * h)
    
    // 2. Build trenches at both ends and clear one wolf
    ans = minOf(ans, pre * h + 2L * b)
    
    // 3. Build trenches at both ends and clear one wolf
    ans = minOf(ans, suf * h + 2L * b)
    
    println(ans)
}

fun main() {
    var t = readInt()
    repeat(t) { runcase() }
}


// https://github.com/VaHiX/codeForces/
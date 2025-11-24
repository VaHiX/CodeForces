// Problem: CF 2113 B - Good Start
// https://codeforces.com/contest/2113/problem/B

/*
B. Good Start

Problem Description:
We are given a roof of size w x h that needs to be covered with identical tiles of size a x b.
Two tiles have already been placed on the roof at positions (x1, y1) and (x2, y2).
We need to determine if it is possible to completely tile the remaining area using only additional tiles of the same size.

Approach:
1. For each test case, we check the relative positions of the two existing tiles.
2. If both tiles are aligned horizontally or vertically (same x or y coordinate), we validate that
   the distance between them allows for complete tiling in the corresponding direction.
3. If they are at different x and y coordinates, we have to verify if there's a way to tile
   remaining gaps, by checking divisibility conditions based on dimensions a and b.

Time Complexity: O(1) - constant time per test case due to all operations being arithmetic checks only.
Space Complexity: O(1) - only using fixed size variables and no extra data structures.

Algorithm:
- Read input parameters for w, h, a, b, and two tile positions.
- Determine directionality of placement between tiles (horizontal, vertical, or diagonal).
- Based on orientation, check divisibility constraints that must hold for full coverage.
- Output Yes/No based on whether all conditions are met.

*/

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readStrings() = readLn().split(" ") 
private fun readInts() = readStrings().map { it.toInt() } 
private fun readLongs() = readStrings().map { it.toLong() } 
private fun printInts(a:List<Int>) = run { a.forEach() { print("$it ")}; println() }
private fun printIaInts(a:IntArray) = run { a.forEach() { print("$it ")}; println() }
private fun readIntArray(n: Int) : IntArray {
    val NV = Int.MIN_VALUE
    val s = readLn()
    val a = IntArray(n) { 0 }
    var idx = 0
    var v = NV
    var sign = 1
    for (c in s) {
        if (c==' ') {
            if (v != NV) {
                a[idx++] = v*sign
                sign = 1
                v = NV
            }
        } else if (c == '-') {
            sign = -1
        } else {
            if (v == NV) {
                v = 0
            }
            val d = c - '0'
            v = v*10 + d
        }
    }
    if (v != NV) {
        a[idx++] = v
    }
    return a
}

private fun main() {
    val t = readInt()
    for (itt in 1..t) {
        val (w,h,a,b) = readInts()
        val (x1,y1,x2,y2) = readInts()
        var ok: Boolean = true
        if (x1 == x2) {
            // Vertical line of alignment - check vertical spacing
            ok = (y2 - y1) % b == 0
        } else if (y1 == y2) {
            // Horizontal line of alignment - check horizontal spacing  
            ok = (x2 - x1) % a == 0
        } else {
            // Diagonal positioning - check if either dimension allows tiling
            val okX = ((x2 - x1) % a) == 0
            val okY = ((y2 - y1) % b) == 0
            ok = okX or okY
        }
        val ans = if (ok) "Yes" else "No"
        println(ans)
    }
}


// https://github.com/VaHiX/CodeForces/
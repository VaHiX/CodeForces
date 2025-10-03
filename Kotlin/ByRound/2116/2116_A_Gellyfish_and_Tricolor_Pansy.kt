// Problem: CF 2116 A - Gellyfish and Tricolor Pansy
// https://codeforces.com/contest/2116/problem/A

/**
 * Problem: Gellyfish and Tricolor Pansy
 * 
 * Game Description:
 * Two players (Gellyfish and Flower) play a turn-based duel with health points (HP).
 * Each player has a knight with separate HP. Players take turns attacking either the opponent or their own knight.
 * The game ends when one player's HP or knight HP reaches zero.
 * 
 * Strategy:
 * - If Gellyfish's HP is less than or equal to Flower's knight HP, then Gellyfish can be defeated in a single attack,
 *   so Gellyfish loses unless Flower's knight dies first.
 * - If Gellyfish's knight HP is insufficient to defeat Flower's HP without being countered, Gellyfish will lose.
 * 
 * Key Insight:
 * - The outcome depends on comparing minimums of health values:
 *   - Minimum(Gellyfish's HP, Gellyfish's Knight HP) >= Minimum(Flower's HP, Flower's Knight HP)
 *   - If true, Gellyfish wins; otherwise, Flower wins.
 * 
 * Algorithms/Techniques:
 * - Comparison logic and math-based game theory
 * 
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */
class GellyfishAndTricolorPansy {
}
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
        val (a,b,c,d) = readInts()
        // Determine winner based on comparing minimum health values
        var winGel = Math.min(a,c) >= Math.min(b,d)
        println(if (winGel) "Gellyfish" else "Flower")
    }
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 2133 D - Chicken Jockey
// https://codeforces.com/contest/2133/problem/D

/**
 * Problem: Chicken Jockey
 * 
 * Task: Given a stack of n mobs with health values h[0] to h[n-1], determine the minimum number of attacks needed to kill all mobs.
 * When a mob dies, all mobs above it fall down and take damage equal to the number of mobs beneath them in the original stack.
 * This can cause a chain reaction where more mobs die due to fall damage.
 * 
 * Algorithm:
 * - Greedy approach using dynamic programming on a transformed problem.
 * - The core idea is to think of this as maximizing the number of attacks that can be "saved" by strategic killing.
 * - We first compute the total base damage (sum of all health minus (n-1) for the fall damage).
 * - Then we model the remaining part as a DP optimization:
 *      a = previous maximum saved attacks
 *      b = current maximum saved attacks
 *      For each element, calculate how much can be saved by removing some mob.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1) - only using constant extra space
 */

import java.util.StringTokenizer
import kotlin.math.max
import kotlin.math.min

fun main() {
    val t = readInt()
    repeat(t) {
        val n = readInt()
        val h = readLongs(n)
        var base: Long = 0
        for (x in h) base += x // Sum of all health values
        base -= (n - 1) // Subtract the fall damage that will occur at every level except the bottom one
        
        var a: Long = 0 // Previous max saved attacks
        var b: Long = 0 // Current max saved attacks
        for (i in 1 until n) {
            // Calculate how many attacks we could save by choosing an optimal mob to kill at this position
            var w = min(i.toLong(), h[i]) - 2
            if (w < 0) w = 0 // Ensure non-negative saving
            
            val c = max(b, a + w) // Update maximum saved attacks using DP logic
            
            a = b // Shift the previous value
            b = c // Update current value
        }
        println(base - b) // Final answer is total base damage minus maximum saves
    }
}

private val input = System.`in`.bufferedReader()
private var tokenizer: StringTokenizer? = null

fun read(): String {
    while (tokenizer == null || !tokenizer!!.hasMoreTokens()) {
        val line = input.readLine() ?: return ""
        tokenizer = StringTokenizer(line)
    }
    return tokenizer!!.nextToken()
}

fun readInt(): Int = read().toInt()
fun readLong(): Long = read().toLong()
fun readInts(n: Int): List<Int> = List(n) { readInt() }
fun readLongs(n: Int): List<Long> = List(n) { readLong() }


// https://github.com/VaHiX/CodeForces/
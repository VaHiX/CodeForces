// Problem: CF 2109 B - Slice to Survive
// https://codeforces.com/contest/2109/problem/B

/**
 * Problem: B. Slice to Survive
 * 
 * Purpose: Determine the minimum number of turns required to reduce an n×m grid
 *          to a single cell, where Mouf (who cuts) and Fouad (who moves) play optimally.
 *          
 * Game Rules:
 * - Mouf cuts the grid along a row or column line into two parts,
 *   discarding the part without Fouad's monster.
 * - Fouad then moves his monster to any cell within the remaining grid.
 * - The game ends when only one cell remains.
 *
 * Approach:
 * - At each turn, Mouf wants to minimize the number of turns to isolate the monster.
 * - Fouad wants to maximize the number of turns by positioning the monster such that
 *   the grid size is reduced slowly.
 * - The optimal strategy for both players means analyzing the minimal cut steps needed
 *   from all possible positions of the monster.
 * 
 * Key Insight:
 * - For each of the four corners defined:
 *   (a,b) = current position,
 *   (n,m) = bottom-right corner,
 *   (1,1) = top-left corner,
 *   and opposite positions to maximize possible cuts.
 * - Each of these points represents a potential move strategy.
 * - For each point, compute the minimal number of binary-like cuts required
 *   in both directions.
 * - The final answer is the minimum over all such strategies.
 *
 * Time Complexity: O(1) per test case — constant time as only fixed arithmetic operations.
 * Space Complexity: O(1) — only using a few variables, no extra space used.
 */

import java.io.PrintWriter
import java.math.BigInteger
import java.util.*
import kotlin.collections.ArrayList
import kotlin.math.abs
import kotlin.math.pow

lateinit var dp: Array<Array<Array<IntArray>>>
const val MOD = 1000000000 + 7

fun solve(caseNumber: Int) {
    var (n, m, a, b) = readInts()
    var first = a
    var second = b
    var third = n - a
    var fouth = m - b
    // Define the four key points that define the possible "optimal" cutting strategies
    val arr = arrayOf(Pair(first, m), Pair(second,n), Pair(third+1, m), Pair(fouth+1, n))
    var ans = 1000000000
    
    // For each key point, calculate minimum number of steps needed to isolate the monster
    for(i in arr) {
        var temp = 1    // Start with 1 because at least one cut is always required to begin
        var r = minOf(i.first, i.second)
        
        // Count binary cuts needed to reduce smallest dimension down to 1
        while (r > 1) {
            r = (r+1)/2   // Simulate halving the grid size using floor division with addition
            temp++
        }
        
        r = maxOf(i.first, i.second)
        // Count binary cuts needed to reduce largest dimension down to 1
        while (r > 1) {
            r = (r+1)/2
            temp++
        }
        ans = minOf(ans, temp)
    }
    
    println(ans)
}

fun main(args: Array<String>) {
    var t = 1
    t = readInt()
    output {
        repeat(t) {
            solve(it)
        }
    }
}

@JvmField
val INPUT = System.`in`
@JvmField
val OUTPUT = System.out
@JvmField
val _reader = INPUT.bufferedReader()
fun readLine(): String? = _reader.readLine()
fun readLn() = _reader.readLine()!!
@JvmField
var _tokenizer: StringTokenizer = StringTokenizer("")
@JvmField
val _writer = PrintWriter(OUTPUT, false)
inline fun output(block: PrintWriter.() -> Unit) {
    _writer.apply(block).flush()
}
fun read(): String {
    while (_tokenizer.hasMoreTokens().not()) _tokenizer = StringTokenizer(_reader.readLine() ?: return "", " ")
    return _tokenizer.nextToken()
}
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readDouble() = readLn().toDouble()
private fun readStrings() = readLn().trim().split(" ") 
private fun readInts() = readStrings().map { it.toInt() } as ArrayList<Int>
private fun readLongs() = readStrings().map { it.toLong() } as ArrayList<Long>
private fun readDoubles() = readStrings().map { it.toDouble() } as ArrayList<Double> 


// https://github.com/VaHiX/CodeForces/
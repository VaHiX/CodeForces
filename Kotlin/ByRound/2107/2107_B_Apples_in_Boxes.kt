// Problem: CF 2107 B - Apples in Boxes
// https://codeforces.com/contest/2107/problem/B

/**
 * Problem: B. Apples in Boxes
 * 
 * Game Description:
 * Tom and Jerry play a game with n boxes of apples. Each player takes turns removing one apple from any non-empty box.
 * The game ends when no moves are possible (all boxes empty).
 * If after a move, the difference between the maximum and minimum number of apples in boxes exceeds k,
 * the current player loses immediately.
 * 
 * Algorithm:
 * - The key observation is that if the range (max - min) of apples exceeds k even before all apples are removed,
 *   then one of the players must lose due to this condition.
 * - If the range can be kept within k throughout the game, we only care about whether the total number of moves
 *   is odd or even. Since Tom starts first:
 *   - Odd moves → Tom wins
 *   - Even moves → Jerry wins
 * 
 * Time Complexity: O(n log n) due to sorting operations in each test case.
 * Space Complexity: O(1) excluding input storage.
 */

import java.io.PrintWriter
import java.util.*
import kotlin.collections.ArrayList
import kotlin.math.max

const val mod = 1000000000 + 7 // Modulo value (not actively used)

var graph1: ArrayList<Pair<Int, Int>> = ArrayList() // Unused in current solution
var graph2: ArrayList<Pair<Int, Int>> = ArrayList() // Unused in current solution

lateinit var parent1: IntArray // Unused in current solution
lateinit var parent2: IntArray // Unused in current solution

fun solve(){
    val (n,k) = readLongs() // Read number of boxes and threshold k
    val arr = readLongs() // Read array of apples in each box
    arr.sort() // Sort to easily calculate min and max
    
    // Check if the difference between max and min already exceeds k
    if(arr.last() - arr.first() > k){
        // If the range is too large, check further conditions
        if(arr.last() - arr.first() > k+1 || arr.count { it == arr.last() } > 1){
            // Case where either difference is larger than k+1 or there are duplicates at max value
            println("Jerry") // Jerry wins due to game rules
        }
        else{
            // Special case when only one element is at max and diff equals k+1
            if(arr.sum()%2 == 0L){
                println("Jerry") // Jerry wins if sum is even
            }
            else{
                println("Tom") // Tom wins if sum is odd
            }
        }
    }
    else{
        // If the difference never exceeds k, winner depends on parity of total apples
        if(arr.sum()%2 == 0L){
            println("Jerry") // Jerry wins if sum is even
        }
        else{
            println("Tom") // Tom wins if sum is odd
        }
    }
}

fun main(args: Array<String>) {
    var t = 1
    t = readInt() // Read number of test cases
    output {
        repeat(t) {
            solve()
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
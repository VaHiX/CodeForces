// Problem: CF 2098 B - Sasha and the Apartment Purchase
// https://codeforces.com/contest/2098/problem/B

/**
 * Problem: Sasha and the Apartment Purchase
 * 
 * Algorithm:
 * - Sort the bar positions
 * - For each unique bar position, calculate the minimum cost to place the apartment
 *   at that position by closing at most k bars
 * - Use a sliding window technique to determine which positions are suitable
 * 
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(n) for storing the array and auxiliary data structures
 */
import java.io.*
import java.util.PriorityQueue
import java.util.TreeMap
import java.util.TreeSet
import kotlin.math.*
typealias ints = IntArray
typealias longs = LongArray
typealias bools = BooleanArray
fun List<Char>.conca():String = this.joinToString("")
val CharArray.conca :String get() = this.joinToString("")
val IntArray.conca :String get() = this.joinToString(" ")
@JvmName("concaInt")
fun List<Int>.conca():String = this.joinToString(" ")
val LongArray.conca:String get() = this.joinToString(" ")
@JvmName("concaLong")
fun List<Long>.conca():String = this.joinToString(" ")
@JvmName("concaString")
fun List<String>.conca():String = this.joinToString("")
fun Int.has(i:Int):Boolean = (this and (1 shl i) != 0)
fun Long.has(i:Int):Boolean = (this and (1L shl i) != 0L)
infix fun Int.mm(b:Int):Int{ return ((this.toLong() * b) % p).toInt() }
infix fun Int.mp(b:Int):Int{ val ans = this + b;return if(ans >= p) ans - p else ans }
infix fun Int.ms(b:Int):Int{ val ans = this - b;return if(ans < 0) ans + p else ans }
const val interactive = false
object Reader{
    private const val BS = 1 shl 16
    private const val NC = 0.toChar()
    private val buf = ByteArray(BS)
    private var bId = 0
    private var size = 0
    private var c = NC
    var lastTC:String = ""
    private var IN: BufferedInputStream = BufferedInputStream(System.`in`, BS)
    val OUT: PrintWriter = PrintWriter(System.out)
    private val char: Char
        get() {
            if(interactive){
                val c = System.`in`.read()
                return if(c == -1) NC else c.toChar()
            }
            while (bId == size) {
                size = IN.read(buf)
                if (size == -1) return NC
                bId = 0
            }
            return buf[bId++].toChar()
        } 
    fun nextLong(): Long {
        var neg = false
        if (c == NC) c = char
        while (c < '0' || c > '9') {
            if (c == '-') neg = true
            if(c == NC) throw Error("Bad Input")
            c = char
        }
        var res = 0L
        while (c in '0'..'9') {
            res = (res shl 3) + (res shl 1) + (c - '0')
            c = char
        }
        return if (neg) -res else res
    }
    fun nextString():String{
        val ret = StringBuilder()
        while (true){
            c = char
            if(c == NC) throw Error("Bad Input")
            if(!isWhitespace(c)){ break}
        }
        do{
            ret.append(c)
            c = char
        }while(!isWhitespace(c))
        return ret.toString()
    }
    private fun isWhitespace(c:Char):Boolean{
        return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == NC
    }
    fun flush(){
        OUT.flush()
    }
    fun takeString(str:String){
        lastTC = str
        IN = BufferedInputStream(lastTC.byteInputStream(),BS)
    }
    fun takeFile(name:String){
        IN = BufferedInputStream(File(name).inputStream(),BS)
    }
}
fun put(aa:Any){
    Reader.OUT.println(aa)
    if(interactive){ Reader.flush()}
}
fun put(vararg x:Any){
    val count = x.size
    for((pt, c) in x.withIndex()){
        Reader.OUT.print(c)
        if(pt + 1 != count) Reader.OUT.print(" ")
    }
    Reader.OUT.print("\n")
    if(interactive){ Reader.flush()}
}
fun done() = Reader.OUT.close()
val getint:Int get(){ val ans = getlong ; if(ans > Int.MAX_VALUE){IntArray(1000000000);error("Input Overflow")};return ans.toInt() }
val getlong:Long get() = Reader.nextLong()
val getstr:String get() = Reader.nextString()
fun getline(n:Int):IntArray = IntArray(n){getint}
fun getlineL(n:Int):LongArray = LongArray(n){getlong}
const val INF = (1e9).toInt() + 5
const val p = 1_000_000_007
const val multiCase = true
fun main() {
    val t = if (multiCase) getint else 1
    repeat(t) {
        val n = getint
        val k = getint
        val a = getline(n)
        val seen = TreeSet<Int>() // Store all positions which can be a valid house
        var count = 0 // Count valid intervals where we can place house
        a.sort()
        for (i in 0 until n-1) {
            if (a[i] == a[i+1]) continue
            // Check if by closing bars we can make a[i+1] to a[i] interval valid
            // max(n-i-2, i) - min(n-i-2, i) represents the number of bars we have to remove to make the current position minimal
            if (max(n-i-2, i) - min(n-i-2, i) <= k) count += a[i+1] - a[i] - 1;
        }
        for (i in 0 until n) {
            // For each bar position, check if we can minimize the cost to that position
            // by closing some bars (up to k)
            if (max(n-i-1, i) - min(n-i-1, i) - 1 <= k) seen.add(a[i])
        }
        put(count + seen.size)
	}
    done()
}


// https://github.com/VaHiX/CodeForces/
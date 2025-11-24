// Problem: CF 2145 F - Long Journey
// https://codeforces.com/contest/2145/problem/F

/**
 * Problem: F. Long Journey
 * 
 * Purpose:
 *   This program solves a game problem where a chip moves along a strip of cells from 0 to m.
 *   Each turn, the chip either moves forward or stays in place. Traps are activated according
 *   to a set of modular rules depending on the turn number and predefined parameters for each turn.
 *   The goal is to find the minimum number of turns to reach cell `m`, or return -1 if impossible.
 *
 * Algorithms:
 *   1. Simulation with cycle detection in a state graph (using next array).
 *   2. Modular arithmetic and LCM computation.
 *   3. Binary search on prefix sums to determine when cumulative traps exceed target.
 *
 * Time Complexity:
 *   O(n * L + log(m)) where L is the least common multiple of all 'a' values,
 *   which in worst case is around 10! = 3628800 (bounded due to small constraints),
 *   and log(m) represents searching through prefix sums for large m.
 *
 * Space Complexity:
 *   O(n * L), used for storing arrays related to the states and transitions.
 */

import java.io.BufferedInputStream
import kotlin.math.abs

private class DocDoc{
    private val nh=BufferedInputStream(System.`in`);
    private val bb=ByteArray(1 shl 16);
    private var ii=0;
    private var zz=0;
    
    private fun doc():Int{
        if(ii>=zz){
            zz=nh.read(bb);
            ii=0;
            if(zz<=0)return -1
        };
        return bb[ii++].toInt()
    }
    
    fun so():Int{
        var c=doc();
        while(c<=32)c=doc();
        var s=1;
        var x=0;
        if(c=='-'.code){
            s=-1;
            c=doc()
        };
        while(c>32){
            x=x*10+(c-48);
            c=doc()
        };
        return x*s
    }
    
    fun lo():Long{
        var c=doc();
        while(c<=32)c=doc();
        var s=1;
        var x=0L;
        if(c=='-'.code){
            s=-1;
            c=doc()
        };
        while(c>32){
            x=x*10L+(c-48);
            c=doc()
        };
        return x*s
    }
};

private fun ucln(a:Long,b:Long):Long{
    var x=abs(a);
    var y=abs(b);
    while(y!=0L){
        val t=x%y;
        x=y;
        y=t
    };
    return x
}

private fun boiChung(a:Long,b:Long):Long{
    if(a==0L||b==0L)return 0L;
    return a/ucln(a,b)*b
}

private fun lb(mang:LongArray,l:Int,r:Int,gia:Long):Int{
    var L=l;
    var R=r;
    var ans=r+1;
    while(L<=R){
        val mid=(L+R) ushr 1;
        if(mang[mid]>=gia){
            ans=mid;
            R=mid-1
        }else L=mid+1
    };
    return ans
}

fun main(){
    val nh=DocDoc();
    val t=nh.so();
    val ra=StringBuilder();
    
    repeat(t){
        val dem=nh.so();
        val muc=nh.lo();
        val bo=IntArray(dem){nh.so()};
        val ga=IntArray(dem){nh.so()};
        
        var lam=1L;
        var i0=0;
        while(i0<dem){
            lam=boiChung(lam,bo[i0].toLong());
            i0++
        };
        
        val suc=(dem.toLong()*lam).toInt(); // Size of cycle
        val tieptheo=IntArray(suc);         // Next state transition table
        val them=IntArray(suc);             // Trap cost at each position
        var i1=0;
        while(i1<dem){
            var r=0L;
            while(r<lam){
                val chiSo=(i1.toLong()*lam+r).toInt();
                if(((r+1L)%bo[i1].toLong()).toInt()==ga[i1]){
                    them[chiSo]=0;              // No trap at this step
                    val ni=(i1+1)%dem;
                    val nr=r%lam;
                    tieptheo[chiSo]=(ni.toLong()*lam+nr).toInt()
                }else{
                    them[chiSo]=1;              // Trap present
                    val ni=(i1+1)%dem;
                    val nr=(r+1L)%lam;
                    tieptheo[chiSo]=(ni.toLong()*lam+nr).toInt()
                };
                r++
            };
            i1++
        }
        
        val dau=IntArray(suc){-1};          // Start of cycle detection
        val thu=ArrayList<Int>();           // List of visited positions in sequence
        val themhet=ArrayList<Int>();       // Trap costs accumulated from start to current state
        var s=0;
        var buoc=0;
        
        while(dau[s]==-1){
            dau[s]=buoc;
            thu.add(s);
            themhet.add(them[s]);
            s=tieptheo[s];
            buoc++
        }
        
        val chi=dau[s];                     // Cycle begins after this many steps
        val truoc=chi;                      // Prefix sum before cycle
        val vong=buoc-chi;                  // Length of repeating cycle
        
        val tich=LongArray(buoc+1);         // Prefix sums of trap costs along path
        var i2=0;
        while(i2<buoc){
            tich[i2+1]=tich[i2]+themhet[i2].toLong();
            i2++
        }
        
        val truocCong=tich[chi];            
        val vongCong=tich[buoc]-tich[chi];
        
        if(truocCong>=muc){
            // If we can reach within prefix before cycle
            val kq=lb(tich,0,truoc,muc);    // Binary search for the first point exceeding 'muc'
            ra.append(kq).append('\n')
        }else if(vongCong==0L){
            // No cost inside cycle, must check if it's reachable even with infinite loops
            ra.append(-1).append('\n')      // If no cost added, and prefix not enough, impossible
        }else{
            var con=muc-truocCong;
            val so=(con-1)/vongCong;         // Number of full cycles to skip to meet or exceed the limit
            var dap=truoc.toLong()+so*vong.toLong();
            con-=so*vongCong;
            
            val vongtich=LongArray(vong+1);  // Prefix sums inside cycle (for binary search)
            var i3=0;
            while(i3<vong){
                vongtich[i3+1]=vongtich[i3]+themhet[chi+i3].toLong();
                i3++
            }
            
            val them2=(0..vong).let{lb(vongtich,0,vong,con)}; // Binary search in cycle part
            dap+=them2.toLong();
            ra.append(dap).append('\n')
        }
    };
    
    print(ra.toString())
}


// https://github.com/VaHiX/CodeForces/
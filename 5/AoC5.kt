package aoc

import java.io.File
import kotlin.collections.*

class SleighManualSorting(
    val rules: MutableMap<Int, MutableList<Int>> = mutableMapOf(),
    val updates: MutableList<List<Int>> = mutableListOf()
) {

    fun readRulesAndUpdates() {
        val lines = File("input.txt").readLines()
        var firstPart = true

        lines.forEach {
            if (it.isBlank()) {
                firstPart = false
            } else if (firstPart) {
                val n = it.split("|")
                val key = n[0].toInt()
                val value = n[1].toInt()
                rules.getOrPut(key) { mutableListOf() }.add(value)
            } else {
                updates.add(it.split(",").map { num -> num.toInt() })
            }
        }
    }

    fun isSorted(update:List<Int>): Boolean {
        update.forEachIndexed{ index, value ->
            val prefix = update.take(index)
            val rule = rules.getOrPut(value) { mutableListOf() }
            if (prefix.any{it in rule}){
                return false
            }
        }
        return true
    }
    
    fun middleValue(update:List<Int>):Int{
        return update[update.size/2]
    }
    
    fun sort(update:List<Int>):List<Int>{
        fun lt(a:Int, b:Int):Boolean{
            val rule = rules.getOrPut(a) { mutableListOf() }
            return b in rule
        }
        
        var result = update.sortedWith{ a,b ->
            when {
                lt(a,b) -> -1
                lt(b,a) -> 1
                else -> 0
            }
        }
        return result
    }
}

fun main() {
    val sms = SleighManualSorting()
    sms.readRulesAndUpdates()

    var sum1 = 0
    var sum2 = 0

    sms.updates.forEach{ update ->
        if(sms.isSorted(update)) sum1+= sms.middleValue(update)
        else sum2+=sms.middleValue(sms.sort(update))
    }
    
    println("originally sorted:$sum1")
    println("newly sorted:$sum2")
    
}

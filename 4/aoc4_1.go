package main

import (
	"bufio"
	"os"
)

type Counter struct {
	deltaX int
	deltaY int
	table  *[][]rune
}

func (c Counter) inc(iX int, iY int) (int, int) {
	iX = iX + c.deltaX
	iY = iY + c.deltaY
	return iX, iY
}

func (c Counter) search(ch chan int, iX int, iY int, word string) { //int {
	var count = 0
	//var dir string
	//if c.deltaY == -1{
	//
	//}
	//var s string = "[" + strconv.Itoa(iX) + "," + strconv.Itoa(iY) + "]" + dir
	var j = 0

	for iY < len(*c.table) && iY >= 0 && iX < len((*c.table)[iY]) && iX >= 0 {
		if (*c.table)[iY][iX] == rune(word[j]) {
			iX, iY = c.inc(iX, iY)
			j++
			if j == len(word) {
				count++
				j = 0
			}
		} else {
			if j != 0 {
				j = 0
			} else {
				iX, iY = c.inc(iX, iY)
			}
		}
	}
	//fmt.Println(s, count)
	ch <- count
	//return count
}

func makeTable() [][]rune {
	file, _ := os.Open("input.txt")
	defer file.Close()

	var table [][]rune
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		var charSlice []rune
		for _, char := range line {
			charSlice = append(charSlice, char)
		}
		table = append(table, charSlice)
	}

	return table
}

func xmas() int {
	var table = makeTable()

	var diagonalCounter = Counter{deltaX: 1, deltaY: 1, table: &table}
	var horizontalCounter = Counter{deltaX: 1, deltaY: 0, table: &table}
	var verticalCounter = Counter{deltaX: 0, deltaY: 1, table: &table}
	var otherDiaCounter = Counter{deltaX: 1, deltaY: -1, table: &table}

	var yChan = make(chan int)

	for y := range table {
		var ch = make(chan int)

		go diagonalCounter.search(ch, 0, y, "XMAS")
		go diagonalCounter.search(ch, 0, y, "SAMX")
		go otherDiaCounter.search(ch, 0, y, "XMAS") // ok
		go otherDiaCounter.search(ch, 0, y, "SAMX") // ok
		go horizontalCounter.search(ch, 0, y, "XMAS")
		go horizontalCounter.search(ch, 0, y, "SAMX")

		go func() {
			var sum = 0
			for _ = range 6 {
				sum += <-ch
			}
			yChan <- sum
		}()
	}
	var sum0 = 0
	//go func() {
	//	for _ = range table {
	//		sum0 += <-yChan
	//	}
	//}()

	var xChan = make(chan int)
	for x := range table[0] {
		var ch = make(chan int)

		if x > 0 {
			go diagonalCounter.search(ch, x, 0, "XMAS")
			go diagonalCounter.search(ch, x, 0, "SAMX")
			go otherDiaCounter.search(ch, x, len(table[0])-1, "XMAS") // ok
			go otherDiaCounter.search(ch, x, len(table[0])-1, "SAMX") // ok

		}
		go verticalCounter.search(ch, x, 0, "XMAS")
		go verticalCounter.search(ch, x, 0, "SAMX")

		go func() {
			var sum = 0
			var size = 6
			if x == 0 {
				size = 2
			}
			for _ = range size {
				sum += <-ch
			}
			xChan <- sum
		}()
	}
	var sum1 = 0
	//go func() {
	for _ = range table[0] {
		sum0 += <-yChan
		sum1 += <-xChan
	}
	//}()

	return sum0 + sum1
}

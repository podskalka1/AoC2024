package main

func mDiag(table *[][]rune, x int, y int) bool {
	var mas = (*table)[y-1][x-1] == 'M' && (*table)[y+1][x+1] == 'S'
	var sam = (*table)[y-1][x-1] == 'S' && (*table)[y+1][x+1] == 'M'
	return mas || sam
}

func aDiag(table *[][]rune, x int, y int) bool {
	var mas = (*table)[y-1][x+1] == 'M' && (*table)[y+1][x-1] == 'S'
	var sam = (*table)[y-1][x+1] == 'S' && (*table)[y+1][x-1] == 'M'
	return mas || sam
}

func search(ch chan int, table *[][]rune, y int) { //int {
	var count = 0

	for x := 1; x < len((*table)[y])-1; x++ {
		if (*table)[y][x] == 'A' {
			if mDiag(table, x, y) && aDiag(table, x, y) {
				count++
			}
		}
	}
	ch <- count
}

func x_mas() int {
	var table = makeTable()

	var chanChan = make(chan int)

	for i := 1; i < len(table)-1; i++ {
		go search(chanChan, &table, i)
	}
	var sum = 0
	for i := 1; i < len(table)-1; i++ {
		sum += <-chanChan
	}
	return sum
}

package main

import (
	"fmt"
	"strings"
	"unicode"
)

func f1() {
	fmt.Println("f1 - start")
	defer f2()
	fmt.Println("f1 - end")
}

func f2() {
	fmt.Println("f2 - deferred")
}

func f() {
	for i := 0;i < 5;i++ {
		defer fmt.Printf("%d ", i)
	}
}

func makeSuffix(suffix string) func(string) string {
	fmt.Println("RUN makeSuffix suffix = ", suffix)
	return func(name string) string {
		fmt.Println("suffix = ", suffix, ";name = ", name)
		if !strings.HasSuffix(name, suffix) {
			return name + suffix
		}
		return name
	}
}

func main() {
	sum := 0
	for i := 0;i < 10;i++ {
		sum += i
	}
	fmt.Println(sum)

	sum2, i := 0, 0
	for i < 10 {
		sum2 += i
		i++
	}
	fmt.Println(sum)

	type Rect struct {
		width int
		height int
	}

	//r := Rect{1, 2}; fmt.Println(r.width * 2 + r.height * 2)
	r := Rect{1, 2}
	fmt.Println(r.width * 2 + r.height * 2)

	f1()
	f()

	fmt.Println("\nmakeSuffix - start")
	addZip := makeSuffix(".zip")
	addTgz := makeSuffix(".tar.gz")
	fmt.Println("makeSuffix - end")

	fmt.Println(addTgz("go1.5.1.src"))
	fmt.Println(addZip("go1.5.1.windows-amd64"))

	f := func(c rune) bool {
		return unicode.Is(unicode.Hangul, c)
	}
	fmt.Println(strings.IndexFunc("Hello, 월드", f))
	fmt.Println(strings.IndexFunc("Hello, world", f))
}
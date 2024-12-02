import Data.List

nthIndexListed :: [[String]] -> Int -> [Int]
nthIndexListed xs n = [read (x!!n)::Int| x <- xs]

findDiffs ::[Int] -> [Int] -> [Int]
findDiffs xs ys = [abs (x - y)| (x,y) <- zip xs ys]

main :: IO ()
main = do
    s <- readFile "input.txt"
    let input = map words (lines s)
    print (sum (findDiffs (sort (nthIndexListed input 0)) (sort (nthIndexListed input 1)) ))


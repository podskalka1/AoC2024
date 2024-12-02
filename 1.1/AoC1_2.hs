import Data.List

nthIndexListed :: [[String]] -> Int -> [Int]
nthIndexListed xs n = [read (x!!n)::Int| x <- xs]

count :: Int -> [Int] -> Int
count _ [] = 0
count x (y:ys)
    | x == y = 1 + count x ys
    | otherwise = count x ys

findSimScore ::[Int] -> [Int] -> [Int]
findSimScore xs ys = [x * count x ys | x <- xs ]

main :: IO ()
main = do
    s <- readFile "input.txt"
    let input = map words (lines s)
    print (sum (findSimScore  (nthIndexListed input 0)  (nthIndexListed input 1)))

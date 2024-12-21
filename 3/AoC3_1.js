import { readFileSync } from "fs";

function extractMuls(memory){
    const matches = memory.match(/mul\(\d+,\d+\)/g); 
    return matches;
}

function doMul(mul){
    const numbers = mul.match(/\d+/g);
    return parseInt(numbers[0],10) * parseInt(numbers[1],10);
}

function sumMuls(muls){
    let sum = 0;
    muls.map(doMul).forEach(element => {
        sum += element;
    });    
    return sum;
}

let input = readFileSync("input.txt", "utf8");
let muls = extractMuls(input);
console.log(sumMuls(muls));
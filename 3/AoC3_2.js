import { readFileSync } from "fs";

function extractMuls(memory){
    const matches = memory.match(/mul\(\d+,\d+\)|do\(\)|don't\(\)/g); 
    return matches;
}

function doMul(mul){
    const numbers = mul.match(/\d+/g);
    return parseInt(numbers[0],10) * parseInt(numbers[1],10);
}

function sumMuls(commands){
    let sum = 0;
    let doing = true;
    commands.forEach(element => {
        if(element === "do()"){
            doing = true;
        }else if(element === "don't()"){
            doing = false;
        } else{
            if(doing){
                sum += doMul(element);
            }
        }
    });    
    return sum;
}

let input = readFileSync("input.txt", "utf8");
let commands = extractMuls(input);
console.log(sumMuls(commands));
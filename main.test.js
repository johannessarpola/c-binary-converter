const { execSync, spawn } = require('child_process');

// Assuming your native application is named 'main' and takes input from command line arguments
const mainCommand = './main'; // Replace 'path/to/main' with the actual path to your 'main' application
const sources = ["main.c"];

/*
Decimal:	  20	    25	    30	    40	    50	    100	    200	        500
Binary:	    10100	11001	11110	101000	110010	1100100	11001000    111110100

*/

beforeAll(() => {
  execSync(`gcc ${sources.join(",")} -o main`);
});


function inputOutputTest(entry) {
  test(`Test ${entry.in} to be ${entry.out}`, () => {
    const input = entry.in.replaceAll(" ", "");
    const output = execSync(`${mainCommand} ${input}`).toString().trim();
    expect(output).toBe(entry.out);
  });
}



describe('Binary conversions to decimal', function () {

  const table = [
    { in: "10100", out: "20" },
    { in: "11001", out: "25" },
    { in: "11110", out: "30" },
    { in: "101000", out: "40" },
    { in: "110010", out: "50" },
    { in: "1100100", out: "100" },
    { in: "11001000", out: "200" },
    { in: "111110100", out: "500" },
  ]
  

  table.forEach((entry) => {
    inputOutputTest(entry);
  })

});




describe('Binary conversions to IEE 754', function () {

  const table = [
    { in: "01000000 00001001 00100001 11111011 10000010 11000010 10111101 01111111", out: "3.14159" },
    { in: "01000000 00110111 11111111 10111110 01110110 11001000 10110100 00111001", out: "23.99900" },
    { in: "11000000 01010011 01100011 10000101 00011110 10111000 01010001 11101100", out: "-77.55500" },
    { in: "01000000 01000101 00000000 00000000 00000000 00000000 00000000 00000000", out: "42.00000" },
    { in: "01000000 10011100 00011011 00100101 01101011 11011110 01110101 01101100", out: "1798.78654" },
    { in: "01000000 00010010 01100010 01110011 00110011 00110011 00110011 00110011", out: "4.59614" },
  ]
  
  table.forEach((entry) => {
    inputOutputTest(entry);
  })

});

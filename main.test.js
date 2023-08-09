const { execSync, spawn } = require('child_process');

const mainCommand = './main'; // output name of executable
const sources = ["main.c"];   // sources to include in gcc

beforeAll(() => {
  execSync(`gcc ${sources.join(",")} -o ${mainCommand} -lm`);
});


function inputOutputTest(entry) {
  test(`Test ${entry.in} to be ${entry.out}`, () => {
    const input = entry.in.replaceAll(" ", "");
    const output = execSync(`${mainCommand} ${input}`).toString().trim();
    expect(output).toBe(entry.out);
  });
}

function inputExceptionTest(entry) {
  test(`Test ${entry.in} to be ${entry.out}`, () => {
    const input = entry.in.replaceAll(" ", "");
    try {
      execSync(`${mainCommand} ${input}`).toString().trim();
    }
    catch (error) {
      expect(error.status).not.toBeLessThan(1)
      expect(error.stdout.toString()).toBe(entry.out);
    }

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

describe("Handle invalid inputs", function () {
  const table = [
    { in: "123", out: "Please use only binary strings" },
    { in: "-99", out: "Please use only binary strings" },
  ];

  table.forEach((entry) => {
    inputExceptionTest(entry);
  })

});


describe('Binary conversions to IEE 754 double-previcision floating point', function () {
  const table = [
    // Custom
    { in: "01000000 00001001 00100001 11111011 10000010 11000010 10111101 01111111", out: "3.14159" },
    { in: "01000000 00110111 11111111 10111110 01110110 11001000 10110100 00111001", out: "23.99900" },
    { in: "11000000 01010011 01100011 10000101 00011110 10111000 01010001 11101100", out: "-77.55500" },
    { in: "01000000 01000101 00000000 00000000 00000000 00000000 00000000 00000000", out: "42.00000" },
    { in: "01000000 10011100 00011011 00100101 01101011 11011110 01110101 01101100", out: "1798.78654" },
    { in: "01000000 00010010 01100010 01110011 00110011 00110011 00110011 00110011", out: "4.59614" },
    { in: "01000000 00100000 10100000 11011000 01000100 11010000 00010011 10101001", out: "8.31415" },
    { in: "11000000 00001001 00100001 11111001 11110000 00011011 10000110 01101110", out: "-3.14159" },
    { in: "01111111 11101111 11111111 11111111 11111111 11111111 11111111 11111111", out: "179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.00000" },
    { in: "11111111 11101111 11111111 11111111 11111111 11111111 11111111 11111111", out: "-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.00000" },
  ];

  table.forEach((entry) => {
    inputOutputTest(entry);
  })

});

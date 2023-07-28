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


describe('Binary conversions to decimal', function () {

  test('Test 10100 to be 20', () => {
    const input = '10100';
    const output = execSync(`${mainCommand} ${input}`).toString().trim();
    expect(output).toBe('20');
  });

  test('Test binary 11001 to be 25', () => {
    const input = '11001';
    const output = execSync(`${mainCommand} ${input}`).toString().trim();
    expect(output).toBe('25');
  });

  test('Test binary 11110 to be 30', () => {
    const input = '11110';
    const output = execSync(`${mainCommand} ${input}`).toString().trim();
    expect(output).toBe('30');
  });

  test('Test binary 101000 to be 40', () => {
    const input = '101000';
    const output = execSync(`${mainCommand} ${input}`).toString().trim();
    expect(output).toBe('40');
  });

  test('Test binary 110010 to be 50', () => {
    const input = '110010';
    const output = execSync(`${mainCommand} ${input}`).toString().trim();
    expect(output).toBe('50');
  });

  test('Test binary 1100100 to be 100', () => {
    const input = '1100100';
    const output = execSync(`${mainCommand} ${input}`).toString().trim();
    expect(output).toBe('100');
  });

  test('Test binary 11001000 to be 200', () => {
    const input = '11001000';
    const output = execSync(`${mainCommand} ${input}`).toString().trim();
    expect(output).toBe('200');
  });

  test('Test binary 111110100 to be 500', () => {
    const input = '111110100';
    const output = execSync(`${mainCommand} ${input}`).toString().trim();
    expect(output).toBe('500');
  });
  
});
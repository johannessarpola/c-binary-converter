# c-binary-converter

at the moment works on double-precision floating-point format binaries, works on basic decimals as well but doubles need to be always 64 long strings, otherwise it will be garbage.

use:
```sh
# <executable> <binary string, 64 long or a decimal number in binary> (--verbose|-v for more prints) 
./a.out 0100000000111111111100000000000000000000000000000000000000000000
31.937500000

./a.out 100
4
```

verbose can be used to check the conversion loop and intermediate values.

tests with npm, Js and Jest: 

```sh
npm install
npm test
```
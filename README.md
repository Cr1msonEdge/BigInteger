# BigInteger

### File names
Class name: BigInteger
Header file: biginteger.h
File implementation: biginteger.cpp

### Implementation 
For the BigInteger class, implement:

- Default constructor (initializes the number to zero).
- Constructors of numeric types.
- An explicit constructor from std::string.
- Copy constructor.
- Move constructor.
- Operators:
    - copy assignment,
    - move assignment,
    - comparisons.
- Operations:
    - Arithmetic operations: addition, subtraction, multiplication, division, unary minus, unary plus, increments and decrements.
    - bit operations: and, or, exclusive or, not, bit shifts.

- The external function std::string to_string(BigInteger const&).

### Description
- The digits of a number are represented by at least 32-bit numbers, all the bits in their representation are used.
- External libraries are not used (the exception is std::string when implementing to_string, std::numeric_limits).
- The project includes tests using Google Test.

### Literature
- [Knuth art of computer programming volume 2](https://www.haio.ir/app/uploads/2022/01/The-art-of-computer-programming.-Vol.2.-Seminumerical-algorithms-by-Knuth-Donald-E-z-lib.org_.pdf)
- [Modern computer arithmetics](https://members.loria.fr/PZimmermann/mca/mca-0.5.pdf)

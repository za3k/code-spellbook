This is a spellbook of computer programs.

- Each program is written on 80 column x 25 row pages. (1 page, if possible!)
- Programs operate Unix-style, on stdin and stdout. 
- Programs may also have a function interface.
- Programs are currently all in the public domain
- Programs are written in C with no library dependencies
- Programs are "minified" (no whitespace, one letter variables) to reduce space
- The goal is that someone could write a simple C compiler to run this code.
  Therefore, the C used is simple.

### Using

To compile a program on any POSIX system, type

    cc <program_name.c> -o <program_name>

For example:

    cc sha256.c -o sha256

Now you can use the program 'sha256' on your system:

    $ echo -n "" | ./sha256
    e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855

### Contributing

If you want to add a new program, feel free. 

Modifications to existing programs are accepted when they improve readability
without increasing page count, or if they reduce page count.

Please mention what license you are releasing your new program under.
Modifications should always be under the same license as the main program.

Suggested style:
- avoid standard library functions not absolutely required
- easy to compile: no macros, casting, or postfix operators
- easy to read: prefer arrays over pointer arithmetic

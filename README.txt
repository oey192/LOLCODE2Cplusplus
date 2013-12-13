LOLCODE Compiler

By Jared Sharpe and Orion Stanger


Translates LOLCODE to C++


Note: this is not a full implementation of the language, but what it does implement follows the 1.2 specificaiton except for the SMOOSH operator (which takes infinite arguments in the 1.2 spec but only takes 2 arguments in our implementation)



This was fully tested on Mac OS X 10.9 (Mavericks) Build 13A603 and on Ubuntu.
To get it to work on previous versions of Mac OS X, all references to <memory> must be changed to <tr1/memory> and all std::shared_ptr references must be changed to std::tr1::shared_ptr

To make everything, cd into the root directory of the project and type "make all"
"make clean" removes everything that might need to be made again if any changes were made
you can run "make runTests" to re-build and re-run the tests
you do not need to run "make clean" before running "make runTests"


When running the tests, test 5 will ask for your password. You must type something in and hit return before the tests will continue, but it could care less what you type in



A note about the var class that is behind all Lolcode variables: It behaves similarly to variables in JavaScript, but will contain a value of NULL if unexpected things are done to it (e.g. subtracting a double from a string)




Grammar note: The grammar will support a few structures not implemented in the AST structure (e.g. Lolcode's swtich statement). This could cause some weird errors if such structures are used.




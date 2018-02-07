Mini Command Shell 
author:Zhizhou Zhang

Mini Command Shell is an application written in C++. It is like a "baby" command shell which supports most of the system built-in commands.
(1)It can parse user input into command and arguments like a command shell does. 
(2)It can search the PATH environment variables for commands
(3)It implements command "cd" to change directory.
(4)It implements command "set var" and "export var" to provide access to variables.



START TESTING≈



/********************************************     Step 1        **********************************************/
----------------------------------------------------------------------------------------------------------------
(1) Run      valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./test

myShell:/home/zz134/ece551/mp_miniproject $

----------------------------------------------------------------------------------------------------------------
(2) Input nothing,  just click return, it will show "myShell: .... $" prompt again

myShell:/home/zz134/ece551/mp_miniproject $
myShell:/home/zz134/ece551/mp_miniproject $

----------------------------------------------------------------------------------------------------------------
(3) Run     exit

myShell will exit correctly, and valgrind is clean.

----------------------------------------------------------------------------------------------------------------
(4) Run      valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./test
Enter myShell again

Click ctrl + c, myShell will exit correctly, and valgrind is clean.


/********************************************     Step 2       **********************************************/


I have written a print.cpp which print the arguments the user inputs, and compiles it before,
so there is a execute file called print, which we can use in this step to test whether myShell
interprets the arguments correctly.

We can input ./print ..... in myShell to test
----------------------------------------------------------------------------------------------------------------
(1) Run      valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./test

In myShell, Run     ./print a b 23

Output:
'./print'
'a'
'b'
'23'
Program exited with status 0

which is correct because './print a b 23' contains a '/' in it, so it searches the current path for the program,
and it interprets the input command line to be 4 arguments, './print',  'a',  'b',  '23', which is correctly seperated.
and when ./print program exits, myShell prints "Program exited with status 0".

/**** In the output, I show ' ' around each arguments to make white space in the argument more clear. ****/

----------------------------------------------------------------------------------------------------------------
(2)  Run     ./print         a               b     23

Output:
'./print'
'a'
'b'
'23'
Program exited with status 0

which is correct because it skips an arbitrary amount of whitespace in between arguments.

----------------------------------------------------------------------------------------------------------------
(3)  Run     ./print a\ b c\ \ d

Output:
'./print'
'a b'
'c  d'
Program exited with status 0

which is correct because white spaces that are escaped with a \ are literally included in the argument, and
not used as a separator.

----------------------------------------------------------------------------------------------------------------
(4)  Run     ./print a\  b c \ d

Output:
'./print'
'a '
'b'
'c'
' d'
Program exited with status 0

which is correct because white spaces that are escaped with a \ are literally included in the argument, and
not used as a separator.

----------------------------------------------------------------------------------------------------------------
(5) Run   ../054_minesweeper/minesweeper 5 5 1

Follow the instruction of minesweeper and play

Output:
Current board:
    00000
    01234
---------
 0: ?????
 1: ?????
 2: ?????
 3: ?????
 4: ?????

---------
    00000
    01234
Found 0 of 1 mines
x coordinate:
0
y coordinate:
0
    00000
    01234
---------
 0:   111
 1:   1*1
 2:   111
 3:
 4:

---------
    00000
    01234
Found 1 of 1 mines
You win!
Do you want to play again?
n
Program exited with status 0

which is correct because we use myShell to run a program which is in former assignment.
It runs correctly, and take arguments correctly.

----------------------------------------------------------------------------------------------------------------
(6) Run   ###

Output:
Command ### not found

which is correct because "###" doesn't have a '/' in it, so myShell searches each directory specified in the PATH,
and still can't find a program named this, so it outputs "Command ### not found"

----------------------------------------------------------------------------------------------------------------
(7) Run  exit

myShell will exit correctly, and valgrind is clean.


/********************************************     Step 3        **********************************************/
----------------------------------------------------------------------------------------------------------------
(1) Run     cd ..

myShell:/home/zz134/ece551/mp_miniproject $cd ..
myShell:/home/zz134/ece551 $

It changes directory to the parent folder
and it show the current directory before the $ correctly.
----------------------------------------------------------------------------------------------------------------
(2) Run     cd
(Just type "cd" and click return)

myShell:/home/zz134/ece551 $cd
myShell:/home/zz134/ece551 $

which is correct because if we just type "cd" and click return, we will be in the same directory.

----------------------------------------------------------------------------------------------------------------
(3) Run     cd 089_lls

Output:
myShell:/home/zz134/ece551/089_lls $

We use cd to go to the correct directory we specified.

----------------------------------------------------------------------------------------------------------------
(4) Run      cd   ../mp_miniproject   %%a   w#

Output:
myShell:/home/zz134/ece551/mp_miniproject $

which is correct because cd will only change directory to the first argument, and ignores the other ones behind it.
So we change directory to /home/zz134/ece551/mp_miniproject.

----------------------------------------------------------------------------------------------------------------
(5) Run      set a hello
             set b world
	     ./print $a $b
Output:
'./print'
'hello'
'world'
Program exited with status 0

which is correct because we correctly set variable a to value "hello", and set b to value "world",
So when we use $a,$b in other program, they should be interpreted as "hello" and "world", respectively.

----------------------------------------------------------------------------------------------------------------
(6) Run      set aaa hello
             export aaa
             env

Output:
We will see the output of each NAME to VALUE in the environment,
The last two lines are:
aaa=hello
Program exited with status 0

which is correct because we "set aaa hello" and "export a", then we can find "aaa=hello" in the environment.
But we can't find"a=hello" or "b=world" we set in (5), because we haven't export them.

----------------------------------------------------------------------------------------------------------------
(7) Run        set 1_asd
               ./print $1_asd

Output:
'./print'
''
Program exited with status 0

which is correct because when we only type "set 1_asd", without typing the value, we will set the value of
"1_asd" to be "", So when we ./print, $1_asd will be interpreted to be "".

----------------------------------------------------------------------------------------------------------------
(8) Run        export 1_asd
               env
Output:
We will see the output of each NAME to VALUE in the environment,
The last three lines are:
aaa=hello
1_asd=
Program exited with status 0

which is correct because we export 1_asd, so we will see its value equals "" in the environment list.

----------------------------------------------------------------------------------------------------------------
(9) Run       set PATH sss
              export PATH
              env
Output:
Failed to open the directory sss
Command env not found

which is correct because we change variable "PATH" in environment list to be value "sss", which is
an invalid path. In this path we can't use env anymore.

Then we Run.   set PATH /bin:/usr/bin
               export PATH
               env
Output:
We will see the output of each NAME to VALUE in the environment,
Among the environment list we can find ç
which is correct because we set PATH to /bin:/usr/bin, we can find the command env in this directory. So we can
use env again. and "/bin:/usr/bin"  means PATH is changed by us.

----------------------------------------------------------------------------------------------------------------
(10) Run        set #a_1  hello

Output:
Variable must be a combination of letters,underscores,and numbers

which is correct because variable must be a combination of letters,underscores,and numbers.

----------------------------------------------------------------------------------------------------------------
(11) Run        set aaa bbb cc_c

Output:
Usage: set var value

which is correct because the format is "set var value" or "set var",
"set aaa bbb cc_c" has four arguments, so myShell tells the right format to the user.

----------------------------------------------------------------------------------------------------------------
(12) Run  exit

myShell will exit correctly, and valgrind is clean.



/******************************************    END OF TESTING      *******************************************/

/******************************************    THANK YOU     *******************************************/





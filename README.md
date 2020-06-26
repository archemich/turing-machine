# turing-machine (windows-version and linux-version branches)
Task: create turing-machine simulator in C++. Tape is 2-way list.
At each step of the simulated Turing machine 
display its configuration on the screen, which means to display the contents of the tape
and mark on it the position of the read / write head.
Prefered way to save rules is table.

The result of the task is a program that simulates
the work of the Turing machine.

The program should ask the user for input for
place on the tape and check their correctness.

The program should display the steps of the Turing machine in steps.
At each step of the machine, the screen should display:
1. Tape;
1. Position of the head on the tape;
1. Current state of the Turing machine.
After reaching the final state(q0), the program should report completion.


## How To Use
Bin folder consist of 2 executable files.
turingmachine.exe for windows and turingmachine_linux for linux

Put file containing instructions in cfg folder. (yourins.txt for example)
So your yourins.txt must contain tape in first line and table with instructions in next line.
Example you can find in tm.txt.
When you run app, you must write name.format (yourins.txt for example) containing your instructions.
State format "q*", state must start with 'q'. Read\write head format "L", allowed symbols "LNR", the last symbol is any symbol, allowed symbols are those you described in alphabet.
Then you will see how you task is solving.
Step button do a step forward in your program

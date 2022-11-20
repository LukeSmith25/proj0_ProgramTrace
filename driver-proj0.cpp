/* CSI 3334
 * Project 0 -- Program trace verification
 * Filename: driver-proj0.cpp
 * Student name: Luke Smith
 * Due Date: 08/28/2022
 *
 * This program traces and validates function calls. This program reads from
 * standard input call or return. If a function is called it is placed on the
 * stack. If a function is returned it is removed from the stack. If there is
 * any error in the function calls, they program will terminate and display the
 * reason for the invalid trace.
 */
#include <iostream>
#include <string>
#include <stack>
#include <cassert>
#include <sstream>

using namespace std;

/* main
 *  parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  return value: 0 (indicating a successful run)
 *
 */
int main(int argc, char **argv) {
    string line;

    // the callStack is used for storing the names of functions that have been
    // called and not yet returned
    stack<string> callStack;

    // Each time we go through this while loop, we read a line of input.
    // The function getline() returns a reference to cin, which is checked by
    // the while condition.  If cin has reached the end of the file, it will
    // return false and the loop will exit.  Otherwise, it will return true and
    // the loop will continue.

    int lineNumber = 0;
    size_t maximum_depth = 0;

    while (getline(cin, line)) {

        stringstream lineIn;
        string functionName;
        string functionAction;

        lineIn.str(line);
        getline(lineIn, functionAction, ' ');
        getline(lineIn, functionName);

        if (functionAction == "call"){
            callStack.push(functionName);
            maximum_depth++;
        }
        else if (functionAction == "return") {
            if (!callStack.empty()) {
                if (callStack.top() == functionName) {
                    // Case 1: Function name and top of stack match.
                    callStack.pop();
                }
                else if (callStack.top() != functionName) {
                    // Case 2: Function name does not match top of stack.
                    cout << "Invalid trace at line " << lineNumber << endl;
                    cout << "Returning from " << functionName << " instead of "
                    << callStack.top() << endl;

                    cout << "Stack trace:" << endl;
                    while (!callStack.empty()) {
                        cout << callStack.top() << endl;
                        callStack.pop();
                    }

                    return 0;
                }
            }
            else if (callStack.empty()) {
                // Case 3: Function is returned but never called.
                cout << "Invalid trace at line " << lineNumber << endl;
                cout << "Returning from " << functionName <<
                " which was not called" << endl;

                cout << "Stack trace:" << endl;
                while (!callStack.empty()) {
                    cout << callStack.top() << endl;
                    callStack.pop();
                }

                return 0;
            }
            lineNumber++;
        }
    }
    if (!callStack.empty()) {
        // Case 4: Function is called but never returned.
        cout << "Invalid trace at line " << lineNumber << endl;
        cout << "Not all functions returned" << endl;
        return 0;
    }

    cout << "Valid Trace" << endl;
    cout << "Maximum call depth was " << lineNumber << endl;

    return 0;
}
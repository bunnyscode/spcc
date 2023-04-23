#include <stdio.h>
#include <string.h>

#define MAX_LINES 1000 // maximum number of lines in input program
#define MAX_LABEL_LENGTH 10 // maximum length of a label
#define MAX_OPCODE_LENGTH 10 // maximum length of an opcode
#define MAX_OPERAND_LENGTH 10 // maximum length of an operand

// structure to store a line of assembly code
struct Line {
    char label[MAX_LABEL_LENGTH];
    char opcode[MAX_OPCODE_LENGTH];
    char operand[MAX_OPERAND_LENGTH];
};

int main() {
    struct Line program[MAX_LINES]; // array of Line structures to store the input program
    int locctr = 0; // location counter
    int line_count = 0; // number of lines in the input program
    int i;

    // read input program from standard input (console)
    printf("Enter the assembly program:\n");
    while (scanf("%s %s %s", program[line_count].label, program[line_count].opcode, program[line_count].operand) == 3) {
        line_count++;
    }

    // print the Pass-1 table
    printf("Line No.\tLocation\tLabel\tOpcode\tOperand\n");
    for (i = 0; i < line_count; i++) {
        printf("%d\t\t%d\t\t%s\t%s\t%s\n", i+1, locctr, program[i].label, program[i].opcode, program[i].operand);

        // check if the current line has a label and update the location counter accordingly
        if (strlen(program[i].label) > 0) {
            locctr += 1;
        }
        // update the location counter based on the opcode and operand of the current line
        if (strcmp(program[i].opcode, "DS") == 0 || strcmp(program[i].opcode, "DC") == 0) {
            locctr += atoi(program[i].operand);
        } else {
            locctr += 1;
        }
    }

    return 0;
}

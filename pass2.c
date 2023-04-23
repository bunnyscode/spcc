#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A structure to store an entry in an opcode table
typedef struct {
  char mne[10]; // mnemonic
  int len; // length
} optab;

// A function to split a string by a delimiter and store it in an array
void split(char *str, char *arr[], char *delim) {
  char *token = strtok(str, delim);
  int i = 0;
  while (token != NULL) {
    arr[i++] = token;
    token = strtok(NULL, delim);
  }
}

// A function to search for a mnemonic in an opcode table and return its length
int search_optab(optab *optable, int n, char *mne) {
  for (int i = 0; i < n; i++) {
    if (strcmp(optable[i].mne, mne) == 0) {
      return optable[i].len;
    }
  }
  return -1;
}

// A function to check if a string is a literal
int is_literal(char *str) {
  return str[0] == '='; // literals start with '='
}

// The main function
int main() {

  // Declare file pointers for input file, output file,
  // symbol table file, literal table file and opcode table file
  FILE *fin, *fout, *fsym, *flit, *fop;

  // Open all files in read or write mode
  fin = fopen("input.txt", "r");
  fout = fopen("output.txt", "w");
  fsym = fopen("symtab.txt", "w");
  flit = fopen("littab.txt", "w");
  fop = fopen("optab.txt", "r");

  // Declare variables for location counter (LC), starting address (SA),
  // length of instruction (len), number of opcodes (n) and number of lines (l)
  int LC, SA, len, n, l;

  // Declare arrays for label (la), mnemonic (mne), operand (op) and intermediate code (ic)
  char la[10], mne[10], op[10], ic[10];

  // Declare an array of optab structures to store opcodes and their lengths
  optab optable[10];

  // Read the number of lines from the input file
  fscanf(fin, "%d", &l);

  // Read the number of opcodes from the opcode table file
  fscanf(fop, "%d", &n);
   // Read all opcodes and their lengths from the opcode table file
  for (int i = 0; i < n; i++) {
    fscanf(fop, "%s%d", optable[i].mne, &optable[i].len);
  }

  // Read the first line of the input file and check if it contains the START directive
  fscanf(fin, "%s%s%s", la, mne, op);
  if (strcmp(mne, "START") == 0) {
    // Store the starting address and skip to the next line
    SA = atoi(op);
    LC = SA;
    fscanf(fin, "%s%s%s", la, mne, op);
  } else {
    // Assume the starting address is zero
    SA = 0;
    LC = 0;
  }

  // Read each line of the input file until the END directive is encountered
  while (strcmp(mne, "END") != 0) {
    // Search for the mnemonic in the opcode table and get its length
    len = search_optab(optable, n, mne);
    if (len == -1) {
      // Report an error if the mnemonic is not found
      printf("Invalid opcode: %s\n", mne);
      exit(1);
    }

    // If the label field is not empty, write it along with the LC value to the symbol table file
    if (strcmp(la, "-") != 0) {
      fprintf(fsym, "%s %d\n", la, LC);
    }

    // If the operand field contains a literal, write it along with a dummy value to the literal table file
    if (is_literal(op)) {
      fprintf(flit, "%s -1\n", op);
    }

    // Increment the LC by the length of the instruction depending on the mnemonic
    LC += len;

    // Write the intermediate code along with the LC value to an output file
    sprintf(ic, "%d %s %s %s", LC, la, mne, op);
    fprintf(fout, "%s\n", ic);

    // Read the next line of the input file
    fscanf(fin, "%s%s%s", la, mne, op);
  }

  // Write the END directive along with the starting address to the output file
  sprintf(ic, "%d - END %d", LC, SA);
  fprintf(fout, "%s\n", ic);

  // Close all files
  fclose(fin);
  fclose(fout);
  fclose(fsym);
  fclose(flit);
  fclose(fop);

  return 0;
}
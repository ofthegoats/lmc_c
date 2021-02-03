#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int ramsize = 99;
const int maxsize = 30;
struct entry {
    char str[maxsize];
    int   n;
};
// allow people to use variable names, ugly solution but should work
struct entry variables[ramsize] = {};  // map var name to var location
struct entry instructions[]     = {
    "LDA", 5,    // load
    "STA", 3,    // store
    "ADD", 1,    // add
    "SUB", 2,    // subtract
    "INP", 901,  // input
    "OUT", 902,  // output
    "END", 0,    // halt
    "BRZ", 7,    // branch if zero
    "BRP", 8,    // branch if positive
    "BRA", 6,    // always branch
    "DAT", 0,    // data/variable
};
// return int if found, -1 if not found
int num_for_instr(char *instr)
{
    int n_instructions = sizeof(instructions) / sizeof(instructions[0]);
    for (int i = 0; i < n_instructions; i++)
        if (strcmp(instr, instructions[i].str) == 0)
            return instructions[i].n;
    return -1;
}
int loc_for_var(char *varname)
{
    int n_vars = sizeof(variables) / sizeof(variables[0]);
    for (int i = 0; i < n_vars; i++)
        if (strcmp(varname, variables[i].str) == 0)
            return variables[i].n;
    return -1;
}

void load_data(int *ram)
{
    FILE *  file = fopen("./instructions", "r");
    int     i    = 0;  // variable location
    char *  line = NULL;
    size_t  len  = 0;
    ssize_t nread;
    while ((nread = getline(&line, &len, file) != -1)) {
        char var_name[maxsize];
        sscanf(line, "%s", var_name);
        if (num_for_instr(var_name) == -1) {
            strcpy(variables[i].str, var_name);
            variables[i].n   = i;
            // TODO put the value of the variable into ram
        }
        i++;
    }
    free(line);
    fclose(file);
    return;
}

void load_instructions()
{

}

int main()
{
    /* CPU REGISTERS */
    int ram[ramsize];  // array acts as main memory
    /* int   acc = 0;       // acculumator */
    /* int   pc  = 0;       // program counter */
    /* int   mar = 0;       // memory address register */
    /* int   mdr = 0;       // memory data register */
    /* char *cir;           // current instruction register */
    load_data(ram);
    return 0;
}
#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_LEN 6

unsigned char cpu_ram_read(struct cpu *cpu, unsigned char MAR) {
  return cpu->ram[MAR];
}

void cpu_ram_write(struct cpu *cpu, unsigned char MAR, unsigned char MDR) {
  cpu->ram[MAR] = MDR;
  return;
}

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu, int argc, char **argv) {
  //  char data[DATA_LEN] = {
  //    // From print8.ls8
  //    0b10000010, // LDI R0,8
  //    0b00000000,
  //    0b00001000,
  //    0b01000111, // PRN R0
  //    0b00000000,
  //    0b00000001  // HLT
  //  };
  //
  //  int address = 0;
  //
  //  for (int i = 0; i < DATA_LEN; i++) {
  //    cpu->ram[address++] = data[i];
  //  }

  // TODO: Replace this with something less hard-coded
  if (argc != 2) {
    printf("Correct usage: ./files file_name.extension\n");
    return;
  }

  FILE *fp;
  char line[MEM_SIZE];

  fp = fopen(argv[1], "r");

  if (fp == NULL) {
    printf("Error opening file.\n");
    return;
  }

  int address = 0;

  while (fgets(line, MEM_SIZE, fp) != NULL) {
    char *endptr;

    unsigned char val = strtoul(line, &endptr, 2);

    if (line == endptr) {
      //         printf("skipping: %s", line);
      continue;
    }

    cpu->ram[address++] = val;
  }
  fclose(fp);
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  (void)cpu;
  (void)regA;
  (void)regB;

  switch (op) {
    case ALU_MUL:
      // TODO
      break;

    // TODO: implement more ALU ops
  }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running) {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    unsigned char IR = cpu_ram_read(cpu, cpu->PC);
    // 2. Figure out how many operands this next instruction requires
    // 3. Get the appropriate value(s) of the operands following this instruction
    unsigned char operand0 = cpu_ram_read(cpu, cpu->PC + 1);
    unsigned char operand1 = cpu_ram_read(cpu, cpu->PC + 2);
    // 4. switch() over it to decide on a course of action.
    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.
    switch (IR) {
    case LDI:
      cpu->registers[operand0] = operand1;
      cpu->PC += 3;
      break;

    case PRN:
      printf("%d\n", cpu->registers[operand0]);
      cpu->PC += 2;
      break;

    case HLT:
      running = 0;
      break;

    default:
      printf("Unknown command 0x%02X at 0x%02X\n", IR, cpu->PC);
      exit(1);
    }
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  // initialize PC to 0
  cpu->PC = 0;
  cpu->FL = 0;
  //  cpu->IR = 0;
  //  cpu->MAR = 0;
  //  cpu->MDR = 0;

  // initialize first 7 registers to 0
  //  for (int i = 0; i < 7; i++) {
  //    cpu->registers[i] = 0;
  //  }
  memset(cpu->registers, 0x00, 7 * sizeof(unsigned char));
  // initialize last register to 0xF4
  cpu->registers[7] = 0xF4;

  // initialize memory to 0
  //  for (int j = 0; j < MEM_SIZE; j++) {
  //    cpu->ram[j] = 0;
  //  }

  memset(cpu->ram, 0x00, 256 * sizeof(unsigned char));
}

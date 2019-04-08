#include "cpu.h"

#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu)
{
  char data[DATA_LEN] = {
    // From print8.ls8
    0b10000010, // LDI R0,8
    0b00000000,
    0b00001000,
    0b01000111, // PRN R0
    0b00000000,
    0b00000001  // HLT
  };

  int address = 0;

  for (int i = 0; i < DATA_LEN; i++) {
    cpu->ram[address++] = data[i];
  }

  // TODO: Replace this with something less hard-coded
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
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
    unsigned char instruction = memory[cur_index];
    // 2. Figure out how many operands this next instruction requires
    // 3. Get the appropriate value(s) of the operands following this instruction
    // 4. switch() over it to decide on a course of action.
    switch (instruction) {
      // 5. Do whatever the instruction should do according to the spec.
      // 6. Move the PC to the next instruction.
    case PRN:
      //      * `PRN`: a pseudo-instruction that prints the numeric value stored
      //      in a register.
      printf("PRN");
      printf("%s", cpu->ram[cpu->PC + 1]);
      cpu->PC += 2;
      break;

    case LDI:
      //      * `LDI`: load "immediate", store a value in a register, or "set
      //      this register to this value".
      printf("LDI");
      cpu->ram[cpu->PC + 1] = cpu->ram[cpu->PC + 2];
      cpu->PC += 3;
      break;

    case HLT:
      //      * `HLT`: halt the CPU and exit the emulator.
      printf("HLT");
      running = 0;
      break;

    default:
      printf("Unknown command");
      break;
    }
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  cpu->PC = 0;
  cpu->registers = {0, 0, 0, 0, 0, 0, 0, 0xF4};
  cpu->ram = {0, 0, 0, 0, 0, 0, 0, 0};

  cpu_load(cpu);
  cpu_run(cpu);
}

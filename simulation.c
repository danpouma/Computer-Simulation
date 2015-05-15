#include <stdio.h>
#include <stdlib.h>

#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUB 31
#define DIV 32
#define MULT 33
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

void read_word( int*, int );
void write_word( int*, int );
void load_program( int*, int );
void fetch( int*, int, int* );
void decode( int, int*, int* );
int execute( int, int, int*, int*, int* );
void dump_memory( int*, int );
void add( int*, int*, int );
void subtract( int*, int*, int );
void divide( int*, int*, int );
void multiply( int*, int*, int );
void load( int*, int*, int );
void store( int*, int*, int );
void branch ( int*, int );
void branchneg( int*, int, int );
void branchzero( int*, int, int );

int main( void )
{
	int* memory; // Memory
	int pc; // Program Counter
	int ir; // Instruction Register
	int op; // Operation Code
	int address; // Address
	int accumulator; // Accumulator
	int size; // Size for malloc
	int complete = 0; //check for halt

	// Welcome the user
	printf( "%s\n", "Welcome to Dan Poumakis' Simulator!" );
	do
	{
		// Prompt user to enter memory size
		printf( "%s", "Enter memory size (10-1000) --> " );
		// Store size
		scanf( "%d", &size );
    } while ( size <= 10 && size >= 1000 );

    // Malloc memory according to size
    memory = malloc( sizeof( int ) * size );

    // Load program
    load_program( memory, size );

    // Initalize program counter
    pc = 0;
    while ( pc < size && complete == 0 )
	{
		// Fetch
	    fetch( memory, pc, &ir );
	    // Decode
	    decode( ir, &op, &address );
	    // Execute, store result in complete to control loop
	    complete = execute( op, address, memory, &accumulator, &pc );	    
	}

	// Print memory to user
	dump_memory( memory, size );
	
}

void fetch( int* memory, int pc, int* ir )
{
	*ir = memory[pc];
}

void decode( int ir, int* op, int* address )
{
	*op = ir / 1000;
	*address = ir % 1000;
}

int execute( int op, int address, int* memory, int* accumulator, int* pc )
{
	switch ( op )
	{
		case READ:
			read_word( memory, address );
			(*pc)++; //make sure it dereferences then adds
			break;

		case WRITE:
			write_word( memory, address );
			(*pc)++;
			break;

		case LOAD:
			load( memory, accumulator, address );
			(*pc)++;
			break;

		case STORE:
			store( memory, accumulator, address );
			(*pc)++;
			break;

		case ADD:
			add( accumulator, memory, address );
			(*pc)++;
			break;

		case SUB:
			subtract( accumulator, memory, address );
			(*pc)++;
			break;

		case DIV:
			divide( accumulator, memory, address );
			(*pc)++;
			break;

		case MULT:
			multiply( accumulator, memory, address );
			(*pc)++;
			break;

		case BRANCH:
			branch( pc, address );
			break;

		case BRANCHNEG:
			branchneg( pc, *accumulator, address );
			break;

		case BRANCHZERO:
			branchzero( pc, *accumulator, address );
			break;

		case HALT:
			// Do nothing
			return 1; // return 1 to break loop
			break;

		default:
			// Do nothing
			break;
	}

	return 0; // return 0 to continue loop
}

void load( int* memory, int* accumulator, int address )
{
	*accumulator = memory[address];
}

void store( int* memory, int* accumulator, int address)
{
	memory[address] = *accumulator;
}

void add( int* accumulator, int* memory, int address )
{
	*accumulator += memory[address];
}

void subtract( int* accumulator, int* memory, int address )
{
	*accumulator -= memory[address];
}

void divide( int* accumulator, int* memory, int address )
{
	*accumulator /= memory[address];
}

void multiply( int* accumulator, int* memory, int address )
{
	*accumulator *= memory[address];
}

void read_word( int* memory, int address )
{
	int num;
	printf( "%s", "Enter num --> " );
	scanf( "%d", &num );
	memory[address] = num;	
}

void write_word( int* memory, int address )
{
	printf( "%d\n", memory[address] );
}

void load_program( int* memory, int size )
{
    for ( int i = 0; i < size; i++ )
    {
    	int num;
    	scanf( "%d", &num );
    	memory[i] = num;
    }
}

void dump_memory( int* memory, int size )
{
	for ( int i = 0; i < size; i++ )
	{
		printf( "%2d: %d\n", i, memory[i] );
	}
}

void branch ( int* pc, int address )
{
	*pc = address;
}

void branchneg( int* pc, int accumulator, int address)
{
	if ( accumulator < 0 )
	{
		*pc = address;
	}
	else
	{
		(*pc)++;
	}
}

void branchzero( int* pc, int accumulator, int address)
{
	if ( accumulator == 0 )
	{
		*pc = address;
	}
	else
	{
		(*pc)++;
	}
}

#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include "structure.h"
#include "disk_operation.h"
#include "b_tree.h"
#include "main.h"

void print_row(Row* row) {
	printf("(%d, %s, %s)\n", row->id, row->username, row->email);
}

InputBuffer* new_input_buffer() {
	InputBuffer* input_buffer 	= (InputBuffer*) malloc(sizeof(InputBuffer));
	input_buffer->buffer 		= NULL;
	input_buffer->buffer_length = 0;
	input_buffer->input_length 	= 0;

	return input_buffer;
}

void print_prompt() {
	printf("db> ");
}

void read_input(InputBuffer* input_buffer) {
	ssize_t bytes_read = getline( &(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

	if (bytes_read <= 0) {
		printf("Error reading input \n");
		exit(EXIT_FAILURE);
	}

	input_buffer->input_length = bytes_read - 1;
	input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer) {
	free(input_buffer->buffer);
	free(input_buffer);
}

MetaCommandResult do_meta_command(InputBuffer* input_buffer, Page *page) {
	if(strcmp(input_buffer->buffer, ".exit") == 0){
		free(page); 
		exit(EXIT_SUCCESS);	
	} 
	return META_COMMAND_UNRECOGNIZED_COMMAND;	
}

PrepareResult prepare_insert(InputBuffer* input_buffer, Statement* statement) {
	statement->type = STATEMENT_INSERT;

	char* keyword = strtok(input_buffer->buffer, " ");
	char* id_string = strtok(NULL, " ");
	char* username = strtok(NULL, " ");
	char* email = strtok(NULL, " ");

	if (id_string == NULL || username == NULL || email == NULL) {
		return PREPARE_SYNTAX_ERROR;
	}

	int id = atoi(id_string);
	if( id < 0) {
		return PREPARE_NEGATIVE_ID; 
	}

	Row *row = malloc(sizeof(Row));
	row->id = id;
	strcpy(row->username, username);
	strcpy(row->email, email);

	statement->row_to_insert = row ;

	return PREPARE_SUCCESS;
}

PrepareResult prepare_select(InputBuffer* input_buffer, Statement* statement) {
	statement->type = STATEMENT_SELECT;

	char* keyword = strtok(input_buffer->buffer, " ");
	char* id_string = strtok(NULL, " ");

	uint32_t id = atoi(id_string);
	statement->wanted_element = id;

	return PREPARE_SUCCESS;
}

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement){
	if(strncmp(input_buffer->buffer, "insert", 6) == 0) {
		return prepare_insert(input_buffer, statement);	
	}
	if (strncmp(input_buffer->buffer, "select", 6) == 0) {
		return prepare_select(input_buffer, statement);
	}

	return PREPARE_UNRECOGNIZED_STATEMENT;
}

ExecuteResult execute_insert(Statement* statement, Page *root) {
	Row* row_to_insert = statement->row_to_insert;
	uint32_t key_to_insert = row_to_insert->id;
	b_tree_insert(root, row_to_insert);
	return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement* statement, Page* root) {
	Row *row = malloc(sizeof(Row)); 
	row = b_tree_search(root, statement->wanted_element);
	print_row(row);	
	return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement* statement, Page* root) {
	switch (statement->type) {
		case (STATEMENT_INSERT):
			return execute_insert(statement, root);
		case (STATEMENT_SELECT):
			return execute_select(statement, root);
	}
}

Page* db_open() {
	return load_root();
}

int main(int argc, char* argv[]) {
	Page* root = db_open();

	InputBuffer* input_buffer = new_input_buffer();

	while(true) {
		print_prompt();
		read_input(input_buffer);

		if(input_buffer->buffer[0] == '.') {
			switch(do_meta_command(input_buffer, root)) {
				case (META_COMMAND_SUCCESS):	
					continue;
				case (META_COMMAND_UNRECOGNIZED_COMMAND):
					printf("Unrecognized command '%s'\n", input_buffer->buffer);
					continue;
			}
		}

		Statement statement;
		switch(prepare_statement(input_buffer, &statement)){
			case(PREPARE_STRING_TOO_LONG):
				printf("String is too long\n");
				continue; 
			case(PREPARE_SUCCESS):
				break;
			case(PREPARE_SYNTAX_ERROR):
				printf("Syntax error. Could not parse statement. \n");
				continue;
			case(PREPARE_UNRECOGNIZED_STATEMENT):
				printf("Unrecognized keyword ar start of '%s'.\n", input_buffer->buffer);
				continue;
			case(PREPARE_NEGATIVE_ID):
				printf("This id is negative \n");
				continue;
		}

		switch(execute_statement(&statement, root)){
			case(EXECUTE_SUCCESS):
				printf("Executed \n");
				break;
			case(EXECUTE_TABLE_FULL):
				printf("Error: Table full. \n");
				break;
			case (EXECUTE_DUPLICATE_KEY):
				printf("Error: Duplicate key \n");
				break;
		}
	}
}

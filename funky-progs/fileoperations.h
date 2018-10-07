#ifndef FILEOPERATIONS_DYNAMIC_H
#define FILEOPERATIONS_DYNAMIC_H
#include <stdio.h>

#define strnicmp strncasecmp

#include "record.h"

struct File{
	void create();
	void close();
	void add(Phone_Record *);                                           
	int search(char []);
	void remove(int recordnum);
	void update(int recordnum, Phone_Record *);
    
	Phone_Record *records;
	int num_records;   // number of records in the dynamic array
	int size;
};
#endif



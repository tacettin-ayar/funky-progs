#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "fileoperations.h"


using namespace std;


void File::add(Phone_Record *new_record_ptr){
   int current_index;
   Phone_Record *temp;
   
   if(num_records == size){
      size *= 2;
   	  temp = new Phone_Record[size];

	  for(current_index=0; current_index < size; current_index++){
	  	temp[current_index].name = new char[strlen(records[current_index].name)];
	  	strcpy(temp[current_index].name, records[current_index].name);
        delete records[current_index].name;
        
	  	temp[current_index].phonenum = new char[strlen(records[current_index].phonenum)];
	  	strcpy(temp[current_index].phonenum, records[current_index].phonenum);
        delete records[current_index].phonenum;
	  } 
      delete[] records;
      
      temp[current_index].name = new char[strlen(new_record_ptr->name)];
	  strcpy(temp[current_index].name, new_record_ptr->name);
      temp[current_index].phonenum = new char[strlen(new_record_ptr->phonenum)];
	  strcpy(temp[current_index].phonenum, new_record_ptr->phonenum);
     
	  num_records++;
	  records = temp;
   }
   else {
      records[num_records].name = new char[strlen(new_record_ptr->name)];
	  strcpy(records[num_records].name, new_record_ptr->name);
	  
      records[num_records].phonenum = new char[strlen(new_record_ptr->phonenum)];
	  strcpy(records[num_records].phonenum, new_record_ptr->phonenum);
     
	  num_records++;
   }
}

void File::create(){
   records = new Phone_Record[INIT_SIZE];
   num_records = 0;
   size = INIT_SIZE;
}

void File::close(){

    for(num_records--; num_records >= 0; num_records--) {
        delete records[num_records].name;
	    delete records[num_records].phonenum;
	}

	delete[] records;
}

int File::search(char *target){
	int current_index = 0;
	bool all = false;
	int num_found = 0;
	
	if( strcmp(target, "*") == 0 ) all = true;

	for( ; current_index < num_records; current_index++ ){		
		
		if(!all && strnicmp(records[current_index].name, target, strlen(target))!=0 )
			continue;    // Continue the loop, look at the next record (if any)

		// A match is found, list it and increment number of found records 
		cout << current_index << "." << records[current_index].name << " ";
		cout << records[current_index].phonenum << endl;
		num_found++;
	}	
	
	return num_found;
}

void File::update(int record_num, Phone_Record *new_record_ptr){
   delete records[record_num].name;
   records[record_num].name = new char[strlen(new_record_ptr->name)];
   strcpy(records[record_num].name,     new_record_ptr->name);

   delete records[record_num].phonenum;
   records[record_num].phonenum = new char[strlen(new_record_ptr->phonenum)];
   strcpy(records[record_num].phonenum, new_record_ptr->phonenum);
}

void File::remove(int record_num){
	delete records[record_num].name;
	delete records[record_num].phonenum;

    for(num_records--; record_num < num_records; record_num++) 
	   records[record_num] = records[record_num+1];
	   	   
}

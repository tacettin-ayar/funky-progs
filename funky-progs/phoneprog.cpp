#include <iostream> // C++ giriþ/çýkýþ fonksiyonlarý için
#include <stdlib.h> // system("cls") fonksiyonu için
#include <iomanip>  // cin.ignore(), setw, vb. kullanýmlar için

#include "fileoperations.h" // Kapsül tanýmlarý


using namespace std; // cin ve cout iþlemlerinin kýsa yazýmý için


typedef File Datastructure; // Kapsül deðiþkeni

Datastructure book;

// Fonksiyon prototip tanýmlarý:
void print_menu();
bool perform_operation(char);
void search_record();
void add_record();
void delete_record();
void update_record();


int main(){	
	book.create();	
	bool end = false; 
	char choice; 	
	while (!end) { 
		print_menu(); 
		cin >> choice;
		end = perform_operation(choice); 
		} 	
	book.close();
	return EXIT_SUCCESS;
}

void print_menu(){
	system("cls"); 
	cout << endl << endl;
	cout << "PHONE BOOK APPLICATION" << endl;
	cout << "Choose an operation" << endl;
	cout << "S: Record Search" << endl;
	cout << "A: Record Add" << endl;
	cout << "U: Record Update" << endl;
	cout << "D: Record Delete" << endl;	
	cout << "E: Exit" << endl;	
	cout << endl;
	cout << "Enter a choice {S,A,U,D,E}: ";
}

bool perform_operation(char choice){
	bool terminate=false;
	switch (choice) { 
	case 'S': case 's': 
			search_record();
			break; 
		case 'A': case 'a': 
			add_record();
			break; 
		case 'U': case 'u': 
			update_record();
			break;
		case 'D': case 'd': 
			delete_record();
			break;
		case 'E': case 'e': 
			cout << "Are you sure you want to exit the program? (Y/N):";
			cin >> choice;
			if(choice=='Y' || choice=='y')
			   terminate=true; 
			break; 
		default: 
			cout << "Error: You have entered an invalid choice" << endl; 
			cout << "Please try again {S, A, U, D, E}  :" ;
			cin >> choice;
			terminate = perform_operation(choice);
			break; 
	}
	return terminate;
}

void search_record(){
	char name[NAME_LENGTH];
	cout << "Please enter the name of the person you want to SEARCH for (press'*'for full list):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(name,NAME_LENGTH);		
	if(book.search(name)==0){
		cout << "Could not find a record matching your search criteria" << endl;
	}
	getchar(); // system("pause") yerine kullanýlýyor.
};

void add_record(){
	Phone_Record newrecord;	
    newrecord.name = new char[NAME_LENGTH];
    newrecord.phonenum = new char[PHONENUM_LENGTH];

	cout << "Please enter contact information you want to ADD" << endl;
	cout << "Name : " ;	
	cin.ignore(1000, '\n');
	cin.getline(newrecord.name,NAME_LENGTH);
	cout << "Phone number :";
	cin >> setw(PHONENUM_LENGTH) >> newrecord.phonenum;
	book.add(&newrecord);
	cout << "Record added" << endl;
	getchar(); 
	
	delete[] newrecord.name;
	delete[] newrecord.phonenum;
};

void delete_record(){
	char name[NAME_LENGTH];
	int choice;	
	cout << "Please enter the name of the person whose record you want to DELETE (press'*'for full 	    list):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(name,NAME_LENGTH);		
	int personcount=book.search(name); 
	if(personcount==0){
		cout << "Could not find a record matching your search criteria" << endl;		
	}
	else {
		if (personcount==1){		
			cout << "Record found." << endl;
			cout << "If you want to delete this record please enter its number (Enter -1 to exit without performing any operations): " ;
		}
		else
			cout << "Enter the number of the record you want to delete (Enter -1 to exit without performing any operations): " ;
		cin >> choice;
		if(choice==-1) return;
		book.remove(choice);	
		cout << "Record deleted." <<endl;
		
	}
	getchar(); 
};

void update_record(){
	char name[NAME_LENGTH];
	int choice;	
	cout << "Please enter the name of the person whose record you want to UPDATE (press'*'for full list):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(name,NAME_LENGTH);		
	int personcount=book.search(name); 
	if(personcount==0){
		cout << "Could not find a record matching your search criteria" << endl;		
	}
	else {
		if (personcount==1){		
			cout << "Record found." << endl;
			cout << "If you want to update this record please enter 			   its number (Enter -1 to exit without performing any operations): " ;
		}
		else
			cout << "Enter the number of the record you want to update (Enter -1 to exit without performing any operations): " ;

		cin >> choice;

		if(choice==-1) return;

		Phone_Record newrecord;
        newrecord.name = new char[NAME_LENGTH];
        newrecord.phonenum = new char[PHONENUM_LENGTH];

		cout << "Please enter current contact information" << endl;
		cout << "Name : " ;
		cin.ignore(1000, '\n');
		cin.getline(newrecord.name,NAME_LENGTH);
		cout << "Phone number :";
		cin >> setw(PHONENUM_LENGTH) >> newrecord.phonenum;
		book.update(choice,&newrecord);	
		cout << "Record successfully updated." <<endl;		
		delete[] newrecord.name;
   	    delete[] newrecord.phonenum;
	}
	getchar(); 
};

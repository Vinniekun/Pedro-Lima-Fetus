#include "DataBase.h"

char* DataBase::sql;

int DataBase::Init(char* address){
 	const char* data = "Callback function called";
 	char* zErrMsg = 0;
 	int row = 0;
 	char* selectQuery;
 	sqlite3* db;
 	sqlite3_stmt* stmt;
 	
 	if (sqlite3_open(address, &db) != SQLITE_OK){
 		printf("Error occurred on opening database\n");
 		exit(1);
 	}
 	sqlite3_prepare(db,selectQuery, strlen(selectQuery)+ 1, &stmt, NULL);
 	while (1){
 		int s;
 		printf ("in select while\n");
 		s = sqlite3_step(stmt);
 		if (s == SQLITE_ROW){
 			int bytes = sqlite3_column_bytes(stmt,0);
 			const unsigned char* text = sqlite3_column_text(stmt, 1);
 			printf ("%d: %s\n", row, text);
 			row++;
 		}
 		else if(s == SQLITE_DONE)
 			break;
 		else{
 			printf ("Failed\n");
 			exit (1);
 		}
 	}
 	sqlite3_finalize(stmt);
 	sqlite3_close(db);
 	return 0;

 }	



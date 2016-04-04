#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class DataBase{
	private:
		static char* sql;

	public:
		static int Init(char* address);
		
};
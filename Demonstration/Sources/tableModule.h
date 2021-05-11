#ifndef TABLE_FUNCTIONS_HEADER
#define TABLE_FUNCTIONS_HEADER

// Table module functions
typedef struct {
  char rowName[10];
  char colName[10];
  int rowSize;
  int colSize;

}Table;

void createTable (void);

#endif
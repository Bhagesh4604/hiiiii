#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define MAX_NUM_EMPLOYEES 100 
#define MAX_HASH_TABLE_SIZE 50 
typedef struct 
{ 
 int iKey; 
 char cName[50]; 
}EMPLOYEE; 
EMPLOYEE* stHashTable[MAX_HASH_TABLE_SIZE]; 
int fnCompHash(int, int); 
void fnInsRecord(EMPLOYEE*, int); 
EMPLOYEE* fnSrchRecord(int, int); 
int main() 
{ 
 int m; 
 printf("Enter the size of the hash table (m): "); 
 scanf("%d",&m);  
 for (int i = 0; i < m; i++) 
 { 
 stHashTable[i] = NULL; 
 } 
 FILE* file = fopen("employee.txt", "r"); 
 if(file == NULL) 
 { 
 printf("Error opening file.n"); 
 return 1; 
 } 
 int n = 0; 
 EMPLOYEE emp; 
 while(fscanf(file, "%d %s", &emp.iKey, emp.cName) != EOF) 
 { 
 EMPLOYEE* newEmp = (EMPLOYEE*)malloc(sizeof(EMPLOYEE)); 
 newEmp->iKey = emp.iKey; 
 strcpy(newEmp->cName, emp.cName); 
 fnInsRecord(newEmp, m); 
 n++; 
 } 
 fclose(file); 
 int iSrchKey; 
 printf("Enter a key to search for an employee record: "); 
 scanf("%d", &iSrchKey); 
 EMPLOYEE* found = fnSrchRecord(iSrchKey, m); 
 if(found != NULL) 
 { 
 printf("Employee found with key %d:\n", found->iKey); 
 printf("Name: %s\n", found->cName); 
 } 
 else 
 { 
 printf("Employee with key %d not found.\n", iSrchKey); 
 } 
 return 0; 
} 
void fnInsRecord(EMPLOYEE* emp, int m) 
{ 
 int index = fnCompHash(emp->iKey, m); 
 while(stHashTable[index] != NULL) 
 { 
 index = (index + 1) % m; 
 } 
 stHashTable[index] = emp; 
} 
int fnCompHash(int iKey, int m) 
{ 
 return iKey % m; 
} 
EMPLOYEE* fnSrchRecord(int iKey, int m) 
{ 
 int index = fnCompHash(iKey, m); 
 while(stHashTable[index] != NULL) 
 { 
 if(stHashTable[index]->iKey == iKey) 
 { 
 return stHashTable[index]; 
 } 
 index = (index + 1) % m; 
 } 
 return NULL; 
} 
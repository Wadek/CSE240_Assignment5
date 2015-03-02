#include <stdio.h> 
#include <string.h>
#include <ctype.h>
#pragma warning(disable: 4996)
#define max 100
typedef enum {diploma, bachelor, master, doctor} education;
char *myDatabase = "filename"; // global declaration of file pointer
 
struct person {              // a node to hold personal details
  char name[30];
  char email[30];
  int phone;
  education degree;
};
 
struct person directory[max]; // an array of structures, 100 entries
int tail = 0;                 // global variable
 
void flush();                 // forward declaration of functions
void branching(char c);       
void saveFile(char *myDatabase);
void loadFile(char *myDatabase);
int insertion();
int print_person(int i);
int print_all(); 
int search_person();
int delete_person();
 
 
int main() {  // print a menu for selection
  loadFile(myDatabase);
  char ch = 'i';
 
  ungetc('\n', stdin); // inject the newline character into input buffer
 
  do {
    printf("Enter your selection\n");
    printf("\ti: insert a new entry\n");
    printf("\td: delete an entry\n");
    printf("\ts: search an entry\n");
    printf("\tp: print all entries\n");
    printf("\tq: quit \n");
 
    flush();  // flush the input buffer. To be discussed later
    ch = tolower(getchar());      
    branching(ch);
  } while (ch != 113); 
  saveFile(myDatabase);
  return 0;
}
 
void loadFile(char *filename)
{
  //char[]  zname;
  //char[] zemail;
  //int zphone;
  //int zdegree;

  FILE *filedescriptor = fopen(filename, "rb");
  if(filedescriptor != NULL)
  {
    fread(&tail, sizeof(tail), 1, filedescriptor);
    int i = 0;
    for( i = 0; i < tail; i++)
    {
      /*fscanf(filedescriptor, "%s %s %d %d", zname, zemail, &zphone, &zdegree);
      strcpy(name, zname);
      strcpy(email, zemail);
      strcpy(&phone, &zphone);
      strcpy(&degree, &zdegree);*/
      fread(directory[i].name, sizeof(directory[i].name), 1, filedescriptor);
      fread(directory[i].email, sizeof(directory[i].email), 1, filedescriptor);
      fread(&directory[i].phone, sizeof(directory[i].phone), 1, filedescriptor);  
      fread(&directory[i].degree, sizeof(directory[i].degree), 1, filedescriptor);

    }
  }
}
 
void saveFile(char *filename)
{
 FILE *filedescriptor = fopen(filename, "wb"); // w for write, b for binary 
 
  if(filedescriptor != NULL)
  { 
    fwrite(&tail, sizeof(tail), 1, filedescriptor);  // save the tail variable
    int i = 0;
    for (i = 0 ; i < tail; i++)
    {
      fwrite(directory[i].name, sizeof(directory[i].name), 1, filedescriptor);
      fwrite(directory[i].email, sizeof(directory[i].email), 1, filedescriptor);
      fwrite(&directory[i].phone, sizeof(directory[i].phone), 1, filedescriptor);
      fwrite(&directory[i].degree, sizeof(directory[i].degree), 1, filedescriptor);
    
    }
    fclose(filedescriptor);//closes file
  }
  else
    printf ("ERROR: Could not open file:%s for saving data !\n", filename);
}

void flush() {  // flush the input buffer. To be discussed later
  int c;
  do {
    c = getchar();
  } while (c != '\n' && c != EOF);
}
 
 
void branching(char c) {    // branch to different tasks
  switch (c) {
    case 'i':
      insertion();
      break;
    case 's':
      search_person();
      break;
    case 'd':
      delete_person();
      break;
    case 'p':
      print_all(); 
      break;
    case 'q':
      break;
    default:
      printf("Invalid input\n");
  }
}
 
int insertion() 
{    // insert a new entry at the end
  int degreeTemp = 0;  
 
  if(tail == max)
  {
    printf("There are no more places to insert.\n");
    return -1;
  }
  else
  {
    printf("Enter name, phone, email:\n");
    scanf("%s", directory[tail].name);
    scanf("%d", &directory[tail].phone); //sizeof(directory[tail].phone));
    scanf("%s", directory[tail].email);
  }
  do
  { 
    printf("Please Enter Education: \n0: diploma \n1: bachelor \n2: master \n3: doctorate \n");  
    scanf("%d", &degreeTemp);
  }while(degreeTemp > 3 || degreeTemp < 0);
 
  directory[tail].degree = degreeTemp;
  tail++;
 
  int i, didSwap = 1, limit = tail - 1; // note the - 1 on tail
  struct person temp; // finally realized that you dont' actually need this to be a pointer.
 
 
  while (didSwap) // tried for loop in a for loop initially, but it just caused problems
  {
    didSwap = 0;
    for (i = 0; i < limit; i++) 
    {
      if (strcmp (directory[i].name, directory[i+1].name) > 0) //handy way to check if ascending
      {
        temp = directory[i]; // do the ol' swap-a-roo
        directory[i]  = directory[i+1];
        directory[i+1] = temp;
        didSwap = 1; // ol' swap-a-roo done
      }
    }
    limit--;
  }
  printf("The number of entries = %d\n", tail);
  return 0;
}
 
int print_person(int i) { 
  // print all information one person in the directory
  printf("\n\nname = %s\n", directory[i].name);
  printf("email = %s\n", directory[i].email);
  printf("phone = %d\n", directory[i].phone);
  switch(directory[i].degree)
  {
    case diploma:
      printf("degree = diploma \n");
      break;
    case bachelor:
      printf("degree = bachelor \n");
      break;
    case master:
      printf("degree = master \n");
      break;
    case doctor: 
      printf("degree = doctor \n");
      break;
  }
  return 0;
 
}
 
int print_all() { 
 
  // print all information each person in the contactbook
  int i;
 
  if (tail == 0) {
    printf("No entries found.");
  }
 
  else {
    for (i = 0; i < tail; i++) {
      print_person(i);
    }
  }
 
  return 0; 
}
 
int search_person() {      // print phone and email via name
  char sname[30];
  struct person *index; //pointer declaration
  int i = 0;
  index = &directory[0];//giving pointer starting point
 
  printf("Please enter the name to be searched for:\n");
  scanf("%s", sname);
 
  // search method should be a while loop, replace all array with pointer operations
  while(i < tail) //runs while i is less than the amount of entries
  {
    if(strcmp(sname,(index+i) -> name) == 0)//easier than using  (*(index+i)).name
    {
      print_person(i);//print correct person when case is met
      return i;
    }
    i++;
  }
  printf("The name does not exist.\n");
  return -1;
}
int delete_person() {
  int i, k;
  k = search_person();
  if (k == -1) {
    printf("The name does not exist.\n"); return -1;
  }
  else {
    for (i = k; i<tail; i++) {
      strcpy(directory[i].name, directory[i + 1].name);
      directory[i].phone = directory[i + 1].phone;
      strcpy(directory[i].email, directory[i + 1].email);
      printf("The index deleted is: %d\n", k);
    }
    tail--;
    return k;
  }
}


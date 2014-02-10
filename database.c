
//PROGRAM WITH PERSISTENT DATA ASSIGNMENT
//PROGRAM TO MANAGE EMPLOYEES DATAS

//Adam Miedziejewski
//ID: C12701419
//DT228/1
//Group: C
//Date: 11/04/13

/*###########################################################################################################

   Program is driven by menu which provide number of options like:
   - add employee record
   - delete employee record
   - display records
   - compact records
   - exit

   Add Employee should ideally include a restriction that the Employee number is unique.
   Employee should be deleted, after requesting an Employee number as the key.
   If the employee record cannot be found, the user should be informed, otherwise the record
   should be marked with ‘*’ in the first byte. List Employees, should display on Screen a
   list of all active employees on file, followed by the total number of records and number
   of deleted employees values retrieved from the header record. Appropriate titles and
   formatting should be used for displaying this information in a meaningful manner.

   Compact Records, should cause the removal of all external fragmentation from the file.
   Adding, deleting and compacting record(s) options, should result in the appropriate updates
   to the header record and informative messages to the user of the outcome.
   Appropriate error checking should be included (e.g. checking for successful opening of files).

   At the commencement of your program, you should check to see if the employee file already exists,
   if not, create one and add an initialised header record and inform user. The data file will be named
   “employee.dat” and is a binary file. The data file will contain a header record and employee records.

###########################################################################################################*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MENUSIZE 5



//STRUCTURES DECLARATION
struct EmployeeHeader
{
    int total;
    int deleted;
    char filler[16];
};
struct EmployeeRecords
{
    char number[6];
    char lastName[16];
    char firstName[16];
    char address[26];
    char department[10];
    char duration[2];
};


//INTRODUCING FUNCTIONS PROTOTYPE
void make_head(void);
void add(void);
void del(void);
void display(void);
void updateHead(void);
void compact(void);

//DEFINE A TYPE REFFERED TO STRUCTURE
struct EmployeeHeader header;
struct EmployeeRecords records;

//FILE POINTER
FILE *pd;


//##################################### MAIN FUNCTION ####################################################

main()
{
    int menu = 0;


    //CHECK IF FILE EXIST IF NOT CREATE HEADER
    if(pd = fopen("employees.dat", "r"))
    {
        fclose(pd);
    }
    else
    {
        //CALL FUNCTION
        make_head();
    }

    while(menu != MENUSIZE)
    {
        //MENU OPTIONS
        printf("\n\n\n\n");
        printf("************ ");
        printf("DATABSE MENU");
        printf(" *************\n\n");
        printf("1) Add Employee\n");
        printf("2) Delete Employee\n");
        printf("3) List Employees\n");
        printf("4) Compact Records\n");
        printf("5) Exit\n\n\n");
        printf("Press option 1 to 5: ");
        scanf("%d",&menu);
        getchar();

        //INVALID INPUT CHECKING
        while(menu>'a' && menu<'z')
        {
            printf("\nInvalid input, press 1 to 5: ");
        }



        //MENU CASES
        switch(menu)
        {
            case 1:
            //CALL FUNCTION
            add();
            break;

            case 2:
            //CALL FUNCTION
            del();
            break;

            case 3:
            //CALL FUNCTION
            display();
            break;

            case 4:
            //CALL FUNCTION
            compact();
            break;

            case 5:
            //EXIT PROGRAM
            system("exit");
            break;

            default:
            //ERRORS HANDLING
            printf("\nInvalid entry type number 1 - 5");
        }

    }
}

//################################### FUNCTION TO CREATE HEADER ###########################################

void make_head(void)
{
    //ASSIGN STARTING VALUES FOR HEADER
    header.total = 0;
    header.deleted = 0;
    header.filler[16];

    //WRITING INTO FILE AND CREATING FILE
    pd = fopen("employees.dat","wb");
        fwrite(&header,sizeof(header), 1, pd);
    fclose(pd);
}


//################################### FUNCTION TO ADD NEW RECORD ##########################################

void add(void)
{
    char choice = 'y'; //menu variable
    char compNumber[6]; //variable to help compare looking record to add with existing records
    int counter;

    pd = fopen("employees.dat","r+b"); //open for read and write

        if(pd == NULL) //check if file exist
        {
            printf("ERROR: Failed to open file!");
        }
        else
        {
            while(choice == 'y' || choice == 'Y') //looping until 'n' pressed
            {
                int temp = 0;
                int position = 0;

                printf("\nType Emplyee Number eg. 10001: "); //ask for number of record you want to add
                gets(compNumber);
                fseek(pd, 0, SEEK_END); //move pointer to the end of file; helps check file size
                counter = ftell(pd); //counter = size of file; starts counting down

                //SEARCH FOR RECORDS WITH ASTERISK IN FIRST BYTE
                while(counter >= 0)
                {
                    fseek(pd, counter, SEEK_SET); //move pointer to the end
                    fread(&records.number, sizeof(records.number), 1, pd); //read record number

                    if(records.number[0] == '*')
                    {
                        position = counter; //record psition of last record found with asterisk in first byte
                        temp = 1; //helps drive next part of code
                    }
                    else if(strcmp(records.number, compNumber) == 0) //compare record numbers (if record already exist)
                    {
                        printf("\nNumber already exist try again (y/n): ");
                        scanf("%s", &choice);
                        getchar();
                        temp = 2; //helps drive next part of code
                    }
                    counter = counter - sizeof(records); //move pointer back by record size
                }

                if(temp == 1) //(record found) replace first record with asterisk in first byte with new record
                {
                    printf("\nType Last Name: ");
                    gets(records.lastName);
                    printf("\nType First Name: ");
                    gets(records.firstName);
                    printf("\nType Employee Address: ");
                    gets(records.address);
                    printf("\nType Department Code: ");
                    gets(records.department);
                    printf("\nType Employee Duration: ");
                    gets(records.duration);
                    strcpy(records.number, compNumber); //copy typed number into record number
                    fseek(pd, position, SEEK_SET); //move pointer to last position of record with asterisk
                    fwrite(&records,sizeof(records), 1, pd); //write new record to file
                    printf("\n Add another record (y/n): ");
                    scanf("%s", &choice);
                    getchar();
                }
                else if(temp == 0) //dfault value of temp (there is no records with asterisks in first byte); apending new record at the end of file
                {
                    printf("\nType Last Name: ");
                    gets(records.lastName);
                    printf("\nType First Name: ");
                    gets(records.firstName);
                    printf("\nType Employee Address: ");
                    gets(records.address);
                    printf("\nType Department Code: ");
                    gets(records.department);
                    printf("\nType Employee Duration: ");
                    gets(records.duration);
                    strcpy(records.number, compNumber); //copy typed number into record number
                    fseek(pd, 0, SEEK_END); //move pointer to the end of file to apend new record
                    fwrite(&records,sizeof(records), 1, pd); //write new record at the and of file
                    printf("\n Add another record (y/n): ");
                    scanf("%s", &choice);
                    getchar();
                }
            } //end while
        }
    fclose(pd);
} //end add


//################################### FUNCTION TO DELETE RECORD ############################################

void del(void)
{
    char choice = 'y'; //menu variable
    char compNumber[6]; //variable to help compare looking record to delete with existing records
    int temp = 0;
    int counter;

    pd = fopen("employees.dat","r+b"); //open for read and write

        while(choice == 'y' || choice == 'Y') //looping until 'n' pressed
        {
            counter = sizeof(header); //counter starts from 25-th byte

            printf("Enter Employee Number eg. 10001: ");
            gets(compNumber);
            //LOOP SEARCHING FOR RECORD NUMBER
            do
            {
                fseek(pd, counter, SEEK_SET);
                fread(&records.number, sizeof(records.number), 1, pd); //read record number
                if(strcmp(compNumber, records.number) == 0) //compare record number with that what we wont to delete
                {
                    records.number[0] = '*'; //puts astarisk into first byte of record
                    fseek(pd,counter ,SEEK_SET); //set pointer
                    fwrite(&records.number,1,1,pd); //write into file
                    counter = (counter + sizeof(records)); //increase counter by record size
                    temp++; //increase if numbers are the same (helps drive next part of code - menu (y/n))
                }
                else
                {
                    counter = (counter + sizeof(records));
                }
            }
            while(!feof(pd)); //end of file

            //MENU INTERACTING WITH USER
            if(temp == 0)
            {
                printf("Record not found\n");
                printf("Do you want to search for anoyher one [y/n]: ");
                scanf("%s", &choice);
                getchar();
            }
            else
            {
                printf("\nRecord deleted\n");
                printf("Do you want delete another one [y/n]: ");
                scanf("%s", &choice);
                getchar();
                temp = 0;
            }
        }
    fclose(pd);
}


//################################### FUNCTION TO UPDATE HEADER ############################################

void updateHead(void)
{
    int fileSize;
    int counter = 0;
    int recordsDeleted = 0;

    pd = fopen("employees.dat","rb"); //open for read only

        fseek(pd, 0, SEEK_END);
        fileSize = ftell(pd); //get the employees file size
        int recordsSize = (fileSize - sizeof(header));

        //SEARCH FOR RECORDS WITH ASTERISK IN FIRST BYTE
        while(counter != recordsSize)
        {
            fseek(pd, (counter + sizeof(header)), SEEK_SET); //move poiner by 24 bytes (header size)
            fread(&records.number, sizeof(records.number), 1, pd);

            if(records.number[0] == '*')
            {
                recordsDeleted++; //counting records with asterisk in first byte
            }
            counter = counter + sizeof(records); //increase counter by size of record (76 bytes)
        }
        //ASSIGN VALUES FOR NUMBERS OF RECORDS
        header.total = ((fileSize - sizeof(header))/sizeof(records));
        header.deleted = recordsDeleted;
    fclose(pd);
}


//################################### FUNCTION TO DISPLAY RECORDS ###########################################

void display(void)
{
    //call function
    updateHead();


    pd = fopen("employees.dat","rb"); //open for read only

        if(pd == NULL) //checking is file exist
        {
            printf("ERROR: Failed to open file!");
        }
        else
        {
            //PRINT HEADER CONTENT
            printf("\n\n********** EMPLOYEES RECORDS **********\n");
            printf("\nTotal number of records:   %d\n", header.total);
            printf("\nNumber of deleted records: %d\n\n", header.deleted);
            printf("\n***************************************\n");

            //PRINT RECORDS
            fseek(pd, sizeof(header), SEEK_SET);
            while(fread(&records, sizeof(records), 1, pd) != 0) //read records until reach the end of file (find empty byte)
            {
                if(records.number[0] != '*') //display records not marked with star
                {
                    printf("\nNumber:     %s \nLast name:  %s \nFirst name: %s \nAddress:    %s \nDepartment: %s \nDuration:   %s\n\n", records.number, records.lastName, records.firstName, records.address, records.department, records.duration);
                    printf("---------------------------------------\n");
                }
            }
        } //end if
    fclose(pd);
} //end display


//############################################ COMPACT #####################################################

void compact(void)
{
    //assign pointer to temp file
    FILE *temp;

    //call function
    updateHead();

    int counter = sizeof(header);
    int fileSize;

    //READ FROM EMPLOYEES AND WRITE INTO TEMP FILE
    pd = fopen("employees.dat","rb"); //open for read only

        fseek(pd, 0, SEEK_END);
        fileSize = ftell(pd); //get the employees file size

        temp = fopen("temp.dat","w+b"); //open for read and write

            fseek(pd, 0, SEEK_SET);
            fread(&header,sizeof(header), 1, pd); //read header
            fwrite(&header,sizeof(header), 1, temp); //write header

            while(counter != fileSize) //reach end of the employees file
            {
                fseek(pd, counter, SEEK_SET); //move poiner by 24 bytes (header size)
                fread(&records,sizeof(records), 1, pd);
                if(records.number[0] != '*')
                {
                    fwrite(&records,sizeof(records), 1, temp); //write record into temp file
                }
                counter = counter + sizeof(records);
            }
        fclose(temp);
    fclose(pd);

    //READ FROM TEMP AND WRITE INTO EMPLOYEES FILE
    counter = sizeof(header);

    temp = fopen("temp.dat","rb"); //open for read only

        fseek(temp, 0, SEEK_END);
        fileSize = ftell(temp); //get the employees file size

        pd = fopen("employees.dat","w+b"); //open for read and write

            fseek(pd, 0, SEEK_SET);
            fread(&header,sizeof(header), 1, temp); //read header
            fwrite(&header,sizeof(header), 1, pd); //write header

            while(counter != fileSize) //reach end of the temp file
            {
                fseek(temp, counter, SEEK_SET); //move poiner by 24 bytes (header size)
                fread(&records,sizeof(records), 1, temp);
                fwrite(&records,sizeof(records), 1, pd); //write record back into employees file
                counter = counter + sizeof(records);
            }
        fclose(pd);
    fclose(temp);
}




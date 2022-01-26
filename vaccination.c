/**
 * @file vaccination.c
 * @author Bathini Ajay Goud, Vempati Tharun
 * @brief This file demonstrates the entrire Vaccination Management System which includes loggin, 
 * Slot Booking, Searching, Viewing Stock, Adding stock, Update credentials, Viewing records......
 * @version 0.1
 * @date 2022-01-11
 * 
 * @copyright Copyright (c) 2022 
 */
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<conio.h>
#define MAX_YR  9999
#define MIN_YR  1900
#define MAX_SIZE_USER_NAME 30
#define MAX_SIZE_PASSWORD  20
#define FILE_NAME  "Vaccination.txt"
#define FILE_NAMES  "Slots.txt"
// Macro related to the info
#define MAX_NAME   50
#define MAX_AADHARNO 13
#define MAX_ADDRESS 300
#define FILE_HEADER_SIZE  sizeof(sFileHeader)
int stock=5;
typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;
typedef struct
{
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
    char UserName[MAX_SIZE_USER_NAME];
    char PassWord[MAX_SIZE_PASSWORD];
} sFileHeader;
typedef struct// to call in program
{
    char aadharNo[MAX_AADHARNO]; // declare the integer data type
    char name[MAX_NAME];// declare the character data type
    char address[MAX_ADDRESS];// declare the character data type
	unsigned int phoneNo;
    Date date;// declare the integer data type
} p_Info;
//Function Declarations
void printMessageCenter(const char*);
void headMessage(const char *);
void welcomeMessage();
void thankYou();
int isNameValid(const char *);
int isaadharexistalready(const char *);
int isaadharexist(const char *);
int  IsLeapYear(int);
void addStock();
void viewStock();
void addDataInDataBase();
void searchVaccinatedPeople();
void viewRecords();
void bookSlot();
void usermenu();
void adminmenu();
void aCredential();
void uCredential();
void adminlogin();
void userlogin();
void login();
int isFileExists(const char *);
void init();

void printMessageCenter(const char* message)
{
    int len =0;
    int pos = 0;
    //calculate how many space need to print
    len = (78 - strlen(message))/2;
    printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("%s",message);
}
void headMessage(const char *message)
{
    system("cls");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############     Vaccination management System Project in C    ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t\t\t----------------------------------------------------------------------------");
}
//ThankYou Message method
void thankYou()
{
    headMessage("Vasavi College of Engineering");
    printf("\n\n\n\n\n");
    printf("\n\t\t\t  ------------------\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                ThankYou                   =");
    printf("\n\t\t\t        =               Project by                  =");
    printf("\n\t\t\t        =         ******B.Ajay Goud********         =");
    printf("\n\t\t\t        =         *******N.Madhukar********         =");
    printf("\n\t\t\t        =         *****M.Jayanth Kumar*****         =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  ------------------\n");
}
//Welcome Message method
void welcomeMessage()
{
    headMessage("Vasavi College of Engineering");
    printf("\n\n\n\n\n");
    printf("\n\t\t\t  ------------------\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                 WELCOME                   =");
    printf("\n\t\t\t        =                   TO                      =");
    printf("\n\t\t\t        =               VACCINATION                 =");
    printf("\n\t\t\t        =               MANAGEMENT                  =");
    printf("\n\t\t\t        =                 SYSTEM                    =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  ------------------\n");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
}
//method to check weather the name is valid or not
int isNameValid(const char *name)
{
    int validName = 1;
    int len = 0;
    int index = 0;
    len = strlen(name);
    for(index =0; index <len ; ++index)
    {
        if(!(isalpha(name[index])) && (name[index] != '\n') && (name[index] != ' '))
        {
            validName = 0;
            break;
        }
    }
    return validName;
}
//method to check weather the entered aadharNo exists in the vaccination.txt file
int isaadharexistalready(const char *name)
{
    int found = 0;
    int len = 0;
    int index = 0;
    char aadharNo[MAX_AADHARNO] = {0};
    char s_aadharNo[MAX_AADHARNO];
    p_Info addInfoInDataBase = {0};
    FILE *fp = NULL;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while reading file\n");
        exit(1);
    }
    while (fread (&addInfoInDataBase, sizeof(addInfoInDataBase), 1, fp))
    {
    	if(!strcmp(addInfoInDataBase.aadharNo, name))
        {
        	found=1;
            break;
        }
    }
    if(found!=1)
    {
	    len = strlen(name);
	    if(len!=12)
		{
			printf("\n\t\t\tInvalid Aadhar Number entered %d digits/12 digits",len);
	        getch();
	        adminmenu();
		}
		for(index =0; index <len-1 ; ++index)
		{
			if(!(isdigit(name[index])) && (name[index] != '\n'))
			{
			    printf("\n\t\t\tInvalid Aadhar Number");
	            getch();
	            adminmenu();
			    break;
			}
		}
	}
    return found;
}
//method to check weather the entered aadharNo exists in the Slot.txt file
int isaadharexist(const char *name)
{
    int found = 0;
    int len = 0;
    int index = 0;
    char aadharNo[MAX_AADHARNO] = {0};
    char s_aadharNo[MAX_AADHARNO];
    p_Info addInfoInDataBase = {0};
    FILE *fp1 = NULL;
    fp1 = fopen(FILE_NAMES,"rb");
    if(fp1 == NULL)
    {
        printf("\n\t\t\tBook the slot to get vaccinated\n");
    }
    if (fseek(fp1,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp1);
        printf("\n\t\t\tFacing issue while reading file\n");
        exit(1);
    }
    while (fread (&addInfoInDataBase, sizeof(addInfoInDataBase), 1, fp1))
    {
    	if(!strcmp(addInfoInDataBase.aadharNo, name))
        {
        	found=1;
            break;
        }
    }
    if(found!=1)
    {
	    len = strlen(name);
	    if(len!=12)
		{
			printf("\n\t\t\tInvalid Aadhar Number entered %d digits/12 digits",len);
	        getch();
	        usermenu();
		}
		for(index =0; index <len-1 ; ++index)
		{
			if(!(isdigit(name[index])) && (name[index] != '\n'))
			{
			    printf("\n\t\t\tInvalid Aadhar Number");
	            getch();
	            usermenu();
			    break;
			}
		}
	}
    return found;
}
int IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}
int isValidDate(Date *validDate)
{
    //check range of year,month and day
    if (validDate->yyyy > MAX_YR ||
            validDate->yyyy < MIN_YR)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;
    //Handle feb days in leap year
    if (validDate->mm == 2)
    {
        if (IsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }
    //handle months which has only 30 days
    if (validDate->mm == 4 || validDate->mm == 6 ||
            validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);
    return 1;
}
//method to add stock
void addStock()
{
	int s;
    printf("\n\t\t\tEnter the quantity of stock :");
    scanf("%d",&s);
    stock=stock+s;
    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    getchar();
}
//method to view stock
void viewStock()
{
    printf("\n\t\t\tThe quantity of stock is %d:",stock);
    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    getchar();
}
/**
 * @brief method to book slot for vaccination
 * books slot for vaccination if the user the doesn't booked for vaccination previously
 * if the user booked the slot previously then it prompts error message
 */
void bookSlot()
{
    int days;
    p_Info book_Slot = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAMES,"ab+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        //exit(1);
    }
    headMessage("Slot Bokking");
    printf("\n\n\t\t\tENTER THE DETAILS BELOW:");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    fflush(stdin);
    do
    {
        printf("\n\t\t\tENTER AADHAR NO OF THE PATIENT  = ");
        fflush(stdin);
        fgets(book_Slot.aadharNo,MAX_AADHARNO,stdin);
        status = isaadharexist(book_Slot.aadharNo);
        if (status)
        {
            printf("\n\t\t\tAlready slot booked.");
            printf("\n\t\t\tPress any key to continue.......");
            getch();            //addDataInDataBase();
        }
    }while(status);
    do
    {
        printf("\n\t\t\tPatient Name  = ");
        fflush(stdin);
        fgets(book_Slot.name,MAX_NAME,stdin);
        status = isNameValid(book_Slot.name);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }while(!status);
    do
    {
        //get date year,month and day from user
        printf("\n\t\t\tEnter date in format (day/month/year): ");
        scanf("%d/%d/%d",&book_Slot.date.dd,&book_Slot.date.mm,&book_Slot.date.yyyy);
        //check date validity
        status = isValidDate(&book_Slot.date);
        if (!status)
        {
            printf("\n\t\t\tPlease enter a valid date.\n");
        }
    }while(!status);
    fwrite(&book_Slot,sizeof(book_Slot), 1, fp);
    fclose(fp);
    printf("\n\n\n\t\t\tSucessfully slot booked...");
    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    getchar();
}
/**
 * @brief method to add data in database after vaccination
 * adds data in storage if the user the booked slot for vaccination and if user does't vaccinated previously 
 * if the user does't booked the slot previously or the user vaccinated previously then it prompts error message
 */
void addDataInDataBase()
{
	if(stock==0)
	{
		printf("\n\t\t\t\tThere is no stock of vaccines please add the stock\n");
	}
	else
	{
		int days;
	    int status1 = 0;
	    p_Info addInfoInDataBase = {0};
	    FILE *fp = NULL;
	    int status = 0;
	    fp = fopen(FILE_NAME,"ab+");
	    if(fp == NULL)
	    {
	        printf("File is not opened\n");
	        //exit(1);
	    }
	    headMessage("ADD VACCINATED PEOPLE DATA");
	    printf("\n\n\t\t\tENTER THE DETAILS BELOW:");
	    printf("\n\t\t\t---------------------------------------------------------------------------\n");
	    fflush(stdin);
	    do
	    {
	        printf("\n\t\t\tENTER AADHAR NO OF THE PATIENT  = ");
	        fflush(stdin);
	        fgets(addInfoInDataBase.aadharNo,MAX_AADHARNO,stdin);
            status = isaadharexistalready(addInfoInDataBase.aadharNo);
	        status1 = isaadharexist(addInfoInDataBase.aadharNo);
        	if (status1)
        	{
                //printf("Asdfasdfasdfasdfasdfasdf");
	        	if (status)
		        {
		            printf("\n\t\t\tPerson already vaccinated,aadhar no already exist.");
                    printf("\n\t\t\tPress any key to goto previous menu.......");
                    getch();
		            adminmenu();
                    getch();
		            //addDataInDataBase();
		        }
            	//addDataInDataBase();
        	}
			else
			{
				printf("\n\t\t\tPlease book the slot first.");
                printf("\n\t\t\tPress any key to goto previous menu......");
                getch();
                adminmenu();
                getch();
			}	
	    }while(status1==0&&status==1);
	    do
	    {
	        printf("\n\t\t\tPatient Name  = ");
	        fflush(stdin);
	        fgets(addInfoInDataBase.name,MAX_NAME,stdin);
	        status = isNameValid(addInfoInDataBase.name);
	        if (!status)
	        {
	            printf("\n\t\t\tName contain invalid character. Please enter again.");
	        }
	    }while(!status);
	    do
	    {
	        //get date year,month and day from user
	        printf("\n\t\t\tEnter date in format (day/month/year): ");
	        scanf("%d/%d/%d",&addInfoInDataBase.date.dd,&addInfoInDataBase.date.mm,&addInfoInDataBase.date.yyyy);
	        //check date validity
	        status = isValidDate(&addInfoInDataBase.date);
	        if (!status)
	        {
	            printf("\n\t\t\tPlease enter a valid date.\n");
	        }
	    }while(!status);
	    fwrite(&addInfoInDataBase,sizeof(addInfoInDataBase), 1, fp);
	    fclose(fp);
	    stock--;
	}
    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    getchar();
}
//search method to search the vaccinated peoples data 
void searchVaccinatedPeople()
{
    int found = 0;
    char aadharNo[MAX_AADHARNO] = {0};
    char s_aadharNo[MAX_AADHARNO];
    p_Info addInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }
    headMessage("SEARCH ");
    //put the control on books detail
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while reading file\n");
        exit(1);
    }
    printf("\n\n\t\t\tEnter aadharNo to search:");
    fflush(stdin);
    scanf("%s",&s_aadharNo);
    while (fread (&addInfoInDataBase, sizeof(addInfoInDataBase), 1, fp))
    {
    	if(!strcmp(addInfoInDataBase.aadharNo, s_aadharNo))
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
        printf("\n\t\t\taadhar No = %s\n",addInfoInDataBase.aadharNo);
        printf("\t\t\tName = %s",addInfoInDataBase.name);
        printf("\t\t\tDate of birth(day/month/year) =  (%d/%d/%d)",addInfoInDataBase.date.dd,
               addInfoInDataBase.date.mm, addInfoInDataBase.date.yyyy);
    }
    else
    {
        printf("\n\t\t\tNo Record");
    }
    fclose(fp);
    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    getchar();
}
//method to view vaccinated peoples record 
void viewRecords()
{
    int found = 0;
    char name[MAX_NAME] = {0};
    p_Info addInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    unsigned int count = 1;
    headMessage("VIEW Vaccine Details");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("Facing issue while reading file\n");
        exit(1);
    }
    while (fread (&addInfoInDataBase, sizeof(addInfoInDataBase), 1, fp))
    {
        printf("\n\t\t\tVaccine Count = %d\n\n",count);
        printf("\t\t\tAadhar No = %s",addInfoInDataBase.aadharNo);
        printf("\n\t\t\tPatient Name = %s",addInfoInDataBase.name);
        //printf("\t\t\tBook authorName = %s",addInfoInDataBase.authorName);
        printf("\t\t\tDate of birth (day/month/year) =  (%d/%d/%d)\n\n",addInfoInDataBase.date.dd,
               addInfoInDataBase.date.mm, addInfoInDataBase.date.yyyy);
        found = 1;
        ++count;
    }
    
    if(!found)
    {
        printf("\n\t\t\tNo Record");
    }
    fclose(fp);
    fflush(stdin);
    printf("\n\n\t\t\tPress any key to go to main menu.....");
    getchar();
}
//method to show user menu
void usermenu()
{
	int choice = 0,b=0,y,status=0;
	p_Info book_Slot = {0};
    FILE *fp = NULL;
    fp = fopen(FILE_NAMES,"ab+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        //exit(1);
    }
    while(1)
    {
        headMessage("MAIN MENU");
        //printf("\n\n\n\t\t\t1.Add Vaccinated data");
        printf("\n\t\t\t1.Book Slot");
        printf("\n\t\t\t2.Search vaccinated data");
        printf("\n\t\t\t3.View Records");
        printf("\n\t\t\t4.Update Password");
        //printf("\n\t\t\t5.Add Stock");
        printf("\n\t\t\t5.View Stock");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1  :	printf("\n\t\t\tENTER AADHAR NO OF THE PATIENT  = ");
				        fflush(stdin);
				        fgets(book_Slot.aadharNo,MAX_AADHARNO,stdin);
				        status = isaadharexist(book_Slot.aadharNo);
				        if (status)
				        {
				            printf("\n\t\t\tAlready slot booked.");
				            getch();
				        }
				        else
				        {
				        	bookSlot();
						}
            		break;
	        case 2	:searchVaccinatedPeople();
	            	break;
	        case 3	:viewRecords();
	            	break;
	        case 4:	uCredential();
            		break;
            case 5:	viewStock();
            		break;
	        case 0	:
	        		system("cls");
	        		headMessage("MAIN MENU");
	            	login();
	            	break;
	        default	:printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }  //Switch Ended
		getch();                                          
    } 
}
//method to show admin menu
void adminmenu()
{
    int choice = 0;
    while(1)
    {
        headMessage("MAIN MENU");
        printf("\n\n\n\t\t\t1.Add Vaccinated data");
        printf("\n\t\t\t2.Search vaccinated data");
        printf("\n\t\t\t3.View Records");
        printf("\n\t\t\t4.Update Password");
        printf("\n\t\t\t5.Add Stock");
        printf("\n\t\t\t6.View Stock");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice)
        {
	        case 1	:addDataInDataBase();
	            	break;
	        case 2	:searchVaccinatedPeople();
	            	break;
	        case 3	:viewRecords();
	            	break;
	        case 4:	aCredential();
            		break;
            case 5:	addStock();
            		break;
            case 6:	viewStock();
            		break;
	        case 0	:printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
	        		getch();
	        		system("cls");
	        		headMessage("MAIN MENU");
	            	login();
	            	break;
	        default	:printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }  //Switch Ended
		getch();                                          
    }     
                                       //Loop Ended
}
void aCredential()
{
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    headMessage("Update Credential");
    fp = fopen(FILE_NAME,"rb+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    if (fseek(fp,0,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }
    printf("\n\n\t\t\tNew Username:");
    fflush(stdin);
    fgets(userName,MAX_SIZE_USER_NAME,stdin);
    printf("\n\n\t\t\tNew Password:");
    fflush(stdin);
    fgets(password,MAX_SIZE_PASSWORD,stdin);
    strncpy(fileHeaderInfo.username,userName,sizeof(userName));
    strncpy(fileHeaderInfo.password,password,sizeof(password));
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    printf("\n\t\t\tYour Password has been changed successfully");
    printf("\n\t\t\tLogin Again");
    adminlogin();
    fflush(stdin);
    exit(1);
    getch();
}
void uCredential()
{
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    headMessage("Update Credential");
    fp = fopen(FILE_NAME,"rb+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    if (fseek(fp,0,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }
    printf("\n\n\t\t\tNew Username:");
    fflush(stdin);
    fgets(userName,MAX_SIZE_USER_NAME,stdin);
    printf("\n\n\t\t\tNew Password:");
    fflush(stdin);
    fgets(password,MAX_SIZE_PASSWORD,stdin);
    strncpy(fileHeaderInfo.UserName,userName,sizeof(userName));
    strncpy(fileHeaderInfo.PassWord,password,sizeof(password));
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    printf("\n\t\t\tYour Password has been changed successfully");
    printf("\n\t\t\tLogin Again");
    userlogin();
    fflush(stdin);
    exit(1);
    getch();
}
//method for admin login
void adminlogin()
{
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    int L=0;
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    headMessage("Login");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        //exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    do
    {
        printf("\n\n\n\t\t\t\tUsername:");
        fgets(userName,MAX_SIZE_USER_NAME,stdin);
        printf("\n\t\t\t\tPassword:");
        fgets(password,MAX_SIZE_PASSWORD,stdin);
        if((!strcmp(userName,fileHeaderInfo.username)) && (!strcmp(password,fileHeaderInfo.password)))
        {
            adminmenu();
        }
        else
        {
            printf("\t\t\t\tLogin Failed Enter Again Username & Password\n\n");
            L++;
        }
    }
    while(L<=3);
    if(L>3)
    {
        headMessage("Login Failed");
        printf("\t\t\t\tSorry,Unknown User.");
        getch();
        system("cls");
    }
}
//method for user login
void userlogin()
{
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    int L=0;
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    headMessage("Login");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        //exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    do
    {
        printf("\n\n\n\t\t\t\tUsername:");
        fgets(userName,MAX_SIZE_USER_NAME,stdin);
        printf("\n\t\t\t\tPassword:");
        fgets(password,MAX_SIZE_PASSWORD,stdin);
        if((!strcmp(userName,fileHeaderInfo.UserName)) && (!strcmp(password,fileHeaderInfo.PassWord)))
        {
            usermenu();
        }
        else
        {
            printf("\t\t\t\tLogin Failed Enter Again Username & Password\n\n");
            L++;
        }
    }
    while(L<=3);
    if(L>3)
    {
        headMessage("Login Failed");
        printf("\t\t\t\tSorry,Unknown User.");
        getch();
        system("cls");
    }
}
//method for login, this has 2 options user login and admin login
void login()
{
    int choice;
    printf("\n\t\t\t1->Admin Login:");
    printf("\n\t\t\t2->User Login");
    printf("\n\t\t\t0->Exit");
    printf("\n\t\t\tEnter your choice:");
    scanf("%d",&choice);
    do{
        switch(choice)
        {
        case 1:
            adminlogin();
            break;
        case 2:
            userlogin();
            break;
        }
    }while(choice!=0);
    if (choice == 0)
    {
        thankYou();
        exit(1);
    }
    getch();
}
int isFileExists(const char *path)
{
    // Try to open file
    FILE *fp = fopen(path, "rb");
    int status = 0;
    // If file does not exists
    if (fp != NULL)
    {
        status = 1;
        // File exists hence close file
        fclose(fp);
    }
    return status;
}
//method to inistialize the file and assigns username and password
void init()
{
    FILE *fp = NULL;
    int status = 0;
    const char defaultUsername[] ="admin\n";
    const char Username[] = "patient\n";
    const char defaultPassword[] ="admin\n";
    const char Password[] = "password\n";
    sFileHeader fileHeaderInfo = {0};
    sFileHeader fileHeaderInfo1 = {0};
    status = isFileExists(FILE_NAME);
    if(!status)
    {
        //create the binary file
        fp = fopen(FILE_NAME,"wb");
        if(fp != NULL)
        {
            //Copy default password
            strncpy(fileHeaderInfo.password,defaultPassword,sizeof(defaultPassword));
            strncpy(fileHeaderInfo.username,defaultUsername,sizeof(defaultUsername));
            //fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
            strncpy(fileHeaderInfo.PassWord,Password,sizeof(Password));
            strncpy(fileHeaderInfo.UserName,Username,sizeof(Username));
            fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
            fclose(fp);

        }
    }
    FILE *fp1 = NULL;
    int status1 = 0;
    status1 = isFileExists(FILE_NAMES);
    if(!status1)
    {
        //create the binary file
        fp1 = fopen(FILE_NAMES,"wb");
        if(fp1 != NULL)
        {
            //Copy default password
            //fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
            strncpy(fileHeaderInfo1.PassWord,Password,sizeof(Password));
            strncpy(fileHeaderInfo1.UserName,Username,sizeof(Username));
            fwrite(&fileHeaderInfo1,FILE_HEADER_SIZE, 1, fp1);
            fclose(fp1);
        }
    }
}
//main method
int main()
{
    init();
    welcomeMessage();
    login();
    thankYou();
    return 0;
}

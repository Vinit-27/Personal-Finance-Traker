/* 

NOTE: This program will create two additional files in the same directory as the code. 
They will NOT be removed automatically as they are to be used during later executions of code too. 
These files are "Bookings.csv" and "LoginData.txt". 
Please manually remove these files if no longer needed.

*/

#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define N struct recNode *
#define R RecD

typedef struct recData{ //Linked List
    char name[50]; // Transaction From/To whom
    char isCredit[10];
    char amount[10];
    char dt[30];
} RecD;

struct recNode{ // Linked List
    RecD data;
    N next;
};

struct name { // Minimum Cashflow - Graph
    char nam[20];
};

struct wishes // Wishlist - Priority Queue
{
    char wish[30];
};

int cashMember;
char newUsrName[25], newUsrPwd[25], newUsrPwdVerify[25];


// Function Declarations
void login(int isUpd);
void menu();
void clearscreen();
void newUser(int isUpd);
void returnMenu();
N recInsert(N head, R r);
void recMenu();
void newData();
void fileInsert(N tempP);
int getMax (int money[]);
int getMin (int money[]);
int minmy (int x, int y);
void minCashFlowRec(int money[],struct name member[]);
void minCashFlow (int graph[][cashMember], struct name member[]);
int cashMain();
void set_priority(char *p);
int priorMain();

int main() { // Driver Code
    login(0);
    menu();
    return 0;
}

void login(int isUpd) { // Handle Login

    // isUpd = 1 means Update the Credentials
    // isUpd = 0 means login from menu


    clearscreen();

    // If updating details or Registering Data
    FILE *fileExist;
    if(access("LoginData.txt", F_OK) != 0 || isUpd!=0)
    {
        // Get newUsrName and newUsrPwd
        newUser(isUpd);

        // Remove Existing User Credentials for Updating
        if(isUpd!=0)
            remove("LoginData.txt");


        // Create new file and update data
        FILE *fp;
        fp = fopen ("LoginData.txt","a+");

        if(isUpd!=0)
            printf("Creating a New User Database...");

        else
            printf("Updating New User Database...");

        // Enter data in file
        fputs(newUsrName,fp);
        fputs("\n",fp);
        fputs(newUsrPwd,fp);
        fputs("\n",fp);

        fclose(fp);

        printf("Done!");

        if(isUpd!=0)
        {
            clearscreen();
            menu();
        }
    }

    // Execute if Login Data Exists
    else
    {

        FILE *fr;
        fr = fopen("LoginData.txt", "r");

        fgets(newUsrName, 25, fr); // newUsrName and newUsrPwd stores existing
        fgets(newUsrPwd, 25, fr); // login information stored

        int nameLen = strlen(newUsrName);
        newUsrName[nameLen - 1] = '\0';

        int pwdLen = strlen(newUsrPwd);
        newUsrPwd[pwdLen - 1] = '\0';

        char loginUsrName[25]; // Take login
        char loginUsrPwd[25];  // from user

        fclose(fr);

    loginStart:

        printf("\n\tEnter your login: ");

        gets(loginUsrName);

        if (strcmp(loginUsrName, newUsrName) == 0)
        {

            printf("\tEnter your password:");

            // To Hide Password on Input Screen
            int i = 0;
            char c = 'c';
            while (i < 25)
            {
                loginUsrPwd[i] = getch();
                c = loginUsrPwd[i];
                if (c == 13)
                    break;
                else
                    printf("*");
                i++;
            }
            loginUsrPwd[i] = '\0';

            if (strcmp(loginUsrPwd, newUsrPwd) == 0)
            {
                printf("\033[0;32m");
                printf("\n\n\tWelcome.Login Success!");
                printf("\033[0;3m");
                printf("\n\tPress any key to continue...");
                getch();
            }
            else
            {
                printf("\033[0;31m");
                printf("\n\n\tError: Incorrect Password");
                printf("\033[0;3m");
                printf("\n\tPress any key to retry: ");
                getch();
                clearscreen();
                goto loginStart;
            }
        }
        else
        {
            printf("\033[0;31m");
            printf("\n\n\tError: Incorrect User");
            printf("\033[0;3m");
            printf("\n\tPress any key to retry: ");
            getch();
            clearscreen();
            goto loginStart;
        }
    }
}

void newUser(int isUpd) { // Take login details for new users


    clearscreen();

    fflush(stdin);
    int pwdLen, digi, up, low, schar, isErr = 0;
    printf("\tCreate New Login:\n\tEnter your Name: "); // Get new Username
    gets(newUsrName);

passStart:
    clearscreen();

    digi = 0;
    up = 0;
    low = 0;
    schar = 0;

    printf("\tHello %s!, Password Requirement:\n\tNo. of Characters: 5 to 12\n\tAtleast 1 Special Characters, Uppercase, Lowercase, Number\n\tPlease enter your password: ", newUsrName);

    // To hide characters of password during input
    int i = 0;
    char c = ' ';
    while (i < 25)
    {
        newUsrPwd[i] = getch();
        c = newUsrPwd[i];
        if (c == 13)
            break;
        else
            printf("*");
        i++;
    }
    newUsrPwd[i] = '\0';

    pwdLen = strlen(newUsrPwd);

    // Check Length of Password

    if (pwdLen < 5)
    {
        printf("\033[0;31m");
        printf("\n\tError: Password should contain minimum 5 characters ");
        printf("\033[0;3m");
        printf("\n\tPress any key to retry: ");
        getch();
        goto passStart;
    }

    else if (pwdLen > 12)
    {
        printf("\033[0;31m");
        printf("\n\tError: Password should not exceed 12 characters ");
        printf("\033[0;3m");
        printf("\n\tPress any key to retry: ");
        getch();
        goto passStart;
    }

    // Check Characters types used

    else
    {
        for (int i = 0; newUsrPwd[i] != '\0'; i++)
        {
            if (newUsrPwd[i] >= 'A' && newUsrPwd[i] <= 'Z')
                up++;
            if (newUsrPwd[i] >= 'a' && newUsrPwd[i] <= 'z')
                low++;
            if (newUsrPwd[i] >= '0' && newUsrPwd[i] <= '9')
                digi++;
            if (newUsrPwd[i] == '@' || newUsrPwd[i] == '#' || newUsrPwd[i] == '$')
                schar++;
        }
    }

    // Password Errors
    if (up == 0)
    {
        printf("\033[0;31m");
        printf("\n\tThere must be at least one Uppercase");
        printf("\033[0;3m");
        isErr = 1;
    }
    if (low == 0)
    {
        printf("\033[0;31m");
        printf("\n\tThere must be at least one Lowercase");
        printf("\033[0;3m");
        isErr = 1;
    }
    if (digi == 0)
    {
        printf("\033[0;31m");
        printf("\n\tThere must be at least one Digit");
        printf("\033[0;3m");
        isErr = 1;
    }
    if (schar == 0)
    {
        printf("\033[0;31m");
        printf("\n\tThere must be at least one Special Character");
        printf("\033[0;3");
        isErr = 1;
    }

    // Retry
    if (isErr == 1)
    {
        printf("\n\n\tPress any key to retry: ");
        getch();
        goto passStart;
    }
    else
    {
        printf("\n\tConfirm your Password: ");
        int i = 0;
        char c = ' ';

        fflush(stdin);
        while (i < 25)
        {
            newUsrPwdVerify[i] = getch();
            c = newUsrPwdVerify[i];
            if (c == 13)
                break;
            else
                printf("*");
            i++;
        }
        newUsrPwdVerify[i] = '\0';

        if (strcmp(newUsrPwd, newUsrPwdVerify) == 0) // Password Match
        {
            printf("\033[0;32m");
            printf("\n\tWelcome %s, your is Password Verified", newUsrName);
            printf("\033[0;3m");
            printf("\n\tPress any key to continue: ");
            fflush(stdin);
            getch();
            fflush(stdin);
            return;
        }
        else // Password Doesn't Match
        {
            printf("\033[0;31m");
            printf("\nPassword did not match");
            printf("\033[0;3m");
            printf("\nPress any key to retry: ");
            fflush(stdin);
            getch();
            fflush(stdin);
            clearscreen();
            goto passStart;
        }
    }

    fflush(stdin);
    clearscreen();
    returnMenu();
}

void menu() { // Main Menu
    while (1)
    {
        clearscreen();

        printf("\n");
        printf("\t***********************   MENU   **************************\n");
        printf("\t*          |-----------------------------------|          *\n");
        printf("\t*          | 1 -> Update Login                 |          *\n");
        printf("\t*          |-----------------------------------|          *\n");
        printf("\t*          | 2 -> Wishlist Priority            |          *\n");
        printf("\t*          |-----------------------------------|          *\n");
        printf("\t*          | 3 -> Minimum Cash Flow Function   |          *\n");
        printf("\t*          |-----------------------------------|          *\n");
        printf("\t*          | 4 -> Add Transactions             |          *\n");
        printf("\t*          |-----------------------------------|          *\n");
        printf("\t*          | 5 -> View Transactions            |          *\n");
        printf("\t*          |-----------------------------------|          *\n");
        printf("\t*          | 6 -> Exit                         |          *\n");
        printf("\t*          |-----------------------------------|          *\n");
        printf("\t*                                                         *\n");
        printf("\t***********************************************************\n");

        fflush(stdin);

        int n;
        printf("\nEnter your choice number:");
        scanf("%d", &n);

        switch (n)
        {
        case 1: 
            login(1);
            break;
        case 2:
            priorMain();
            returnMenu();
            break;
        case 3:
            cashMain();
            returnMenu();
            break;
        case 4:
            recMenu();
            break;
        case 5:
            newData();
            printf("Close Excel to continue");
            system("Records.csv");
            returnMenu();
            break;
        case 6:
            return;
        default:
            printf("\033[0;31m");
            printf("Invalid Input. Please Try Again!");
            printf("\033[0;3m");
            continue;
        }
    }
}

void clearscreen() { // Clear Screen and Heading

    system("cls");
    fflush(stdin);

    printf("\t***********************************************************\n");
    printf("\t*                                                         *\n");
    printf("\t*               Personal Finance Tracker                  *\n");
    printf("\t*                                                         *\n");
    printf("\t***********************************************************\n");
}

void returnMenu() { // Press any key to continue

    printf("\nPress any key to return to Main Menu: ");
    getch();
    fflush(stdin);
    menu();
}

void recMenu(){ // Records (Transaction) menu

    N head=NULL; 
    N tempP=NULL;
    R r;
    int temp;

    newData();

    while (1)
    {
        clearscreen();

        printf("\n");
        printf("\t***********************   MENU   **************************\n");
        printf("\t*          |-----------------------------------|          *\n");
        printf("\t*          | 1 -> Add Transaction              |          *\n");
        printf("\t*          |-----------------------------------|          *\n");
        printf("\t*          | 2 -> View Transactions            |          *\n");
        printf("\t*          |-----------------------------------|          *\n");
        printf("\t*          | 3 -> Save and Return to menu      |          *\n");
        printf("\t*          |-----------------------------------|          *\n");
        printf("\t*                                                         *\n");
        printf("\t***********************************************************\n");

        int n;
        fflush(stdin);

        printf("\nEnter your choice number:");
        scanf("%d", &n);

        switch (n)
        {
        case 1:
        // Take Data
            fflush(stdin);
            printf("To /From: ");
            scanf("%s", r.name);
            fflush(stdin);
            printf("Type of Transaction (Credit/Debit) : ");
            scanf("%s", r.isCredit);
            fflush(stdin);
            printf("Amount: ");
            scanf("%s", r.amount);
            fflush(stdin);
            printf("Date and Time: ");
            scanf("%s", r.dt);
            fflush(stdin);

            // Insert Data in Linked List
            head = recInsert(head,r);
            printf("Added.");

            // Press to continue
            printf("\nPress any key to return to Menu: ");
            getch();
            fflush(stdin);
            break;

        case 2:
            tempP=head;
            // Column Headings
            printf("\n%-50s %-15s %-15s %-50s","To/From","Credit/Debit","Amount","Date and Time");
            // Iterate till End
            while(tempP!=NULL){
                printf("\n%-50s %-15s %-15s %-50s",tempP->data.name,tempP->data.isCredit,tempP->data.amount,tempP->data.dt);
                tempP=tempP->next;
            }
            printf("\nPress any key to return to Menu: ");
            getch();
            fflush(stdin);
            break;            

        case 3:
            // Iterate till End
            tempP=head;
            while(tempP!=NULL){
                fileInsert(tempP);
                tempP=tempP->next;
            }
            return;
        default:
            printf("\033[0;31m");
            printf("Invalid Input. Please Try Again!");
            printf("\033[0;3m");
            continue;
        }
    }
        
}

N recInsert(N head, R r){ // Insert in Linked List
    N new = (N)(malloc(sizeof(struct recNode)));
    new -> next = NULL;

    if(head == NULL){ // No head exists
        new -> data = r;
        head = new;
        return head;
    }

    N temp = head; // Head Exists
    while(temp->next!=NULL){ // Iterate till End
        temp=temp->next;
    }
    temp->next = new;
    new->data = r;
    return head;
}

void newData() { // New Record File if doesn't exist
    FILE *fileExist;
    if(access("Records.csv", F_OK) != 0) // If file Doesn't exist
    {
        printf("Creating a New Database...");

        FILE *fp;
        fp = fopen ("Records.csv","a+");
        fprintf(fp,"To/From,Credit/Debit,Amount,Date and Time\n"); // Column Headings
        printf("Created.");
        fclose(fp);
    }

}

void fileInsert(N tempP){ // Insert data (from Linked List) to file
    FILE *fp;
    fp=fopen("Records.csv","a+");
    fflush(stdin);
    fprintf(fp,"%s,%s,%s,%s\n",tempP->data.name,tempP->data.isCredit,tempP->data.amount,tempP->data.dt);
    fclose(fp);
}

int getMax (int money[]) { // Helper function to get maximam index
    int ans = 0;

    for (int i = 0; i < cashMember; i++) {
        if (money[ans] < money[i]) {
            ans = i;
        }
    }

    return ans;
}

int getMin (int money[]) { // Helper function to get minimam index
    int ans = 0;

    for (int i = 0; i < cashMember; i++) {
        if (money[ans] > money[i]) {
            ans = i;
        }
    }

    return ans;
}

int minmy (int x, int y) { // Function to find minimam of two Number
    if (x < y) {
        return x;
    } else {
        return y;
    }
}

void minCashFlowRec(int money[],struct name member[]) { // Recursive Function to get minimum cashFlow
    int maxCreditIdx = getMax(money);
    int maxDebitIdx = getMin(money);

    if (money[maxCreditIdx] == 0 && money[maxDebitIdx] == 0) {
        return;
    }

    int minValue = minmy(-money[maxDebitIdx], money[maxCreditIdx]);
    money[maxCreditIdx] -= minValue;
	money[maxDebitIdx] += minValue;

    printf("%s pays %d to %s\n",member[maxDebitIdx].nam,minValue,member[maxCreditIdx].nam);
    // printf("\nPress any key to return to Menu: ");
    // getch();
    // fflush(stdin);


    minCashFlowRec(money,member);
}

void minCashFlow (int graph[][cashMember], struct name member[]) {
    int money[cashMember];

    for (int i = 0; i < cashMember; i++) {
        money[i] = 0;
    }

    for (int i = 0; i < cashMember; i++) {
        for (int j = 0; j < cashMember; j++) {
            money[i] += ((graph[j][i] - graph[i][j]));
        }
    }

    minCashFlowRec(money,member);
}

int cashMain() { // Driver Code for CashFlow function


    printf("Enter the number of members in CashFlow --> ");

    scanf("%d",&cashMember);

    int graph[cashMember][cashMember];
    struct name member[cashMember];

    for (int i = 0; i < cashMember; i++) {
        printf("Enter the name of Member %d --> ", i+1);
        scanf("%s",member[i].nam);
    }


    for (int i = 0; i < cashMember; i++) {
        for (int j = 0; j < cashMember; j++) {
            if (i == j) {
                graph[i][j] = 0;
            }
            else {
                printf("Enter the Number of Amount that %s has to pay to %s --> ",member[i].nam,member[j].nam);
                scanf("%d",&graph[i][j]);
            }
        }
    }

    minCashFlow(graph, member);
}

void set_priority(char *p) { //set-priority function
    int l = strlen(p);
    if(strcmpi("car",p)==0)
    {
        p[l]='4';
        p[l+1]='\0';
    }
    else if(strcmpi("food",p)==0)
    {
        p[l]='1';
        p[l+1]='\0';
    }
    else if(strcmpi("cloth",p)==0)
    {
        p[l]='2';
        p[l+1]='\0';
    }
    else if(strcmpi("tour",p)==0)
    {
        p[l]='3';
        p[l+1]='\0';
    }
    else if(strcmpi("bike",p)==0)
    {
        p[l]='4';
        p[l+1]='\0';
    }
    else if(strcmpi("mobile",p)==0)
    {
        p[l]='3';
        p[l+1]='\0';
    }
    else if(strcmpi("donate",p)==0)
    {
        p[l]='5';
        p[l+1]='\0';
    }
}

int priorMain() { //Driver Code for Priority Queue Function
    int n;
    printf("Enter number of your wishes: ");
    scanf("%d",&n);
    char arr[n],l,m=n;
    struct wishes w[n];
    //input
    printf("Select from the following  : [food , cloth , donate , car , bike , mobile ,tour ]\n");
    for(int i=0;i<n;i++)
    {
        printf("Enter your no.%d wish: ",i+1);
        scanf("%s",&w[i].wish);
    }
    //set priority function call
    for(int i=0;i<n;i++)
    {
        set_priority(w[i].wish);
        l=strlen(w[i].wish);
        arr[i]=(int)(w[i].wish[l-1]) - 48;
    }

//max_heep_tree_create:
    int min_heep[n];
    for(int i=0;i<n;i++)
    {
        min_heep[i]=arr[i];
        int k = i;
        while(k>=0 && min_heep[k]<min_heep[k/2])
        {
            int temp = min_heep[k];
            min_heep[k] = min_heep[k/2];
            min_heep[k/2] = temp;
            k=k/2;
        }
    }

//max_heep_tree_use_as_que:
    while(n>0)
    {
        int k=0;
        for(int i=0;i<m;i++)
        {
            if(min_heep[k]==arr[i])
            {
                printf("Your best choice as per priority: ");
                printf("%s\b \n",w[i].wish);
                arr[i]=-1;
                break;
            }
        }
        int temp = min_heep[n-1];
        min_heep[n-1] = min_heep[k];
        min_heep[k] = temp;
        n--;
        while((2*k+2)<n && (min_heep[k]>min_heep[2*k+1] || min_heep[k]>min_heep[2*k+2]))
        {
            if(min_heep[k]>min_heep[2*k+1])
            {
                int temp1 = min_heep[k];
                min_heep[k]=min_heep[2*k+1];
                min_heep[2*k+1]=temp1;
            }
            if(min_heep[k]>min_heep[2*k+2])
            {
                int temp1 = min_heep[k];
                min_heep[k]=min_heep[2*k+2];
                min_heep[2*k+2]=temp1;
            }
            k++;
        }
    }
    return 0;
}


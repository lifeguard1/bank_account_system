#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

// Function prototypes for operations
void createAccount(void);
void accountCreated(void);
void login(void);
void success(char*);
void checkBalance(char*);
void deposit(char*);
void transfer(char*);


// Function to set cursor position in console window
void gotoxy(int x, int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
 
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// Structures for storing user, password, and transaction data
struct Data {
    char username[20];
    int date, month, year, pnumber;
    char fname[20];
    char lname[20];
    char father[20];
    char mother[20];
    char address[50];
};

struct userpass{
    char password[50];
};

struct money{
    long int money1, money2;
    char user[20];
    char userto[20];
    char userfrom[20];
};

// Main function displaying the user menu
int main(){

    int choice;
    system("cls");
    gotoxy(24,3);
    
    // Creating menu for user
    printf("Welcome to Bank Account System\n\n");
    gotoxy(23,5);

    printf("*********************************");
    gotoxy(25,7);

    printf("Developer-Nikos Koutsounis");
    gotoxy(25,10);

    printf("1---Create a Bank Account");
    gotoxy(25, 12);

    printf("2---Login");
    gotoxy(25, 14);

    printf("3---Exit");
    
    printf("\n\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
      createAccount();
        break;
    
    case 2:
      login();
        break;

    case 3:
       exit(0);
        break;    
    }
}

// Account creation function
void createAccount(void){
    
    char ch;
    char password[50];
    struct Data user;
    struct userpass pass;

    FILE *fu, *fp;

    fu=fopen("data.txt", "ab");
    fp=fopen("password.txt", "ab");
    
    system("cls");
    printf("\n\n-----Let's create an account-----\n\n");
    // Data entry section
    printf("\n\nFirst Name: ");
    scanf("%s", &user.fname);

    printf("\n\nLast Name: ");
    scanf("%s", &user.lname);

    printf("\n\nFather's Name: ");
    scanf("%s", &user.father);

    printf("\n\nMother's Name: ");
    scanf("%s", &user.mother);
    
    printf("\n\nDate of Birth: \n");
    printf("\nDate: \n");
    scanf("%d", &user.date);
    printf("\nMonth: \n");
    scanf("%d", &user.month);
    printf("\nYear: ");
    scanf("%s", &user.year);

    printf("\n\nPhone Number: ");
    scanf("%d", &user.pnumber);

    printf("\n\nAdress: ");
    scanf("%s", &user.address);

    printf("\n\nUsername: ");
    scanf("%s", &user.username);

    printf("\n\nPassword: ");
    // Password entry section with masking
    for (int i = 0; i < 50; i++) {
        ch = getch();
        if (ch != 13) {
            pass.password[i] = ch;
            ch = '*';
            printf("%c", ch);
        }
        else
            break;
    }
    
    fwrite(&user, sizeof(user), 1, fu);
    fwrite(&pass, sizeof(pass), 1, fp);

    fclose(fu);
    fclose(fp);

    accountCreated();
}

// Account creation confirmation
void accountCreated(void){

    system("cls");
    printf(
        "PLEASE WAIT....\n\nYOUR DATA IS PROCESSING....");
    for (int i = 0; i < 200000000; i++){
        i++;
        i--;
}

gotoxy(30, 10);
 
    printf("ACCOUNT CREATED SUCCESSFULLY....");
    gotoxy(0, 20);
 
    printf("Press enter to login");
 
    getch();
    login();
}

// Login function
void login(void){
   
   system("cls");
    char ch;
    char password[50];
    struct Data user;
    struct userpass pass;

    char usern[50];
    char passw[50];

    FILE *fu, *fp;

    fu=fopen("data.txt", "rb");

    fp=fopen("password.txt", "rb");

    gotoxy(34, 2);
    printf(" ACCOUNT LOGIN ");
    gotoxy(7, 5);
    printf("***********************************************"
    "********************************");

    gotoxy(35, 12);
    printf("Username: ");
    scanf("%s", &usern);

    gotoxy(35, 14);
    printf("Password: ");
    // Password masking again
    for (int i = 0; i < 50; i++) {
        ch = getch();
        if (ch != 13) {
            passw[i] = ch;
            ch = '*';
            printf("%c", ch);
        }
        else
            break;
    }

    // Set the file pointer to the beginning of the file
    fseek(fu, 0, SEEK_SET);
    fseek(fp, 0, SEEK_SET);



       // Loop through both files simultaneously
       int found = 0; // Flag to track if a matching user/password pair is found
       while (fread(&user, sizeof(user), 1, fu) && fread(&pass, sizeof(pass), 1, fp)) {
         if(strcmp(user.username, usern) == 0 && strcmp(pass.password, passw) == 0) {
          success(usern);
          found = 1; // Set the flag to indicate successful authentication
          break; // Exit the loop once successful login is found
    }
}

// Check if a matching user/password pair was found
if (!found) {
    // If no match was found, display an error message and prompt for login again
    printf("\n\nIncorrect Username or Password :(");
    printf("\n\nPress enter to try again");
    getch();
    login();

    fclose(fp);
    fclose(fu);
     }
}

// Possible actions for user function 
void success(char username1[]){
        
       int choice; 
       system("cls");
      
    gotoxy(34, 2);
    printf(" ACCOUNT ACTIONS ");
    gotoxy(7, 5);
    printf("***********************************************"
    "********************************");

    printf("\n\n\n1---Check Balance");
    printf("\n\n2---Deposit");
    printf("\n\n3---Transfer Money");

    printf("\n\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
      checkBalance(username1);
        break;
    
    case 2:
      deposit(username1);
        break;

    case 3:
       transfer(username1);
        break;    
    }
}

// Deposit function
void deposit(char username2[]){

    struct money balance;
    long int deposit_amount;
    system("cls");
    FILE *fd;
    FILE *tempFile = fopen("temp.txt", "w");
    char buffer[1024];
    int updated = 0;

    fd=fopen("balance.txt", "r+");

    gotoxy(34, 2);
    printf("Enter amount you want to deposit: ");
    scanf("%ld", &deposit_amount);
    
    while (fgets(buffer, sizeof(buffer), fd) != NULL) {
        char *username = strtok(buffer, " "); // Get the username
        long balance1;
        sscanf(strtok(NULL, " "), "%ld", &balance1); // Get the balance

        // Update balance for user
        if (strcmp(username, username2) == 0) {
            balance1 += deposit_amount;
            updated = 1;
        }
       
        // Write username and balance to the temporary file
        fprintf(tempFile, "%s %ld\n", username, balance1);
    }

    if (!updated) {
        printf("Error\n");
        fclose(fd);
        fclose(tempFile);
        remove("temp.txt"); // Delete the temporary file
        return;
    }

    // Close the original file
    fclose(fd);

    // Close the temporary file
    fclose(tempFile);

    // Replace the original file with the temporary file
    remove("balance.txt");
    rename("temp.txt", "balance.txt");
    fclose(tempFile);

    fclose(fd);
    printf("\n\n\nPress enter to continue");
    getch();
    success(username2);
}

// Check current balance function
void checkBalance(char username2[]){

    system("cls");
    FILE *fb;
    struct money balance;

    fb=fopen("balance.txt", "r+");

    while(fscanf(fb, "%s %ld", balance.user, &balance.money1) != EOF){
        if(strcmp(balance.user, username2)==0){
            gotoxy(34, 2);
            printf("Account Balance: %d", balance.money1);
        }
    }
    fclose(fb);
    printf("\n\n\nPress enter to continue");
    getch();
    success(username2);
}

// Transfer money to different user function
void transfer(char username2[]){

   system("cls");

    struct money amount;
    struct money sender_balance, recipient_balance;
    char recipient_username[50];
    FILE *ft;
    FILE *tempFile = fopen("temp.txt", "w");

    ft = fopen("balance.txt", "r+");
    if (ft == NULL) {
        printf("Error opening balance file.\n");
        return;
    }

    gotoxy(33, 4);
    printf("---- TRANSFER MONEY ----");
    gotoxy(33, 5);
    printf("========================");

    gotoxy(33, 11);
    printf(" TO (username of recipient): ");
    scanf("%s", recipient_username);

    gotoxy(33, 13);
    printf("\n\nTransfer Amount: ");
    scanf("%ld", &amount.money2);

    char buffer[1024];
    int updated = 0;

    while (fgets(buffer, sizeof(buffer), ft) != NULL) {
        char *username = strtok(buffer, " "); // Get the username
        long balance;
        sscanf(strtok(NULL, " "), "%ld", &balance); // Get the balance

        // Update balance for sender
        if (strcmp(username, username2) == 0 && amount.money2<balance) {
            balance -= amount.money2;
            updated = 1;
        }
        // Update balance for recipient
        else if (strcmp(username, recipient_username) == 0) {
            balance += amount.money2;
            updated = 1;
        }

        // Write username and balance to the temporary file
        fprintf(tempFile, "%s %ld\n", username, balance);
    }

    // If sender or recipient not found, indicate error
    if (updated==0) {
        printf("Error: Sender or recipient not found.\n");
        fclose(ft);
        fclose(tempFile);
        remove("temp.txt"); // Delete the temporary file
        return;
    }

    // Close the original file
    fclose(ft);

    // Close the temporary file
    fclose(tempFile);

    // Replace the original file with the temporary file
    remove("balance.txt");
    rename("temp.txt", "balance.txt");
    fclose(tempFile);
    printf("\n\n\nPress enter to continue");
    getch();
    success(username2);
}





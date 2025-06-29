#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME 20
#define MAX_LINE 100

typedef struct {
    char name[MAX_NAME];
    int account_no;
    int balance;
    int transaction_count;
} Account;

Account acc = {"", 0, 10000, 0};

// Function Prototypes
void menu();
void deposit_money();
void withdraw_money();
void transfer_money();
void check_detail();
void transaction_details();
void last_detail();
void divider();
void press_enter();

void divider() {
    int i;
    for (i = 0; i < 50; i++) printf("-");
    printf("\n");
}

void press_enter() {
    printf("\nPress ENTER to continue...");
    getchar(); // wait for Enter
}

int main() {
    FILE *fp = fopen("Account.txt", "w");
    if (!fp) {
        printf("Error opening file.\n");
        return 1;
    }

    printf("Enter your name: ");
    fgets(acc.name, MAX_NAME, stdin);
    acc.name[strcspn(acc.name, "\n")] = '\0';  // Remove newline

    printf("Enter your account number: ");
    scanf("%d", &acc.account_no);
    getchar();  // Clear input buffer

    fprintf(fp, "Name: %s\n", acc.name);
    fprintf(fp, "Account No: %d\n", acc.account_no);
    fclose(fp);

    while (1) {
        int choice;
        menu();
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            break;
        }
        getchar(); // clear newline

        switch (choice) {
            case 1: deposit_money(); break;
            case 2: withdraw_money(); break;
            case 3: transfer_money(); break;
            case 4: check_detail(); break;
            case 5: transaction_details(); break;
            case 6: last_detail(); exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}

void menu() {
    divider();
    printf("               BANK MENU               \n");
    divider();
    printf("1. Deposit Money\n");
    printf("2. Withdraw Money\n");
    printf("3. Transfer Money\n");
    printf("4. Account Details\n");
    printf("5. Transaction History\n");
    printf("6. Exit\n");
    divider();
}

void deposit_money() {
    int amount;
    time_t t = time(NULL);
    FILE *fp = fopen("Account.txt", "a");

    divider();
    printf("Deposit Money\n");
    divider();
    printf("Enter amount to deposit: ");
    scanf("%d", &amount);
    getchar();

    if (amount <= 0) {
        printf("Amount must be greater than 0.\n");
    } else {
        acc.balance += amount;
        acc.transaction_count++;
        printf("Deposited Rs%d. Current balance: Rs%d\n", amount, acc.balance);
        fprintf(fp, "\nDeposited: Rs%d\nTime: %s", amount, ctime(&t));
    }

    fclose(fp);
    press_enter();
}

void withdraw_money() {
    int amount;
    time_t t = time(NULL);
    FILE *fp = fopen("Account.txt", "a");

    divider();
    printf("Withdraw Money\n");
    divider();
    printf("Enter amount to withdraw: ");
    scanf("%d", &amount);
    getchar();

    if (amount <= 0) {
        printf("Amount must be greater than 0.\n");
    } else if (amount > acc.balance) {
        printf("Insufficient balance.\n");
    } else {
        acc.balance -= amount;
        acc.transaction_count++;
        printf("Withdrawn Rs%d. Current balance: Rs%d\n", amount, acc.balance);
        fprintf(fp, "\nWithdrawn: Rs%d\nTime: %s", amount, ctime(&t));
    }

    fclose(fp);
    press_enter();
}

void transfer_money() {
    int amount, target_acc;
    time_t t = time(NULL);
    FILE *fp = fopen("Account.txt", "a");

    divider();
    printf("Transfer Money\n");
    divider();
    printf("Enter target account number: ");
    scanf("%d", &target_acc);
    printf("Enter amount to transfer: ");
    scanf("%d", &amount);
    getchar();

    if (amount <= 0) {
        printf("Amount must be greater than 0.\n");
    } else if (amount > acc.balance) {
        printf("Insufficient balance.\n");
    } else {
        acc.balance -= amount;
        acc.transaction_count++;
        printf("Transferred Rs%d to account %d. Current balance: Rs%d\n", amount, target_acc, acc.balance);
        fprintf(fp, "\nTransferred: Rs%d to account %d\nTime: %s", amount, target_acc, ctime(&t));
    }

    fclose(fp);
    press_enter();
}

void check_detail() {
    divider();
    printf("Account Details\n");
    divider();
    printf("Name: %s\n", acc.name);
    printf("Account Number: %d\n", acc.account_no);
    printf("Current Balance: Rs%d\n", acc.balance);
    printf("Total Transactions: %d\n", acc.transaction_count);
    press_enter();
}

void transaction_details() {
    FILE *fp = fopen("Account.txt", "r");
    char line[MAX_LINE];

    divider();
    printf("Transaction History\n");
    divider();

    if (!fp) {
        printf("No transaction history found.\n");
    } else {
        while (fgets(line, sizeof(line), fp)) {
            printf("%s", line);
        }
        fclose(fp);
    }

    press_enter();
}

void last_detail() {
    divider();
    printf("Final Account Summary\n");
    divider();
    printf("Name: %s\n", acc.name);
    printf("Account Number: %d\n", acc.account_no);
    printf("Final Balance: Rs%d\n", acc.balance);
    printf("Total Transactions: %d\n", acc.transaction_count);
    press_enter();
}


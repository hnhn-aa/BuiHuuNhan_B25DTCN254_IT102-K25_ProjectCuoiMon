#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#define MAX 200

typedef struct {
	char accountId[20];
	char fullName[50];
	char phone[15];
	double balance;
	int status;
} Account;

typedef struct {
	char transId[20];
	char senderId[20];
	char receiverId[20];
	double amount;
	char type[10];
	char date[20];
} Transaction;

int isDuplicate(Account accounts[], int count, char id[]);
int addAccount(Account accounts[], int *count);
void updateAccount(Account accounts[], int count);
void manageStatus(Account accounts[], int count);
void searchAccount(Account accounts[], int count);
void sortByBalance(Account accounts[], int count);
void sortByName(Account accounts[], int count);
void sortAccounts(Account accounts[], int count);
void pressEnterToContinue();
void pressEnterToReturnMenu();
void pressEnterToReturnOption();
void pressEnterToNextPage();
void pressEnterToPreviousPage();
void displayAccountPaging(Account accounts[], int count);
void transferMoney(Account accounts[], int count, Transaction trans[], int *transCount);
int findAccountIndex(Account accounts[], int count, char id[]);
void viewTransactionHistory(Account accounts[], int accCount, Transaction trans[], int transCount);
void toLowerStr(char dest[], const char src[]);
int searchByName(Account accounts[], int count, const char keyword[]);
int isValidPhone(const char *phone);
void PressEnterToLogInToTheMenu();

Transaction trans[MAX];
int transCount=0;
Account accounts[MAX];
int count=0;

int main(){
	Account acc1 = {"A001","Nguyen Van A","0123456789",123.45,1};
	Account acc2 = {"A002","Nguyen Van B","0123456789",12121.22,0};
	Account acc3 = {"A003","Nguyen Van C","0123456789",33113.13,1};
	Account acc4 = {"A004","Nguyen Van D","0123456789",31312.131,0};
	Account acc5 = {"A005","Nguyen Van E","0123456789",32131.434,1};
	Account acc6 = {"A006","Nguyen Van F","0123456789",4443.133,0};
	Account acc7 = {"A007","Nguyen Van G","0123456789",33113.32,1};
	Account acc8 = {"A008","Nguyen Van H","0123456789",33113.32,0};
	Account acc9 = {"A009","Nguyen Van I","0123456789",33113.32,1};
	Account acc10 = {"A010","Nguyen Van K","0123456789",33113.32,0};
	Account acc11 = {"A011","Nguyen Van L","0123456789",33113.32,1};
	Account acc12 = {"A012","Nguyen Van M","0123456789",33113.32,0};
	
	accounts[0] = acc1;
	accounts[1] = acc2;
	accounts[2] = acc3;
	accounts[3] = acc4;
	accounts[4] = acc5;
	accounts[5] = acc6;
	accounts[6] = acc7;
	accounts[7] = acc8;
	accounts[8] = acc9;
	accounts[9] = acc10;
	accounts[10] = acc11;
	accounts[11] = acc12;
	
	count = 12;
		
	int choice;
	char buffer[10];
	printf("Welcome to the C Project Demo!\n");
	PressEnterToLogInToTheMenu();
	
	do{
		system("cls");
		printf("\n");
		printf("================================================\n");
		printf("                MINI BANKING SYSTEM             \n");
		printf("================================================\n");
		printf("   1)  Insert Account                           \n");
		printf("   2)  Update Account Information               \n");
		printf("   3)  Manage Status                            \n");
		printf("   4)  Search Account                           \n");
		printf("   5)  List Accounts                            \n");
		printf("   6)  Sort Accounts                            \n");
		printf("   7)  Transfer Transactions                    \n");
		printf("   8)  Transaction History                      \n");
		printf("------------------------------------------------\n");
		printf("   0)  Exit                                     \n");
		printf("================================================\n");
		printf("Select an option: ");
        fgets(buffer,sizeof(buffer),stdin);
        if(sscanf(buffer,"%d",&choice)!=1){
        	printf("Invalid Selection!!!\n");
        	pressEnterToReturnMenu();
        	continue;	
		}
	
	switch(choice){
		case 1:
			addAccount(accounts, &count);
			pressEnterToReturnMenu();
			break;
		case 2:
			updateAccount(accounts,count);
			pressEnterToReturnMenu();
			break;
		case 3:
			manageStatus(accounts,count);
			pressEnterToReturnMenu();
			break;
		case 4:
			searchAccount(accounts,count);
			pressEnterToReturnMenu();
			break;
		case 5:
			displayAccountPaging(accounts,count);
			break;
		case 6:
			sortAccounts(accounts,count);
			pressEnterToReturnMenu();
			break;
		case 7:
			transferMoney(accounts,count,trans,&transCount);
			pressEnterToReturnMenu();
			break;
		case 8:
			viewTransactionHistory(accounts,count,trans,transCount);
			pressEnterToReturnMenu();
			break;
		case 0:
			printf("Process completed. See you next time!\n");
			printf("Thank you for using!\n");
			break;
		default:
			printf("Error: You need to select the correct function!!!\n");
			pressEnterToReturnMenu();
		}
	}while(choice != 0 || sscanf(buffer,"%d",&choice)!=1);
	return 0;
}

int isDuplicate(Account accounts[], int count, char id[]){
	for (int i=0;i<count;i++){
		if(strcmp(accounts[i].accountId, id)==0){
			return 1;
		}
	}
	return 0;
}

int addAccount(Account accounts[], int *count){
	if(*count >= MAX){
		printf("The account list is full!!!\n");
		return 0;
	}
	
	printf("\n ===== INSERT ACCOUNT =====\n");
	Account acc;
	acc.balance =0;
	do{
		printf("Enter Account ID: ");
		fgets(acc.accountId, sizeof(acc.accountId), stdin);
		acc.accountId[strcspn(acc.accountId, "\n")]= '\0';
	
		if(strlen(acc.accountId)==0){
			printf("Error: Account ID cannot be blank!!!\n");
		}
	
		if(isDuplicate(accounts, *count, acc.accountId)){
			printf("Error: Duplicate Account ID!!!\n");
		}
	}while(strlen(acc.accountId)==0 || isDuplicate(accounts, *count, acc.accountId));
	do{
		printf("Enter FullName: ");
		fgets(acc.fullName,sizeof(acc.fullName),stdin);
		acc.fullName[strcspn(acc.fullName, "\n")]= '\0';
	
		if(strlen(acc.fullName)==0){
			printf("Error: Full name cannot be left blank!!!\n");
		}
	}while(strlen(acc.fullName)==0);
	
	while (1) {
    	printf("Enter Phone: ");
    	fgets(acc.phone, sizeof(acc.phone), stdin);
    	acc.phone[strcspn(acc.phone, "\n")] = '\0';

	    if (!isValidPhone(acc.phone)) {
	        printf("Error: Phone number is invalid! It must contain digits only and have 10 characters.\n");
	        continue;
    }

    break;
}

	printf("Insert complete\n");
	
	acc.status = 1;
	
	accounts[*count]=acc;
	(*count)++;
	return 1;
}

void updateAccount(Account accounts[], int count){
	char id[20];
	char newName[50];
	char newPhone[15];
	int found = -1;
	
	if(count==0){
		printf("Account list is empty!!!\n");
		return;
	}
	
	printf("\n ===== UPDATE ACCOUNT ===== \n");
	do{
		printf("Enter Account ID need update: ");
		fgets(id,sizeof(id),stdin);
		id[strcspn(id,"\n")]='\0';
	
		if(strlen(id)==0){
			printf("Error: Account ID cannot be blank!!!\n");
		}
	}while(strlen(id)==0);
		
	for(int i=0;i<count;i++){
		if(strcmp(accounts[i].accountId, id)==0){
			found=i;
			break;
		}
	}
	
	if(found ==-1){
		printf("Error: Account with this ID not found!!!\n");
		return ;
	}
	
	if (accounts[found].status != 1) {
        printf("Error: This account is LOCKED and cannot be updated!!!\n");
        return;
    }
    
	Account acc=accounts[found];
	
	printf("\n -------- OLD INFORMATION --------\n");
    printf("+---------------------+--------------------------------+\n");
    printf("| Field               | Value                          |\n");
    printf("+---------------------+--------------------------------+\n");
    printf("| Account ID          | %-30s |\n", acc.accountId);
    printf("| Full Name           | %-30s |\n", acc.fullName);
    printf("| Phone               | %-30s |\n", acc.phone);
    printf("| Balance             | %-30.2lf |\n", acc.balance);
    printf("| Status              | %-30s |\n", acc.status == 1 ? "ACTIVE" : "LOCKED");
    printf("+---------------------+--------------------------------+\n");
	
	do{
		printf("Enter NewName: ");
		fgets(newName,sizeof(newName),stdin);
		newName[strcspn(newName,"\n")]='\0';
	
		if(strlen(newName)==0){
			printf("Error: Name cannot be blank!!!\n");
		}
	}while(strlen(newName)==0);	
	
	do{
	    printf("Enter NewPhone: ");
	    fgets(newPhone,sizeof(newPhone),stdin);
	    newPhone[strcspn(newPhone,"\n")] = '\0';
	
	    if (!isValidPhone(newPhone)) {
	        printf("Error: Phone number is invalid! It must contain digits only and have 10 characters.\n");
	    }
	} while (!isValidPhone(newPhone));
	
	strcpy(accounts[found].fullName,newName);
	strcpy(accounts[found].phone,newPhone);
	
	printf("\nUpdate complete!\n");
}

void manageStatus(Account accounts[],int count){
	if(count==0){
		printf("Account list is empty!!!\n");
		return;
	}
	char id[20];
	do{
		printf("Enter Account ID need change status: ");
		fgets(id,sizeof(id),stdin);
		id[strcspn(id,"\n")]='\0';
		
		if(strlen(id)==0){
			printf("Account ID cannot be blank!!!\n");
		}
	}while(strlen(id)==0);
	
	int found = -1;
	for(int i=0;i<count;i++){
		if(strcmp(accounts[i].accountId,id)==0){
			found =i;
			break;
		}
	}
	if(found==-1){
		printf("Error: Account with this ID not found!!!\n");
		return;
	}

    printf("\n--- ACCOUNT INFORMATION ---\n");
	printf("+---------------------+--------------------------------+\n");
	printf("| Field               | Value                          |\n");
	printf("+---------------------+--------------------------------+\n");
	printf("| Account ID          | %-30s |\n", accounts[found].accountId);
	printf("| Full Name           | %-30s |\n", accounts[found].fullName);
	printf("| Phone               | %-30s |\n", accounts[found].phone);
	printf("| Balance             | %-30.2lf |\n", accounts[found].balance);
	printf("| Status              | %-30s |\n", accounts[found].status == 1 ? "ACTIVE" : "LOCKED");
	printf("+---------------------+--------------------------------+\n");


    int option;
    char buffer[10];
    do{
    	printf("\nWhat do you want?\n");
    	printf("1. Unlock account\n");
    	printf("0. Locked account\n");
    	printf("Lua chon: ");
    	fgets(buffer,sizeof(buffer),stdin);
    	if(sscanf(buffer,"%d",&option)!=1){
    		printf("You need enter option!!!\n");
		}
	}while(sscanf(buffer,"%d",&option)!=1);

    if (option == 1) {
        accounts[found].status = 1;
        printf("Account has been unlocked.\n");
    } 
    else if (option == 0) {
        accounts[found].status = 0;
        printf("Account has been locked.\n");
    } 
    else {
        printf("Invalid Option!\n");
    }
}

void searchAccount(Account accounts[],int count){
	if(count==0){
		printf("Error: Account list is empty!!!\n");
		return ;
	}
	int choose;
	char id[20];
	char name[50];
	char buffer[10];
	char keyword[50];
	do{
		printf("What form of account do you want to search???\n");
		printf("1. Search by Account ID\n");
		printf("2. Search by FullName\n");
		printf("0. Exit\n");
		printf("Invite you to choose funtion: ");
		fgets(buffer,sizeof(buffer),stdin);
		if(sscanf(buffer,"%d",&choose)!=1){
			printf("Error: You need choose correct funtion!!!\n");
		}
		
		switch(choose){
			case 1:
				do{
					printf("Enter ID you want to search: ");
					fgets(id,sizeof(id),stdin);
					id[strcspn(id,"\n")]='\0';
					if(strlen(id)==0){
						printf("Error: Account ID cannot be blank!!!\n");
					}
				}while(strlen(id)==0);
				
				int found=-1;
				for(int i=0;i<count;i++){
					if(strcmp(accounts[i].accountId,id)==0){
						found=i;
						break;
					}
				}
				if(found==-1){
					printf("Account with this ID not found!!!\n");
					break;
				}
				
				printf("===== ACCOUNT INFORMATION TO SEARCH ===== \n");
				printf("+---------------------+--------------------------------+\n");
				printf("| Field               | Value                          |\n");
				printf("+---------------------+--------------------------------+\n");
				printf("| Account ID          | %-30s |\n", accounts[found].accountId);
				printf("| Full Name           | %-30s |\n", accounts[found].fullName);
				printf("| Phone               | %-30s |\n", accounts[found].phone);
				printf("| Balance             | %-30.2lf |\n", accounts[found].balance);
				printf("| Status              | %-30s |\n", accounts[found].status == 1 ? "ACTIVE" : "LOCKED");
				printf("+---------------------+--------------------------------+\n");

				break;
			case 2:			
				printf("Nhap ten can tim: ");
				fgets(keyword, sizeof(keyword), stdin);
				keyword[strcspn(keyword, "\n")] = '\0'; 

				searchByName(accounts, count, keyword);
				break;
			case 0:
				printf("====== THANK YOU FOR USING THIS FUNCTION ======\n");
				break;
			default:
				printf("Error: You need enter correct funtion!!!\n");
		}
	}while(choose!=0 || sscanf(buffer,"%d",&choose)!=1);
}

void sortByBalance(Account accounts[], int count){
	for(int i=0;i<count-1;i++){
		for(int j=i+1;j<count;j++){
			if(accounts[i].balance < accounts[j].balance){
				Account temp = accounts[i];
				accounts[i] = accounts[j];
				accounts[j] = temp;
			}
		}
	}
	printf("Sort the list by descending balance successfully!!!\n");
}

void sortByName(Account accounts[], int count){
	for(int i=0;i<count-1;i++){
		for(int j=i+1;j<count;j++){
			if(strcmp(accounts[i].fullName, accounts[j].fullName)>0){
				Account temp = accounts[i];
				accounts[i] = accounts[j];
				accounts[j] = temp;
			}
		}
	}
	printf("Sort list by name from A -> Z successfully!!!\n");
}

void sortAccounts(Account accounts[], int count){
	if(count==0){
		printf("Error: Account list is empty!!!\n");
		return;
	}
	char buffer[10];
	int choice;
	do{
		printf("How do you want to sort the list?\n");
		printf("1. Sort the list by descending balance\n");
		printf("2. Sort list by name from A -> Z\n");
		printf("3. Exit\n");
		printf("Your choice: ");
		fgets(buffer,sizeof(buffer),stdin);
		if(sscanf(buffer,"%d",&choice)!=1){
			printf("Invalid Choice!!!\n");
		}
		
		switch(choice){
			case 1:
				sortByBalance(accounts,count);
				break;
			case 2:
				sortByName(accounts,count);
				break;
			case 3:
				printf("====== THANK YOU FOR USING THIS FUNCTION ======\n");
				break;
			default:
				printf("Error: You need enter correct choice!!!\n");
		}
	}while(choice!=3 || sscanf(buffer,"%d",&choice)!=1);
}

void pressEnterToContinue(){
	char temp[10];
	printf("\nPress Enter To Continue...");
	fgets(temp,sizeof(temp),stdin);
}

void pressEnterToReturnMenu(){
	char temp[10];
	printf("\nPress Enter To Return Menu...");
	fgets(temp,sizeof(temp),stdin);
}

void pressEnterToReturnOption(){
	char temp[10];
	printf("\nPress Enter To Return Option...");
	fgets(temp,sizeof(temp),stdin);
}

void pressEnterToNextPage(){
	char temp[10];
	printf("\nPress Enter To Next Page...");
	fgets(temp,sizeof(temp),stdin);
}

void pressEnterToPreviousPage(){
	char temp[10];
	printf("\nPress Enter To Previous Page...");
	fgets(temp,sizeof(temp),stdin);
}

void PressEnterToLogInToTheMenu(){
	char temp[10];
	printf("\nPress Enter To Log In To The Menu...");
	fgets(temp,sizeof(temp),stdin);
}

void displayAccountPaging(Account accounts[], int count){
	if(count==0){
		printf("Error: Account List Is Empty!!!\n");
		return;
	}
	
	int itemPerPage = 3;
	int totalPages = (count + itemPerPage - 1)/itemPerPage;
	int page = 1;
	char option[10];
	
	while (1) {
        system("cls");

        printf("\n 		============ LIST ACCOUNT (PAGE %d / %d) ============\n", page, totalPages);
        printf("+-----------------+----------------------+--------------+--------------+----------+\n");
		printf("|   ACCOUNT ID    |       FULLNAME       |    PHONE     |   BALANCE    |  STATUS  |\n");
		printf("+-----------------+----------------------+--------------+--------------+----------+\n");

        int start = (page - 1) * itemPerPage;
        int end = start + itemPerPage;
        if (end > count) end = count;

        for (int i = start; i < end; i++) {
    		printf("| %-15s | %-20s | %-12s | %12.2lf | %-8s |\n",
           accounts[i].accountId,
           accounts[i].fullName,
           accounts[i].phone,
           accounts[i].balance,
           accounts[i].status == 1 ? "ACTIVE" : "LOCKED");
}
		printf("+-----------------+----------------------+--------------+--------------+----------+\n");

        printf("\nOptions:\n");
        printf("N - Next page\n");
        printf("P - Previous page\n");
        printf("G - Go to page\n");
        printf("Q - Quit\n");
        printf("Your option: ");

        fgets(option, sizeof(option), stdin);

        if (option[0] == 'N' || option[0] == 'n') {
            if (page < totalPages){
            	page++;
            	pressEnterToNextPage();
			}else{
				printf("This is the last page!\n");
				pressEnterToReturnOption();
			}  
        }else if(option[0] == 'P' || option[0] == 'p') {
            if (page > 1){
            	page--;
            	pressEnterToPreviousPage();
			}else{
				printf("This is the first page!\n");
				pressEnterToReturnOption();
			}     
        }else if(option[0] == 'G' || option[0] == 'g'){
            char buffer[10];
            int go;

            do{
                printf("Enter page number (1 - %d): ", totalPages);
                fgets(buffer, sizeof(buffer), stdin);

                if (sscanf(buffer, "%d", &go) != 1 || go < 1 || go > totalPages) {
                    printf("Invalid page number!\n");
                    pressEnterToReturnOption();
                }else{
                    page = go;
                    char temp[10];
                    printf("\nPress Enter To Go To Page %d...",page);
                    fgets(temp,sizeof(temp),stdin);
                    break;
                }
            } while (1);
        }else if (option[0] == 'Q' || option[0] == 'q') {
            break;
    	}else{
            printf("Invalid choice!\n");
            pressEnterToReturnOption();
        }
    }
}

void transferMoney(Account accounts[], int count, Transaction trans[], int *transCount){
	char senderId[20];
	char receiverId[20];
	double amount;
	
	int senderIndex;
	int receiverIndex;
	
	printf("\n====== TRANSFER MONEY FUNCTION =====\n");
	
	do{
		printf("Enter Sender Account ID: ");
		fgets(senderId,sizeof(senderId),stdin);
		senderId[strcspn(senderId,"\n")]='\0';
	
		if(strlen(senderId)==0){
			printf("Error: Account ID cannot be blank!!!\n");
			continue;
		}
		
		senderIndex = findAccountIndex(accounts,count,senderId);
			
		if(senderIndex == -1){
			printf("Error: Sender ID does not exist!!!\n");
			continue;
		}
		
		if(accounts[senderIndex].status != 1){
			printf("Error: The account of Sender is locked!!!\n");
			continue;
		}
		
		if (accounts[senderIndex].balance <= 0) {
		    printf("Error: Sender account balance is 0, cannot transfer!!!\n");
		    continue;
		}

		break;
	}while(1);
	
	do{
		printf("Enter Receriver Account ID: ");
		fgets(receiverId,sizeof(receiverId),stdin);
		receiverId[strcspn(receiverId,"\n")]='\0';
	
		if(strlen(receiverId)==0){
			printf("Error: Account ID cannot be blank!!!\n");
			continue;
		}
		
		receiverIndex = findAccountIndex(accounts,count,receiverId);
			
		if(receiverIndex == -1){
			printf("Error: Receriver ID does not exist!!!\n");
			continue;
		}
		
		if(accounts[receiverIndex].status != 1){
			printf("Error: The account of Receriver is locked!!!\n");
			continue;
		}	
		break;
	}while(1);
	
	if(strcmp(senderId,receiverId)==0){
		printf("Error: Sender ID and Receiver ID are the same!!!\n");
		return;
	}
	
	char buffer[20];
	int ok;
	do {
	    ok = 1;
	    printf("Enter the amount to transfer: ");
	    fgets(buffer, sizeof(buffer), stdin);
	
    	if (sscanf(buffer, "%lf", &amount) != 1) {
        	printf("Invalid amount! Please enter a number.\n");
        	ok = 0;
    	} else {
	        if (amount <= 0) {
	            printf("Error: The transfer amount must be greater than 0!!!\n");
        	    ok = 0;
    	    } else if (amount > accounts[senderIndex].balance) {
	            printf("Error: Insufficient account balance!!!\n");
            	ok = 0;
        	}
    	}
	} while (!ok);		
	
	printf("Transfer successful\n");
	if (*transCount >= MAX) {
    	printf("Error: Transaction history is full!!!\n");
    	return;
}

	accounts[senderIndex].balance -= amount;
	accounts[receiverIndex].balance += amount;
	
	Transaction t;

	sprintf(t.transId, "T%03d", *transCount + 1);
	strcpy(t.senderId, senderId);
	strcpy(t.receiverId, receiverId);
	t.amount = amount;
	strcpy(t.type, "TRANSFER");

	time_t now = time(NULL);
	struct tm *tm_info = localtime(&now);

	strftime(t.date, sizeof(t.date), "%Y-%m-%d %H:%M:%S", tm_info);

	trans[*transCount] = t;
	(*transCount)++;

	printf("Transaction history saved\n");
}
int findAccountIndex(Account accounts[], int count, char id[]){
    for(int i = 0; i < count; i++){
        if(strcmp(accounts[i].accountId, id) == 0){
            return i;
        }
    }
    return -1;
}

void viewTransactionHistory(Account accounts[], int count, Transaction trans[], int transCount) {
    char targetId[20];

    if (count == 0) {
        printf("Error: Account list is empty!!!\n");
        return;
    }

    printf("\n====== VIEW TRANSACTION HISTORY ======\n");

    do {
        printf("Enter Account ID to view history: ");
        fgets(targetId, sizeof(targetId), stdin);
        targetId[strcspn(targetId, "\n")] = '\0';

        if (strlen(targetId) == 0) {
            printf("Error: Account ID cannot be blank!!!\n");
        }
    } while (strlen(targetId) == 0);

    int exist = isDuplicate(accounts, count, targetId);

    if (!exist) {
        printf("Error: Account does not exist!!!\n");
        return;
    }

    if (transCount == 0) {
        printf("The system has no transactions yet!!!\n");
        return;
    }

    int found = 0;

    printf("\n===== TRANSACTION HISTORY OF ACCOUNT %s =====\n", targetId);
    printf("+------------+---------------------+------------+--------+--------------+--------------+\n");
    printf("| TransID    | Date                | Type       | Dir    |   Amount     |   Partner    |\n");
    printf("+------------+---------------------+------------+--------+--------------+--------------+\n");

    for (int i = 0; i < transCount; i++) {
        int isSender   = (strcmp(trans[i].senderId,   targetId) == 0);
        int isReceiver = (strcmp(trans[i].receiverId, targetId) == 0);

        if (isSender || isReceiver) {
            found = 1;

            char dir[4];
            char partner[20];

            if (isSender) {
                strcpy(dir, "Out");
                strcpy(partner, trans[i].receiverId);
            } else {
                strcpy(dir, "In");
                strcpy(partner, trans[i].senderId);
            }

            printf("| %-10s | %-19s | %-10s | %-6s | %12.2lf | %-12s |\n",
                   trans[i].transId,
                   trans[i].date,
                   trans[i].type,
                   dir,
                   trans[i].amount,
                   partner);
        }
    }

    if (!found) {
        printf("No transaction!!!\n");
    } else {
        printf("+------------+---------------------+------------+--------+--------------+--------------+\n");
    }
}

void toLowerStr(char dest[], const char src[]) {
    int i;
    for (i = 0; src[i] != '\0'; i++) {
        dest[i] = (char)tolower((unsigned char)src[i]);
    }
    dest[i] = '\0';
}

int searchByName(Account accounts[], int count, const char keyword[]) {
    char keyLower[50];
    char nameLower[50];
    int dem = 0;

    toLowerStr(keyLower, keyword);

    for (int i = 0; i < count; i++) {

        toLowerStr(nameLower, accounts[i].fullName);

        if (strstr(nameLower, keyLower) != NULL) {

            if (dem == 0){
                printf("\n====== SEARCH RESULTS ======\n");
                printf("+------------+--------------------------+--------------+\n");
                printf("|   ID       | Name                     |   Balance    |\n");
                printf("+------------+--------------------------+--------------+\n");
            }    

            printf("| %-10s | %-24s | %12.2f |\n",
                   accounts[i].accountId,
                   accounts[i].fullName,
                   accounts[i].balance);

            dem++;
        }
    }

    if (dem == 0){
        printf("No matching results!!!\n");
    }else{
        printf("+------------+--------------------------+--------------+\n");
    }

    return dem;
}

int isValidPhone(const char *phone) {
    int len = strlen(phone);

    if (len == 0) return 0;

    if (len != 10) return 0;

    for (int i = 0; i < len; i++) {
        if (!isdigit((unsigned char)phone[i])) {
            return 0;
        }
    }
    
    return 1;
}

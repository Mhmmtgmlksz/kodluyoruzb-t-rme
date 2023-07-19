#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Kullanıcı veri yapısı
struct User {
    char name[100];
    int accountNumber;
    double balance;
};

// Dosya adı
const char* FILE_NAME = "bank_accounts.txt";

// Kullanıcı verilerini dosyadan yükleyen fonksiyon
void loadUsers(struct User users[], int* userCount) {
    FILE* file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    *userCount = 0;
    while (!feof(file)) {
        fscanf(file, "%s %d %lf", users[*userCount].name, &users[*userCount].accountNumber, &users[*userCount].balance);
        (*userCount)++;
    }

    fclose(file);
}

// Kullanıcı verilerini dosyaya kaydeden fonksiyon
void saveUsers(struct User users[], int userCount) {
    FILE* file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %d %.2lf\n", users[i].name, users[i].accountNumber, users[i].balance);
    }

    fclose(file);
}

// Kullanıcı kaydı oluşturan fonksiyon
void createUser(struct User users[], int* userCount) {
    // Kullanıcı bilgilerini al
    printf("Ad ve soyad girin: ");
    scanf("%s", users[*userCount].name);
    printf("Hesap numarasini girin: ");
    scanf("%d", &users[*userCount].accountNumber);
    printf("Baslangic bakiyesini girin: ");
    scanf("%lf", &users[*userCount].balance);

    (*userCount)++;
}

// Hesap bakiyesini güncelleyen fonksiyon
void updateBalance(struct User users[], int userCount, int accountNumber, double amount) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].accountNumber == accountNumber) {
            users[i].balance += amount;
            break;
        }
    }
}

// Hesap bakiyesini gösteren fonksiyon
void showBalance(struct User users[], int userCount, int accountNumber) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].accountNumber == accountNumber) {
            printf("Hesap bakiyesi: %.2lf\n", users[i].balance);
            break;
        }
    }
}

int main() {
    struct User users[100];
    int userCount = 0;

    loadUsers(users, &userCount);

    int choice;
    do {
        printf("\nBanka Hesap Yonetimi\n");
        printf("1. Yeni hesap olustur\n");
        printf("2. Hesap bakiyesini goruntule\n");
        printf("3. Para yatirma\n");
        printf("4. Para cekme\n");
        printf("0. Cikis\n");
        printf("Seciminizi yapin: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createUser(users, &userCount);
                break;
            case 2: {
                int accountNumber;
                printf("Hesap numarasini girin: ");
                scanf("%d", &accountNumber);
                showBalance(users, userCount, accountNumber);
                break;
            }
            case 3: {
                int accountNumber;
                double amount;
                printf("Hesap numarasini girin: ");
                scanf("%d", &accountNumber);
                printf("Yatirilacak miktarini girin: ");
                scanf("%lf", &amount);
                updateBalance(users, userCount, accountNumber, amount);
                break;
            }
            case 4: {
                int accountNumber;
                double amount;
                printf("Hesap numarasini girin: ");
                scanf("%d", &accountNumber);
                printf("Cekilecek miktarini girin: ");
                scanf("%lf", &amount);
                updateBalance(users, userCount, accountNumber, -amount);
                break;
            }
            case 0:
                break;
            default:
                printf("Geçersiz secim!\n");
                break;
        }
    } while (choice != 0);

    saveUsers(users, userCount);

    return 0;
}
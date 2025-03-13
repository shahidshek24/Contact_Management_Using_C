#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct contact {
    char n[20];
    long int ph;
    char em[30];
};

struct contact p, q[50];
int n, i;
FILE *f, *f2;

void save(void);
void print(void);
void search(void);
void edit(void);
void delet(void);
int login(void);

int main() {
    int a, b, key;
    key = login();
    if (key == 1) {
        do {
            system("clear"); 
            printf("\t\t\tMAIN MENU\n");
            printf("-------------------------------------------------------------------\n");
            printf("\t1. SAVE NEW CONTACT\n\t2. LIST OF CONTACT\n\t3. SEARCH CONTACT\n\t4. EDIT CONTACT\n\t5. DELETE CONTACT\n");
            printf("-------------------------------------------------------------------\n");
            printf("Enter your choice: ");
            scanf("%d", &a);
            switch (a) {
                case 1: save(); break;
                case 2: print(); break;
                case 3: search(); break;
                case 4: edit(); break;
                case 5: delet(); break;
                default: printf("Enter correct choice\n");
            }
            printf("Press 0 to exit or 1 to continue: ");
            scanf("%d", &b);
        } while (b == 1);
    }
    printf("Thank you\n");
    return 0;
}

int login() {
    char key[] = "12345678", password[9];
    int i = 0;
    char ch;

    printf("Enter 8 digit password: ");
    while (i < 8) {
        ch = getche();
        password[i] = ch;
        printf("*"); 
        ++i;
    }
    password[i] = '\0';
    printf("\n");

    return strcmp(key, password) == 0 ? 1 : 0;
}

void save(void) {
    int a;
    system("clear"); 
    f = fopen("contact.txt", "a");
    if (f == NULL) {
        perror("Error opening file");
        return;
    }

    printf("Enter the number of contacts to save: ");
    scanf("%d", &a);
    for (i = 0; i < a; i++) {
        printf("Enter the name: ");
        scanf("%s", p.n);
        printf("Enter the phone number: ");
        scanf("%ld", &p.ph);
        printf("Enter the email ID: ");
        scanf("%s", p.em);
        fprintf(f, "%s\n%ld\n%s\n", p.n, p.ph, p.em);
    }
    fclose(f);
    printf("Successfully saved contacts\n");
}

void print(void) {
    system("clear");
    f = fopen("contact.txt", "r");
    if (f == NULL) {
        perror("Error opening file");
        return;
    }

    printf("\t\t\tLIST OF CONTACTS\n");
    printf("-------------------------------------------------------------------\n");
    printf("Name\t\tNumber\t\tEmail ID\n");
    printf("-------------------------------------------------------------------\n");

    while (fscanf(f, "%s%ld%s", q[n].n, &q[n].ph, q[n].em) != EOF) {
        n++;
    }

    for (i = 0; i < n; i++) {
        printf("%s\t\t%ld\t\t%s\n", q[i].n, q[i].ph, q[i].em);
        printf("-------------------------------------------------------------------\n");
    }
    fclose(f);
    n = 0; 
}

void search(void) {
    int c;
    char tn[20];
    long int tph;
    int found = 0;

    printf("\tSEARCH BY\n\t\t1. Name\n\t\t2. Number: ");
    scanf("%d", &c);
    f = fopen("contact.txt", "r");
    if (f == NULL) {
        perror("Error opening file");
        return;
    }

    switch (c) {
        case 1:
            printf("Enter the name to search: ");
            scanf("%s", tn);
            while (fscanf(f, "%s%ld%s", p.n, &p.ph, p.em) != EOF) {
                if (strcmp(tn, p.n) == 0) {
                    found = 1;
                    printf("Name: %s, Number: %ld, Email: %s\n", p.n, p.ph, p.em);
                    break;
                }
            }
            if (!found) printf("%s not found\n", tn);
            break;
        case 2:
            printf("Enter the number to search: ");
            scanf("%ld", &tph);
            while (fscanf(f, "%s%ld%s", p.n, &p.ph, p.em) != EOF) {
                if (tph == p.ph) {
                    found = 1;
                    printf("Name: %s, Number: %ld, Email: %s\n", p.n, p.ph, p.em);
                    break;
                }
            }
            if (!found) printf("%ld not found\n", tph);
            break;
        default:
            printf("Enter correct choice\n");
    }
    fclose(f);
}

void edit() {
    int h, e, g;
    char tn[20];
    int found = 0;

    printf("Enter the name to edit: ");
    scanf("%s", tn);
    f = fopen("contact.txt", "r");
    f2 = fopen("temp.txt", "w");
    if (f == NULL || f2 == NULL) {
        perror("Error opening file");
        return;
    }

    while (fscanf(f, "%s%ld%s", q[i].n, &q[i].ph, q[i].em) != EOF) {
        if (strcmp(tn, q[i].n) == 0) {
            found = 1;
            printf("Current details - Name: %s, Number: %ld, Email: %s\n", q[i].n, q[i].ph, q[i].em);
            printf("Edit Name (1 for yes, 0 for no): ");
            scanf("%d", &h);
            if (h == 1) {
                printf("Enter new name: ");
                scanf("%s", q[i].n);
            }
            printf("Edit Number (1 for yes, 0 for no): ");
            scanf("%d", &e);
            if (e == 1) {
                printf("Enter new number: ");
                scanf("%ld", &q[i].ph);
            }
            printf("Edit Email (1 for yes, 0 for no): ");
            scanf("%d", &g);
            if (g == 1) {
                printf("Enter new email: ");
                scanf("%s", q[i].em);
            }
        }
        fprintf(f2, "%s\n%ld\n%s\n", q[i].n, q[i].ph, q[i].em);
        i++;
    }
    fclose(f);
    fclose(f2);

    if (!found) {
        printf("%s not found\n", tn);
    } else {
        f = fopen("contact.txt", "w");
        f2 = fopen("temp.txt", "r");
        while (fscanf(f2, "%s%ld%s", p.n, &p.ph, p.em) != EOF) {
            fprintf(f, "%s\n%ld\n%s\n", p.n, p.ph, p.em);
        }
        fclose(f);
        fclose(f2);
    }
}

void delet() {
    char tn[20];
    int found = 0;
    char choice;

    printf("Enter the name to delete: ");
    scanf("%s", tn);
    f = fopen("contact.txt", "r");
    f2 = fopen("temp.txt", "w");
    if (f == NULL || f2 == NULL) {
        perror("Error opening file");
        return;
    }

    while (fscanf(f, "%s%ld%s", q[i].n, &q[i].ph, q[i].em) != EOF) {
        if (strcmp(tn, q[i].n) == 0) {
            found = 1;
            printf("Current details - Name: %s, Number: %ld, Email: %s\n", q[i].n, q[i].ph, q[i].em);
            printf("Are you sure you want to delete this contact? (y/n): ");
            scanf(" %c", &choice);
            if (choice != 'y') {
                fprintf(f2, "%s\n%ld\n%s\n", q[i].n, q[i].ph, q[i].em);
            }
        } else {
            fprintf(f2, "%s\n%ld\n%s\n", q[i].n, q[i].ph, q[i].em);
        }
        i++;
    }
    fclose(f);
    fclose(f2);

    if (!found) {
        printf("%s not found\n", tn);
    } else {
        f = fopen("contact.txt", "w");
        f2 = fopen("temp.txt", "r");
        while (fscanf(f2, "%s%ld%s", p.n, &p.ph, p.em) != EOF) {
            fprintf(f, "%s\n%ld\n%s\n", p.n, p.ph, p.em);
        }
        fclose(f);
        fclose(f2);
    }
}

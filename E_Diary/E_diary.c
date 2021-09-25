#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define MAX 1000

void addrecord();
void viewrecord();
void editrecord();

struct record
{
    char time[10];
    char name[30];
    char note[MAX];
};

int main(int argc, char const *argv[])
{
    int ch;

    printf("\n\n\t****************************************\n");
    printf("\t* ---->  WELCOME TO THE E-DIARY  <---- *\n");
    printf("\t****************************************");

    while (1)
    {
        printf("\n\n\t\tMAIN MENU:");
        printf("\n\n\tADD RECORD\t[1]");
        printf("\n\tVIEW RECORD\t[2]");
        printf("\n\tEDIT RECORD\t[3]");
        printf("\n\tEXIT\t\t[4]");
        printf("\n\n\tENTER YOUR CHOICE: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            addrecord();
            break;

        case 2:
            viewrecord();
            break;

        case 3:
            editrecord();
            break;

        case 4:
            printf("\n\n\t\tTHANK YOU FOR USING THE E-DIARY ");
            getch();
            exit(0);

        default:
            printf("\nYOU ENTERED WRONG CHOICE..");
            printf("\nPRESS ANY KEY TO TRY AGAIN");
            getch();
            break;
        }
        system("cls");
    }

    return 0;
}

// ADD RECORD FUNCTION WILL ADDING DATA

void addrecord()
{
    system("cls");

    FILE *fp;

    char another = 'Y';
    char time[10];
    struct record e;
    char filename[15];
    int choice;

    printf("\n\n\t\t********************************\n");
    printf("\t\t* WELCOME TO THE ADD MENU *");
    printf("\n\t\t********************************\n\n");
    printf("\n\n\tENTER DATE OF YOUR RECORD:[dd-mm-yyyy]:");

    fflush(stdin);
    gets(filename);
    fp = fopen(filename, "ab+");

    if (fp == NULL)
    {
        fp = fopen(filename, "wb+");
        if (fp == NULL)
        {
            printf("\nIT IS A SYSTEM ERROR...");
            printf("\nPRESS ANY KEY TO EXIT");
            getch();

            return;
        }
    }

    while (another == 'Y' || another == 'y')
    {
        choice = 0;
        fflush(stdin);
        printf("\n\tENTER TIME:[hh:mm-AM/PM]: ");
        scanf("%s", time);
        rewind(fp);

        while (fread(&e, sizeof(e), 1, fp) == 1)
        {
            if (strcmp(e.time, time) == 0)
            {
                printf("\n\tTHE RECORD ALREADY EXISTS.\n");
                choice = 1;
            }
        }

        if (choice == 0)
        {
            strcpy(e.time, time);
            printf("\tENTER NAME: ");
            fflush(stdin);
            gets(e.name);
            fflush(stdin);

            printf("\tNOTE: ");
            gets(e.note);
            fwrite(&e, sizeof(e), 1, fp);

            printf("\nYOUR RECORD IS ADDED...\n");
        }

        printf("\n\tADD ANOTHER RECORD...(Y/N) ");
        fflush(stdin);
        another = getchar();
    }

    fclose(fp);
    printf("\n\n\tPRESS ANY KEY TO EXIT...");
    getch();
}

// VIEW RECORD FUNCTION WILL DISPLAY THR RECORD

void viewrecord()
{
    FILE *fpte;
    system("cls");

    struct record customer;
    char time[6], choice, filename[14];
    int ch;

    printf("\n\n\t\t*******************************\n");
    printf("\t\t* HERE IS THE VIEWING MENU *");
    printf("\n\t\t*******************************\n\n");

    do
    {
        printf("\n\tENTER THE DATE OF RECORD TO BE VIEWED:[dd-mm-yyyy]:");

        fflush(stdin);
        gets(filename);
        fpte = fopen(filename, "rb");

        if (fpte == NULL)
        {
            puts("\nTHE RECORD DOES NOT EXIST...\n");
            printf("PRESS ANY KEY TO EXIT...");
            getch();

            return;
        }

        system("cls");

        printf("\nTHE WHOLE RECORD FOR %s IS:", filename);

        while (fread(&customer, sizeof(customer), 1, fpte) == 1)
        {
            printf("\n");
            printf("\nTIME: %s", customer.time);
            printf("\nNOTES BY: %s", customer.name);
            printf("\n");
            printf("\nNOTE: %s", customer.note);
            printf("\n");
        }

        printf("\n\nWOULD YOU LIKE TO CONTINUE VIEWING...(Y/N):");
        fflush(stdin);
        scanf("%c", &choice);
    } while (choice == 'Y' || choice == 'y');

    fclose(fpte);

    return;
}

// EDIT FUCTOPN WILL EDIT THE RECORD

void editrecord()
{
    system("cls");
    FILE *fpte;
    struct record customer;
    char time[6], choice, filename[14];
    int num, count = 0;

    printf("\n\n\t\t*******************************\n");
    printf("\t\t* WELCOME TO THE EDITING MENU *");
    printf("\n\t\t*******************************\n\n");

    do
    {
        printf("\n\tENTER THE DATE OF RECORD TO BE EDITED:[dd-mm-yyyy]:");
        fflush(stdin);
        gets(filename);
        fpte = fopen(filename, "rb+");

        if (fpte == NULL)
        {
            printf("\nRECORD DOES NOT EXISTS:");
            printf("\nPRESS ANY KEY TO GO BACK");
            getch();
            return;
        }

        while (fread(&customer, sizeof(customer), 1, fpte) == 1)
        {
            printf("\nYOUR OLD RECORD WAS AS:");
            printf("\nTIME: %s", customer.time);
            printf("\nNAME: %s", customer.name);
            printf("\n");
            printf("\nNOTE: %s", customer.note);

            printf("\n\n\t\tWHAT WOULD YOU LIKE TO EDIT..");

            printf("\n1.TIME.");
            printf("\n2.NAME.");
            printf("\n3.NOTE.");
            printf("\n4.WHOLE RECORD.");
            printf("\n5.GO BACK TO MAIN MENU.");

            do
            {
                printf("\n\tENTER YOUR CHOICE:");
                fflush(stdin);
                scanf("%d", &num);
                fflush(stdin);

                switch (num)
                {
                case 1:
                    printf("\nENTER THE NEW DATA:");
                    printf("\nNEW TIME:[hh:mm]: ");
                    gets(customer.time);
                    break;

                case 2:
                    printf("\nENTER THE NEW DATA:");
                    printf("\nNEW NAME: ");
                    gets(customer.name);
                    break;

                case 3:
                    printf("ENTER THE NEW DATA:");
                    printf("\nNOTE: ");
                    gets(customer.note);
                    break;

                case 4:
                    printf("\nENTER THE NEW DATA:");
                    printf("\nNEW TIME:[hh:mm]: ");
                    gets(customer.time);
                    printf("\nNEW NAME: ");
                    gets(customer.name);
                    printf("\n");
                    printf("\nNOTE: ");
                    gets(customer.note);
                    break;

                case 5:
                    printf("\nPRESS ANY KEY TO GO BACK...\n");
                    getch();
                    return;
                    break;

                default:
                    printf("\nYOU TYPED SOMETHING ELSE...TRY AGAIN\n");
                    break;
                }
            } while (num < 1 || num > 8);

            fseek(fpte, -sizeof(customer), SEEK_CUR);
            fwrite(&customer, sizeof(customer), 1, fpte);
            fseek(fpte, -sizeof(customer), SEEK_CUR);
            fread(&customer, sizeof(customer), 1, fpte);
            choice = 5;
            break;
        }

        if (choice == 5)
        {
            system("cls");
            printf("\n\t\tEDITING COMPLETED...\n");
            printf("--------------------\n");
            printf("THE NEW RECORD IS:\n");
            printf("--------------------\n");
            printf("\nTIME: %s", customer.time);
            printf("\nNAME: %s", customer.name);
            printf("\n");
            printf("\nNOTE: %s", customer.note);
            fclose(fpte);

            printf("\n\n\tWOULD YOU LIKE TO EDIT ANOTHER RECORD.(Y/N)");
            scanf("%c", &choice);
            count++;
        }

        else
        {
            printf("\nTHE RECORD DOES NOT EXIST::\n");
            printf("\nWOULD YOU LIKE TO TRY AGAIN...(Y/N)");
            scanf("%c", &choice);
        }

    } while (choice == 'Y' || choice == 'y');

    fclose(fpte);

    if (count == 1)
        printf("\n%d FILE IS EDITED...\n", count);
    else if (count > 1)
        printf("\n%d FILES ARE EDITED..\n", count);
    else
        printf("\nNO FILES EDITED...\n");

    printf("\tPRESS ENTER TO EXIT EDITING MENU.");

    getch();
}

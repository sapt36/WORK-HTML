#include <stdio.h> 
#include <conio.h> 
#include <string.h> 

const char* maintitle[] = { "Show all records","Show one record","Add one record","Delete one record","Exit" };

// clientData structure definition 
struct clientData
{
    char name[7];
    char position[11];
    char departmentno[4];
    char city[7];
    char address[33];
    char telephone[17];
    double payofhour;
    double salary;
    double seniority;
};

void showoption(const char* optionname[], unsigned int);
int choice(int);
void onerecord(struct clientData*);
void showrecord(struct clientData);

int main(void)
{
    FILE* cfPtr; // accounts.dat file pointer 

    // fopen opens the file; exits if file cannot be opened 
    if ((cfPtr = fopen("employeee.txt", "rb")) == NULL)
    {
        puts("File could not be opened.");
    }
    else
    {
        struct clientData client[100];
        int mainchoice;
        unsigned int count = 0;

        // read all records from file 
        int result = fread(client, sizeof(struct clientData), 100, cfPtr);
        fclose(cfPtr); // fclose closes the file 

        printf("\nThere are %d records are read.\n\n", result);
        while (result > 0)
        {
            if (strcmp("", client[result - 1].name))
            {
                count++;
            }
            result--;
        }
        printf("\nThere are %d data records. \n\n", count);
        do
        {
            showoption(maintitle, 5);
            mainchoice = choice(5);
            switch (mainchoice)
            {
            case 1:
                printf("\nThere are %d records\n", count);
                if (count != 0)
                {
                    int temp = 0, press;
                    for (size_t i = 0; i <= 99; i++)
                    {
                        if (strcmp("", client[i].name))
                        {
                            showrecord(client[i]);
                            temp++;
                            if ((temp % 5) == 0)
                            {
                                printf("%s", "Press any button to continue\n");
                                press = _getche();
                                press = _getche();
                            }
                        }
                    }
                }
                break;
            case 2:
                printf("\nThere are %d records\n", count);
                if (count != 0)
                {
                    char nameofinput[7];
                    int found = 0;
                    printf("Please enter the name you want to show:");
                    scanf("%6s", nameofinput);
                    for (size_t i = 0; i <= 99; i++)
                    {
                        if ((strcmp(nameofinput, client[i].name)) == 0)
                        {
                            showrecord(client[i]);
                            found = 1;
                        }
                    }
                    if (found == 0)
                    {
                        printf("\n%s!\n\n", "Not found");
                    }
                }
                break;
            case 3:
                printf("\nThere are %d records\n", count);
                if (count < 100)
                {
                    int found = -1;
                    size_t i = 0;
                    do
                    {
                        if (!strcmp("", client[i].name))
                        {
                            found = i;
                        }
                        i++;
                    } while ((i < 100) && (found == -1));
                    if (found != -1)
                    {
                        onerecord(&client[found]);
                        count++;
                        if ((cfPtr = fopen("employeee.dat", "rb+")) == NULL)
                        {
                            puts("File could not be opened. ");
                        }
                        else
                        {
                            fseek(cfPtr, found * sizeof(struct clientData), SEEK_SET);
                            fwrite(&client[found], sizeof(struct clientData), 1, cfPtr);
                            fclose(cfPtr);
                        }
                    }
                }
                else
                {
                    printf("\n%s!\n\n", "There are already 100 people");
                }
                break;
            case 4:
                printf("\nThere are %d records\n", count);
                if (count != 0)
                {
                    char nameofinput[7];
                    int found = 0;
                    printf("Please enter the name you want to delete:");
                    scanf("%6s", nameofinput);
                    for (size_t i = 0; i <= 99; i++)
                    {
                        if ((strcmp(nameofinput, client[i].name)) == 0)
                        {
                            strcpy(client[i].name, "");
                            strcpy(client[i].position, "");
                            strcpy(client[i].departmentno, "");
                            strcpy(client[i].city, "");
                            strcpy(client[i].address, "");
                            strcpy(client[i].telephone, "");
                            client[i].payofhour = 0.0;
                            client[i].salary = 0.0;
                            client[i].seniority = 0.0;
                            found = 1;
                            count--;
                            if ((cfPtr = fopen("employeee.dat", "rb+")) == NULL)
                            {
                                puts("File could not be opened.");
                            }
                            else
                            {
                                fseek(cfPtr, i * sizeof(struct clientData), SEEK_SET);
                                fwrite(&client[i], sizeof(struct clientData), 1, cfPtr);
                                fclose(cfPtr);
                            }
                        }
                    }
                    if (found == 0)
                    {
                        printf("\n%s!\n\n", "Not found");
                    }
                }
                break;
            }
        } while (mainchoice != 5);
    }
}

void showoption(const char* optiontype[], unsigned int typecount)
{
    printf("\n");
    for (size_t i = 0; i <= typecount - 1; i++)
        printf("(%d) %s\n", i + 1, optiontype[i]);
}

int choice(int count)
{
    int choose;
    do
    {
        printf("\nPlease enter option 1-%1d:", count);
        scanf("%d", &choose);
    } while (choose < 1 || choose > count);
    return choose;
}

void onerecord(struct clientData* oneclient)
{
    printf("\n");
    printf("Please enter name:");
    scanf("%6s", oneclient->name);
    printf("Please enter position:");
    scanf("%10s", oneclient->position);
    printf("Please enter department number:");
    scanf("%3s", oneclient->departmentno);
    printf("Please enter city:");
    scanf("%6s", oneclient->city);
    printf("Please enter address:");
    scanf("%32s", oneclient->address);
    printf("Please enter telephone:");
    scanf("%16s", oneclient->telephone);
    printf("Please enter pay of hour:");
    scanf("%1f", &oneclient->payofhour);
    printf("Please enter salary:");
    scanf("%1f", &oneclient->salary);
    printf("Please enter seniority:");
    scanf("%1f", &oneclient->seniority);
}

void showrecord(struct clientData employee)
{
    printf("\n");
    printf("name :%s", employee.name);
    printf("position :%s", employee.position);
    printf("department number :%s", employee.departmentno);
    printf("city :%s\n", employee.city);
    printf("address :%s\n", employee.address);
    printf("telephone :%s", employee.telephone);
    printf("pay of hour : %1f", employee.payofhour);
    printf("salary : %1f", employee.salary);
    printf("seniority : %1f\n", employee.seniority);
}
#include "../include/Student.h"
#include "../include/Utils.h"

int main(int argc, char *argv[])
{
    ValidCode vstatus = ValidPaths(argc, argv);
    if (vstatus != VALID_SUCCESS)
    {
        valid_handle(vstatus);
        return vstatus;
    }

    Class class;
    StatusCode status = Init_Class(&class, 4);
    if (status != SUCCESS)
    {
        status_handle(status);
        return 1;
    }

    status = Read_File(argv[1], &class);
    if (status != SUCCESS)
    {
        status_handle(status);
        Destroy_Class(&class);
        return 1;
    }

    int option = 0;
    print_options();
    vstatus = ValidOptions(&option);
    if (vstatus != VALID_SUCCESS)
    {
        valid_handle(vstatus);
        Destroy_Class(&class);
        return vstatus;
    }

    switch (option)
    {
    case 0:
    {
        print_attribute();
        Search_by(&class, argv[2]);
        break;
    }
    case 1:
    {
        int key = 0;
        printf("Enter sort key (0=id, 1=surname, 2=name, 3=group): ");
        if (ValidOptions(&key) == VALID_SUCCESS)
        {
            status = Sort_Class(&class, key);
            if (status != SUCCESS)
            {
                printf("Error: sorting failed.\n");
            }
            else
            {
                printf("Sorting successful.\n");
                Print(class);
            }
        }
        else
        {
            printf("Invalid key input.\n");
        }
        break;
    }
    case 2:
    {
        status = Print_Above_Average(&class, argv[2]);
        if (status != SUCCESS)
        {
            status_handle(status);
        }
        else
        {
            printf("Above-average students written to trace file.\n");
        }
        break;
    }
    default:
    {
        printf("ERROR: Wrong number!\n");
        break;
    }
    }

    Destroy_Class(&class);
    return 0;
}
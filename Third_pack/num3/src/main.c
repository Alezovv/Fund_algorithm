#include "../include/Liver_List.h"
#include "../include/Utils.h"

main(int argc, char **argv)
{

    print_usage();
    if (argc != 2)
        return 1;
    
    const char *input_path = argv[1];
    StatusCode status = valid_path(input_path);
    if (status != SUCCESS)
    {
        status_handle(status);
        return 1;
    }

    select_options();
    int choice = 0;
    if (scanf("%d", &choice) != 1)
    {
        printf("ERROR!");
        return 1;
    }

    list *lst = create_list();
    scan_file(input_path, lst);

    switch (choice)
    {
    case 0:
    {
    }
    }

    return 0;
}

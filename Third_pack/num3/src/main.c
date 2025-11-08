#include "../include/Liver_List.h"
#include "../include/Utils.h"

main(int argc, char **argv)
{

    print_usage();
    if (argc != 2)
        return 1;

    const char *input_path = argv[1];
    StatusCode status = valid_path(input_path);
    CHECK;

    select_options();
    int choice = 0;
    if (scanf("%d", &choice) != 1)
    {
        status = SCAN_ERROR;
        CHECK;
    }

    list *lst = create_list();
    scan_file(input_path, lst);

    /* switch (choice)
    {
    case 0:
    {
        int attr = 0;
        if (scanf("%d", &attr) != 1)
        {
            status = SCAN_ERROR;
            CHECK;
        }

        status = search_by(lst, attr);
        CHECK;
    }
    } */
    status = write_to_file(input_path, lst);
    CHECK;
    return 0;
}

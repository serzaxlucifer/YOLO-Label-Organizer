#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <io.h>         // windows only.

// using Command line arguments.
// Program to Manage YOLOv5 Existing Label (Class values)

void configure(int* conditionChecks, int** initialClass, int** finalClass)
{
    printf("\nSETTINGS [Please configure]:    \n\nHow many class modifications do you want to make? -    ");
    scanf("%d", conditionChecks);

    *initialClass = (int*)malloc(sizeof(int)*(*conditionChecks));
    *finalClass = (int*)malloc(sizeof(int)*(*conditionChecks));

    for(int i = 0; i < *conditionChecks; i++)
    {
        printf("\n\n(%d) Please enter initial class value to replace:    ", i+1);
        scanf("%d", &(*initialClass)[i]);
        printf("(%d) Please enter class value to replace with:    ", i+1);
        scanf("%d", &(*finalClass)[i]);
    }

    printf("\n\nConfigured to do following modifications:\n\n");
    for(int i = 0; i < *conditionChecks; i++)
    {
        printf("%d  -->  %d\n", (*initialClass)[i], (*finalClass)[i]);
    }

    printf("\nBEGINNING...\n\n");

}

void cleanMemory(int* initialClass, int* finalClass)
{
    free(initialClass);
    free(finalClass);
}


int main (int argc, char *argv[]) 
{

    int conditionChecks;
    int* initialClass, *finalClass;

    // Configure how you want to modify/re-organize the class values.
    configure(&conditionChecks, &initialClass, &finalClass);

    DIR *directory;
    struct dirent* file;
    FILE *a;
    char ch;

    int files = 0;
    int filesModified = 0;
    int modify = 0;

    if (argc != 2 || argc > 2) 
    {
        printf("Error. Supply only ONE argument which is folder name to run this program on.\n", argv[0]);
        exit(1);
    }

    directory = opendir(argv[1]);
    if (directory == NULL) 
    {
        printf("Error. No such directory exists!\n");
        exit(2);
    }

    while ((file = readdir(directory)) != NULL) 
    {
        modify = 0;
        char filename[1000]; 
        sprintf(filename, "%s/%s", argv[1], file->d_name);

        FILE* fin = fopen(filename, "r+");
        int class;
        float dump1, dump2, dump3, dump4;
        int i = 0;

        if ( fin != NULL )
        {
            files++;
            char line[100][150];     // max 100 lines of 150 characters should suffice.
            i = 0;

            while(fscanf(fin, "%d %f %f %f %f", &class, &dump1, &dump2, &dump3, &dump4) != EOF)
            {

                // if(class == 0)
                // {
                //     modify = 1;
                //     class = 6;          // change 0 to 6 for cars.
                // }

                for(int j = 0; j < conditionChecks; j++)
                {
                    if(class == initialClass[j])
                    {
                        class = finalClass[j];
                        modify = 1;
                    }
                }

                sprintf(line[i], "%d %f %f %f %f", class, dump1, dump2, dump3, dump4);
                i++;
                if(i == 100)
                {
                    printf("\n\nFILE: %s , has more than 100 labels! This program CAN not process more than 100 labels in a file. Therefore, it is exiting. Please recompile the program from source code with higher label limits.\n\n");
                    exit(3);
                }
            }

            _chsize( fileno(fin), 0);
            fseek(fin, 0, SEEK_SET);        // reposition to write

            for(int j = 0; j < i; j++)
            {
                fprintf(fin, "%s\n", line[j]);
            }

            if(modify)
            {
                filesModified++;
            }

        }

        printf("\nSuccessfully done! @ %s", filename);

        fclose(fin);

    }

    closedir(directory);
    cleanMemory(initialClass, finalClass);
    printf("\n\nRESULTS:\n\nFiles Checked: %d\nFiles Corrected: %d\n\n", files, filesModified);

    return 0;
}

// alter the code whenever needed.
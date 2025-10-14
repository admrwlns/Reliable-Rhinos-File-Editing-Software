//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Maximum size constants for various buffers
#define MAX_FILENAME 100 //Maximum length of filename
#define MAX_CONTENT 1000 //Maximum size of file content buffer
#define MAX_LINE 1000 //Maximum length of a single line
#define MAX_LOG 1000 //Maximum number of entries in change log

//Global Variables for Change Log
char changeLog[MAX_LOG][256];//Array to create space for 1000 log enries where each entry can be up to 256 characters long
int logIndex = 0; //Current position in change log array

//Declaring functions
void createFile();
void copyFile();
void deleteFile();
void showFile();
void appendLine();
void deleteLine();
void insertLine();
void showLine();
void showChangeLog();
void showNumberOfLines();
void renameFile();
void editLine();
void addToLog(const char* operation, const char* filename, int lineCount);
int countLines(const char* filename);


//Main method
int main() {
    char input[10]; //Create space for 9 characters + null terminator
    int choice; //Store users input
   
   //main program loop
    while (1) {
        //Display menu options
        printf("\nFile Editor\n");
        printf("1. Create File\n2. Copy File\n3. Delete File\n4. Show File\n5. Rename File\n6. Append Line\n7. Delete Line\n8. Insert Line\n9. Show Line\n10. Edit line\n11. Show Change Log\n12. Show Number of Lines\n13. Exit\n");
        printf("Enter your choice: ");
       
       //Read user input and check for errors(Wrong inputs)
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input. Exiting.\n");
            return 1;
        }

        choice = atoi(input); //Convert input string to integer(from stdlib library)

        //Process user choice
        switch (choice) {
            case 1: createFile(); break;
            case 2: copyFile(); break;
            case 3: deleteFile(); break;
            case 4: showFile(); break;
            case 5: renameFile(); break;    // New option
            case 6: appendLine(); break;
            case 7: deleteLine(); break;
            case 8: insertLine(); break;
            case 9: showLine(); break;
            case 10: editLine(); break;     // New option
            case 11: showChangeLog(); break;
            case 12: showNumberOfLines(); break;
            case 13: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice. Please try again.\n");
        }
    }
}


//Function for creating file
void createFile() {
    char filename[MAX_FILENAME], content[MAX_CONTENT];
   
   //Get filename from user
    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; //Remove newline character
   
   //Open file in write mode
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error creating file.\n");
        return;
    }
   
   //Get content from user untl Ctrl+Z+enter is pressed
    printf("Enter file content (Press enter to go to next line and press Ctrl+Z + Enter to finish):\n");
    while (fgets(content, sizeof(content), stdin) != NULL) {
        fputs(content, file);
    }
   
    fclose(file);
    printf("File created successfully.\n");
    addToLog("Create", filename, countLines(filename)); //Count the change number of lines and store in changelog array
}


//Function for copying file
void copyFile() {
    char sourceFile[MAX_FILENAME], destFile[MAX_FILENAME], buffer[MAX_CONTENT];
   
   //Get source and destination filenames
    printf("Enter source filename: ");
    fgets(sourceFile, sizeof(sourceFile), stdin);
    sourceFile[strcspn(sourceFile, "\n")] = 0;
   
    printf("Enter destination filename(New file name): ");
    fgets(destFile, sizeof(destFile), stdin);
    destFile[strcspn(destFile, "\n")] = 0;
   
   //Open source file for reading
    FILE *source = fopen(sourceFile, "r");
    if (source == NULL) {
        printf("Error opening source file.\n");
        return;
    }
   
   //Open destination file for writing
    FILE *dest = fopen(destFile, "w");
    if (dest == NULL) {
        printf("Error creating destination file.\n");
        fclose(source);
        return;
    }
   
   //Copy content line by line
    while (fgets(buffer, sizeof(buffer), source) != NULL) {
        fputs(buffer, dest);
    }
   
    fclose(source);
    fclose(dest);
    printf("File copied successfully.\n");
    addToLog("Copy", destFile, countLines(destFile)); //Save the line changes to changlog array
}


//Function for deleting file
void deleteFile() {
    char filename[MAX_FILENAME];
   
   //Get filename to delete
    printf("Enter filename to delete: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;

    //Deleting the file
    if (remove(filename) == 0) {
        printf("File deleted successfully.\n");
        addToLog("Delete", filename, 0); //Save the line changes to changelog array
    } else {
        printf("Error deleting file.\n");
    }
}


//Functions for showing the content of the file
void showFile() {
    char filename[MAX_FILENAME], buffer[MAX_CONTENT];
   
   //Get filename to display
    printf("Enter filename to display: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;
   
   //Open file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
   
   //Display the file content
    printf("\nFile contents:\n");
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
   
    fclose(file);
}


//Functions for adding new line and content to the file
void appendLine() {
    char filename[MAX_FILENAME], line[MAX_LINE];
   
   //Get file name
    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;
   
   //Open file in append mode
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
   
   //Get and append new line
    printf("Enter Content to append: ");
    fgets(line, sizeof(line), stdin);
   
    fputs(line, file);
    fclose(file);
    printf("Line appended successfully.\n");
    addToLog("Append", filename, countLines(filename));
}


//Functions for deleting the line
void deleteLine() {
    char filename[MAX_FILENAME], buffer[MAX_LINE];
    int lineNum, currentLine = 0;
   
    // Get filename and line number to delete
    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;
   
    printf("Enter line number to delete: ");
    scanf("%d", &lineNum);
    getchar(); // Consume newline character
   
    // Open original file and temporary file
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (file == NULL || temp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    // Copy all lines except the one to be deleted
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        currentLine++;
        if (currentLine != lineNum) {
            fputs(buffer, temp);
        }
    }
   
    fclose(file);
    fclose(temp);
   
    // Replace original file with modified version
    remove(filename);
    rename("temp.txt", filename);
   
    printf("Line deleted successfully.\n");
    addToLog("Delete Line", filename, countLines(filename));
}


//Functions for inserting line to the file
void insertLine() {
    char filename[MAX_FILENAME], buffer[MAX_LINE], newLine[MAX_LINE];
    int lineNum, currentLine = 0;
   
    // Get filename and line number for insertion
    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;
   
    printf("Enter line number to insert at: ");
    scanf("%d", &lineNum);
    getchar(); // Consume newline character
   
    printf("Enter Content to insert: ");
    fgets(newLine, sizeof(newLine), stdin);
   
   // Open original file and temporary file
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (file == NULL || temp == NULL) {
        printf("Error opening file.\n");
        return;
    }
   // Copy lines and insert new line at specified position
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        currentLine++;
        if (currentLine == lineNum) {
            fputs(newLine, temp); //insert new line
        }
        fputs(buffer, temp); //copy existing line
    }
   
   // If the insertion point is after last line, append the new line
    if (lineNum > currentLine) {
        fputs(newLine, temp);
    }
   
    fclose(file);
    fclose(temp);
   
    // Replace original file with modified version
    remove(filename);
    rename("temp.txt", filename);
   
    printf("Line inserted successfully.\n");
    addToLog("Insert Line", filename, countLines(filename)); //Save the line changes to changelog array
}


//Functions for showing the specific line
void showLine() {
    char filename[MAX_FILENAME], buffer[MAX_LINE];
    int lineNum, currentLine = 0;
   
    // Get filename and line number to display
    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;
   
    printf("Enter line number to display: ");
    scanf("%d", &lineNum);
    getchar(); // Consume newline character
   
    // Open file and find specified line
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
   
    // Read file until specified line is found
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        currentLine++;
        if (currentLine == lineNum) {
            printf("Line %d: %s", lineNum, buffer);
            fclose(file);
            return;
        }
    }
   
    fclose(file);
    printf("Line %d not found in the file.\n", lineNum);
}


//Functions for showing the changes in the file and updating the log array
void showChangeLog() {
    // Display all logged operations
    printf("\nChange Log:\n");
    for (int i = 0; i < logIndex; i++) {
        printf("%s\n", changeLog[i]);
    }
}


//Function for showing the number of lines in a file
void showNumberOfLines() {
    char filename[MAX_FILENAME];
   
    //Get filename
    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;
   
    // Count and display number of lines
    int lines = countLines(filename);
    if (lines >= 0) {
        printf("Number of lines in %s: %d\n", filename, lines);
    } else {
        printf("Error: Unable to open file %s\n", filename);
    }
}


// Function for renaming a file
void renameFile() {
    char oldName[MAX_FILENAME], newName[MAX_FILENAME];
   
    // Get the current filename
    printf("Enter the current filename: ");
    fgets(oldName, sizeof(oldName), stdin);
    oldName[strcspn(oldName, "\n")] = 0;
   
    // Get the new filename
    printf("Enter the new file name: ");
    fgets(newName, sizeof(newName), stdin);
    newName[strcspn(newName, "\n")] = 0;
   
    // Attempt to rename the file
    if (rename(oldName, newName) == 0) {
        printf("File renamed successfully.\n");
    } else {
        perror("Error renaming file");
    }
}


// Function for editing a specific line in the file
void editLine() {
    char filename[MAX_FILENAME], buffer[MAX_LINE], newContent[MAX_LINE];
    int lineNum, currentLine = 0;


    // Get filename and line number to edit
    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;


    printf("Enter line number to edit: ");
    scanf("%d", &lineNum);
    getchar(); // Consume newline character


    // Get new content for the line
    printf("Enter new content for the line: ");
    fgets(newContent, sizeof(newContent), stdin);
    newContent[strcspn(newContent, "\n")] = 0;


    // Open original file and temporary file
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (file == NULL || temp == NULL) {
        printf("Error opening file.\n");
        return;
    }


    // Copying and replacing the specified line with new content
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        currentLine++;
        if (currentLine == lineNum) {
            fputs(newContent, temp);
            fputs("\n", temp); // Add newline after the updated line
        } else {
            fputs(buffer, temp);
        }
    }


    fclose(file);
    fclose(temp);


    // Replace original file with modified version
    remove(filename);
    rename("temp.txt", filename);


    printf("Line edited successfully.\n");
    addToLog("Edit Line", filename, countLines(filename)); // Save the line changes to changelog array
}


//Funtion for getting the log information
void addToLog(const char* operation, const char* filename, int lineCount) {
    // Get current timestamp
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", t);
   
    // Format and store log entry
    snprintf(changeLog[logIndex], sizeof(changeLog[logIndex]),
             "[%s] %s: %s (Lines: %d)", timestamp, operation, filename, lineCount);
   
    // Increment log index (circular buffer) (Prevent program from running out of space)
    logIndex = (logIndex + 1) % MAX_LOG;
}


//Functions to count the number of lines in a file
int countLines(const char* filename) {
    //Open file in read mode
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -1; //Return -1 if the file cannot be opened
    }
   
    int lines = 0; //Line counter
    int ch; //Current Character
    int prevChar = EOF;//Track previous character to handle files without trailing newline


    //Read file character by character
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++; //Increment counter when newline found
        }
        prevChar = ch;
    }
   
    //Handle case where
    if (prevChar != '\n' && prevChar != EOF) {
        lines++;
    }
   
    fclose(file);
    return lines;
}












#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void compressFile(const char* inputFile, const char* outputFile);
void decompressFile(const char* inputFile, const char* outputFile);

int main() {
    int choice;
    char inputFile[100], outputFile[100];

    printf("Data Compression Tool\n");
    printf("1. Compress a file\n");
    printf("2. Decompress a file\n");
    printf("Enter your choice (1/2): ");
    scanf("%d", &choice);

    printf("Enter the input file name: ");
    scanf("%s", inputFile);
    printf("Enter the output file name: ");
    scanf("%s", outputFile);

    if (choice == 1) {
        compressFile(inputFile, outputFile);
        printf("File compressed successfully to '%s'.\n", outputFile);
    } else if (choice == 2) {
        decompressFile(inputFile, outputFile);
        printf("File decompressed successfully to '%s'.\n", outputFile);
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}

// Function to compress a file using RLE
void compressFile(const char* inputFile, const char* outputFile) {
    FILE *input, *output;
    input = fopen(inputFile, "r");
    output = fopen(outputFile, "w");

    if (!input || !output) {
        printf("Error: Unable to open file.\n");
        exit(1);
    }

    char currentChar, previousChar;
    int count = 1;

    previousChar = fgetc(input);
    while ((currentChar = fgetc(input)) != EOF) {
        if (currentChar == previousChar) {
            count++;
        } else {
            fprintf(output, "%c%d", previousChar, count);
            previousChar = currentChar;
            count = 1;
        }
    }
    if (count > 0) {
        fprintf(output, "%c%d", previousChar, count);
    }

    fclose(input);
    fclose(output);
}

// Function to decompress a file using RLE
void decompressFile(const char* inputFile, const char* outputFile) {
    FILE *input, *output;
    input = fopen(inputFile, "r");
    output = fopen(outputFile, "w");

    if (!input || !output) {
        printf("Error: Unable to open file.\n");
        exit(1);
    }

    char ch;
    int count;

    while (fscanf(input, "%c%d", &ch, &count) == 2) {
        for (int i = 0; i < count; i++) {
            fputc(ch, output);
        }
    }

    fclose(input);
    fclose(output);
}

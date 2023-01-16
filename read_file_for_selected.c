#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// To Upper 
#include <ctype.h>

void upper(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        str[i] = toupper(str[i]);
    }
}


void replaceSpace(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (isspace(str[i])) {
            str[i] = '_';
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 5) { // Kullanıcı en az 4 argüman girmiş olmalı
        printf("Kullanim: %s -d dosya_adi -n line1 line2 line3 line4\n", argv[0]);
        return 1;
    }

    if (argv[1][0] != '-' || argv[1][1] != 'd' || argv[3][0] != '-' || argv[3][1] != 'n') {
        printf("Kullanim: %s -d dosya_adi -n line1 line2 line3 line4\n", argv[0]);
        return 1;
    }
    char *filename=argv[2];
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file: %s\n",filename);
        return 1;
    }

    char **lines = NULL; // Array to store the lines
    int n = 0; // Number of lines in the file

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1) {
        // Reallocate memory for the lines array
        lines = (char**) realloc(lines, sizeof(char*) * (n + 1));
        lines[n] = (char*) malloc(sizeof(char) * (read + 1));

        // Copy the line to the array
        strncpy(lines[n], line, read);
        lines[n][read] = '\0'; // Null-terminate the string

        n++;
    }

    // Close the file
    fclose(file);

        int line_num;
    for (int i = 4; i < argc; i++) {
        line_num = atoi(argv[i]);

        if (line_num <= 0 || line_num>n) {
            printf("Satir numarasi pozitif bir sayi ve dosyada mevcut olan satirlardan birisi olmalidir : %s\n", argv[i]);
            continue;
        }
         upper(lines[line_num-1]);
        printf("Line %d: %s",line_num, lines[line_num-1]);
        replaceSpace(lines[line_num-1]);
        printf("Line %d: %s\n",line_num, lines[line_num-1]);
    }
    // Free the memory allocated for the array
    for (int i = 0; i < n; i++) {
        free(lines[i]);
    }
    free(lines);

    return 0;
}

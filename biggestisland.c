#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 1000
#define MAX_COLS 1000

int rows = 0;
int cols = 0;
char grid[MAX_ROWS][MAX_COLS];

/* DFS to calculate island area */
int dfs(int x, int y) {
    if (x < 0 || x >= rows || y < 0 || y >= cols)
        return 0;

    if (grid[x][y] != 'X')
        return 0;

    grid[x][y] = '.';  // mark visited

    int area = 1;

    area += dfs(x + 1, y);
    area += dfs(x - 1, y);
    area += dfs(x, y + 1);
    area += dfs(x, y - 1);

    return area;
}

/* Find maximum island area */
int maxAreaOfIsland() {
    int maxArea = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 'X') {
                int area = dfs(i, j);
                if (area > maxArea)
                    maxArea = area;
            }
        }
    }

    return maxArea;
}

/* Parse input file */
int loadFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 0;
    }

    char line[MAX_COLS + 2]; // +2 for newline and null
    int expectedCols = -1;

    while (fgets(line, sizeof(line), file)) {
        int len = strlen(line);

        // Remove newline if present
        if (line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }

        if (len == 0)
            continue; // skip empty lines

        if (len > MAX_COLS) {
            printf("Error: Line exceeds maximum column size\n");
            fclose(file);
            return 0;
        }

        if (expectedCols == -1)
            expectedCols = len;
        else if (len != expectedCols) {
            printf("Error: Unequal row lengths detected\n");
            fclose(file);
            return 0;
        }

        if (rows >= MAX_ROWS) {
            printf("Error: Exceeded maximum row size\n");
            fclose(file);
            return 0;
        }

        for (int i = 0; i < len; i++) {
            if (line[i] != 'X' && line[i] != '.') {
                printf("Error: Invalid character '%c'\n", line[i]);
                fclose(file);
                return 0;
            }
            grid[rows][i] = line[i];
        }

        rows++;
    }

    cols = expectedCols;
    fclose(file);
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    if (!loadFile(argv[1])) {
        return 1;
    }

    int result = maxAreaOfIsland();
    printf("Max Island Area: %d\n", result);

    return 0;
}

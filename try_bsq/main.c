#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_map
{
    int cols;
    int rows;
    char empty;
    char obstacle;
    char full;
    char **grid;
} t_map;

void printmap(t_map *map)
{
    for (int r = 0; r < map->rows; r++)
    {    
        for (int c = 0; c < map->cols; c++)
            printf("%c", map->grid[r][c]);
        printf("%c", '\n');
    }
}

void solve(t_map *map)
{
	int	**dp = calloc(map->rows, sizeof(int *));
	for (int i = 0; i < map->rows; i++)
		dp[i] = calloc(map->cols, sizeof(int));


    int best = 0, best_r = 0, best_c = 0;
    for (int r = 0; r < map->rows; r++)
    {    
        for (int c = 0; c < map->cols; c++)
        {
            if (map->grid[r][c] == map->obstacle)
            {
                dp[r][c] = 0;

            }
            else if (r == 0 || c == 0)
            {
                dp[r][c] = 1;
            }
            else
            {
                int min;
                int top = dp[r - 1][c];
                int left = dp[r][c - 1];
                int diag = dp[r - 1][c - 1];
                min = top < left ? top : left;
                min = diag < min ? diag : min;
                if (min > best)
                {
                    best = min;
                    best_c = c;
                    best_r = r;
                }
                dp[r][c] = min + 1;
            }
            printf("%d", dp[r][c]);
        }
        printf("%c", '\n');

    }
    printf("best %d r c %d %d\n", best, best_r, best_c);
    for (int r = best_r; r >= best_r - best; r--)
    {    
        for (int c = best_c; c >= best_c - best; c--)
        {
            map->grid[r][c] = 'X';
        }
    }

// printf("%c", '\n');
}

int main(int argc, char **argv)
{
    FILE *f = fopen(argv[1], "r");
    char *line = NULL;
    ssize_t len;
    size_t n;
    t_map map;
    int row = 0;
    int firstline = 1;
    
    while ((len = getline(&line, &n, f)) != -1)
    {
        // int i;
        // for (i = 0; line[i] != '\0'; i++) {}
        // printf("len %d, line %s\n", i, line);
        if (firstline)
        {
            int rows = atoi(line);
            map.rows = rows;
            int index = 0;
            while (line[index] >= '0' && line[index] <= '9')
            {
                index++;
            }
            map.empty = line[index++];
            map.obstacle = line[index++];
            map.full = line[index++];
            firstline = 0;
            continue;
        }
        if (row == 0)
        {
            printf("cols %zd rows %d len %zd\n", n, map.rows, len);
            map.cols = len;
            map.grid = calloc(map.rows, sizeof(char *));
            for (int i = 0; i < map.rows; i++)
            {
                map.grid[i] = calloc(map.cols, sizeof(char) + 1); // one extra for '\0'
            }
        }
        for (int i = 0; i < len - 1; i++)
        {
            
            if (i >= map.cols)
            {
                printf("aaa");
                exit(0);
            }
            else if (row >= map.rows)
            {
                printf("aaa");
                exit(0);
            }
            
            if (line[i] == map.empty || line[i] == map.obstacle)
                map.grid[row][i] = line[i];
            else
            {
                printf("i %d row %d -> cols %d rows %d\n", i, row, map.cols, map.rows);
                printf("yes %d", map.grid[row][i]);
                fprintf(stdout, "Error");
            }
        }
        row++;
    }
    printmap(&map);
    solve(&map);
    printmap(&map);

}


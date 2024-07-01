#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define ROW 5
#define COL 5

typedef struct {
    int parent_i, parent_j;
    double f, g, h;
} Cell;

typedef struct {
    int x, y;
} Point;

bool isValid(int row, int col) {
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

bool isUnBlocked(int grid[ROW][COL], int row, int col) {
    return grid[row][col] == 1;
}

bool isDestination(int row, int col, Point dest) {
    return row == dest.x && col == dest.y;
}

double calculateHValue(int row, int col, Point dest) {
    return (double)sqrt((row - dest.x) * (row - dest.x) + (col - dest.y) * (col - dest.y));
}

void tracePath(Cell cellDetails[ROW][COL], Point dest) {
    printf("The path is: ");
    int row = dest.x;
    int col = dest.y;

    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
        printf("(%d, %d) <- ", row, col);
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }
    printf("(%d, %d)\n", row, col);
}

void aStarSearch(int grid[ROW][COL], Point src, Point dest) {
    if (!isValid(src.x, src.y) || !isValid(dest.x, dest.y)) {
        printf("Source or destination is invalid\n");
        return;
    }

    if (!isUnBlocked(grid, src.x, src.y) || !isUnBlocked(grid, dest.x, dest.y)) {
        printf("Source or destination is blocked\n");
        return;
    }

    if (isDestination(src.x, src.y, dest)) {
        printf("We are already at the destination\n");
        return;
    }

    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));

    Cell cellDetails[ROW][COL];

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            cellDetails[i][j].f = INFINITY;
            cellDetails[i][j].g = INFINITY;
            cellDetails[i][j].h = INFINITY;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    int i = src.x, j = src.y;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    typedef struct {
        double f;
        Point point;
    } Node;

    Node openList[ROW * COL];
    int openListSize = 0;
    openList[openListSize++] = (Node){ .f = 0.0, .point = src };

    bool foundDest = false;

    int rowNum[] = {-1, 0, 0, 1};
    int colNum[] = {0, -1, 1, 0};

    while (openListSize > 0) {
        Node temp = openList[0];
        openList[0] = openList[--openListSize];

        for (int k = 1; k < openListSize; k++) {
            if (openList[k].f < openList[0].f) {
                Node swap = openList[0];
                openList[0] = openList[k];
                openList[k] = swap;
            }
        }

        i = temp.point.x;
        j = temp.point.y;
        closedList[i][j] = true;

        for (int add = 0; add < 4; add++) {
            int newRow = i + rowNum[add];
            int newCol = j + colNum[add];

            if (isValid(newRow, newCol)) {
                if (isDestination(newRow, newCol, dest)) {
                    cellDetails[newRow][newCol].parent_i = i;
                    cellDetails[newRow][newCol].parent_j = j;
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                } else if (!closedList[newRow][newCol] && isUnBlocked(grid, newRow, newCol)) {
                    double gNew = cellDetails[i][j].g + 1.0;
                    double hNew = calculateHValue(newRow, newCol, dest);
                    double fNew = gNew + hNew;

                    if (cellDetails[newRow][newCol].f == INFINITY || cellDetails[newRow][newCol].f > fNew) {
                        openList[openListSize++] = (Node){ .f = fNew, .point = (Point){ newRow, newCol } };
                        cellDetails[newRow][newCol].f = fNew;
                        cellDetails[newRow][newCol].g = gNew;
                        cellDetails[newRow][newCol].h = hNew;
                        cellDetails[newRow][newCol].parent_i = i;
                        cellDetails[newRow][newCol].parent_j = j;
                    }
                }
            }
        }
    }

    if (!foundDest) {
        printf("Failed to find the destination cell\n");
    }
}

int main() {
    int grid[ROW][COL] =
    {
        { 1, 1, 1, 1, 1 },
        { 1, 1, 0, 1, 1 },
        { 1, 1, 1, 0, 1 },
        { 0, 0, 1, 1, 1 },
        { 1, 1, 1, 1, 1 }
    };

    Point src = {0, 0};
    Point dest = {4, 4};

    aStarSearch(grid, src, dest);

    return 0;
}

// Compile with: gcc -o A_star A_star.c -lm
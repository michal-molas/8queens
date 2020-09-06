#include <stdio.h>
#include <stdbool.h>

bool check_position(int* pos, const int* n, int x, int y){
    //check_columns
    for(int i = 0; i < *n; i++){
        if(*(pos+i) == x){
            return false;
        }
    }

    //check_diagonals (right_down)
    int diag_rd = x-y; //const for a rd diagonal
    int i = 0;
    for(int j = diag_rd; j < *n; j++){
        if(i != y && j >= 0 && i < *n){
            if(*(pos+i) == j){
                return false;
            }
        }
        i++;
    }

    //check_diagonals (left_down)
    int diag_ld = x+y; //const for a ld diagonal
    i = 0;
    for(int j = diag_ld; j >= 0; j--){
        if(i != y && j < *n && i < *n){
            if(*(pos+i) == j){
                return false;
            }
        }
        i++;
    }

    return true;
}

void try(int* pos, const int* n, int* curr_line, int* val, FILE* fp){
    //check if trying is finished
    if(*curr_line < *n){
        //check if all values already checked
        if(*val < *n){
            //check diagonals and columns, if no collision set pos[cl] = v, go to next line
            if(check_position(pos, n, *val, *curr_line)){
                *(pos+*curr_line) = *val;
                *curr_line += 1;
                *val = 0;
                try(pos, n, curr_line, val, fp);
            //else try next value
            } else {
                *val += 1;
                try(pos, n, curr_line, val, fp);
            }
        //go back a line and try next value there
        } else {
            *curr_line -= 1;
            *val = *(pos + *curr_line) + 1;
            if(*curr_line == 0 && *val == *n){
                printf("FINISHED");
                return;
            }
            *(pos + *curr_line) = -1;
            try(pos, n, curr_line, val, fp);
        }
    //found a solution, print to file and try next one
    } else {
        for(int i = 0; i < *n; i++){
            fprintf(fp, "%d, ", *(pos+i));
        }
        fprintf(fp, "\n");
        *curr_line -= 1;
        *val = *(pos + *curr_line) + 1;
        *(pos + *curr_line) = -1;
        return;
    }
}

int main() {
    FILE* fp;
    fp = fopen("wynik.txt", "w");

    const int n = 11;
    int pos[n];

    for(int i = 0; i < n; i++){
        pos[i] = -1;
    }
    int curr_line = 0;
    int val = 0;
    while (!(curr_line == 0 && val == n)){
        try(pos, &n, &curr_line, &val, fp);
    }

    fclose(fp);

    return 0;
}

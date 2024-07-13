#include "s21_3Dviewer.h"

void s21_mat_res(matrix_t * A, int colums, int rows, int type) {
    A->columns = colums;
    A->rows = rows;
    A->matrix_type = type;
}

double ** s21_memory_allocation(int rows, int columns) {
    int error = 0;
    double ** matrix = calloc(rows, sizeof(double *));
    if (matrix != NULL) {
        for  (int i = 0; i < rows; i++) {
            matrix[i] = calloc(columns, sizeof(double));
            if (matrix[i] == NULL) {
                error = 1;
                break;
            }
        }
    } else {
        error = 1;
    }
    if (error == 1) {
        matrix = NULL;
    }
    return matrix;
}

int s21_matrix_type(matrix_t A) {
    int res = CORRECT_MATRIX;
    int diagonal = -1;
    int pereferia = 0;
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.columns; j++) {
            if (i != j && A.matrix[i][j] != 0) {
                pereferia = -1;
                break;
            }
        }
    }
    if (A.columns == A.rows && pereferia == 0) {
        diagonal = A.matrix[0][0];
        if (diagonal == 0 || diagonal == 1) {
            for (int i = 0; i < A.columns; i++) {
                if (A.matrix[i][i] != diagonal) {
                    diagonal = -1;
                    break;
                }
            }
        }
    }
    if (diagonal == 0) {
        res = ZERO_MATRIX;
    } else if (diagonal == 1) {
        res = IDENTITY_MATRIX;
    }
    return res;
}

matrix_t s21_create_matrix(int rows, int columns) {
    matrix_t zero;
    if (rows > 0 && columns > 0 && (zero.matrix = s21_memory_allocation(rows, columns)) != NULL) {
        s21_mat_res(&zero, columns, rows, ZERO_MATRIX);
    } else {
        zero.matrix = NULL;
        s21_mat_res(&zero, 0, 0, INCORRECT_MATRIX);
    }
    return zero;
}

int s21_check(matrix_t * A) {
    int res = 0;
    if (A != NULL && A->columns > 0 && A->rows > 0 && A->matrix_type != INCORRECT_MATRIX) {
        res = 1;
    }
    return res;
}

int isinf_isnan_check(double x) {
    int res = 1;
    if (isnan(x) || isinf(x)) {
        res = 0;
    }
    return res;
}

void s21_remove_matrix(matrix_t *A) {
    if (s21_check(A) == 1) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                A->matrix[i][j] = 0;
            }
        }
        for (int i = 0; i < A->rows; i++) {
            free(A->matrix[i]);
        }
        free(A->matrix);
        s21_mat_res(A, 0, 0, INCORRECT_MATRIX);
    }
}

matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B) {
    int error = 0;
    matrix_t res;
    if (s21_check(A) == 1 && s21_check(B) == 1 && A->columns == B->rows) {
        res = s21_create_matrix(A->rows, B->columns);
        if (res.matrix_type != INCORRECT_MATRIX) {
            for (int i = 0; i < res.rows; i++) {
                for (int j = 0; j < res.columns; j++) {
                    for (int k = 0; k < A->columns; k++) {
                        if (isinf_isnan_check(A->matrix[i][k]) == 1
                        && isinf_isnan_check(B->matrix[k][j]) == 1) {
                            res.matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
                        } else {
                            error = 1;
                            break;
                        }
                    }
                }
            }
            s21_mat_res(&res, B->columns, A->rows, s21_matrix_type(res));
        } else {
            error = 1;
        }
    } else {
        error = 1;
    }
    if (error == 1) {
        s21_mat_res(&res, 0, 0, INCORRECT_MATRIX);
    }
    return res;
}

void BubbleSort(unsigned int * num, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = (size - 1); j > i; j--) {
            if (num[j - 1] > num[j]) {
                int temp = num[j - 1];
                num[j - 1] = num[j];
                num[j] = temp;
            }
        }
    }
}

vertex_t Parsing(FILE *file, int * error) {
    vertex_t res_array;
    unsigned int * temp_array = NULL;
    int temp_col = 0;
    res_array.col = 0;
    res_array.col_connect = 0;
    res_array.connect_array = NULL;
    res_array.coord_array = NULL;
    if (file != NULL) {
        int digit_ind = 0;
        int minus = 0;
        int idx = 1;
        int idx_2 = 1;
        double res = 0;
        unsigned int res_2 = 0;
        int st = -1;
        char c;
        int v = 0, f = 0, dot = 0, slash = 0;
        do {
            c = fgetc(file);
            //printf("%c", c);
            if (c == 'v' && f == 0) {
                v = 1;
            } else if (c == 'f' && v == 0) {
                f = 1;
            } else if (c == '.' && dot == 0) {
                dot = 1;
            } else if (c == '-' && slash == 0) {
                minus = 1;
            } else if (c >= '0' && c <= '9') {
                if (slash == 0) {
                    digit_ind = 1;
                    if (dot == 0) {
                        res *= 10;
                        res += (c - '0');
                        res_2 *= 10;
                        res_2 += (c - '0');
                    } else {
                        res += (c - '0') * pow(10, st--);
                    }
                }
            } else if (c == '/') {
                slash += 1;
            } else if (c == ' ' || c == '\n' || c == EOF) {
                if (digit_ind == 1) {
                    if (minus == 1) {
                        res *= -1;
                        minus = 0;
                    }
                    if (v == 1) {
                        res_array.coord_array = realloc(res_array.coord_array, sizeof(double) * idx++);
                        res_array.coord_array[idx - 2] = res;
                        res_array.col += 1;
                    } else {
                        temp_array = realloc(temp_array, sizeof(unsigned int) * idx_2++);
                        temp_array[idx_2 - 2] = res_2 - 1;
                        printf("res2 = %u\n", res_2 - 1);
                        temp_col += 1;
                    }
                    res = 0;
                    res_2 = 0;
                    st = -1;
                    dot = 0;
                    digit_ind = 0;
                    slash = 0;
                }
                if (c == '\n' || c == EOF) {
                    if ((idx < 4 && v == 1) || (idx_2 < 3 && f == 1)) {
                        *error = 1;
                        printf("1 Error!\n");
                        break;
                    }
                    BubbleSort(temp_array, temp_col);
                    int temp_c = res_array.col_connect + (temp_col * 2);
                    res_array.connect_array = realloc(res_array.connect_array, sizeof(unsigned int) * (temp_c));
                    printf("temp_col = %d\n", temp_col);
                    printf("m = %d\n", res_array.col_connect);
                    printf("temp_c = %d\n", temp_c);
                    for (int m = res_array.col_connect, r = 0; m < temp_c; m++) {
                        if (m + 2 == temp_c) {
                            res_array.connect_array[m++] = temp_array[0];
                            res_array.connect_array[m] = temp_array[r];
                            printf("1) res_2 = %u\n", temp_array[0]);
                            printf("2) res_2 = %u r = %d\n", temp_array[r], r);
                        } else {
                            res_array.connect_array[m] = temp_array[r];
                            printf("3) res_2 = %u r = %d\n", temp_array[r], r);
                        }
                        if (m % 2 == 0) {
                            r++;
                        }
                    }
                    res_array.col_connect = temp_c;
                    free(temp_array);
                    temp_array = NULL;
                    temp_col = 0;
                    digit_ind = 0;
                    idx_2 = 1;
                    v = 0;
                    f = 0;
                }
            }
        } while (c != EOF && slash <= 2);
        if (slash > 2) {
            *error = 1;
            printf("3 Error!\n");
        }
    } else {
        *error = 1;
        printf("file not open\n");
    }
    return res_array;
}

vertex_t TurnAroundShift(vertex_t data, double corner, int type) {
    if (type >= 0 && type <= 2) {
        corner = (corner * M_PI)/180;
    } else if (type == 6) {
        corner = pow(corner, 0.33);
    }
    int i_idx, j_idx;
    if (type == 0) {//z
        i_idx = 0;
        j_idx = 1;
    } else if (type == 1) {//x
        i_idx = 1;
        j_idx = 2;
    } else if (type == 2) {//y
        i_idx = 2;
        j_idx = 0;
    }
    for (int m = 0, m_e = 0; m < data.col;) {
        matrix_t matrix_A = s21_create_matrix(4, 4), matrix_B = s21_create_matrix(4, 1);
        for (int i = 0; i < 4; i++) {
            if (i == 3) {
                matrix_B.matrix[i][0] = 1;
            } else {
                matrix_B.matrix[i][0] = data.coord_array[m++];
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == j) {
                    if (type == 6) {
                        if (j == 3) {
                            matrix_A.matrix[i][j] = 1;
                        } else {
                            matrix_A.matrix[i][j] = corner;
                        }
                    } else {
                        matrix_A.matrix[i][j] = 1;
                    }
                } else {
                    matrix_A.matrix[i][j] = 0;
                }
            }
        }
        printf("type = %d\n", type);
        if (type >= 0 && type <= 2) {
            matrix_A.matrix[i_idx][i_idx] = cos(corner);
            matrix_A.matrix[j_idx][j_idx] = cos(corner);
            matrix_A.matrix[i_idx][j_idx] = sin(corner) * -1;
            matrix_A.matrix[j_idx][i_idx] = sin(corner);
        } else if (type == 3) {//x
            matrix_A.matrix[0][3] = corner;
        } else if (type == 4) {//y
            matrix_A.matrix[1][3] = corner;
        } else if (type == 5) {//z
            printf("corner = %f\n", corner);
            matrix_A.matrix[2][3] = corner;
        }
        for (int i = 0; i < matrix_A.rows; i++) {
            for (int j = 0; j < matrix_A.columns; j++) {
                printf("%f ", matrix_A.matrix[i][j]);
            }
            printf("\n");
        }
        matrix_t res = s21_mult_matrix(&matrix_A, &matrix_B);
        for (int i = 0; i < res.rows - 1; i++) {
            for (int j = 0; j < res.columns; j++) {
                data.coord_array[m_e++] = res.matrix[i][j];
            }
        }
    }
    return data;
}

vertex_t TurnAround(vertex_t data, double corner, char c) {// eto gotovie
    if (c == 'z') {
        data = TurnAroundShift(data, corner, 0);
    } else if (c == 'x') {
        data = TurnAroundShift(data, corner, 1);
    } else {
        data = TurnAroundShift(data, corner, 2);
    }
    return data;
}

vertex_t Shift(vertex_t data, double corner, char c) {// eto toje
    if (c == 'z') {
        data = TurnAroundShift(data, corner, 5);
    } else if (c == 'x') {
        data = TurnAroundShift(data, corner, 3);
    } else {
        data = TurnAroundShift(data, corner, 4);
    }
    return data;
}

vertex_t Scale(vertex_t data, double corner) {// eto toje
    data = TurnAroundShift(data, corner, 6);
    return data;
}


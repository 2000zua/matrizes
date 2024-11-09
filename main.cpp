#include <iostream>
#include <random>
#include <stdexcept> 

using namespace std;

const int SIZE_L = 15;
const int SIZE_C = 15;

void printMatriz(const int matrix[SIZE_L][SIZE_C]){
    cout << "Matrix = [ \n";
    for (int i = 0; i < SIZE_L; i++){
        cout <<"\t[ ";
        for (int j = 0; j < SIZE_C; j++){
            //cout << matrix[i][j] << ", ";
            printf("%-6d", matrix[i][j]);
        }
        cout <<"] \n";
    }
    cout << " ] \n\n";
}

void printMatrizP(int** matrix){
    cout << "Matrix = [ \n";
    for (int i = 0; i < SIZE_L; i++){
        cout <<"\t[ ";
        for (int j = 0; j < SIZE_C; j++){
            //cout << matrix[i][j] << ", ";
            printf("%-6d", matrix[i][j]);
        }
        cout <<"] \n";
    }
    cout << " ] \n\n";
}


void popularMatrix(int (*matrix)[SIZE_C]){
    // iniciar a matrixa com valores atearios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100);

    for (int i = 0; i < SIZE_L; i++){
        for (int j = 0; j < SIZE_C; j++){
            matrix[i][j] = distrib(gen);
        }
    }
}

void multiplicaparPorK(int matrix[SIZE_L][SIZE_C] , int k){
    for (int i = 0; i < SIZE_L; i++){
        for (int j = 0; j < SIZE_C; j++){
            matrix[i][j] *= k;
        }
    }  
}

int** transpostaMatrix(const int matrix[SIZE_L][SIZE_C]){
    int** result = new int*[SIZE_L];

    // alocar os valores
    for (int i = 0; i < SIZE_C; i++){
        result[i] = new int[SIZE_C];
    }

    for (int i = 0; i < SIZE_L; i++){
        for (int j = 0; j < SIZE_C; j++){
            result[i][j] = matrix[j][i];
        }
    }

    return result;
}

int** opostoMatrix(const int matrix[SIZE_L][SIZE_C]){
    int** result = new int*[SIZE_L];

    // alocar os valores
    for (int i = 0; i < SIZE_C; i++){
        result[i] = new int[SIZE_C];
    }

    for (int i = 0; i < SIZE_L; i++){
        for (int j = 0; j < SIZE_C; j++){
            result[i][j] = (-1)*matrix[i][j];
        }
    }

    return result;
}

int** reflexaoLateralMatrix(const int matrix[SIZE_L][SIZE_C]){
    int** result = new int*[SIZE_L];

    // alocar os valores
    for (int i = 0; i < SIZE_C; i++){
        result[i] = new int[SIZE_C];
    }

    for (int i = 0; i < SIZE_L; i++){
        for (int j = 0; j < SIZE_C; j++){
            result[i][j] = matrix[i][(SIZE_C-1-j)];
        }
    }

    return result;
}

int** relexaoInferiorMatrix(const int matrix[SIZE_L][SIZE_C]){
    int** result = new int*[SIZE_L];

    // alocar os valores
    for (int i = 0; i < SIZE_C; i++){
        result[i] = new int[SIZE_C];
    }

    for (int i = 0; i < SIZE_L; i++){
        for (int j = 0; j < SIZE_C; j++){
            result[i][j] = matrix[(SIZE_C-1-i)][j];
        }
    }

    return result;
}

int** arritmeticMatrizes(const int matrixA[SIZE_L][SIZE_C], const int matrixB[SIZE_L][SIZE_C], char sinal){
    int** matrix = new int*[SIZE_L];

    // ALOCAR O NOVO VECTOR A SER RETORNADAO
    for (int i = 0; i < SIZE_L; i++){
        matrix[i] = new int[SIZE_C];
    }

    if (SIZE_C == SIZE_L){
        if (sinal == '+'){
            for (int i = 0; i < SIZE_L; i++){
                for (int j = 0; j < SIZE_C; j++){
                    matrix[i][j]  = matrixA[i][j] + matrixB[i][j];
                }
            }  
        }else{
            for (int i = 0; i < SIZE_L; i++){
                for (int j = 0; j < SIZE_C; j++){
                    matrix[i][j]  = matrixA[i][j] - matrixB[i][j];
                }
            }  
        }

        return matrix;
    }else{
       throw std::runtime_error("As matrzes devem ter a mesma ordem!");
    }

}



int** multiplicacaoMatrizes(const int matrixA[SIZE_L][SIZE_C], const int matrixB[SIZE_L][SIZE_C]){
    int** matrix = new int*[SIZE_L];


    // ALOCAR O NOVO VECTOR A SER RETORNADAO
    for (int i = 0; i < SIZE_L; i++){
        matrix[i] = new int[SIZE_C];
    }

    int n = SIZE_C;

    if (SIZE_C == SIZE_L){
        for (int i = 0; i < SIZE_L; i++){
            for (int j = 0; j < SIZE_C; j++){
                for (int n = 0; n < SIZE_L; n++) {
                    matrix[i][j]  += (matrixA[i][n] * matrixB[n][j]);
                }
            }
        }  
        return matrix;
    }else{
       throw std::runtime_error("As matrzes devem ter a mesma ordem!");
    }

}

// Regra de Laplace, Complecidade O(n!), rum para programar
long determinante(int matriz[SIZE_C][SIZE_C], int n) {
    if (n == 1) {
        return matriz[0][0];
    }
    if (n == 2) {
        return matriz[0][0] * matriz[1][1] - matriz[0][1] * matriz[1][0];
    }

    long det = 0.0;
    int submatriz[SIZE_C][SIZE_C];

    for (int x = 0; x < n; x++) {
        // Criar a submatriz
        int subi = 0; // Índice da submatriz
        for (int i = 1; i < n; i++) {
            int subj = 0; // Índice da coluna da submatriz
            for (int j = 0; j < n; j++) {
                if (j == x) continue; // Ignorar a coluna atual
                submatriz[subi][subj] = matriz[i][j];
                subj++;
            }
            subi++;
        }
        // Calcular o determinante usando o Teorema de Laplace
        det += (x % 2 == 0 ? 1 : -1) * matriz[0][x] * determinante(submatriz, n-1);
    }
    return det;
}

// Usando o metodo Redução a Forma Escalonada, Complecidade O(n^(3))
long double determinant(int matrix[SIZE_C][SIZE_C], int n) {
    long det = 1;
    double temp[SIZE_C][SIZE_C];

    // Copiar a matriz original para a matriz temporária
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            temp[i][j] = matrix[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        // Encontrar o pivô
        long double pivot = temp[i][i];
        if (pivot == 0) {
            // Se o pivô for zero, troque com uma linha abaixo
            for (int j = i + 1; j < n; j++) {
                if (temp[j][i] != 0) {
                    for (int k = 0; k < n; k++) {
                        swap(temp[i][k], temp[j][k]);
                    }
                    det *= -1; // Troca de linhas altera o sinal do determinante
                    break;
                }
            }
            pivot = temp[i][i];
            if (pivot == 0) {
                return 0; // Determinante é zero se não houver pivô
            }
        }

        // Reduzir a matriz
        for (int j = i + 1; j < n; j++) {
            long double factor = temp[j][i] / pivot;
            for (int k = 0; k < n; k++) {
                temp[j][k] -= factor * temp[i][k];
            }
        }
        det *= pivot; // Multiplica o determinante pelo pivô
    }

    return det;
}



int main(int argc, char const *argv[]){
    int matrixA[SIZE_L][SIZE_C];
    int matrixB[SIZE_L][SIZE_C];

    popularMatrix(matrixA);
    popularMatrix(matrixB);

    cout << "Valor original da Matrix A("<<SIZE_L <<"x"<<SIZE_C <<"): \n";
    printMatriz(matrixA);

    cout << "Valor original da Matrix B("<<SIZE_L <<"x"<<SIZE_C <<"): \n";
    printMatriz(matrixB);

    long double detA = determinant(matrixA, SIZE_C);
    cout << "Matrix A("<<SIZE_L <<"x"<<SIZE_C << ") Determinate = " << detA<< " \n\n";

    long double det = determinant(matrixB, SIZE_C);
    cout << "Matrix B("<<SIZE_L <<"x"<<SIZE_C << ") Determinate = " << det<< " \n\n";

    try{
        cout << "Reflexao Lateral Da Matrix A("<<SIZE_L <<"x"<<SIZE_C << ") "<< "Matrix M("<<SIZE_L <<"x"<<SIZE_C <<"): \n";
        int** matrixT2 = reflexaoLateralMatrix(matrixA);
        printMatrizP(matrixT2);

        cout << "Matrix B("<<SIZE_L <<"x"<<SIZE_C << ") "<< "Matrix C("<<SIZE_L <<"x"<<SIZE_C <<"): \n";
        int** matrixT3 = relexaoInferiorMatrix(matrixB);
        printMatrizP(matrixT3);

        cout << "Multiplicacao da "<< "Matrix A("<<SIZE_L <<"x"<<SIZE_C << ") - "<< "Matrix B("<<SIZE_L <<"x"<<SIZE_C <<")"" = " << "Matrix Q("<<SIZE_L <<"x"<<SIZE_C <<")" ": \n";
        int** matrixQ = multiplicacaoMatrizes(matrixA, matrixB);
        printMatrizP(matrixQ);

        cout << "Soma da "<< "Matrix A("<<SIZE_L <<"x"<<SIZE_C << ") + "<< "Matrix B("<<SIZE_L <<"x"<<SIZE_C <<")"" = " << "Matrix C("<<SIZE_L <<"x"<<SIZE_C <<")" ": \n";
        int** matrixC = arritmeticMatrizes(matrixA, matrixB, '+');
        printMatrizP(matrixC);

        cout << "Subtracao da "<< "Matrix A("<<SIZE_L <<"x"<<SIZE_C << ") - "<< "Matrix B("<<SIZE_L <<"x"<<SIZE_C <<")"" = " << "Matrix H("<<SIZE_L <<"x"<<SIZE_C <<")" ": \n";
        int** matrixH = arritmeticMatrizes(matrixA, matrixB, '-');
        printMatrizP(matrixH);

        cout << "Subtracao da "<< "Matrix A("<<SIZE_L <<"x"<<SIZE_C << ") - "<< "Matrix B("<<SIZE_L <<"x"<<SIZE_C <<")"" = " << "Matrix B("<<SIZE_L <<"x"<<SIZE_C <<")" ": \n";
        int** matrixD = arritmeticMatrizes(matrixB, matrixA, '-');
        printMatrizP(matrixD);

        cout << "Matrix A("<<SIZE_L <<"x"<<SIZE_C << ") Transposta =  "<< "T.Matrix A("<<SIZE_L <<"x"<<SIZE_C <<"): \n";
        int** matrixT = transpostaMatrix(matrixA);
        printMatrizP(matrixT);


        cout << "Matrix B("<<SIZE_L <<"x"<<SIZE_C << ") Transposta =  "<< "T.Matrix B("<<SIZE_L <<"x"<<SIZE_C <<"): \n";
        int** matrixT1 = transpostaMatrix(matrixB);
        printMatrizP(matrixT1);

        cout << "Matrix A("<<SIZE_L <<"x"<<SIZE_C << ") Oposto =  "<< "Matrix -A("<<SIZE_L <<"x"<<SIZE_C <<"): \n";
        int** matrixT21 = opostoMatrix(matrixA);
        printMatrizP(matrixT21);


        cout << "Matrix B("<<SIZE_L <<"x"<<SIZE_C << ") Oposto =  "<< "Matrix -B("<<SIZE_L <<"x"<<SIZE_C <<"): \n";
        int** matrixT31 = opostoMatrix(matrixB);
        printMatrizP(matrixT31);

        cout << "Matrix A multiplicada por 2: \n";
        multiplicaparPorK(matrixA, 2);
        printMatriz(matrixA);

        cout << "Matrix B multiplicada por 2: \n";
        multiplicaparPorK(matrixB, 2);
        printMatriz(matrixB);
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }

    return 0;
}


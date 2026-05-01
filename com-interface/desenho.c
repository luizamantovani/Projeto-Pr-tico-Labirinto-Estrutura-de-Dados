#include "raylib.h"

#define TAM 32
#define LINHAS 10
#define COLUNAS 10

char lab[LINHAS][COLUNAS] = {
    "##########",
    "#P     # #",
    "# ### ## #",
    "#   #    #",
    "### #### #",
    "#   T    #",
    "# ###### #",
    "#      A #",
    "# ######S#",
    "##########"
};

void desenharLabirinto() {
    for(int i = 0; i < LINHAS; i++) {
        for(int j = 0; j < COLUNAS; j++) {

            int x = j * TAM;
            int y = i * TAM;

            switch(lab[i][j]) {
                case '#':
                    DrawRectangle(x, y, TAM, TAM, DARKGRAY);
                    break;

                case 'P':
                    DrawRectangle(x, y, TAM, TAM, GREEN);
                    break;

                case 'S':
                    DrawRectangle(x, y, TAM, TAM, BLUE);
                    break;

                case 'T':
                    DrawRectangle(x, y, TAM, TAM, YELLOW);
                    break;

                case 'A':
                    DrawRectangle(x, y, TAM, TAM, RED);
                    break;

                case '.':
                    DrawRectangle(x, y, TAM, TAM, LIGHTGRAY);
                    break;

                default:
                    DrawRectangle(x, y, TAM, TAM, RAYWHITE);
            }
        }
    }
}

int main() {

    InitWindow(COLUNAS * TAM, LINHAS * TAM, "Labirinto 2D");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        desenharLabirinto();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

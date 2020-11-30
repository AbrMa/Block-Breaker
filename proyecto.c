/*
 2: INSTITUTO POLITÉCNICO NACIONAL
 3: ESCUELA SUPERIOR DE CÓMPUTO
 4: ALGORITMIA Y PROG. ESTRUCTURADA
 5: GRUPO: 1CV2
 6: ALUMNO(S): Meza Zamora Abraham Manuel
 7:
 8: PROF: DR. BENJAMÍN LUNA BENOSO
 9: SEMESTRE 2018-2
 10: Arkanoid:
 11: Juego chido.
 12: FECHA 19 Junio 2018
 13: */

//Librerías.
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
//Librerías de gráficos.
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

// Tamaños de la ventana.
#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)

// Velocidad en pixeles por segundo.
#define SPEED (400)
#define FILA (5)
#define COLUMNA (2)


void llenaArreglo(int A[FILA][COLUMNA]);
void graficos(int A[FILA][COLUMNA]);
void errorSuperficie(SDL_Surface *superficie, SDL_Window* ventana);
int choque(SDL_Rect* rect1,SDL_Rect* rect2);
void lectura_Archivo(void);
void ingresar_archivo(void);
void ingresaBloque(int A[FILA][COLUMNA] , int n);
void mostrarCompa(int A[FILA][COLUMNA] , int n);
void lectura_Archivo();

int main(void)
{
    int ladrillos[FILA][COLUMNA];
    int continuar = 1;
    //while (continuar == 1) {
        llenaArreglo(ladrillos);
        graficos(ladrillos);
        printf("Desea jugar otra ronda 1. Continuar 2. Terminar\n");
        scanf("%d", &continuar);
    //}
    return 0;
}

void llenaArreglo(int A[FILA][COLUMNA])
{
    int i,j;
    for (i=0; i<COLUMNA; i++) {
        for (j=0; j<FILA; j++) {
            A[i][j]= 1;
            printf("%d\t",A[i][j]);
        }
        printf("\n");
    }
}

void graficos(int A[FILA][COLUMNA]){
    int i,j,lad1=1,lad2=1,lad3=1,lad4=1,lad5=1,lad6=1,lad7=1,lad8=1,lad9=1,lad10=1,ganar=0, letPierde=0, letGana=0;
    // Inicia la libreria de gráficos.
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    //Ventana.
    SDL_Window* win = SDL_CreateWindow("Arkanoid - Meza Zamora Abraham Manuel ICV2",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT,0);
    //Si no se genera una ventana entonces imprime el error.
    if (!win)
    {
        printf("Error al crear ventana: %s\n", SDL_GetError());
        SDL_Quit();
    }
    
    // Hace uso de la targeta gráfica.
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend)
    {
        printf("Error al crear dibujo: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
    }
    
    // Crea la superficie de las imágenes.
    SDL_Surface *surface = IMG_Load("pics/barra.png"), *surfaceBola = IMG_Load("pics/bola.png"), *surfaceLadrillo1 = IMG_Load("pics/ladrillo.png"), *surfaceLadrillo2 = IMG_Load("pics/ladrillo.png"), *surfaceLadrillo3 = IMG_Load("pics/ladrillo.png"), *surfaceLadrillo4 = IMG_Load("pics/ladrillo.png"), *surfaceLadrillo5 = IMG_Load("pics/ladrillo.png"), *surfaceLadrillo6 = IMG_Load("pics/ladrillo.png"), *surfaceLadrillo7 = IMG_Load("pics/ladrillo.png"), *surfaceLadrillo8 = IMG_Load("pics/ladrillo.png"), *surfaceLadrillo9 = IMG_Load("pics/ladrillo.png"), *surfaceLadrillo10 = IMG_Load("pics/ladrillo.png"),*surfaceGana = IMG_Load("pics/gana.png"), *surfacePierde = IMG_Load("pics/pierde.png");
    //Imprime errores en caso de no crearse las imágenes

    if(!surface || !surfaceBola || !surfaceLadrillo1 || !surfaceLadrillo2 || !surfaceLadrillo3 || !surfaceLadrillo4 || !surfaceLadrillo5 || !surfaceLadrillo6 || !surfaceLadrillo7 || !surfaceLadrillo8 || !surfaceLadrillo9 || !surfaceLadrillo10 || !surfaceGana || !surfacePierde)
    {
        errorSuperficie(rend,win);
    }
    
    // Hace que la ventana se pueda mover.
    
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_Texture* texBola = SDL_CreateTextureFromSurface(rend, surfaceBola);
    SDL_Texture* texLad1 = SDL_CreateTextureFromSurface(rend, surfaceLadrillo1);
    SDL_Texture* texLad2 = SDL_CreateTextureFromSurface(rend, surfaceLadrillo2);
    SDL_Texture* texLad3 = SDL_CreateTextureFromSurface(rend, surfaceLadrillo3);
    SDL_Texture* texLad4 = SDL_CreateTextureFromSurface(rend, surfaceLadrillo4);
    SDL_Texture* texLad5 = SDL_CreateTextureFromSurface(rend, surfaceLadrillo5);
    SDL_Texture* texLad6 = SDL_CreateTextureFromSurface(rend, surfaceLadrillo6);
    SDL_Texture* texLad7 = SDL_CreateTextureFromSurface(rend, surfaceLadrillo7);
    SDL_Texture* texLad8 = SDL_CreateTextureFromSurface(rend, surfaceLadrillo8);
    SDL_Texture* texLad9 = SDL_CreateTextureFromSurface(rend, surfaceLadrillo9);
    SDL_Texture* texLad10 = SDL_CreateTextureFromSurface(rend, surfaceLadrillo10);
    SDL_Texture* texGana = SDL_CreateTextureFromSurface(rend, surfaceGana);
    SDL_Texture* texPierde = SDL_CreateTextureFromSurface(rend, surfacePierde);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(surfaceBola);
    SDL_FreeSurface(surfaceLadrillo1);
    SDL_FreeSurface(surfaceLadrillo2);
    SDL_FreeSurface(surfaceLadrillo3);
    SDL_FreeSurface(surfaceLadrillo4);
    SDL_FreeSurface(surfaceLadrillo5);
    SDL_FreeSurface(surfaceLadrillo6);
    SDL_FreeSurface(surfaceLadrillo7);
    SDL_FreeSurface(surfaceLadrillo8);
    SDL_FreeSurface(surfaceLadrillo9);
    SDL_FreeSurface(surfaceLadrillo10);
    SDL_FreeSurface(surfaceGana);
    SDL_FreeSurface(surfacePierde);
    
    if (!tex || !texBola || !texLad1 || !texLad2 || !texLad3 || !texLad4 || !texLad5 || !texLad6 || !texLad7 || !texLad8 || !texLad9 || !texLad10 || !texGana || !texPierde)
    {
        errorSuperficie(rend,win);
    }
    
    // Contiene los sprites.
    SDL_Rect barraV, bola, ladrillo1, ladrillo2, ladrillo3, ladrillo4, ladrillo5, ladrillo6, ladrillo7, ladrillo8 , ladrillo9 , ladrillo10, gana, pierde;
    
    // Dimensiones de los sprites.
    SDL_QueryTexture(tex, NULL, NULL, &barraV.w, &barraV.h);
    SDL_QueryTexture(texBola, NULL, NULL, &bola.w, &bola.h);
    SDL_QueryTexture(texLad1, NULL, NULL, &ladrillo1.w, &ladrillo1.h);
    SDL_QueryTexture(texLad2, NULL, NULL, &ladrillo2.w, &ladrillo2.h);
    SDL_QueryTexture(texLad3, NULL, NULL, &ladrillo3.w, &ladrillo3.h);
    SDL_QueryTexture(texLad4, NULL, NULL, &ladrillo4.w, &ladrillo4.h);
    SDL_QueryTexture(texLad5, NULL, NULL, &ladrillo5.w, &ladrillo5.h);
    SDL_QueryTexture(texLad6, NULL, NULL, &ladrillo6.w, &ladrillo6.h);
    SDL_QueryTexture(texLad7, NULL, NULL, &ladrillo7.w, &ladrillo7.h);
    SDL_QueryTexture(texLad8, NULL, NULL, &ladrillo8.w, &ladrillo8.h);
    SDL_QueryTexture(texLad9, NULL, NULL, &ladrillo9.w, &ladrillo9.h);
    SDL_QueryTexture(texLad10, NULL, NULL, &ladrillo10.w, &ladrillo10.h);
    SDL_QueryTexture(texGana, NULL, NULL, &gana.w, &gana.h);
    SDL_QueryTexture(texPierde, NULL, NULL, &pierde.w, &pierde.h);
    
    //Se escala la imagen original a una más pequeña.
    barraV.w /= 5;
    barraV.h /= 10;
    bola.w /= 15;
    bola.h /= 15;
    ladrillo1.w /= 10;
    ladrillo1.h /= 10;
    ladrillo2.w /= 10;
    ladrillo2.h /= 10;
    ladrillo3.w /= 10;
    ladrillo3.h /= 10;
    ladrillo4.w /= 10;
    ladrillo4.h /= 10;
    ladrillo5.w /= 10;
    ladrillo5.h /= 10;
    ladrillo6.w /= 10;
    ladrillo6.h /= 10;
    ladrillo7.w /= 10;
    ladrillo7.h /= 10;
    ladrillo8.w /= 10;
    ladrillo8.h /= 10;
    ladrillo9.w /= 10;
    ladrillo9.h /= 10;
    ladrillo10.w /= 10;
    ladrillo10.h /= 10;
    gana.w /= 1;
    gana.h /= 1;
    pierde.w /= 1;
    pierde.h /= 1;
    
    // Mantiene la ventana abierta
    int close_requested = 0;
    //Posición gana, pierde.
    float x_posGana = (WINDOW_WIDTH - gana.w) / 2;
    float y_posGana = (WINDOW_HEIGHT - gana.h) / 2;
    float x_posPierde = (WINDOW_WIDTH - pierde.w) / 2;
    float y_posPierde = (WINDOW_HEIGHT - pierde.h) / 2;
    // Posición de la barra verde al inicio del programa.
    float x_posbarraV = (WINDOW_WIDTH - barraV.w) / 2;
    float y_posbarraV = (WINDOW_HEIGHT - barraV.h);
    // Posición de la bola al inicio del programa.
    float x_posBola = (WINDOW_WIDTH - barraV.w) / 3;
    float y_posBola = (WINDOW_HEIGHT - barraV.h) / 3;
    //Posición de los bloques.
    float x_ladrillo1 = ladrillo1.h;
    float y_ladrillo1 = 70;
    float x_ladrillo2 = ladrillo1.h;
    float y_ladrillo2 = (70 + ladrillo1.w);
    float x_ladrillo3 = ladrillo1.h;
    float y_ladrillo3 = (70 + ladrillo1.w + ladrillo2.w);
    float x_ladrillo4 = ladrillo1.h;
    float y_ladrillo4 = (70 + ladrillo1.w + ladrillo2.w + ladrillo3.w);
    float x_ladrillo5 = ladrillo1.h;
    float y_ladrillo5 = (70 + ladrillo1.w + ladrillo2.w + ladrillo3.w + ladrillo4.w);
    float x_ladrillo6 = 2*ladrillo1.h;
    float y_ladrillo6 = 70;
    float x_ladrillo7 = 2*ladrillo1.h;
    float y_ladrillo7 = (70 + ladrillo1.w);
    float x_ladrillo8 = 2*ladrillo1.h;
    float y_ladrillo8 = (70 + ladrillo1.w + ladrillo2.w);
    float x_ladrillo9 = 2*ladrillo1.h;
    float y_ladrillo9 = (70 + ladrillo1.w + ladrillo2.w + ladrillo3.w);
    float x_ladrillo10 = 2*ladrillo1.h;
    float y_ladrillo10 = (70 + ladrillo1.w + ladrillo2.w + ladrillo3.w + ladrillo4.w);
    //La velocidad se inicia en 0 ya que no queremos que la barra se mueva hasta que el usuario presione una tecla.
    float x_velbarraV = 0;
    float x_velBola = SPEED;
    float y_velBola = SPEED;
    
    // Inicialización del movimiento de la barra.
    int left = 0;
    int right = 0;
    
    // Animación para la barra verde.
    while (!close_requested)
    {
        // Eventos
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    close_requested = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_LEFT:
                        left = 1;
                        break;
                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        right = 1;
                        break;
                }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_LEFT:
                        left = 0;
                        break;
                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        right = 0;
                        break;
                }
                    break;
            }
        }
        
        //Animación de la bola.
        if(x_posBola <= 0)
        {
            x_posBola =0;
            x_velBola =-x_velBola;
        }
        if (y_posBola <= 0)
        {
            y_posBola = 0;
            y_velBola = -y_velBola;
        }
        if (x_posBola >= WINDOW_WIDTH - bola.w)
        {
            x_posBola = WINDOW_WIDTH - bola.w;
            x_velBola = -x_velBola;
        }
        if (y_posBola >= WINDOW_HEIGHT - bola.h)
        {
            letPierde = 1;
            
//            y_posBola = WINDOW_HEIGHT - bola.h;
//            y_velBola = -y_velBola;
        }
        //Detecta el choque entre la pelota y la barra.
        if(choque(&bola,&barraV) == 1){
            if(x_velBola >= 0 ){
                if(bola.x <= ((barraV.x)+(barraV.w/2))){
                    x_velBola = -x_velBola;
                    y_velBola = -y_velBola;
                }
                if(bola.x >= ((barraV.x)+(barraV.w/2))){
                    y_velBola = -y_velBola;
                }
            }
            else{
                if(bola.x >= ((barraV.x)+(barraV.w/2))){
                    x_velBola = -x_velBola;
                    y_velBola = -y_velBola;
                }
                if(bola.x <= ((barraV.x)+(barraV.w/2))){
                    y_velBola = -y_velBola;
                    
                }
            }
        }
        // Determinamos la velocidad  de la barra.
        
        x_velbarraV = 0;
        if (left && !right) x_velbarraV = -SPEED;
        if (right && !left) x_velbarraV = SPEED;
        
        // Actualiza la posición de la barra.
        x_posbarraV += x_velbarraV / 60;
        
        //Actualiza la posición de la bola.
        x_posBola += x_velBola / 60;
        y_posBola += y_velBola / 60;
        
        // Evita que la barra se salga de la ventana.
        if (x_posbarraV <= 0) x_posbarraV = 0;
        if (x_posbarraV >= WINDOW_WIDTH - barraV.w) x_posbarraV = WINDOW_WIDTH - barraV.w;
        
        
        // Dibujo final.
        ladrillo1.y = (int) x_ladrillo1;
        ladrillo1.x = (int) y_ladrillo1;
        ladrillo2.y = (int) x_ladrillo2;
        ladrillo2.x = (int) y_ladrillo2;
        ladrillo3.y = (int) x_ladrillo3;
        ladrillo3.x = (int) y_ladrillo3;
        ladrillo4.y = (int) x_ladrillo4;
        ladrillo4.x = (int) y_ladrillo4;
        ladrillo5.y = (int) x_ladrillo5;
        ladrillo5.x = (int) y_ladrillo5;
        ladrillo6.y = (int) x_ladrillo6;
        ladrillo6.x = (int) y_ladrillo6;
        ladrillo7.y = (int) x_ladrillo7;
        ladrillo7.x = (int) y_ladrillo7;
        ladrillo8.y = (int) x_ladrillo8;
        ladrillo8.x = (int) y_ladrillo8;
        ladrillo9.y = (int) x_ladrillo9;
        ladrillo9.x = (int) y_ladrillo9;
        ladrillo10.y = (int) x_ladrillo10;
        ladrillo10.x = (int) y_ladrillo10;
        barraV.y = (int) y_posbarraV;
        barraV.x = (int) x_posbarraV;
        bola.x = (int) x_posBola;
        bola.y = (int) y_posBola;
        pierde.x = (int) x_posPierde;
        pierde.y = (int) y_posPierde;
        gana.x = (int) x_posPierde;
        gana.y = (int) y_posPierde;
        
        // Limpia la ventana de "basura"
        SDL_RenderClear(rend);
        
        //Colisión con bloques.
        
        if(choque(&bola,&ladrillo1) == 1){
            SDL_DestroyTexture(texLad1);
            if(lad1 == 1){
                x_velBola = -x_velBola;
                y_velBola = -y_velBola;
                ganar++;
                lad1++;
            }
        }
        
        if(choque(&bola,&ladrillo2) == 1){
            SDL_DestroyTexture(texLad2);
            if(lad2 == 1){
                x_velBola = -x_velBola;
                y_velBola = -y_velBola;
                ganar++;
                lad2++;
            }
        }
        
        if(choque(&bola,&ladrillo3) == 1){
            SDL_DestroyTexture(texLad3);
            if(lad3 == 1){
                x_velBola = -x_velBola;
                y_velBola = -y_velBola;
                ganar++;
                lad3++;
            }
        }
        
        if(choque(&bola,&ladrillo4) == 1){
            SDL_DestroyTexture(texLad4);
            if(lad4 == 1){
                x_velBola = -x_velBola;
                y_velBola = -y_velBola;
                ganar++;
                lad4++;
            }
        }
        
        if(choque(&bola,&ladrillo5) == 1){
            SDL_DestroyTexture(texLad5);
            if(lad5 == 1){
                x_velBola = -x_velBola;
                y_velBola = -y_velBola;
                ganar++;
                lad5++;
            }
        }
        
        if(choque(&bola,&ladrillo6) == 1){
            SDL_DestroyTexture(texLad6);
            if(lad6 == 1){
                x_velBola = -x_velBola;
                y_velBola = -y_velBola;
                ganar++;
                lad6++;
            }
        }
        
        if(choque(&bola,&ladrillo7) == 1){
            SDL_DestroyTexture(texLad7);
            if(lad7 == 1){
                x_velBola = -x_velBola;
                y_velBola = -y_velBola;
                ganar++;
                lad7++;
            }
        }
        
        if(choque(&bola,&ladrillo8) == 1){
            SDL_DestroyTexture(texLad8);
            if(lad8 == 1){
                x_velBola = -x_velBola;
                y_velBola = -y_velBola;
                ganar++;
                lad8++;
            }
        }
        
        if(choque(&bola,&ladrillo9) == 1){
            SDL_DestroyTexture(texLad9);
            if(lad9 == 1){
                x_velBola = -x_velBola;
                y_velBola = -y_velBola;
                ganar++;
                lad9++;
            }
        }
        
        if(choque(&bola,&ladrillo10) == 1){
            SDL_DestroyTexture(texLad10);
            if(lad10 == 1){
                x_velBola = -x_velBola;
                y_velBola = -y_velBola;
                ganar++;
                lad10++;
            }
        }
        
        // Dibuja las imagenes en la ventana, sin esto no sale nada :c.
        SDL_RenderCopy(rend, tex, NULL, &barraV);
        SDL_RenderCopy(rend, texBola, NULL, &bola);
        SDL_RenderCopy(rend, texLad1, NULL, &ladrillo1);
        SDL_RenderCopy(rend, texLad2, NULL, &ladrillo2);
        SDL_RenderCopy(rend, texLad3, NULL, &ladrillo3);
        SDL_RenderCopy(rend, texLad4, NULL, &ladrillo4);
        SDL_RenderCopy(rend, texLad5, NULL, &ladrillo5);
        SDL_RenderCopy(rend, texLad6, NULL, &ladrillo6);
        SDL_RenderCopy(rend, texLad7, NULL, &ladrillo7);
        SDL_RenderCopy(rend, texLad8, NULL, &ladrillo8);
        SDL_RenderCopy(rend, texLad9, NULL, &ladrillo9);
        SDL_RenderCopy(rend, texLad10, NULL, &ladrillo10);
        SDL_RenderPresent(rend);
        
        if(ganar == 10)
        {
            SDL_RenderCopy(rend, texGana, NULL, &gana);
            SDL_RenderPresent(rend);
            SDL_Delay(3000);
            close_requested = 1;
        }
        if (letPierde == 1) {
            SDL_RenderCopy(rend, texPierde, NULL, &pierde);
            SDL_RenderPresent(rend);
            SDL_Delay(3000);
            close_requested = 1;
        }
        
        // Fotogramas por segundo.
        SDL_Delay(1000/50);
    }
    
    // Cierra todo antes de terminar.
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void errorSuperficie(SDL_Surface *superficie, SDL_Window* ventana){
    printf("Error\n");
    SDL_DestroyRenderer(superficie);
    SDL_DestroyWindow(ventana);
    SDL_Quit();
}


int choque(SDL_Rect* rect1,SDL_Rect* rect2)
{
    if(rect1->y >= rect2->y + rect2->h)
        return 0;
    if(rect1->x >= rect2->x + rect2->w)
        return 0;
    if(rect1->y + rect1->h <= rect2->y)
        return 0;
    if(rect1->x + rect1->w <= rect2->x)
        return 0;
    return 1;
}

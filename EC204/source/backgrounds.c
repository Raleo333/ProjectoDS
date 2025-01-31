/********************************************************** 
 * backgrounds.c
 *
 * Este codigo se ha implementado basandose en el ejemplo 
 * "Simple sprite demo" de dovoto y otro de Jaeden Amero
 **********************************************************/

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 
 * Anadir aquí los includes para cada fondo [gfx]
 **/

#include "back00.h"
#include "back01.h"
#include "back02.h"
#include "back03.h"
#include "back04.h"
#include "menu_null.h"
#include "menu_down.h"
#include "menu_up.h"


/* 
 * Seleccionar un canal DMA para copiar a memoria las imágenes
 **/
static const int DMA_CHANNEL = 3;


/* 
 * Para cada imagen que se quiera llevar a pantalla hay que hacer una de estas funciones
 **/

void display_back00() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     back00Bitmap,              // Variable generada automáticamente
                     (uint16 *)BG_BMP_RAM(0),   // Dirección del fondo 3 principal 
                     back01BitmapLen);          // Longitud (en bytes) generada automáticamente 
}

void display_back01() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     back01Bitmap,              // Variable generada automáticamente
                     (uint16 *)BG_BMP_RAM(0),   // Dirección del fondo 3 principal 
                     back01BitmapLen);          // Longitud (en bytes) generada automáticamente 
}

void display_back02() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     back02Bitmap,              // Variable generada automáticamente
                     (uint16 *)BG_BMP_RAM(0),   // Dirección del fondo 3 principal 
                     back01BitmapLen);          // Longitud (en bytes) generada automáticamente 
}

void display_back03() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     back03Bitmap,              // Variable generada automáticamente
                     (uint16 *)BG_BMP_RAM(0),   // Dirección del fondo 3 principal 
                     back01BitmapLen);          // Longitud (en bytes) generada automáticamente 
}

void display_back04() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     back04Bitmap,              // Variable generada automáticamente
                     (uint16 *)BG_BMP_RAM(0),   // Dirección del fondo 3 principal 
                     back01BitmapLen);          // Longitud (en bytes) generada automáticamente 
}

void display_menu_null() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     menu_nullBitmap,              // Variable generada automáticamente
                     (uint16 *)BG_BMP_RAM(0),   // Dirección del fondo 3 principal 
                     back01BitmapLen);          // Longitud (en bytes) generada automáticamente 
}
void display_menu_up() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     menu_upBitmap,              // Variable generada automáticamente
                     (uint16 *)BG_BMP_RAM(0),   // Dirección del fondo 3 principal 
                     back01BitmapLen);          // Longitud (en bytes) generada automáticamente 
}
void display_menu_down() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     menu_downBitmap,              // Variable generada automáticamente
                     (uint16 *)BG_BMP_RAM(0),   // Dirección del fondo 3 principal 
                     back01BitmapLen);          // Longitud (en bytes) generada automáticamente 
}
/* 
 * Definir el sistema de video
 **/
void init_video() {
    /* 
     * Mapear la memoria VRAM para mostrar graficos en las dos pantallas
     **/
    vramSetMainBanks(VRAM_A_MAIN_BG_0x06000000,
                     VRAM_B_MAIN_BG_0x06020000,
                     VRAM_C_SUB_BG_0x06200000,
                     VRAM_E_LCD);
    vramSetBankE(VRAM_E_MAIN_SPRITE);
    vramSetBankD(VRAM_D_SUB_SPRITE);

    /* 
     * Establecer el modo de video de la pantalla principal
     **/
    videoSetMode(MODE_5_2D | // Establecer el modo grafico 5
                 DISPLAY_BG2_ACTIVE | // Activar el fondo 2
                 DISPLAY_BG3_ACTIVE); // Activar el fondo 3

    /* 
     * Establecer el modo de video de la pantalla secundaria
     **/
        videoSetModeSub(MODE_5_2D | // Establecer el modo grafico 5
                    DISPLAY_BG3_ACTIVE); // Activar el fondo 3
} // init_video()



/* 
 * Procedimiento para configurar el sistema de fondos
 **/
void init_background() {
    /* 
     * Establecer la afinidad del fondo 3 de la pantalla principal con color de 16 bits
     **/
    REG_BG3CNT = BG_BMP16_256x256 |
                 BG_BMP_BASE(0) |   // La dirección inicial de memoria
                 BG_PRIORITY(3);    // Baja prioridad

    /* 
     * Establecer la matriz de transformación afin del fondo 3 de la pantalla principal
     * a la matriz de identidad
     **/
    REG_BG3PA = 1 << 8;
    REG_BG3PB = 0;
    REG_BG3PC = 0;
    REG_BG3PD = 1 << 8;

    /* 
     * Definir la situación del fondo 3 de la pantalla principal. 
     * Esto deberá cambiar según la posición en la que se quiera poner el gráfico
     **/
    REG_BG3X = 0;
    REG_BG3Y = 0;

    /* 
     * Establecer la afinidad del fondo 2 de la pantalla principal con color de 16 bits
     **/
    REG_BG2CNT = BG_BMP16_128x128 |
                 BG_BMP_BASE(8) |   // La dirección inicial de memoria
                 BG_PRIORITY(2);    // Baja prioridad

    /* 
     * Establecer la matriz de transformación afin del fondo 2 de la pantalla principal 
     * a la matriz de identidad
     **/
    REG_BG2PA = 1 << 8;
    REG_BG2PB = 0;
    REG_BG2PC = 0;
    REG_BG2PD = 1 << 8;

    /* 
     * Definir la situación del fondo 2 de la pantalla principal. 
     * Esto deberá cambiar según la posición en la que se quiera poner el gráfico
     **/
    REG_BG2X = -(SCREEN_WIDTH / 2 - 32) << 8;
    REG_BG2Y = -32 << 8;

    /* 
     * Establecer la afinidad del fondo 3 de la pantalla secundaria con color de 16 bits
     **/
    REG_BG3CNT_SUB = BG_BMP16_256x256 |
                     BG_BMP_BASE(0) |   // La dirección inicial de memoria
                     BG_PRIORITY(3);    // Baja prioridad

    /* 
     * Establecer la matriz de transformación afin del fondo 3 de la pantalla secundaria
     * a la matriz de identidad
     **/
    REG_BG3PA_SUB = 1 << 8;
    REG_BG3PB_SUB = 0;
    REG_BG3PC_SUB = 0;
    REG_BG3PD_SUB = 1 << 8;

    /* 
     * Definir la situación del fondo 3 de la pantalla secundaria
     * Esto deberá cambiar según la posición en la que se quiera poner el gráfico
     **/
    REG_BG3X_SUB = 0;
    REG_BG3Y_SUB = 0;

} // init_background()

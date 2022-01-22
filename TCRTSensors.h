// -- Classe que molda o comportamento de um módulo de sensores TCRT5000 --
// -- Plataforma: Arduino --
// -- Autor: Allan Cedric --

#ifndef __TCRTSENSORS_H__
#define __TCRTSENSORS_H__

// --- Bibliotecas ---
#include <Arduino.h>

class TCRTSensors
{
private:
    uint8_t *_pins;         // Pinos
    uint8_t _numSensors;    // Número de sensores
    uint16_t _lastPosition; // Última posição do sensores

    uint16_t _minRead;     // Menor valor retornado por um sensor
    uint16_t _maxRead;     // Maior valor retornado por um sensor
    uint16_t _reflectance; // Refletância da linha branca ou preta
public:
    /*!
        @brief  Construtor

        @param  pins        Pinos
        @param  numSensors  Número de sensores
    */
    TCRTSensors(uint8_t *pins, uint8_t numSensors);

    /*!
        @brief  Calibração dos sensores.
                Determina o menor e o maior valor lido,
                e calcula a refletância para uma superfície branca.
    */
    void calibrate();

    /*!
        @brief  Retorna a posição relativa dos sensores (Linha branca no meio)
                0: Esquerda / 150: Meio / 300: Direita
    */
    uint16_t readLineWhite();

    /*!
        @brief  Retorna a posição relativa dos sensores (Linha preta no meio)
                0: Esquerda / 150: Meio / 300: Direita
    */
    uint16_t readLineBlack();
};

#endif
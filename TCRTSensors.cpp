// -- Implementação da classe TCRTSensors --
// -- Plataforma: Arduino --
// -- Autor: Allan Cedric --

#include "TCRTSensors.h"

TCRTSensors::TCRTSensors(uint8_t *pins, uint8_t numSensors)
{
    _pins = pins;
    _numSensors = numSensors;
    for (uint8_t i = 0; i < _numSensors; i++)
        pinMode(_pins[i], INPUT);
        
    _lastPosition = (_numSensors - 1) * 150 / 2; // Suponha que o robô já está no meio da linha
    _minRead = 0;
    _maxRead = 1023;
    _reflectance = (_minRead + _maxRead) / 3;
}

void TCRTSensors::calibrate()
{
    uint16_t read = analogRead(_pins[0]);
    _minRead = read;
    _maxRead = read;
    for (uint8_t i = 1; i < _numSensors; i++)
    {
        read = analogRead(_pins[i]);
        if (read < _minRead)
            _minRead = read;
        else if (read > _maxRead)
            _maxRead = read;
    }
    _reflectance = (_minRead + _maxRead) / 3;
}

uint16_t TCRTSensors::readLineWhite()
{
    uint16_t value = 0, count = 0;
    for (uint8_t i = 0; i < _numSensors; i++)
    {
        if (analogRead(_pins[i]) > (int)_reflectance)
        {
            value += ((_numSensors - 1 - i) * 150);
            count++;
        }
    }
    if (count > 0)
        _lastPosition = value / count;
    return _lastPosition;
}

uint16_t TCRTSensors::readLineBlack()
{
    uint16_t value = 0, count = 0;
    for (uint8_t i = 0; i < _numSensors; i++)
    {
        if (analogRead(_pins[i]) < (int)_reflectance)
        {
            value += ((_numSensors - 1 - i) * 150);
            count++;
        }
    }
    if (count > 0)
        _lastPosition = value / count;
    return _lastPosition;
}
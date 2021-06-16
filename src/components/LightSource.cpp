//
// Created by Luecx on 16.06.2021.
//
#include "LightSource.h"
LightSource::LightSource(const Vector<3>& color, float falloffStrength, float falloff_base, float falloff_exponent)
    : color(color), falloffStrength(falloffStrength), falloffBase(falloff_base), falloffExponent(falloff_exponent) {
}

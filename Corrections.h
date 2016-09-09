//
// Created by Arkadiy on 09/09/2016.
//

#ifndef MEERKAT2_CORRECTIONS_H
#define MEERKAT2_CORRECTIONS_H

#include "ReconstructionParameters.h"

float material_absorption_coefficient(string material, float wavelength);
float calculate_correction_coefficient(ExperimentalParameters & exp, int x, int y);

#endif //MEERKAT2_CORRECTIONS_H

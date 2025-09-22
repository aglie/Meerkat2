//
// Created by Arkadiy Simonov on 03.10.2024.
//

#ifndef MEERKAT2_IMAGELOADERFACTORY_H
#define MEERKAT2_IMAGELOADERFACTORY_H

#include "AbstractImageLoader.h"
#include <memory>

std::unique_ptr<AbstractImageLoader> createImageLoader(ReconstructionParameters par);

#endif //MEERKAT2_IMAGELOADERFACTORY_H

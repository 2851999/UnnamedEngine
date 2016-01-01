/*****************************************************************************
 *
 *   Copyright 2015 - 2016 Joel Davies
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *****************************************************************************/

#include "Vector.h"

/***************************************************************************************************
 * Colour class
 ***************************************************************************************************/

Colour Colour::NONE =        Colour(0.0f, 0.0f, 0.0f, 0.0f);
Colour Colour::BLACK =       Colour(0.0f, 0.0f, 0.0f, 1.0f);
Colour Colour::GREY  =       Colour(0.2f, 0.2f, 0.2f, 1.0f);
Colour Colour::LIGHT_GREY =  Colour(0.45f, 0.45f, 0.45f, 1.0f);
Colour Colour::RED =         Colour(1.0f, 0.0f, 0.0f, 1.0f);
Colour Colour::ORANGE =      Colour(1.0f, 0.6470588235294118f, 0.0f, 1.0f);
Colour Colour::YELLOW  =     Colour(1.0f, 1.0f, 0.0f, 1.0f);
Colour Colour::PINK =        Colour(1.0f, 0.0f, 1.0f, 1.0f);
Colour Colour::GREEN =       Colour(0.0f, 1.0f, 0.0f, 1.0f);
Colour Colour::BLUE  =       Colour(0.0f, 0.0f, 1.0f, 1.0f);
Colour Colour::LIGHT_BLUE =  Colour(0.0f, 1.0f, 1.0f, 1.0f);
Colour Colour::WHITE   =     Colour(1.0f, 1.0f, 1.0f, 1.0f);

Colour Colour::ARRAY_RGB[] = { Colour::RED, Colour::GREEN, Colour::BLUE };
Colour Colour::ARRAY_GREY[] = { Colour::GREY, Colour::LIGHT_GREY };
Colour Colour::ARRAY_BLUE[] = { Colour::BLUE, Colour::LIGHT_BLUE };
Colour Colour::ARRAY_SUNSET [] = { Colour::RED, Colour::ORANGE, Colour::YELLOW };

/***************************************************************************************************/

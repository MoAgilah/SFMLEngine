#pragma once

#include <Utilities/Defines.h>

#if USE_SFML

#include "../Resources/SFFont.h"
#include "../Resources/SFMusic.h"
#include "../Resources/SFSound.h"
#include "../Resources/SFShader.h"
#include "../Resources/SFTexture.h"

// Repeat the aliases here with complete types available
using ActiveFont = SFFont;
using ActiveMusic = SFMusic;
using ActiveSound = SFSound;
using ActiveShader = SFShader;
using ActiveTexture = SFTexture;

#endif

#include <memory>

#include <Utilities/ActiveTypesFwd.h>
#include "ActiveTypes.h"

std::unique_ptr<IFont>    MakeActiveFont() { return std::make_unique<ActiveFont>(); }
std::unique_ptr<IMusic>   MakeActiveMusic() { return std::make_unique<ActiveMusic>(); }
std::unique_ptr<ISound>   MakeActiveSound() { return std::make_unique<ActiveSound>(); }
std::unique_ptr<IShader>  MakeActiveShader() { return std::make_unique<ActiveShader>(); }
std::unique_ptr<ITexture> MakeActiveTexture() { return std::make_unique<ActiveTexture>(); }


#pragma once

#include <Engine/Interface/Input/IKeyConverter.h>

class SFKeyConverter : public IKeyConverter
{
public:
    KeyCode ConvertFromPlatform(int platformCode) const override;
};
#pragma once

#include <Engine/Interface/Collisions/ITile.h>
#include <Utilities/Vector.h>
#include <string>

class SFTile : public ITile
{
public:
	SFTile(int gX, int gY);
	SFTile(int gX, int gY, const std::string& fontName);

	void Render(IRenderer* renderer) override;
	void ResolveCollision(IDynamicGameObject* obj, float tFirst, float tLast) override;

	void SetPosition(const Vector2f& pos) override;

	void SetFillColour(Colour col) override;
	void SetOutlineColour(Colour col) override;

protected:

	bool ResolveObjectToSlopeTop(IDynamicGameObject* obj) override;
	bool ResolveObjectToSlopeIncline(IDynamicGameObject* obj, int start, int end) override;
	bool ResolveObjectToSlopeDecline(IDynamicGameObject* obj, int start, int end) override;
	void ResolveObjectToEdgeBounds(IDynamicGameObject* obj) override;
};
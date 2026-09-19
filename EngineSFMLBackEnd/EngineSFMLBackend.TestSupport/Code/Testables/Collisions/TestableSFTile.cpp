#include "TestableSFTile.h"

void TestableSFTile::ForTestingMakeVolumeNull()
{
	m_aabb.reset();
}

std::shared_ptr<IDrawable> TestableSFTile::GetTextObject()
{
	return m_text;
}

void TestableSFTile::CallOriginalResolveObjectToBoxTop(IDynamicGameObject* obj, float tFirst, float tLast)
{
	SFTile::ResolveObjectToBoxTop(obj, tFirst, tLast);
}

void TestableSFTile::CallOriginalResolveObjectToBoxBottom(IDynamicGameObject* obj, float tFirst, float tLast)
{
	SFTile::ResolveObjectToBoxBottom(obj, tFirst, tLast);
}

void TestableSFTile::CallOriginalResolveObjectToBoxHorizontally(IDynamicGameObject* obj, float tFirst, float tLast)
{
	SFTile::ResolveObjectToBoxHorizontally(obj, tFirst, tLast);
}

bool TestableSFTile::CallOriginalResolveObjectToSlopeTop(IDynamicGameObject* obj, float tFirst, float tLast)
{
	return SFTile::ResolveObjectToSlopeTop(obj, tFirst, tLast);
}

bool TestableSFTile::CallOriginalResolveObjectToSlopeIncline(IDynamicGameObject* obj, int start, int end, float tFirst, float tLast)
{
	return SFTile::ResolveObjectToSlopeIncline(obj, start, end, tFirst, tLast);
}

bool TestableSFTile::CallOriginalResolveObjectToSlopeDecline(IDynamicGameObject* obj, int start, int end, float tFirst, float tLast)
{
	return SFTile::ResolveObjectToSlopeDecline(obj, start, end, tFirst, tLast);
}

void TestableSFTile::CallOriginalResolveObjectToEdgeBounds(IDynamicGameObject* obj)
{
	SFTile::ResolveObjectToEdgeBounds(obj);
}

void TestableSFTile::ResolveObjectToBoxTop(IDynamicGameObject* obj, float tFirst, float tLast)
{
	boxTopCalled = true;
}

void TestableSFTile::ResolveObjectToBoxBottom(IDynamicGameObject* obj, float tFirst, float tLast)
{
	boxBottomCalled = true;
}

void TestableSFTile::ResolveObjectToBoxHorizontally(IDynamicGameObject* obj, float tFirst, float tLast)
{
	boxHorizontalCalled = true;
}

bool TestableSFTile::ResolveObjectToSlopeTop(IDynamicGameObject* obj, float tFirst, float tLast)
{
	slopeTopCalled = true;
	return slopeTopResult;
}

bool TestableSFTile::ResolveObjectToSlopeIncline(IDynamicGameObject* obj, int start, int end, float tFirst, float tLast)
{
	slopeInclineCalled = true;
	return slopeInclineResult;
}

bool TestableSFTile::ResolveObjectToSlopeDecline(IDynamicGameObject* obj, int start, int end, float tFirst, float tLast)
{
	slopeDeclineCalled = true;
	return slopeDeclineResult;
}

void TestableSFTile::ResolveObjectToEdgeBounds(IDynamicGameObject* obj)
{
	edgeBoundsCalled = true;
}

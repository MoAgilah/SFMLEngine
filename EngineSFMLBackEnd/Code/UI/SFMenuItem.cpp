#include "SFMenuItem.h"

#include "../Drawables/SFShape.h"
#include <Utilities/Guards.h>

SFMenuItem::SFMenuItem(const Vector2f& menuSize, float outlineThickness)
{
	m_cellSpace = std::make_shared<SFRect>(menuSize, Vector2f());

	if (!CheckNotNull(m_cellSpace.get(), "Invalid Pointer 'm_cellSpace'"))
		throw std::invalid_argument("SFMenuItem requires a valid SFRect for m_cellSpace");

	auto* rect = static_cast<SFRect*>(m_cellSpace.get());

	rect->SetScale({ 1.f, 1.f });
	rect->SetOrigin(rect->GetSize() / 2.f);
	rect->SetOutlineThickness(outlineThickness);
	rect->SetOutlineColour(Colour::Green);
}

Vector2f SFMenuItem::GetPosition() const
{
	if (!CheckNotNull(m_cellSpace.get(), "Invalid Pointer 'm_cellSpace'"))
		return Vector2f();

	auto rect = static_cast<SFRect*>(m_cellSpace.get());

	return rect->GetPosition();
}

void SFMenuItem::SetPosition(const Vector2f& position)
{
	if (!CheckNotNull(m_cellSpace.get(), "Invalid Pointer 'm_cellSpace'"))
		return;

	auto rect = static_cast<SFRect*>(m_cellSpace.get());

	rect->SetPosition(position);
}

Vector2f SFMenuItem::GetOrigin() const
{
	if (!CheckNotNull(m_cellSpace.get(), "Invalid Pointer 'm_cellSpace'"))
		return Vector2f();

	auto rect = static_cast<SFRect*>(m_cellSpace.get());

	return rect->GetOrigin();
}

Vector2f SFMenuItem::GetSize() const
{
	if (!CheckNotNull(m_cellSpace.get(), "Invalid Pointer 'm_cellSpace'"))
		return Vector2f();

	auto rect = static_cast<SFRect*>(m_cellSpace.get());

	return rect->GetSize();
}
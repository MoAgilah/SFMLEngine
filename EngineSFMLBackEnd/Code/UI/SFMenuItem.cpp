#include "SFMenuItem.h"

#include "../Drawables/SFShape.h"
#include <Utilities/Guards.h>

SFMenuItem::SFMenuItem(const Vector2f& menuSize, float outlineThickness)
{
	m_cellSpace = std::make_shared<SFRect>(menuSize, Vector2f());

	if (!CheckNotNull(m_cellSpace.get(), "Invalid Pointer 'm_cellSpace'"))
		throw std::invalid_argument("SFMenu requires a valid SFRect for m_cellSpace");

	auto rect = static_cast<SFRect*>(m_cellSpace.get());
	if (!CheckNotNull(rect, "Invalid Pointer 'rect'"))
		throw std::invalid_argument("SFMenu requires a valid SFRect");

	rect->SetScale({ 1.f, 1.f });
	rect->SetOrigin(Vector2f(rect->GetSize()) / 2.f);
	rect->SetOutlineThickness(outlineThickness);
	rect->SetOutlineColour(Colour::Green);
}

Vector2f SFMenuItem::GetPosition() const
{
	if (!CheckNotNull(m_cellSpace.get(), "Invalid Pointer 'm_cellSpace'"))
		return Vector2f();

	auto rect = static_cast<SFRect*>(m_cellSpace.get());
	if (!CheckNotNull(rect, "Invalid Pointer 'rect'"))
		return Vector2f();

	return rect->GetPosition();
}

void SFMenuItem::SetPosition(const Vector2f& position)
{
	if (!CheckNotNull(m_cellSpace.get(), "Invalid Pointer 'm_cellSpace'"))
		return;

	auto rect = static_cast<SFRect*>(m_cellSpace.get());
	if (!CheckNotNull(rect, "Invalid Pointer 'rect'"))
		return;

	rect->SetPosition(position);
}

Vector2f SFMenuItem::GetOrigin() const
{
	if (!CheckNotNull(m_cellSpace.get(), "Invalid Pointer 'm_cellSpace'"))
		return Vector2f();

	auto rect = static_cast<SFRect*>(m_cellSpace.get());
	if (!CheckNotNull(rect, "Invalid Pointer 'rect'"))
		return Vector2f();

	return rect->GetOrigin();
}

Vector2f SFMenuItem::GetSize() const
{
	if (!CheckNotNull(m_cellSpace.get(), "Invalid Pointer 'm_cellSpace'"))
		return Vector2f();

	auto rect = static_cast<SFRect*>(m_cellSpace.get());
	if (!CheckNotNull(rect, "Invalid Pointer 'rect'"))
		return Vector2f();

	return rect->GetSize();
}

IText* SFMenuItem::AddTextElement(std::shared_ptr<IText> text)
{
	if (!CheckNotNull(text.get(), "Invalid Pointer 'text'"))
		return nullptr;

	m_textElement = std::move(text);
	if (!CheckNotNull(m_textElement.get(), "Invalid Pointer 'm_textElement'"))
		return nullptr;

	return m_textElement.get();
}

ISprite* SFMenuItem::AddSpriteElement(std::shared_ptr<ISprite> spr)
{
	if (!CheckNotNull(spr.get(), "Invalid Pointer 'spr'"))
		return nullptr;

	m_spriteElement = std::move(spr);
	if (!CheckNotNull(m_spriteElement.get(), "Invalid Pointer 'm_spriteElement'"))
		return nullptr;

	return m_spriteElement.get();
}
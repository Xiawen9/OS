#include "Argument.h"

Argument::Argument(const char *name)
{
    m_name  = name;
    m_id    = 0;
    m_count = 0;
}

char Argument::getIdentifier() const
{
    return m_id;
}

Size Argument::getCount() const
{
    return m_count;
}

const String & Argument::getName() const
{
    return m_name;
}

const String & Argument::getDescription() const
{
    return m_description;
}

const String & Argument::getValue() const
{
    return m_value;
}

void Argument::setIdentifier(char id)
{
    m_id = id;
}

void Argument::setName(const char *name)
{
    m_name = name;
}

void Argument::setDescription(const char *description)
{
    m_description = description;
}

void Argument::setValue(const char *value)
{
    m_value = value;
}

void Argument::setCount(Size count)
{
    m_count = count;
}

bool Argument::operator == (const Argument & arg) const
{
    return arg.m_id == m_id;
}

bool Argument::operator != (const Argument & arg) const
{
    return arg.m_id != m_id;
}

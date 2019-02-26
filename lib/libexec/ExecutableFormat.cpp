#include <Macros.h>
#include "ExecutableFormat.h"
#include "ELF.h"

ExecutableFormat::ExecutableFormat(u8 *image, Size size)
{
    m_image = image;
    m_size  = size;
}

ExecutableFormat::~ExecutableFormat()
{
}

ExecutableFormat::Result ExecutableFormat::find(u8 *image, Size size, ExecutableFormat **fmt)
{
    return ELF::detect(image, size, fmt);
}

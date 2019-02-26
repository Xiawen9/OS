#include "Container.h"

Container::Container()
{
}

Container::~Container()
{
}

bool Container::isEmpty() const
{
<<<<<<< HEAD
    return count() == 0;
=======
	return count() == 0;
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
}

bool Container::reserve(Size size)
{
<<<<<<< HEAD
    if (this->size() > size)
        return true;

    return resize(size);
=======
	if(this->size() > size)
		return true;

	return resize(size);
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
}

bool Container::shrink(Size size)
{
<<<<<<< HEAD
    return resize(this->size() - size);
=======
	return resize(this->size() - size)
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
}

Size Container::squeeze()
{
<<<<<<< HEAD
    return size();
=======
	return size();
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
}

bool Container::resize(Size size)
{
<<<<<<< HEAD
    return false;
=======
	return false;
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
}

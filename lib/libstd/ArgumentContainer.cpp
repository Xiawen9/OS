#include "ArgumentContainer.h"

ArgumentContainer::ArgumentContainer()
{
}

ArgumentContainer::~ArgumentContainer()
{
    // cleanup flags
    for (HashIterator<String, Argument *> it(m_flags);
         it.hasCurrent();)
    {
        delete it.current();
        it.remove();
    }

    // cleanup positionals
    for (Size i = 0; i < m_positionals.count(); i++)
        delete m_positionals[i];
}

Vector<Argument *> & ArgumentContainer::getPositionals()
{
    return m_positionals;
}

HashTable<String, Argument *> & ArgumentContainer::getFlags()
{
    return m_flags;
}

const char * ArgumentContainer::get(const char *name) const
{
    // Search flag arguments
    const Argument * const *arg = m_flags.get(name);
    if (arg)
        return *(*arg)->getValue();

    // Search positional arguments
    for (Size i = 0; i < m_positionals.count(); i++)
    {
        const Argument *a = m_positionals[i];

        if (a->getName().equals(name))
            return *a->getValue();
    }
    return ZERO;
}

ArgumentContainer::Result ArgumentContainer::addPositional(Argument *arg)
{
    m_positionals.insert(arg);
    return Success;
}

ArgumentContainer::Result ArgumentContainer::addFlag(Argument *arg)
{
    m_flags.insert(arg->getName(), arg);
    return Success;
}

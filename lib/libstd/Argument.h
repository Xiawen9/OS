#ifndef __LIBSTD_ARGUMENT_H
#define __LIBSTD_ARGUMENT_H

#include "Types.h"
#include "String.h"

class Argument
{
  public:

    Argument(const char *name);

    char getIdentifier() const;

    const String & getName() const;

    const String & getDescription() const;

    const String & getValue() const;

    Size getCount() const;

    void setIdentifier(char id);

    void setName(const char *name);

    void setDescription(const char *description);

    void setValue(const char *value);

    void setCount(Size count);

    bool operator == (const Argument & arg) const;

    bool operator != (const Argument & arg) const;

  private:

    char m_id;
    
    String m_name;

    String m_description;

    String m_value;

    Size m_count;

};

#endif /* __LIBSTD_ARGUMENT_H */

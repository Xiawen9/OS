#ifndef __LIBSTD_CALLBACK_H
#define __LIBSTD_CALLBACK_H

#include "Types.h"

<<<<<<< HEAD
class CallbackFunction
=======
class CallBackFunction
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
{
  public:
    virtual void execute(void *parameter) = 0;
};

/**
 * Abstraction for providing a callback function to a object instance.
 */
<<<<<<< HEAD
template <class Base, class ParamType> class Callback : public CallbackFunction
{
  private:

    /** Callback function prototype */
=======
template <class Base, class ParamType> class Callback :
public CallbackFunction
{
  private:

    /** Callback function prototype. */
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
    typedef void (Base::*Function)(ParamType *param);

  public:

    /**
     * Constructor
     */
    Callback(Base *object, Function func)
    {
<<<<<<< HEAD
        m_object   = object;
        m_function = func;
    }

    virtual void execute(void *parameter)
    {
        executeOnObject((ParamType *) parameter);
    }

  private:

    /**
     * Execute the callback.
     *
=======
	m_object = object;
	m_function = func;
    }

    virtual void execute(coid *parameter)
    {
	executeOnObject((ParamType *) parameter);
    }

  private:
    /**
     * Execute the callback.
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
     * @param parameter One parameter which is passed to the callback function.
     */
    virtual void executeOnObject(ParamType *parameter)
    {
<<<<<<< HEAD
        (m_object->*m_function)(parameter);
    }


    /** Object instance */
    Base *m_object;

    /** Function pointer */
=======
	(m_object->*m_function)(parameter);
    }

    /** Object instance. */
    Base *m_object;

    /** Function pointer. */
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
    Function m_function;
};

#endif /* __LIBSTD_CALLBACK_H */

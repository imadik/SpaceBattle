#pragma once

#include <exception>
#include <string>

namespace SpaceBattle
{
    enum class ExceptionType : unsigned int
    {
        FIRST,
        SECOND,
        FUEL,
        MACRO_COMMAND,
    };

    class IException: public std::exception
    {
    public:
        /** Destructor.
         * Virtual to allow for subclassing.
         */
        virtual ~IException() noexcept {}

        /** Returns a pointer to the (constant) error description.
         *  @return A pointer to a const char*. The underlying memory
         *          is in posession of the Exception object. Callers must
         *          not attempt to free the memory.
         */
        virtual const char* what() const noexcept 
        {
            return mMessage.c_str();
        }

        virtual ExceptionType getType() const = 0;

        int count() const
        {
            return mCount;
        }

        void repeat()
        {
            mCount++;
        }

    protected:
        /** Error message.
         */
        std::string mMessage{"SpaceBattle exception"};
        int mCount{0};
    };
}

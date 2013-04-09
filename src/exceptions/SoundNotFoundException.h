#ifndef SOUNDNOTFOUNDEXCEPTION_H
#define SOUNDNOTFOUNDEXCEPTION_H

#include <exception>
#include <sstream>

class SoundNotFoundException : public std::exception
{
    public:
        // In the constructor we create the message
            SoundNotFoundException(std::string soundName)
            {
                std::ostringstream oss;
                oss << "The sound/song " << soundName << " cannot be loaded. Make sure it's in the data folder.";
                this->m_msg = oss.str();

            }
        // Virtual destructor
            virtual ~SoundNotFoundException() throw()
            {
            }

        // Return the message so we can display it
            virtual const char * what() const throw()
            {
                return this->m_msg.c_str();
            }

    private:
        std::string m_msg;
};

#endif // SOUNDNOTFOUNDEXCEPTION_H

#pragma once

#include "Config.h"
#include <vector>

namespace rbp
{

/*! \brief Interface for objects that can be serialized
 *
 */
class RBP_DLL Serializable {

public:

    /*! \brief Returns an array representation of an object
     *
     * \return The Buffer of data
     */
    virtual std::vector<unsigned char> Serialize()=0;

private:

};

} /* rbp */


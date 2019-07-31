#include "object_manufacture.h"
#include "person.h"
#include "house.h"

using namespace Game;

void Object_manufacture::get_object(Object_type type, Object** object)
{
    switch (type) {
        case Object_type::HOUSE:
            (*object) = new House();
            break;
        case Object_type::PERSON:
            (*object) = new Person();
            break;
        default:
            (*object) = new Object();
            break;
    }
}

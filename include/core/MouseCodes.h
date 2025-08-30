//
// Created by ChiroYuki on 26/07/2025.
//

#ifndef PIXLENGINE_MOUSECODES_H
#define PIXLENGINE_MOUSECODES_H

#include <cstdint>

using MouseCode = uint16_t;

namespace Mouse {
    enum : MouseCode {
        Button0 = 0,
        Button1 = 1,
        Button2 = 2,
        Button3 = 3,
        Button4 = 4,
        Button5 = 5,
        Button6 = 6,
        Button7 = 7,

        Last = Button7,
        Left = Button0,
        Right = Button1,
        Middle = Button2
    };
}

#endif //PIXLENGINE_MOUSECODES_H

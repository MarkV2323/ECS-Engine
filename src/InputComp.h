#pragma once

namespace ecse {
    class InputComp {
    public:
        bool up {false};
        bool left {false};
        bool right {false};
        bool down {false};
        bool shoot {false};
        InputComp() {};
        ~InputComp() {};
    };
}
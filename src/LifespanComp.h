#pragma once

namespace ecse {
    class LifespanComp {
    public:
        int remaining {0};
        int total {0};
        LifespanComp() {};
        LifespanComp(int total) : remaining(total), total(total) {};
        ~LifespanComp() {};
    };
}
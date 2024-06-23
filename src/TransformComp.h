#pragma once

#include <SFML/System/Vector2.hpp>

namespace ecse {
    class TransformComp {
    public:
        sf::Vector2f pos {0.0, 0.0};
        sf::Vector2f speed {0.0, 0.0};
        sf::Vector2f scale {0.0, 0.0};
        double angle {0.0};

        TransformComp() : pos(sf::Vector2f(0.0, 0.0)), 
            speed(sf::Vector2f(0.0, 0.0)), 
            scale(sf::Vector2f(0.0, 0.0)), 
            angle(0.0) {}
        TransformComp(sf::Vector2f& p, sf::Vector2f& sp, sf::Vector2f& sc, double a) : 
            pos(p), 
            speed(sp), 
            scale(sc), 
            angle(a) {}
        ~TransformComp() {}
    };
}
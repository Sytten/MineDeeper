#ifndef FILTER_H
#define FILTER_H

#include <SFML/Graphics.hpp>

class Filter
{
    public:
        Filter(sf::Color color, float alphaChange, sf::Rect<float> filterRect, bool toColor = true, float filterDelay = 0.01f);

        // To be able to do the modifications
            void runFilter();

        // Getters
            float getAlpha() const { return m_alpha; }
            float getAlphaChange() const { return m_alphaChange; }
            sf::RectangleShape const& getFilter() const { return m_filter; }
            bool isActive() { return m_active; }

        // Setters
            void setFilterDelay(float delay) { m_filterDelay = delay; } // To change the delay between each changes
            void setAlphaChange(float alphaChange) { m_alphaChange = alphaChange; } // To change the alpha change each we reach the delay
            void setActive(bool active = true) { m_active = active; } // So we can stop the filter
            void setToColor (bool toColor = true);
            void setColor(sf::Color color);
            void setAlpha(float alpha); // So we can start we a certain filter

        // Change position and size of the filter
            void changePosition(sf::Vector2f position) { m_filter.setPosition(position); }
            void changeSize(sf::Vector2f size) { m_filter.setSize(size); }

    private:
        sf::RectangleShape m_filter;
        sf::Clock m_filterClock;
        float m_filterDelay;

        float m_alpha;
        float m_alphaChange; //Number of alpha decrease or increase at each frame (1 : Slow, 2.5 : Medium, 5 : Fast) if the user don't change the delay
        sf::Color m_color;

        bool m_active;
        bool m_toColor; // If set to false, we'll go from this color to the screen color
};

#endif // FILTER_H

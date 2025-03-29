#ifndef UMJAHO_TEXT_H
#define UMJAHO_TEXT_H
#include "engine/scenes/SceneElement.h"
#include "string"

class Text: public SceneElement{
public:
    Text(double x, double y, double width = 50, double height = 50, double angle = 0, double zIndex = 0, const std::string& text = "");
    std::string content;

    void setContent(const std::string& text);
};

#endif //UMJAHO_TEXT_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Pen {
public:
    string color;
    float thickness;
    string type;

    Pen(const string& color = "black", float thickness = 1.0, const string& type = "solid")
        : color(color), thickness(thickness), type(type) {}

    virtual void Draw() const {
        cout << "Pen: " << color << ", thickness: " << thickness << ", type: " << type << endl;
    }
};

class Brush {
public:
    string color;

    Brush(const string& color = "transparent") : color(color) {}

    virtual void Fill() const {
        cout << "Brush color: " << color << endl;
    }
};

class SolidBrush : public Brush {
public:
    using Brush::Brush;
};

class GradientBrush : public Brush {
public:
    vector<string> colors;

    GradientBrush(const vector<string>& colors)
        : Brush(), colors(colors) {}

    void Fill() const override {
        cout << "GradientBrush with colors: ";
        for (const auto& c : colors) {
            cout << c << " ";
        }
        cout << endl;
    }
};

class HatchBrush : public Brush {
public:
    string secondaryColor;
    string patternType;

    HatchBrush(const string& color, const string& secondaryColor, const string& patternType)
        : Brush(color), secondaryColor(secondaryColor), patternType(patternType) {}

    void Fill() const override {
        cout << "HatchBrush with primary color: " << color
            << ", secondary color: " << secondaryColor
            << ", pattern type: " << patternType << endl;
    }
};

class TextureBrush : public Brush {
public:
    string texturePath;

    TextureBrush(const string& texturePath)
        : Brush(), texturePath(texturePath) {}

    void Fill() const override {
        cout << "TextureBrush with texture path: " << texturePath << endl;
    }
};

class VisualBrush : public Brush {
public:
    string elementId;

    VisualBrush(const string& elementId)
        : Brush(), elementId(elementId) {}

    void Fill() const override {
        cout << "VisualBrush with element ID: " << elementId << endl;
    }
};

class LinearGradientBrush : public GradientBrush {
public:
    LinearGradientBrush(const vector<string>& colors)
        : GradientBrush(colors) {}
    void Fill() const override {
        cout << "LinearGradientBrush with colors: ";
        for (const auto& c : colors) {
            cout << c << " ";
        }
        cout << endl;
    }
};

class RadialGradientBrush : public GradientBrush {
public:
    RadialGradientBrush(const vector<string>& colors)
        : GradientBrush(colors) {}

    void Fill() const override {
        cout << "RadialGradientBrush with colors: ";
        for (const auto& c : colors) {
            cout << c << " ";
        }
        cout << endl;
    }
};

class Geometry {
public:
    Pen* pen;
    Brush* brush;

    Geometry(Pen* pen = nullptr, Brush* brush = nullptr) : pen(pen), brush(brush) {}

    virtual void Draw() const = 0;
};


class Rectangle : public Geometry {
public:
    float width, height;

    Rectangle(float width, float height, Pen* pen = nullptr, Brush* brush = nullptr)
        : Geometry(pen, brush), width(width), height(height) {}

    void Draw() const override {
        if (pen) pen->Draw();
        if (brush) brush->Fill();
        cout << "Rectangle: " << width << "x" << height << endl;
    }
};

class Ellipse : public Geometry {
public:
    float radiusX, radiusY;

    Ellipse(float radiusX, float radiusY, Pen* pen = nullptr, Brush* brush = nullptr)
        : Geometry(pen, brush), radiusX(radiusX), radiusY(radiusY) {}

    void Draw() const override {
        if (pen) pen->Draw();
        if (brush) brush->Fill();
        cout << "Ellipse: radiusX=" << radiusX << ", radiusY=" << radiusY << endl;
    }
};

class Polyline : public Geometry {
public:
    vector<pair<float, float>> points;

    Polyline(const vector<pair<float, float>>& points, Pen* pen = nullptr, Brush* brush = nullptr)
        : Geometry(pen, brush), points(points) {}

    void Draw() const override {
        if (pen) pen->Draw();
        if (brush) brush->Fill();
        cout << "Polyline with points: ";
        for (const auto& p : points) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    }
};

class Font {
public:
    string fontFamily;
    int size;
    bool bold;
    bool italic;
    bool underline;
    string color;

    Font(const string& fontFamily = "Arial", int size = 12, bool bold = false,
        bool italic = false, bool underline = false, const string& color = "black")
        : fontFamily(fontFamily), size(size), bold(bold), italic(italic), underline(underline), color(color) {}

    void Print() const {
        cout << "Font: " << fontFamily << ", size: " << size
            << ", bold: " << (bold ? "yes" : "no")
            << ", italic: " << (italic ? "yes" : "no")
            << ", underline: " << (underline ? "yes" : "no")
            << ", color: " << color << endl;
    }
};

class Button : public Rectangle {
public:
    string text;
    Font font;

    Button(float width, float height, const string& text, const Font& font,
        Pen* pen = nullptr, Brush* brush = nullptr)
        : Rectangle(width, height, pen, brush), text(text), font(font) {}

    void Draw() const override {
        Rectangle::Draw();
        cout << "Button text: " << text << endl;
        font.Print();
    }
};

int main() {
    Pen pen("red", 2.0, "dashed");
    SolidBrush brush("blue");
    Font font("Verdana", 16, true, false, true, "white");
    Button button(200, 50, "Click Me", font, &pen, &brush);

    button.Draw();

    return 0;
}
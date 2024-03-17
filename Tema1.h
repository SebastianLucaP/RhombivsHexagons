#pragma once

#include <iostream>
#include <vector>
#include "components/simple_scene.h"

namespace m1
{
    struct Hitbox {
    glm::vec2 A, B, C, D;
    };

   struct Square {
    Mesh *mesh;
    std::string name;
    glm::vec3 center;
    float length;
    glm::vec3 color;
    bool fill;
    Square(){};
    Square(const std::string name, glm::vec3 center, float length, glm::vec3 color, bool fill) :
        name(name),
        center(center),
        length(length),
        color(color),
        fill(fill)
    {
        std::vector<VertexFormat> vertices =
        {
            VertexFormat(center + glm::vec3(length * -0.5, length * -0.5, 0), color),
            VertexFormat(center + glm::vec3(length * 0.5, length * -0.5, 0), color),
            VertexFormat(center + glm::vec3(length * 0.5, length * 0.5, 0), color),
            VertexFormat(center + glm::vec3(length * -0.5, length * 0.5, 0), color)
        };
        std::vector<unsigned int> indices = { 0, 1, 2, 3 };

        mesh = new Mesh(name);
        if (!fill) {
            mesh->SetDrawMode(GL_LINE_LOOP);
        } else {
        indices.push_back(0);
        indices.push_back(2);
    }
        mesh->InitFromData(vertices, indices);
    }
        Hitbox getHitboxCoord(glm::vec2(newCenter)) {
        Hitbox hitbox;
        hitbox.A = newCenter + glm::vec2(length * -0.5, length * -0.5);
        hitbox.B = newCenter + glm::vec2(length * 0.5, length * -0.5);
        hitbox.C = newCenter + glm::vec2(length * 0.5, length * 0.5);
        hitbox.D = newCenter + glm::vec2(length * -0.5, length * 0.5);
        return hitbox;
        }
    };

    struct Cross {
    Mesh *mesh;
    std::string name;
    glm::vec3 center;
    float length;
    glm::vec3 color;
    Cross(){};
    Cross(const std::string name, glm::vec3 center, float length, glm::vec3 color) :
        name(name),
        center(center),
        length(length),
        color(color)
    {
        std::vector<VertexFormat> vertices =
        {
            VertexFormat(center + glm::vec3(length * -0.5, length * -0.1666666666, 0), color), //A || 0
            VertexFormat(center + glm::vec3(length * -0.1666666666, length * -0.5, 0), color), //C || 1
            VertexFormat(center + glm::vec3(length * 0.1666666666, length * -0.5, 0), color), //D || 2
            VertexFormat(center + glm::vec3(length * 0.5, length * -0.1666666666, 0), color), //F || 3
            VertexFormat(center + glm::vec3(length * 0.5, length * 0.1666666666, 0), color), //G || 4
            VertexFormat(center + glm::vec3(length * 0.1666666666, length * 0.5, 0), color), //I || 5
            VertexFormat(center + glm::vec3(length * -0.1666666666, length * 0.5, 0), color), //J || 6
            VertexFormat(center + glm::vec3(length * -0.5, length * 0.1666666666, 0), color) //L || 7
        };
        std::vector<unsigned int> indices = {0, 3, 4, 0, 4, 7, 6, 1, 2, 6, 2, 5};
        mesh = new Mesh(name);
        mesh->InitFromData(vertices, indices);
    }
    float getCrossXPlusLength(float X) {
        return X + length * 0.5;
    }
    };

   struct Hexagon {
    Mesh *mesh;
    std::string name;
    glm::vec3 center;
    float length;
    glm::vec3 outerColor, innerColor;
    int type;
    Hexagon(){};
    Hexagon(const std::string name, glm::vec3 center, float length, int type) :
        name(name),
        center(center),
        length(length),
        type(type)
    {
        switch(type) {
            case(1) : 
                outerColor = glm::vec3(0, 0.4, 0.7);
                innerColor = glm::vec3(0.7, 0.1, 0);
                break;
            case(2) : 
                outerColor = glm::vec3(0.7, 0.7, 0);
                innerColor = glm::vec3(0.7, 0, 0.7);
                break;
            case(3) : 
                outerColor = glm::vec3(0.6, 0, 0.8);
                innerColor = glm::vec3(0.4, 0.6, 0.2);
                break;
            case(4):
                outerColor = glm::vec3(1, 1, 1);
                innerColor = glm::vec3(0, 0, 0);
                break;
            default:
                outerColor = glm::vec3(0.8, 0.8, 0.8);
                innerColor = glm::vec3(0.8, 0.8, 0.8);
                break;


        }
        std::vector<VertexFormat> vertices =
        {
            VertexFormat(center + glm::vec3(length * -0.5, length * -0.8660254037844, 0), outerColor), //0
            VertexFormat(center + glm::vec3(length * 0.5, length * -0.8660254037844, 0), outerColor), //1
            VertexFormat(center + glm::vec3(length, 0, 0), outerColor), //2
            VertexFormat(center + glm::vec3(length * 0.5, length * 0.8660254037844, 0), outerColor), //3
            VertexFormat(center + glm::vec3(length * -0.5, length * +0.8660254037844, 0), outerColor), //4
            VertexFormat(center + glm::vec3(-length, 0, 0), outerColor), //5
            VertexFormat(center, outerColor), //6

            VertexFormat(center + glm::vec3(length * -0.5 * 0.7, length * -0.8660254037844 * 0.7, 1), innerColor), //7
            VertexFormat(center + glm::vec3(length * 0.5 * 0.7, length * -0.8660254037844 * 0.7, 1), innerColor), //8
            VertexFormat(center + glm::vec3(length * 0.7, 0, 1), innerColor), //9
            VertexFormat(center + glm::vec3(length * 0.5 * 0.7, length * 0.8660254037844 * 0.7, 1), innerColor), //10
            VertexFormat(center + glm::vec3(length * -0.5 * 0.7, length * +0.8660254037844 * 0.7, 1), innerColor), //11
            VertexFormat(center + glm::vec3(-length * 0.7, 0, 1), innerColor), //12
            VertexFormat(center, innerColor) //13
        };
        std::vector<unsigned int> indices = {0, 1, 6, 1, 2, 6, 2, 3, 6, 3, 4, 6, 4, 5, 6, 5, 0, 6,
                                             7, 8, 13, 8, 9, 13, 9, 10, 13, 10, 11, 13, 11, 12, 13, 12, 7, 13};
        mesh = new Mesh(name);
        mesh->InitFromData(vertices, indices);
    }
    float getHexXMinusLength(float X) {
        return X - length;
    }
    };
   struct Star {
    Mesh *mesh;
    std::string name;
    glm::vec3 center;
    float length;
    glm::vec3 color;
    Star(){};
    Star(const std::string name, glm::vec3 center, float length, glm::vec3 color) :
        name(name),
        center(center),
        length(length),
        color(color)
    {
        std::vector<VertexFormat> vertices =
        {
            VertexFormat(center + glm::vec3(length * 0.5 , length * 0.6881909602356, 0), color), //0 | A
            VertexFormat(center + glm::vec3(length * -0.5 , length * 0.6881909602356, 0), color), //1 | B
            VertexFormat(center + glm::vec3(length * -0.8090169943749 , length * -0.2628655560596, 0), color), //2 | C
            VertexFormat(center + glm::vec3(0 , length * -0.850650808352, 0), color), //3 | D
            VertexFormat(center + glm::vec3(length * 0.8090169943749 , length * -0.2628655560596, 0), color), //4 | E
            VertexFormat(center + glm::vec3(0, length * 2.2270327288232, 0), color), //5 | G
            VertexFormat(center + glm::vec3(length * -2.1180339887499 , length * 0.6881909602356, 0), color), //6 | H
            VertexFormat(center + glm::vec3(length * -1.3090169943749 , length * -1.8017073246472, 0), color), //7 | I
            VertexFormat(center + glm::vec3(length * 1.3090169943749 , length * -1.8017073246472, 0), color), //8 | J
            VertexFormat(center + glm::vec3(length * 2.1180339887499 , length * 0.6881909602356, 0), color), //9 | K
            
            //VertexFormat(center + glm::vec3(length * -2.1180339887499, length * -1.8017073246472, 0), glm::vec3(1, 1, 1)), //A
            //VertexFormat(center + glm::vec3(length * 2.1180339887499, length * -1.8017073246472, 0), glm::vec3(1, 1, 1)), //B
            //VertexFormat(center + glm::vec3(length * 2.1180339887499, length * 2.2270327288232, 0), glm::vec3(1, 1, 1)), //C
            //VertexFormat(center + glm::vec3(length * -2.1180339887499, length * 2.2270327288232, 0), glm::vec3(1, 1, 1)), //D
                
        };
        std::vector<unsigned int> indices = {0, 2, 8, 1, 3, 9, 2, 4, 5, 3, 0, 6, 4, 1, 7};// 10, 11, 12, 13, 10, 12}; 
        mesh = new Mesh(name);
        mesh->InitFromData(vertices, indices);
    }
    Hitbox getHitboxCoord(glm::vec2(newCenter)) {
        Hitbox hitbox;
        hitbox.A = newCenter + glm::vec2(length * -2.1180339887499, length * -1.8017073246472);
        hitbox.B = newCenter + glm::vec2(length * 2.1180339887499, length * -1.8017073246472);
        hitbox.C = newCenter + glm::vec2(length * 2.1180339887499, length * 2.2270327288232);
        hitbox.D = newCenter + glm::vec2(length * -2.1180339887499, length * 2.2270327288232);
        return hitbox;
    }
    float getPjXPlusLength(float X) {
        return X + length * 2.2270327288232;
    }
    };
   struct Rhombus {
    Mesh *mesh;
    std::string name;
    glm::vec3 center;
    float length;
    glm::vec3 color;
    int type;
    Rhombus(){};
    Rhombus(const std::string name, glm::vec3 center, float length, int type) :
        name(name),
        center(center),
        length(length),
        type(type)
    {
        switch(type) {
            case(1): 
                color = glm::vec3(0, 0.4, 0.7);
                break;
            case(2): 
                color = glm::vec3(0.7, 0.7, 0);
                break;
            case(3): 
                color = glm::vec3(0.6, 0, 0.8);
                break;
            case(4):
                color = glm::vec3(1, 1, 1);
                break;
            default:
                color = glm::vec3(0.8, 0.8, 0.8);
                break;
        }
        std::vector<VertexFormat> vertices =
        {
            VertexFormat(center + glm::vec3(length * -0.25 , 0, 0), color), //0
            VertexFormat(center + glm::vec3(0 , length * -0.5, 0), color), //1
            VertexFormat(center + glm::vec3(length * 0.25 , 0, 0), color), //2
            VertexFormat(center + glm::vec3(0 ,length * 0.5, 0), color), //3
            VertexFormat(center + glm::vec3(0 , length * -0.083333, 0), color), //4
            VertexFormat(center + glm::vec3(length * 0.6 , length * -0.083333, 0), color), //5
            VertexFormat(center + glm::vec3(length * 0.6 , length * 0.083333, 0), color), //6  
            VertexFormat(center + glm::vec3(0 , length * 0.083333, 0), color), //7
        };
        std::vector<unsigned int> indices = {0, 1, 2, 3, 0, 2, 4, 5, 6, 7, 4, 6}; 
        mesh = new Mesh(name);
        mesh->InitFromData(vertices, indices);
    }
    float getRhXPlusLength(float X) {
        return X + length * 0.6;
    }
    float getRhXMinusLength(float X) {
        return X - length * 0.6;
    }
    };
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        glm::mat3 modelMatrix;
        float x, y;
        Square* squares;
        int lives;
        Star* guiStars;

        std::vector<glm::mat3> cStarMatrix, invStarMatrix, pjStarMatrix;
        std::vector<float> cStarTranslateX, cStarTranslateY, pjStarTranslateX, pjStarPosX, pjStarPosY ,pjStarAngularStep;
        float invStarTranslateX, invStarTranslateY;
        float starTime;
        std::vector<float>deleteTime;
        int stars;
        int invStars;
        int pjStars;
        std::vector<Hitbox> starHitbox;
        Star collectStar;
        Star collectedStar;
        Star pjS1, pjS2, pjS3, pjS4;
        std::vector<float> pjTime;
        std::vector<int> pjStarColor;

        Rhombus* staticRhombi;

        Hexagon h1, h2, h3, h4;
        std::vector<glm::mat3> hexMatrix;
        std::vector<float> hexTranslateX, hexTranslateY, hexScale;
        std::vector<int> hexLife;
        int hexes; 
        float hexTime;
        int hexRandTime;
        int randRow;
        std::vector<int> hexColor;
        glm::vec3 hexRandRowMatrix;

        Rhombus r1, r2, r3, r4;
        std::vector<glm::mat3> rhombiMatrix;
        std::vector<float> rhTranslateX, rhTranslateY;
        int rhombi;
        std::vector<int> rhColor;
        std::vector<Hitbox> selectRhombus;
        std::vector<int> occ;
        std::vector<Hitbox> gridHitbox;
        std::vector<int> rhPush;
        std::vector<Hitbox> rhPos;
        std::vector<int> rhTBD;
        std::vector<float> rhScale;
        std::vector<int> rhActive;

        Cross c1;
        std::vector<glm::mat3> crossMatrix;
        std::vector<float> crossTranslateX, crossTranslateY;
        int crosses;
        std::vector<int> crossAttack;
        std::vector<float> crossAngularStep;

    };
}   // namespace m1

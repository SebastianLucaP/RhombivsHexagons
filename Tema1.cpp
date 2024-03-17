#include "lab_m1/Tema1/Tema1.h"
#include <string>
#include <vector>
#include <iostream>
#include "lab_m1/Tema1/transform2D.h"

using namespace std;
using namespace m1;

Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    squares = new Square[17];
    staticRhombi = new Rhombus[4];
    guiStars = new Star[8];
    occ.assign(9, 0);

    x = 140;
    y = 70;
    for(int i = 0; i < 9; i++) {
        squares[i] = Square("square" + to_string(i), glm::vec3(x, y, 0), 100, glm::vec3(0, 0.5, 0), true);
        gridHitbox.push_back(squares[i].getHitboxCoord(glm::vec3(x, y, 0)));
        if(!((i + 1) % 3)) {
            x = 140;
            y+= 130;
        }
        else
            x += 130;
        AddMeshToList(squares[i].mesh);
    }
    squares[9] = Square("rectangle", glm::vec3(30, 200, 0), 100, glm::vec3(0.2, 0, 0), true);
    AddMeshToList(squares[9].mesh);
    x = 110;
    y = 650;
    for(int i = 0; i < 4; i++) {
        squares[i+10] = Square("outline_square" + to_string(i), glm::vec3(x, y, 0), 100, glm::vec3(0.6, 0.6, 0.6), false);
        selectRhombus.push_back(squares[i+10].getHitboxCoord(glm::vec3(x, y, 0)));
        x += 200;
        AddMeshToList(squares[i+10].mesh);
    }
    guiStars[0] = Star("guiStar0", glm::vec3(110, 575, 0), 7, glm::vec3(0.4, 0.4, 0.4));
    x = 290;
    for(int i = 1; i < 3; i++) {
        guiStars[i] = Star("guiStar" + to_string(i), glm::vec3(x, 575, 0), 7, glm::vec3(0.4, 0.4, 0.4));
        x += 40;
        AddMeshToList(guiStars[i].mesh);
    }
    x = 490;
    for(int i = 3; i < 5; i++) {
        guiStars[i] = Star("guiStar" + to_string(i), glm::vec3(x, 575, 0), 7, glm::vec3(0.4, 0.4, 0.4));
        x += 40;
        AddMeshToList(guiStars[i].mesh);
    }
     x = 674;
    for(int i = 5; i < 8; i++) {
        guiStars[i] = Star("guiStar" + to_string(i), glm::vec3(x, 575, 0), 7, glm::vec3(0.4, 0.4, 0.4));
        x += 36;
        AddMeshToList(guiStars[i].mesh);
    }
    AddMeshToList(guiStars[0].mesh);
    x = 100;
    y = 650;
    glm::vec4 rhombusColors = glm::vec4{1, 2, 3, 4};
    for(int i = 0; i < 4; i++) {
        staticRhombi[i] = Rhombus("rhombus" + to_string(i), glm::vec3(x, y, 0), 80, rhombusColors[i]);
        x += 200;
        AddMeshToList(staticRhombi[i].mesh);
    }
    lives = 3;
    x = 885;
    y = 650;
    for(int i = 0; i < 3; i++) {
        squares[i+14] = Square("life_square" + to_string(i), glm::vec3(x, y, 0), 80, glm::vec3(0.6, 0, 0.2), true);
        x += 130;
        AddMeshToList(squares[i+14].mesh);
    }
    invStarTranslateX = 857;
    invStarTranslateY = 580;
    collectedStar = Star("collectedStar", glm::vec3(0, 0, 0), 7, glm::vec3(0.4, 0.4, 0.4));
    AddMeshToList(collectedStar.mesh);
    collectStar = Star("collectStar", glm::vec3(0, 0, 4), 8, glm::vec3(0.8, 0.8, 0.8));
    AddMeshToList(collectStar.mesh);
    pjS1 = Star("pjS1", glm::vec3(0, 0, 1), 17.9611190632, glm::vec3(0, 0.4, 0.7));
    AddMeshToList(pjS1.mesh);
    pjS2 = Star("pjS2", glm::vec3(0, 0, 1), 17.9611190632, glm::vec3(0.7, 0.7, 0));
    AddMeshToList(pjS2.mesh);
    pjS3 = Star("pjS3", glm::vec3(0, 0, 1), 17.9611190632, glm::vec3(0.6, 0, 0.8));
    AddMeshToList(pjS3.mesh);    
    pjS4 = Star("pjS4", glm::vec3(0, 0, 1), 17.9611190632, glm::vec3(1, 1, 1));
    AddMeshToList(pjS4.mesh);

    starTime = 0;
    stars = 3;
    invStars = 0;
    pjStars = 0;
    for(int i = 0; i < stars; i++) {
        deleteTime.push_back(0);
        cStarTranslateX.push_back(rand() % (1268 - 12 + 1) + 12);
        cStarTranslateY.push_back(rand() % (708 - 12 + 1) + 12);
        cStarMatrix.push_back(transform2D::Translate(cStarTranslateX[i], cStarTranslateY[i]) * glm::mat3(1));
        starHitbox.push_back(collectStar.getHitboxCoord(glm::vec2(cStarTranslateX[i], cStarTranslateY[i])));
    }

    h1 = Hexagon("h1", glm::vec3(0, 0, 1), 40, 1);
    AddMeshToList(h1.mesh);
    h2 = Hexagon("h2", glm::vec3(0, 0, 1), 40, 2);
    AddMeshToList(h2.mesh);
    h3 = Hexagon("h3", glm::vec3(0, 0, 1), 40, 3);
    AddMeshToList(h3.mesh);
    h4 = Hexagon("h4", glm::vec3(0, 0, 1), 40, 4);
    AddMeshToList(h4.mesh);
    hexes = 0;
    hexTime = 0;
    hexRandTime = rand() % (10 - 4 + 1) + 4;
    hexRandRowMatrix[0] = 70;
    hexRandRowMatrix[1] = 200;
    hexRandRowMatrix[2] = 330;

    rhombi = 0;
    r1 = Rhombus("r1", glm::vec3(0, 0, 1), 80, 1);
    AddMeshToList(r1.mesh);
    r2 = Rhombus("r2", glm::vec3(0, 0, 1), 80, 2);
    AddMeshToList(r2.mesh);
    r3 = Rhombus("r3", glm::vec3(0, 0, 1), 80, 3);
    AddMeshToList(r3.mesh);
    r4 = Rhombus("r4", glm::vec3(0, 0, 1), 80, 4);
    AddMeshToList(r4.mesh);

    c1 = Cross("c1", glm::vec3(0, 0, 3), 60, glm::vec3(1, 0.6, 0.6));   
    AddMeshToList(c1.mesh);
    crosses = 3;
    for(int i = 0; i < crosses; i++) {
        crossTranslateX.push_back(0);
        crossTranslateY.push_back(hexRandRowMatrix[i]);
        crossMatrix.push_back(transform2D::Translate(30, crossTranslateY[i]));
        crossAttack.push_back(0);
        crossAngularStep.push_back(0);
    }
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.07, 0.07, 0.07, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
    if(lives >= 0) {
        {
            modelMatrix = glm::mat3(1);
            for(int i = 0; i < 9; i++) {
                RenderMesh2D(meshes["square" + to_string(i)], shaders["VertexColor"], modelMatrix);
            }
        }

        {
            modelMatrix = transform2D::Translate(squares[9].center.x, squares[9].center.y) * transform2D::Scale(0.6, 3.6) * transform2D::Translate(-squares[9].center.x, -squares[9].center.y);
            RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);
        }

        {
            modelMatrix = glm::mat3(1);
            for(int i = 0; i < 4; i++) {
                RenderMesh2D(meshes["outline_square" + to_string(i)], shaders["VertexColor"], modelMatrix);
            }
        }
        
        {
            modelMatrix = glm::mat3(1);
            for(int i = 0; i < 8; i++) {
                RenderMesh2D(meshes["guiStar" + to_string(i)], shaders["VertexColor"], modelMatrix);
            }
        }

        {
            modelMatrix = glm::mat3(1);
            for(int i = 0; i < 4; i++) {
                RenderMesh2D(meshes["rhombus" + to_string(i)], shaders["VertexColor"], modelMatrix);
            }
        }

        {
            modelMatrix = glm::mat3(1);
            for(int i = 0; i < lives; i++) {
                RenderMesh2D(meshes["life_square" + to_string(i)], shaders["VertexColor"], modelMatrix);
            }
        }

        {
            starTime += deltaTimeSeconds;
            if(starTime >= 10) {
                for(int i = 0; i < 3; i++) {
                    deleteTime.push_back(0);
                    cStarTranslateX.push_back(rand() % (1268 - 12 + 1) + 12);
                    cStarTranslateY.push_back(rand() % (708 - 12 + 1) + 12);
                    cStarMatrix.push_back(transform2D::Translate(cStarTranslateX[stars+i], cStarTranslateY[stars+i]) * glm::mat3(1));
                    starHitbox.push_back(collectStar.getHitboxCoord(glm::vec2(cStarTranslateX[stars+i], cStarTranslateY[stars+i])));
                }
                starTime = 0;
                stars += 3;
            }
            for(int i = 0; i < stars; i++) {
                deleteTime[i] += deltaTimeSeconds;
                if(deleteTime[i] >= 15) {
                    cStarTranslateX.erase(cStarTranslateX.begin() + i);
                    cStarTranslateY.erase(cStarTranslateY.begin() + i);
                    cStarMatrix.erase(cStarMatrix.begin() + i);
                    starHitbox.erase(starHitbox.begin() + i);
                    deleteTime.erase(deleteTime.begin() + i);
                    stars--;
                    i--;
                }
            }
            for(int i = 0; i < stars; i++)
                RenderMesh2D(meshes["collectStar"], shaders["VertexColor"], cStarMatrix[i]);
            for(int i = 0; i < invStars; i++)
                RenderMesh2D(meshes["collectedStar"], shaders["VertexColor"], invStarMatrix[i]);
        }

        {
            hexTime += deltaTimeSeconds;
            if(hexTime >= hexRandTime) {
                hexTranslateX.push_back(0);
                randRow = rand() % 3;
                hexTranslateY.push_back(hexRandRowMatrix[randRow]);
                hexColor.push_back(rand() % 4 + 1);
                hexMatrix.push_back(transform2D::Translate(1320, hexTranslateY[hexes]));
                hexLife.push_back(3);
                hexScale.push_back(1);
                hexes++;
                hexTime = 0;
                hexRandTime = rand() % (10 - 4 + 1) + 4;
            }
            for(int i = 0; i < hexes; i++) {
                hexTranslateX[i] -= deltaTimeSeconds * 50;
                hexMatrix[i] = transform2D::Translate(1320, hexTranslateY[i]);
                if(!(hexLife[i]) && hexScale[i] > 0) {
                    hexScale[i] -= deltaTimeSeconds * 3;
                    hexMatrix[i] *= transform2D::Translate(hexTranslateX[i], 0) * transform2D::Scale(hexScale[i], hexScale[i]) * transform2D::Translate(-hexTranslateX[i], 0) * transform2D::Translate(hexTranslateX[i], 0);
                }
                else {
                hexMatrix[i] *= transform2D::Translate(hexTranslateX[i], 0);
                }
                if(hexScale[i] <= 0) {
                    hexTranslateX.erase(hexTranslateX.begin() + i);
                    hexTranslateY.erase(hexTranslateY.begin() + i);
                    hexColor.erase(hexColor.begin() + i);
                    hexMatrix.erase(hexMatrix.begin() + i);
                    hexLife.erase(hexLife.begin() + i);
                    hexScale.erase(hexScale.begin() + i);
                    hexes--;
                    i--;
                } else {
                if(hexTranslateX[i] <= -1280  && lives && hexLife[i] > 0) { 
                    lives--;
                    hexLife[i] = -1;
                }
                if(hexTranslateX[i] < - 1360) {
                    if(!lives)
                        lives = -1;
                    hexLife[i] = 0;
                }
                RenderMesh2D(meshes["h" + to_string(hexColor[i])], shaders["VertexColor"], hexMatrix[i]);
                }
            }

        }

        {
            for(int i = 0; i < rhombi; i++) {
                for(int j = 0; j < hexes; j++) {
                    if(hexLife[j] && r1.getRhXPlusLength(rhTranslateX[i]) >= h1.getHexXMinusLength(1320 + hexTranslateX[j]) &&
                        r1.getRhXMinusLength(rhTranslateX[i]) <= h1.getHexXMinusLength(1320 + hexTranslateX[j]) && rhTranslateY[i] == hexTranslateY[j]) {
                        rhTBD[i] = 1;
                        for(int j = 0; j < 9; j++)
                            if(rhPos[i].A.x == gridHitbox[j].A.x)
                                occ[j] = 0;
                    }
                }
                if(rhTBD[i] && rhScale[i] > 0) {
                    rhombiMatrix[i] = transform2D::Translate(rhTranslateX[i], rhTranslateY[i]);
                    rhScale[i] -= deltaTimeSeconds * 3;
                    rhombiMatrix[i] *= transform2D::Scale(rhScale[i], rhScale[i]);            
                }
                if(rhScale[i] <= 0) {
                    rhombiMatrix.erase(rhombiMatrix.begin() + i);
                    rhPush.erase(rhPush.begin() + i);
                    rhColor.erase(rhColor.begin() + i);
                    rhTranslateX.erase(rhTranslateX.begin() + i);
                    rhTranslateY.erase(rhTranslateY.begin() + i);
                    rhPos.erase(rhPos.begin() + i);
                    rhTBD.erase(rhTBD.begin() + i);
                    rhScale.erase(rhScale.begin() + i);
                    rhActive.erase(rhActive.begin() + i);
                    pjTime.erase(pjTime.begin() + i);
                    rhombi--;
                    i--;
                }
                else 
                    RenderMesh2D(meshes["r" + to_string(rhColor[i])], shaders["VertexColor"], rhombiMatrix[i]);
            }
        }

        {
            for(int i = 0; i < rhombi; i++) {
                for(int j = 0; j < hexes; j++) {
                    if(hexTranslateY[j] == rhTranslateY[i] && hexColor[j] == rhColor[i] && hexLife[j]) {
                        if(!rhActive[i] && !rhPush[i]) {
                            rhActive[i] ++;
                            pjTime[i] = 0;
                        }   
                    }
                }
                if(rhActive[i]) {
                    pjTime[i] += deltaTimeSeconds;
                    if(pjTime[i] >= 2) {
                        pjStarPosX.push_back(rhTranslateX[i] + 70);
                        pjStarPosY.push_back(rhTranslateY[i]);
                        pjStarTranslateX.push_back(0);
                        pjStarAngularStep.push_back(55);
                        pjStarColor.push_back(rhColor[i]);
                        pjStarMatrix.push_back(transform2D::Translate(0, 0));
                        pjStars++;
                        pjTime[i] = 0;
                    }
                }
            }

            for(int i = 0; i < pjStars; i++) {
                pjStarTranslateX[i] += deltaTimeSeconds * 250;
                pjStarAngularStep[i] -= deltaTimeSeconds * 4;
                pjStarMatrix[i] = transform2D::Translate(pjStarPosX[i], pjStarPosY[i]);
                pjStarMatrix[i] *= transform2D::Translate(pjStarTranslateX[i], 0) * transform2D::Rotate(pjStarAngularStep[i]) * transform2D::Translate(-pjStarTranslateX[i], 0) * transform2D::Translate(pjStarTranslateX[i], 0);            RenderMesh2D(meshes["pjS" + to_string(pjStarColor[i])], shaders["VertexColor"], pjStarMatrix[i]);
                for(int j = 0; j < hexes; j++) {
                    if(hexLife[j] && pjS1.getPjXPlusLength(pjStarPosX[i] + pjStarTranslateX[i]) >= h1.getHexXMinusLength(1320 + hexTranslateX[j]) && pjStarPosY[i] == hexTranslateY[j] && pjStarColor[i] == hexColor[j]) {
                        hexLife[j]--;
                        pjStarPosX.erase(pjStarPosX.begin() + i);
                        pjStarPosY.erase(pjStarPosY.begin() + i);
                        pjStarTranslateX.erase(pjStarTranslateX.begin() + i);
                        pjStarAngularStep.erase(pjStarAngularStep.begin() + i);
                        pjStarColor.erase(pjStarColor.begin() + i);
                        pjStarMatrix.erase(pjStarMatrix.begin() + i);
                        pjStars--;
                        if(!hexLife[j])
                            for(int k = 0; k < rhombi; k++)
                                if(hexTranslateY[j] == rhTranslateY[k] && hexColor[j] == rhColor[k] && rhActive[k])
                                    rhActive[k]--;
                        i--;
                        j = hexes;
                    }
                }
            }
        }
        {
            for(int i = 0; i < crosses; i++) {
                for(int j = 0; j < hexes; j++) {
                    if(hexLife[j] && c1.getCrossXPlusLength(30 + crossTranslateX[i]) >= h1.getHexXMinusLength(1320 + hexTranslateX[j]) && crossTranslateY[i] == hexTranslateY[j]) {
                        crossAttack[i] = 1;
                    }
                }
                if(crossAttack[i]) {
                    crossTranslateX[i] += deltaTimeSeconds * 400;
                    crossAngularStep[i] -= deltaTimeSeconds * 4;
                    crossMatrix[i] = transform2D::Translate(30, crossTranslateY[i]);
                    crossMatrix[i] *= transform2D::Translate(crossTranslateX[i], 0) * transform2D::Rotate(crossAngularStep[i]) * transform2D::Translate(-crossTranslateX[i], 0) * transform2D::Translate(crossTranslateX[i], 0);
                    for(int j = 0; j < hexes; j++) {
                        if(hexLife[j] && c1.getCrossXPlusLength(crossTranslateX[i]) >= h1.getHexXMinusLength(1320 + hexTranslateX[j]) && crossTranslateY[i] == hexTranslateY[j]) {
                            hexLife[j] = 0;
                            for(int k = 0; k < rhombi; k++)
                                    if(hexTranslateY[j] == rhTranslateY[k] && hexColor[j] == rhColor[k] && rhActive[k])
                                        rhActive[k]--;
                            j--;
                        }
                    }
                }
                if(crossTranslateX[i] > 1320) {
                    crossTranslateX.erase(crossTranslateX.begin() + i);
                    crossTranslateY.erase(crossTranslateY.begin() + i);
                    crossAngularStep.erase(crossAngularStep.begin() + i);
                    crossAttack.erase(crossAttack.begin() + i);
                    crossMatrix.erase(crossMatrix.begin() + i);
                    crosses--;
                    i--;
                }
                else
                    RenderMesh2D(meshes["c1"], shaders["VertexColor"], crossMatrix[i]);
            }
        }
    }
}


void Tema1::FrameEnd()
{
}



void Tema1::OnInputUpdate(float deltaTime, int mods)
{   

}


void Tema1::OnKeyPress(int key, int mods)
{   
}


void Tema1::OnKeyRelease(int key, int mods)
{
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    for(int i = 0; i < rhombi; i++) { 
        if(rhPush[i]) {
            rhTranslateX[i] = deltaX;
            rhTranslateY[i] = -deltaY;
            rhombiMatrix[i] *= transform2D::Translate(rhTranslateX[i], rhTranslateY[i]);
        }
    }
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if(IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        for(int i = 0; i < stars; i++)
            if(mouseX >= starHitbox[i].A.x && mouseX <= starHitbox[i].C.x &&
               720 - mouseY >= starHitbox[i].A.y && 720 - mouseY <= starHitbox[i].C.y) {
                cStarTranslateX.erase(cStarTranslateX.begin() + i);
                cStarTranslateY.erase(cStarTranslateY.begin() + i);
                cStarMatrix.erase(cStarMatrix.begin() + i);
                deleteTime.erase(deleteTime.begin() + i);
                starHitbox.erase(starHitbox.begin() + i);
                stars--;
                i--;
                invStars++;
                invStarMatrix.push_back(transform2D::Translate(invStarTranslateX, invStarTranslateY) * glm::mat3(1));
                if(!(invStars % 10)) {
                    invStarTranslateX = 857;
                    invStarTranslateY -= 35;
                }
                else
                    invStarTranslateX += 35;
            }
        for(int i = 0; i < selectRhombus.size(); i++)
            if(mouseX >= selectRhombus[i].A.x && mouseX <= selectRhombus[i].C.x &&
               720 - mouseY >= selectRhombus[i].A.y && 720 - mouseY <= selectRhombus[i].C.y)
                    if((i == 0 && invStars >= 1) || ((i == 1 || i == 2) && invStars >= 2) || (i == 3 && invStars >= 3)){
                        rhTranslateX.push_back(0);
                        rhTranslateY.push_back(0);
                        rhTBD.push_back(0);
                        rhScale.push_back(1);
                        rhombiMatrix.push_back(transform2D::Translate(mouseX, 720 - mouseY));
                        rhPush.push_back(1);
                        rhColor.push_back(i + 1);
                        pjTime.push_back(0);
                        rhActive.push_back(0);
                        rhombi++;
                    }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    if(IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        for(int i = 0; i < rhombi; i++) {
            for(int j = 0; j < 9; j++) {
                if(rhPush[i])
                    if(mouseX >= gridHitbox[j].A.x && mouseX <= gridHitbox[j].C.x &&
                       720 - mouseY >= gridHitbox[j].A.y && 720 - mouseY <= gridHitbox[j].C.y && occ[j] == 0) {
                        rhPush[i] = 0;
                        occ[j] = 1;
                        rhTranslateX[i] = gridHitbox[j].A.x + 40;
                        rhTranslateY[i] = gridHitbox[j].A.y + 50; 
                        rhombiMatrix[i] = transform2D::Translate(rhTranslateX[i], rhTranslateY[i]);
                        rhPos.push_back(squares[j].getHitboxCoord(glm::vec2 (gridHitbox[j].A.x + 50, gridHitbox[j].A.y + 50)));
                        if(rhColor[i] == 1) {
                            invStarMatrix.pop_back();
                            if(!(invStars % 10)) {
                                invStarTranslateX = 1172;
                                invStarTranslateY += 35;
                            }
                            else
                                invStarTranslateX -= 35;
                            invStars--;
                        }
                        if(rhColor[i] == 2 || rhColor[i] == 3) {
                            for(int i = 0; i < 2; i++){
                                invStarMatrix.pop_back();
                                if(!(invStars % 10)) {
                                    invStarTranslateX = 1172;
                                    invStarTranslateY += 35;
                                }
                                else
                                    invStarTranslateX -= 35;
                                invStars--;
                            }
                        }
                        if(rhColor[i] == 4) {
                            for(int i = 0; i < 3; i++) {
                                invStarMatrix.pop_back();
                                if(!(invStars % 10)) {
                                    invStarTranslateX = 1172;
                                    invStarTranslateY += 35;
                                }
                                else
                                    invStarTranslateX -= 35;
                                invStars--;
                            }
                        }
                    }
            }
            if(rhPush[i]) {
                rhombiMatrix.erase(rhombiMatrix.begin() + i);
                rhPush.erase(rhPush.begin() + i);
                rhColor.erase(rhColor.begin() + i);
                rhTranslateX.erase(rhTranslateX.begin() + i);
                rhTranslateY.erase(rhTranslateY.begin() + i);
                rhTBD.erase(rhTBD.begin() + i);
                rhScale.erase(rhScale.begin() + i);
                pjTime.erase(pjTime.begin() + i);
                rhActive.erase(rhActive.begin() + 1);
                rhombi--;
                i--;
            }

        }
    }

     if(IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT)) {
        for(int i = 0; i < rhombi; i++) {
            if(mouseX >= rhPos[i].A.x && mouseX <= rhPos[i].C.x &&
               720 - mouseY >= rhPos[i].A.y && 720 - mouseY <= rhPos[i].C.y) {
                rhTBD[i] = 1;
                for(int j = 0; j < 9; j++)
                    if(rhPos[i].A.x == gridHitbox[j].A.x)
                        occ[j] = 0;
               }
        }
    }
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
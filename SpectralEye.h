#ifndef SPECTRALEYE_H
#define SPECTRALEYE_H

#include <vector>
#include "Spectre.h"

class SpectralEye {
private:
    int posX;
    int posY;
    int visionRange;
    std::vector<Spectre>* spectres;

public:
    SpectralEye(int x, int y, int range, std::vector<Spectre>* spectres);
    void update(int playerX, int playerY);
    bool detectPlayer(int playerX, int playerY);
    void alertSpectres(int playerX, int playerY);

    int getX() const { return posX; }
    int getY() const { return posY; }
};

void alertSpectresNearby(std::vector<Spectre>& spectres, int playerX, int playerY);

#endif // SPECTRALEYE_H


#ifndef SPECTRE_H
#define SPECTRE_H

#include <queue>
#include <vector>

class Spectre {
private:
    int posX;
    int posY;
    float speed;
    bool isChasing;

    // Estructura para representar los nodos en el mapa durante la búsqueda A*
    struct Node {
        int x;
        int y;
        float f;
        float g;
        float h;
        Node* parent;
    };

public:
    Spectre(int x, int y, float spd);
    void update();
    void detectPlayer(int playerX, int playerY);
    void chasePlayer(int playerX, int playerY);
    void returnToPatrol();
    void attackPlayer();

private:
    void moveTowardsPlayer(int playerX, int playerY);
    float heuristic(int x1, int y1, int x2, int y2);
    bool isValidPosition(int x, int y);
    bool isObstacle(int x, int y);
    bool isOpenSetContains(std::priority_queue<Node*, std::vector<Node*>, CompareNodes>& openSet, Node* node);

    struct CompareNodes {
        bool operator()(const Node* a, const Node* b) {
            return a->f > b->f;
        }
    };
};

#endif // SPECTRE_H



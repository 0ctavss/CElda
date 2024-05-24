#ifndef SPECTRE_H
#define SPECTRE_H

#include <queue>
#include <vector>
#include <utility>

enum SpectreType {
    GREY,
    RED,
    BLUE
};

class Spectre {
private:
    int posX;
    int posY;
    float speed;
    bool isChasing;
    SpectreType type;
    std::vector<std::pair<int, int>> patrolRoute;
    size_t currentPatrolIndex;

    // Estructura para representar los nodos en el mapa durante la búsqueda A*
    struct Node {
        int x, y;
        float f, g, h;
        Node* parent;
    };

    struct CompareNodes {
        bool operator()(const Node* a, const Node* b) {
            return a->f > b->f;
        }
    };

public:
    Spectre(int x, int y, float spd, SpectreType spectreType, const std::vector<std::pair<int, int>>& route);
    void update(int playerX, int playerY);
    void detectPlayer(int playerX, int playerY);
    void chasePlayer(int playerX, int playerY);
    void returnToPatrol();
    void attackPlayer(int& playerHP);
    void specialAbility();

private:
    void moveTowardsPlayer(int playerX, int playerY);
    void moveToNextPatrolPoint();
    float heuristic(int x1, int y1, int x2, int y2);
    bool isValidPosition(int x, int y);
    bool isObstacle(int x, int y);
    bool isOpenSetContains(std::priority_queue<Node*, std::vector<Node*>, CompareNodes>& openSet, Node* node);
    std::vector<Node*> reconstructPath(Node* currentNode);
    void alertNearbySpectres(std::vector<Spectre>& allSpectres);
};

#endif // SPECTRE_H



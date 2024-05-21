#include "Spectre.h"
#include <cmath>
#include <algorithm> 
#include <queue>

Spectre::Spectre(int x, int y, float spd, SpectreType spectreType, const std::vector<std::pair<int, int>>& route)
    : posX(x), posY(y), speed(spd), isChasing(false), type(spectreType), patrolRoute(route), currentPatrolIndex(0) {}


void Spectre::specialAbility() {
    if (type == RED) {
        // Habilidad especial del espectro rojo: Velocidad aumentada
        speed *= 1.5;
    }
    else if (type == BLUE) {
        // Habilidad especial del espectro azul: Invisibilidad temporal o evasión
        // Implementar la lógica para la habilidad del espectro azul
    }
}

void Spectre::update(int playerX, int playerY) {
    if (isChasing) {
        chasePlayer(playerX, playerY);
    }
    else {
        moveToNextPatrolPoint();
        detectPlayer(playerX, playerY);
    }
    specialAbility();
}

void Spectre::detectPlayer(int playerX, int playerY) {
    float distance = sqrt(pow(playerX - posX, 2) + pow(playerY - posY, 2));
    float visionRange = 10.0; // Ejemplo de rango de visión

    if (distance < visionRange) {
        isChasing = true;
        alertNearbySpectres(/* referencia a la lista de todos los espectros */);
    }
}

void Spectre::chasePlayer(int playerX, int playerY) {
    moveTowardsPlayer(playerX, playerY);
    if (std::abs(playerX - posX) <= 1 && std::abs(playerY - posY) <= 1) {
        attackPlayer(playerX, playerY);
    }
}

// Lógica para que el espectro regrese a su ruta de patrullaje después de perder al jugador
void Spectre::returnToPatrol() {

    // Coordenadas del punto de inicio del espectro (su posición actual)
    int startX = posX;
    int startY = posY;

    // Coordenadas del punto de destino (inicio de la ruta de patrullaje)
    int targetX = patrolRouteStartX;
    int targetY = patrolRouteStartY;

    // Implementación básica de búsqueda de ruta (A* u otro método)
    std::queue<std::pair<int, int>> queue;
    queue.push(std::make_pair(startX, startY));

    std::unordered_map<std::pair<int, int>, std::pair<int, int>> parentMap;
    parentMap[std::make_pair(startX, startY)] = std::make_pair(-1, -1);

    bool pathFound = false;

    while (!queue.empty()) {
        auto current = queue.front();
        queue.pop();

        int currentX = current.first;
        int currentY = current.second;

        if (currentX == targetX && currentY == targetY) {
            // Se encontró el destino, reconstruir el camino
            pathFound = true;
            break;
        }

        // Expandir los nodos vecinos
        for (int i = 0; i < 4; ++i) { // Movimientos hacia arriba, abajo, izquierda y derecha
            int nextX = currentX + dx[i];
            int nextY = currentY + dy[i];

            // Verificar si el vecino está dentro del mapa y no es un obstáculo
            if (isValidPosition(nextX, nextY) && !isObstacle(nextX, nextY)) {
                if (parentMap.find(std::make_pair(nextX, nextY)) == parentMap.end()) {
                    queue.push(std::make_pair(nextX, nextY));
                    parentMap[std::make_pair(nextX, nextY)] = current;
                }
            }
        }
    }

    if (pathFound) {
        // Reconstruir el camino desde el destino hasta el inicio
        std::vector<std::pair<int, int>> path;
        std::pair<int, int> current = std::make_pair(targetX, targetY);
        while (current != std::make_pair(-1, -1)) {
            path.push_back(current);
            current = parentMap[current];
        }

        // Mover el espectro a lo largo del camino reconstruido
        for (int i = path.size() - 2; i >= 0; --i) {
            // Se debería mover al espectro a la posición path[i]
            posX = path[i].first;
            posY = path[i].second;

            // Realizar otras operaciones necesarias, como la actualización visual del espectro en el juego
        }
    }
    else {
        // No se encontró un camino, probablemente no haya conexión con la ruta de patrullaje
        // En este caso, el espectro puede quedarse en su posición actual o realizar otra acción apropiada
    }
}

void Spectre::attackPlayer(int& playerHP) {
    playerHP -= 5; // Implementar daño al jugador
}

void Spectre::moveTowardsPlayer(int playerX, int playerY) {
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> openSet;
    std::vector<Node*> closedSet;

    Node* startNode = new Node{ posX, posY, 0, 0, 0, nullptr };
    openSet.push(startNode);

    while (!openSet.empty()) {
        Node* current = openSet.top();
        openSet.pop();

        if (current->x == playerX && current->y == playerY) {
            std::vector<Node*> path = reconstructPath(current);
            for (auto node : path) {
                posX = node->x;
                posY = node->y;
                delete node;
            }
            return;
        }

        closedSet.push_back(current);

        std::vector<std::pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1} };
        for (auto& dir : directions) {
            int neighborX = current->x + dir.first;
            int neighborY = current->y + dir.second;

            if (!isValidPosition(neighborX, neighborY) || isObstacle(neighborX, neighborY)) {
                continue;
            }

            float g = current->g + 1;
            float h = heuristic(neighborX, neighborY, playerX, playerY);
            float f = g + h;

            Node* neighbor = new Node{ neighborX, neighborY, f, g, h, current };

            if (std::find_if(closedSet.begin(), closedSet.end(), [neighbor](Node* n) { return n->x == neighbor->x && n->y == neighbor->y; }) != closedSet.end()) {
                delete neighbor;
                continue;
            }

            if (!isOpenSetContains(openSet, neighbor) || g < neighbor->g) {
                openSet.push(neighbor);
            }
        }
    }
}

void Spectre::moveToNextPatrolPoint() {
    if (patrolRoute.empty()) return;

    int targetX = patrolRoute[currentPatrolIndex].first;
    int targetY = patrolRoute[currentPatrolIndex].second;

    if (posX < targetX) posX += speed;
    else if (posX > targetX) posX -= speed;

    if (posY < targetY) posY += speed;
    else if (posY > targetY) posY -= speed;

    if (std::abs(posX - targetX) < speed && std::abs(posY - targetY) < speed) {
        currentPatrolIndex = (currentPatrolIndex + 1) % patrolRoute.size();
    }
}

float Spectre::heuristic(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

bool Spectre::isValidPosition(int x, int y) {
    // Verificar si la posición está dentro del mapa
    // Implementar según las dimensiones del mapa
    return true; // Por ahora, se devueñve verdadero para demostración
}

bool Spectre::isObstacle(int x, int y) {
    // Verificar si la posición es un obstáculo (como una pared o un objeto)
    // Implementar según las características de tu mapa
    return false; // Por ahora, se devuelve falso para demostración
}

bool Spectre::isOpenSetContains(std::priority_queue<Node*, std::vector<Node*>, CompareNodes>& openSet, Node* node) {
    auto copy = openSet;
    while (!copy.empty()) {
        Node* n = copy.top();
        copy.pop();
        if (n->x == node->x && n->y == node->y) {
            return true;
        }
    }
    return false;
}

std::vector<Spectre::Node*> Spectre::reconstructPath(Node* currentNode) {
    std::vector<Node*> path;
    while (currentNode != nullptr) {
        path.push_back(currentNode);
        currentNode = currentNode->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

void Spectre::alertNearbySpectres(std::vector<Spectre>& allSpectres) {
    for (auto& spectre : allSpectres) {
        if (&spectre != this && !spectre.isChasing) {
            spectre.isChasing = true;
        }
    }
}

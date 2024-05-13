#include "Spectre.h"
#include <cmath>
#include <algorithm> 

Spectre::Spectre(int x, int y, float spd) : posX(x), posY(y), speed(spd), isChasing(false) {}

void Spectre::update() {
    // Implementaci�n de la actualizaci�n del espectro
    // Llamar a las funciones para detectar al jugador, perseguirlo, etc.
}

void Spectre::detectPlayer(int playerX, int playerY) {
    // L�gica para detectar al jugador
    // Calcular la distancia entre el espectro y el jugador
    float distance = sqrt(pow(playerX - posX, 2) + pow(playerY - posY, 2));
    if (distance < visionRange) { // visionRange es el rango de visi�n del espectro
        isChasing = true;
    }
}

void Spectre::chasePlayer(int playerX, int playerY) {
    // L�gica para perseguir al jugador
    // Llamar a la funci�n moveTowardsPlayer(playerX, playerY)
}

// L�gica para que el espectro regrese a su ruta de patrullaje despu�s de perder al jugador
void Spectre::returnToPatrol() {

    // Coordenadas del punto de inicio del espectro (su posici�n actual)
    int startX = posX;
    int startY = posY;

    // Coordenadas del punto de destino (inicio de la ruta de patrullaje)
    int targetX = patrolRouteStartX;
    int targetY = patrolRouteStartY;

    // Implementaci�n b�sica de b�squeda de ruta (A* u otro m�todo)
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
            // Se encontr� el destino, reconstruir el camino
            pathFound = true;
            break;
        }

        // Expandir los nodos vecinos
        for (int i = 0; i < 4; ++i) { // Movimientos hacia arriba, abajo, izquierda y derecha
            int nextX = currentX + dx[i];
            int nextY = currentY + dy[i];

            // Verificar si el vecino est� dentro del mapa y no es un obst�culo
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
            // Se deber�a mover al espectro a la posici�n path[i]
            posX = path[i].first;
            posY = path[i].second;

            // Realizar otras operaciones necesarias, como la actualizaci�n visual del espectro en el juego
        }
    }
    else {
        // No se encontr� un camino, probablemente no haya conexi�n con la ruta de patrullaje
        // En este caso, el espectro puede quedarse en su posici�n actual o realizar otra acci�n apropiada
    }
}

void Spectre::attackPlayer() {
    // L�gica para que el espectro ataque al jugador si est� lo suficientemente cerca
}

void Spectre::moveTowardsPlayer(int playerX, int playerY) {
    // Implementaci�n del algoritmo A*
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> openSet;
    std::vector<Node*> closedSet;

    Node* startNode = new Node{ posX, posY, 0, 0, 0, nullptr };
    openSet.push(startNode);

    while (!openSet.empty()) {
        Node* current = openSet.top();
        openSet.pop();

        // Si llegamos al jugador, detenemos la b�squeda
        if (current->x == playerX && current->y == playerY) {
            // Reconstruir el camino
            while (current->parent != nullptr) {
                // Mover al espectro en direcci�n al nodo padre
                posX = current->x;
                posY = current->y;
                current = current->parent;
            }
            break;
        }

        // Expandir los nodos vecinos
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue; // Saltar el nodo actual

                int neighborX = current->x + i;
                int neighborY = current->y + j;

                // Verificar si el vecino est� dentro del mapa y no es un obst�culo
                if (isValidPosition(neighborX, neighborY) && !isObstacle(neighborX, neighborY)) {
                    // Calcular los valores de las funciones f, g y h
                    float g = current->g + 1; // Distancia entre nodos es 1 en este caso
                    float h = heuristic(neighborX, neighborY, playerX, playerY);
                    float f = g + h;

                    // Crear el nodo vecino
                    Node* neighbor = new Node{ neighborX, neighborY, f, g, h, current };

                    // Si el vecino ya est� en el conjunto cerrado, continuar
                    if (std::find(closedSet.begin(), closedSet.end(), neighbor) != closedSet.end()) {
                        delete neighbor;
                        continue;
                    }

                    // Si el vecino no est� en el conjunto abierto o tiene un costo menor, agregarlo
                    if (!isOpenSetContains(openSet, neighbor) || g < neighbor->g) {
                        openSet.push(neighbor);
                    }
                }
            }
        }

        closedSet.push_back(current);
    }
}

bool Spectre::isOpenSetContains(std::priority_queue<Node*, std::vector<Node*>, CompareNodes>& openSet, Node* node) {
    // Verificar si el conjunto abierto contiene el nodo especificado
    auto copy = openSet;
    while (!copy.empty()) {
        if (copy.top()->x == node->x && copy.top()->y == node->y) {
            return true;
        }
        copy.pop();
    }
    return false;
}

float Spectre::heuristic(int x1, int y1, int x2, int y2) {
    // Distancia Manhattan como heur�stica (puede ajustarse seg�n la forma del mapa)
    return abs(x1 - x2) + abs(y1 - y2);
}

bool Spectre::isValidPosition(int x, int y) {
    // Verificar si la posici�n est� dentro del mapa
    // Implementar seg�n las dimensiones del mapa
    return true; // Por ahora, se devue�ve verdadero para demostraci�n
}

bool Spectre::isObstacle(int x, int y) {
    // Verificar si la posici�n es un obst�culo (como una pared o un objeto)
    // Implementar seg�n las caracter�sticas de tu mapa
    return false; // Por ahora, se devuelve falso para demostraci�n
}
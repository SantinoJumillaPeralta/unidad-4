#include "Game.h"
#include "Box2DHelper.h"
#include <iostream>
#include "Obstacle.h" // Agregamos la inclusión de Obstacle.h

using namespace sf;

// Declaración de la clase Cannon
class Game {
private:
    Cannon* cannon;
    b2Body* cannonBody;
    RenderWindow* window;
    float power;
public:
    Game(int width, int height, std::string title);
    void DoEvents();
    void DrawGame();
    Cannon(b2World* world, RenderWindow* wnd);
    void update(Vector2f mousePosition);
    void shoot();
};

// Implementación de la clase Cannon
Cannon::Cannon(b2World* world, RenderWindow* wnd) : window(wnd), power(0.0f) {
    // Crear cuerpo del cañón
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(100.0f, 90.0f);
    cannonBody = world->CreateBody(&bodyDef);

    // Crear forma del cañón (círculo)
    b2CircleShape cannonShape;
    cannonShape.m_radius = 5.0f;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &cannonShape;
    fixtureDef.density = 1.0f;
    cannonBody->CreateFixture(&fixtureDef);
}

void Cannon::update(Vector2f mousePosition) {
    // Calcular ángulo y potencia del disparo según la posición del mouse
    float dx = mousePosition.x - cannonBody->GetPosition().x;
    float dy = mousePosition.y - cannonBody->GetPosition().y;
    float angle = atan2(dy, dx);
    power = sqrt(dx * dx + dy * dy); // Potencia es la distancia al mouse
}

void Cannon::shoot() {
    // Crear y lanzar el ragdoll con la potencia y el ángulo calculados
    std::cout << "Pum! Potencia: " << power << std::endl;
}

// Declaración de la clase Obstacle
class Obstacle {
private:
    b2Body* obstacleBody;
public:
    Obstacle(b2World* world, float x, float y);
};

// Implementación de la clase Obstacle
Obstacle::Obstacle(b2World* world, float x, float y) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x, y);
    obstacleBody = world->CreateBody(&bodyDef);

    b2PolygonShape obstacleShape;
    obstacleShape.SetAsBox(5.0f, 5.0f); // Tamaño arbitrario
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &obstacleShape;
    fixtureDef.density = 1.0f;
    obstacleBody->CreateFixture(&fixtureDef);
}

// Clase Game con integración de Cannon y Obstacle
class Game {
private:
    Cannon* cannon;
    RenderWindow window;
    b2World* phyWorld;
    Cannon* cannon;
    Obstacle* obstacle;
public:
    Game(int width, int height, std::string title);
    void DoEvents();
    void DrawGame();
    void run();
    void update();
    void render();
};

// Implementación de la clase Game
Game::Game(int width, int height, std::string title), phyWorld(new b2World(b2Vec2(0.0f, 9.8f))), cannon(nullptr), obstacle(nullptr) {
    cannon = new Cannon(phyWorld, &window);
    obstacle = new Obstacle(phyWorld, 50.0f, 70.0f);
}


Game::Game(int width, int height, std::string title) {
    wnd = new RenderWindow(VideoMode(width, height), title);
    wnd->setVisible(true);
    fps = 60;
    wnd->setFramerateLimit(fps);
    frameTime = 1.0f / fps;
    SetZoom();
    InitPhysics();
    delete cannon;
    delete obstacle;
    delete phyWorld;
}


void Game::run() {
    while (window.isOpen()) {
        update();
        render();
    }
}

void Game::DoEvents() {
    // Manejar eventos del mouse y teclado
    cannon->update(static_cast<sf::Vector2f>(Mouse::getPosition(*wnd)));
}

void Game::DrawGame() {
    // Dibujar elementos del juego (incluyendo el cañón)
}

void Game::update() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
        if (Mouse::isButtonPressed(Mouse::Left))
            cannon->update(Vector2f(Mouse::getPosition(window)));
        if (Keyboard::isKeyPressed(Keyboard::Space))
            cannon->shoot();
    }
    phyWorld->Step(1 / 60.0f, 8, 3);
}

void Game::render() {
    window.clear();
    // Dibujar objetos aquí
    window.display();
}

void Cannon::shoot() {
    // Crear y lanzar el ragdoll
    // Usa la potencia y el ángulo calculados anteriormente
    b2Vec2 impulse(power * cos(angle), power * sin(angle)); // Convertir potencia y ángulo en un vector de impulso
    cannonBody->ApplyLinearImpulse(impulse, cannonBody->GetWorldCenter(), true); // Aplicar impulso al cañón
}

void Game::DoEvents() {
    if (Mouse::isButtonPressed(Mouse::Left)) {
        sf::Vector2i mousePosition = Mouse::getPosition(*wnd);
        cannon->shoot();
    }
}

void Game::InitPhysics()
{
    // Inicializamos el mundo con la gravedad por defecto
    phyWorld = new b2World(b2Vec2(0.0f, 9.8f));

    // Creamos un piso y paredes
    b2Body* groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
    groundBody->SetTransform(b2Vec2(50.0f, 100.0f), 0.0f);

    b2Body* leftWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
    leftWallBody->SetTransform(b2Vec2(0.0f, 50.0f), 0.0f);

    b2Body* rightWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
    rightWallBody->SetTransform(b2Vec2(100.0f, 50.0f), 0.0f);

    // Creamos un círculo que controlaremos con el teclado
    controlBody = Box2DHelper::CreateCircularDynamicBody(phyWorld, 5, 1.0f, 0.5, 0.1f);
    controlBody->SetTransform(b2Vec2(50.0f, 50.0f), 0.0f);

    // Crear obstáculos
    obstacles.push_back(new Obstacle(phyWorld, 50.0f, 80.0f));
    obstacles.push_back(new Obstacle(phyWorld, 80.0f, 70.0f));
    // Agregar más obstáculos según sea necesario
}


// Función main
int main() {
    Game game(800, 600, "Cannon Game");
    game.run();
    return 0;
}

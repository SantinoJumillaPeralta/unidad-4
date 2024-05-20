#include <Box2D/Box2D.h>
#pragma once

class Box2DHelper
{
public:
	//-------------------------------------------------------------
	// Crea un body din�mico sin fixtures centrado en 0,0
	//-------------------------------------------------------------

	static b2Body* CreateDynamicBody(b2World* phyWorld) {

		// Declaramos el body
		b2Body* body;

		// Llenamos la definici�n
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(0.0f, 0.0f);
		body = phyWorld->CreateBody(&bodyDef);

		return body;
	}

	//-------------------------------------------------------------
	// Crea un body est�tico sin fixtures centrado en 0,0
	//-------------------------------------------------------------
	static b2Body* CreateStaticBody(b2World* phyWorld)
	{
		// Declaramos el body
		b2Body* body;

		// Llenamos la definici�n
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position.Set(0.0f, 0.0f);
		body = phyWorld->CreateBody(&bodyDef);

		return body;
	}

	//-------------------------------------------------------------
	// Crea un body cinem�tico sin fixtures centrado en 0,0
	//-------------------------------------------------------------
	static b2Body* CreateKinematicBody(b2World* phyWorld)
	{
		// Declaramos el body
		b2Body* body;

		// Llenamos la definici�n
		b2BodyDef bodyDef;
		bodyDef.type = b2_kinematicBody;
		bodyDef.position.Set(0.0f, 0.0f);
		body = phyWorld->CreateBody(&bodyDef);

		return body;
	}

	//-------------------------------------------------------------
	// Crea un fixture rectangular con el 0,0 en el medio
	//-------------------------------------------------------------
	static b2FixtureDef CreateRectangularFixtureDef(float sizeX, float sizeY, float density, float friction, float restitution)
	{

		b2PolygonShape* box = new b2PolygonShape();

		box->SetAsBox(sizeX / 2.0f, sizeY / 2.0f, b2Vec2(0.0f, 0.0f), 0.0f);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = box;
		fixtureDef.density = density;
		fixtureDef.friction = friction;
		fixtureDef.restitution = restitution;

		return fixtureDef;
	}

	//-------------------------------------------------------------
	// Crea un fixture circular con el 0,0 en el medio
	//-------------------------------------------------------------
	static b2FixtureDef CreateCircularFixtureDef(float radius, float density, float friction, float restitution)
	{
		b2CircleShape* circle = new b2CircleShape();
		circle->m_p = b2Vec2(0.0f, 0.0f);
		circle->m_radius = radius;

		b2FixtureDef fixtureDef;
		fixtureDef.shape = circle;
		fixtureDef.density = density;
		fixtureDef.friction = friction;
		fixtureDef.restitution = restitution;

		return fixtureDef;
	}

	//-------------------------------------------------------------
	// Crea un fixture poligonal dado un conj de puntos
	//-------------------------------------------------------------
	static b2FixtureDef CreatePolyFixtureDef(b2Vec2* v, int n, float density, float friction, float restitution)
	{
		b2PolygonShape* poly = new b2PolygonShape();
		poly->Set(v, n);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = poly;
		fixtureDef.density = density;
		fixtureDef.friction = friction;
		fixtureDef.restitution = restitution;

		return fixtureDef;
	}

	//-------------------------------------------------------------
	// Crea un fixture triangular (tri�ngulo equil�tero)
	//-------------------------------------------------------------
	static b2FixtureDef CreateTriangularFixtureDef(b2Vec2 c, float h, float density, float friction, float restitution)
	{
		b2Vec2 verts[3];
		verts[0].x = -h / 2;
		verts[0].y = -h / 2;
		verts[1].x = h / 2;
		verts[1].y = -h / 2;
		verts[2].x = 0;
		verts[2].y = h / 2;

		return CreatePolyFixtureDef(verts, 3, density, friction, restitution);
	}

	//-------------------------------------------------------------
	// Crea un body din�mico con un fixture rectangular centrado en el origen
	//-------------------------------------------------------------
	static b2Body* CreateRectangularDynamicBody(b2World* phyWorld, float sizeX, float sizeY, float density, float friction, float restitution)
	{
		b2Body* body = CreateDynamicBody(phyWorld);
		b2FixtureDef box = CreateRectangularFixtureDef(sizeX, sizeY, density, friction, restitution);
		body->CreateFixture(&box);

		return body;
	}

	//-------------------------------------------------------------
	// Crea un body cinem�tico con un fixture rectangular centrado en el origen
	//-------------------------------------------------------------
	static b2Body* CreateRectangularKinematicBody(b2World* phyWorld, float sizeX, float sizeY)
	{
		b2Body* body = CreateKinematicBody(phyWorld);
		b2FixtureDef box = CreateRectangularFixtureDef(sizeX, sizeY, 0.0f, 0.0f, 0.0f);
		body->CreateFixture(&box);

		return body;
	}

	//-------------------------------------------------------------
	// Crea un body est�tico con un fixture rectangular centrado en el origen
	//-------------------------------------------------------------
	static b2Body* CreateRectangularStaticBody(b2World* phyWorld, float sizeX, float sizeY)
	{
		b2Body* body = CreateStaticBody(phyWorld);
		b2FixtureDef box = CreateRectangularFixtureDef(sizeX, sizeY, 0.0f, 0.0f, 0.0f);
		body->CreateFixture(&box);

		return body;
	}

	//-------------------------------------------------------------
	// Crea un body din�mico con un fixture circular centrado en el origen
	//-------------------------------------------------------------
	static b2Body* CreateCircularDynamicBody(b2World* phyWorld, float radius, float density, float friction, float restitution)
	{
		b2Body* body = CreateDynamicBody(phyWorld);
		b2FixtureDef cir = CreateCircularFixtureDef(radius, density, friction, restitution);
		body->CreateFixture(&cir);

		return body;
	}

	//-------------------------------------------------------------
	// Crea un body cinem�tico con un fixture circular centrado en el origen
	//-------------------------------------------------------------
	static b2Body* CreateCircularKinematicBody(b2World* phyWorld, float radius)
	{
		b2Body* body = CreateKinematicBody(phyWorld);
		b2FixtureDef cir = CreateCircularFixtureDef(radius, 0.0f, 0.0f, 0.0f);
		body->CreateFixture(&cir);

		return body;
	}

	//-------------------------------------------------------------
	// Crea un body est�tico con un fixture circular centrado en el origen
	//-------------------------------------------------------------
	static b2Body* CreateCircularStaticBody(b2World* phyWorld, float radius)
	{
		b2Body* body = CreateStaticBody(phyWorld);
		b2FixtureDef cir = CreateCircularFixtureDef(radius, 0.0f, 0.0f, 0.0f);
		body->CreateFixture(&cir);

		return body;
	}
	Cannon::Cannon(b2World* world, RenderWindow* wnd) : window(wnd), power(0.0f) {
		// Crear el cuerpo del ca��n
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody; // El ca��n no se mover�
		bodyDef.position.Set(100.0f, 90.0f); // Posici�n inicial
		cannonBody = world->CreateBody(&bodyDef);

		// Crear la forma del ca��n (puedes usar un pol�gono o una cadena de c�rculos)
		b2CircleShape cannonShape;
		cannonShape.m_radius = 5.0f; // Tama�o del ca��n
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &cannonShape;
		fixtureDef.density = 1.0f; // Densidad arbitraria
		cannonBody->CreateFixture(&fixtureDef);
	}

	Cannon::Cannon(b2World* world, RenderWindow* wnd) : window(wnd), power(0.0f) {
		// Crear el cuerpo del ca��n
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody; // El ca��n no se mover�
		bodyDef.position.Set(100.0f, 90.0f); // Posici�n inicial
		cannonBody = world->CreateBody(&bodyDef);

		// Crear la forma del ca��n (puedes usar un pol�gono o una cadena de c�rculos)
		b2CircleShape cannonShape;
		cannonShape.m_radius = 5.0f; // Tama�o del ca��n
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &cannonShape;
		fixtureDef.density = 1.0f; // Densidad arbitraria
		cannonBody->CreateFixture(&fixtureDef);
	}

	void Cannon::update(sf::Vector2f mousePosition) {
		// Calcular �ngulo y potencia del disparo seg�n la posici�n del mouse
		b2Vec2 cannonPosition = cannonBody->GetPosition();
		float dx = mousePosition.x - cannonPosition.x;
		float dy = mousePosition.y - cannonPosition.y;
		float angle = atan2(dy, dx); // Calcular �ngulo en radianes
		power = sqrt(dx * dx + dy * dy); // Calcular potencia como distancia al mouse
	}

	void Cannon::shoot() {
		// Crear y lanzar el ragdoll
		// Usa la potencia y el �ngulo calculados anteriormente
	}

	//-------------------------------------------------------------
	// Crea un body din�mico con un fixture triangular centrado en el origen
	//-------------------------------------------------------------
	static b2Body* CreateTriangularDynamicBody(b2World* phyWorld, b2Vec2 center, float h, float density, float friction, float restitution)
	{
		b2Body* body = CreateDynamicBody(phyWorld);
		b2FixtureDef tri = CreateTriangularFixtureDef(center, h, density, friction, restitution);
		body->CreateFixture(&tri);

		return body;
	}

	//-------------------------------------------------------------
	// Crea un body cinem�tico con un fixture triangular centrado en el origen
	//-------------------------------------------------------------
	static b2Body* CreateTriangularKinematicBody(b2World* phyWorld, b2Vec2 center, float h)
	{
		b2Body* body = CreateKinematicBody(phyWorld);
		b2FixtureDef tri = CreateTriangularFixtureDef(center, h, 0.0f, 0.0f, 0.0f);
		body->CreateFixture(&tri);

		return body;
	}

	//-------------------------------------------------------------
	// Crea un body est�tico con un fixture triangular centrado en el origen
	//-------------------------------------------------------------
	static b2Body* CreateTriangularStaticBody(b2World* phyWorld, b2Vec2 center, float h)
	{
		b2Body* body = CreateStaticBody(phyWorld);
		b2FixtureDef tri = CreateTriangularFixtureDef(center, h, 0.0f, 0.0f, 0.0f);
		body->CreateFixture(&tri);

		return body;
	}

	//-------------------------------------------------------------
	// Crea un body din�mico con un fixture poligonal 
	//-------------------------------------------------------------
	static b2Body* CreatePolyDynamicBody(b2World* phyWorld, b2Vec2* v, int n, float density, float friction, float restitution)
	{
		b2Body* body = CreateDynamicBody(phyWorld);
		b2FixtureDef tri = CreatePolyFixtureDef(v, n, density, friction, restitution);
		body->CreateFixture(&tri);

		return body;
	}

	//-------------------------------------------------------------
	// Crea un body cinem�tico con un fixture poligonal 
	//-------------------------------------------------------------
	static b2Body* CreatePolyKinematicBody(b2World* phyWorld, b2Vec2* v, int n)
	{
		b2Body* body = CreateKinematicBody(phyWorld);
		b2FixtureDef tri = CreatePolyFixtureDef(v, n, 0.0f, 0.0f, 0.0f);
		body->CreateFixture(&tri);

		return body;
	}

	//-------------------------------------------------------------
	// Crea un body est�tico con un fixture poligonal
	//-------------------------------------------------------------
	static b2Body* CreatePolyStaticBody(b2World* phyWorld, b2Vec2* v, int n)
	{
		b2Body* body = CreateDynamicBody(phyWorld);
		b2FixtureDef tri = CreatePolyFixtureDef(v, n, 0.0f, 0.0f, 0.0f);
		body->CreateFixture(&tri);

		return body;
	}
};
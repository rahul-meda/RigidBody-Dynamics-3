
#include "GJK_Test.h"
#include "../Components/Body.h"
#include "../Physics/Physics.h"
#include "../Physics/HullCollider.h"
#include "../Mesh/ObjParser.h"
#include "../Components/Model.h"
#include "../Graphics/Graphics.h"
#include "../Mesh/Geometry.h"
#include "../Physics/SphereCollider.h"

GJK_Test& GJK_Test::GetInstance()
{
	static GJK_Test instance;
	return instance;
}

void GJK_Test::Init(std::vector<GameObject>& gameObjects)
{
	ModelDef box, sphere, line;
	HMesh mesh;
	ParseObj("Resources/Models/Box.obj", mesh);
	mesh.GetModelData(box);
	unsigned int boxModel = Graphics::GetInstance().CreateModel(box);

	Transform tx;
	BodyDef bd;
	unsigned int bID = 0;
	HullCollider* boxCollider;

	glm::quat q = glm::angleAxis(0.75f, glm::vec3(0.0f, 0.0f, 1.0f));
	tx = Transform(glm::vec3(0.0f, 11.5f, 0.0f), q);
	bd.tx = tx;
	bd.isStatic = false;
	bd.angularVelocity = glm::vec3(1.0f);
	bID = Physics::GetInstance().AddBody(bd);
	boxCollider = new HullCollider();
	boxCollider->massData->density = 1.0f;
	mesh.GetColliderData(boxCollider);
	boxCollider->Scale(glm::vec3(1.0f));
	Physics::GetInstance().bodies.back()->AddCollider(boxCollider);
	Graphics::GetInstance().scales.push_back(glm::vec3(1.0f));
	gameObjects.push_back(GameObject(boxModel, bID));

	CreateSphere(sphere);
	unsigned int sphereModel = Graphics::GetInstance().CreateModel(sphere);
	glm::vec3 yellowGreen(0.5f, 1.0f, 0.3f);
	glm::vec3 disco(0.2f, 0.7f, 1.0f);

	tx = Transform(glm::vec3(10.0f, 20.0f, 0.0f));
	bd.tx = tx;
	bd.isStatic = false;
	bID = Physics::GetInstance().AddBody(bd);
	SphereCollider* sphereCollider = new SphereCollider();
	sphereCollider->Scale(1.0f);
	Physics::GetInstance().bodies.back()->AddCollider(sphereCollider);
	Graphics::GetInstance().scales.push_back(glm::vec3(1.0f));
	gameObjects.push_back(GameObject(sphereModel, bID, disco));
}
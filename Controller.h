#pragma once

#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "EventManager.h"
#include "Event.h"
#include <memory>


class Coordinator
{
public:
	void Init()
	{
		mComponentManager = std::make_unique<ComponentManager>();
		mEntityManager = std::make_unique<EntityManager>();
		mEventManager = std::make_unique<EventManager>();
		mSystemManager = std::make_unique<SystemManager>();
	}


	// Entity methods
	Entity CreateEntity()
	{
		return mEntityManager->CreateEntity();
	}

	void DestroyEntity(Entity entity)
	{
		mEntityManager->DestroyEntity(entity);

		mComponentManager->EntityDestroyed(entity);

		mSystemManager->EntityDestroyed(entity);
	}


	// Component methods
	template<typename T>
	void RegisterComponent()
	{
		mComponentManager->RegisterComponent<T>();
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		mComponentManager->AddComponent<T>(entity, component);

		auto signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentManager->GetComponentType<T>(), true);
		mEntityManager->SetSignature(entity, signature);

		mSystemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		mComponentManager->RemoveComponent<T>(entity);

		auto signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentManager->GetComponentType<T>(), false);
		mEntityManager->SetSignature(entity, signature);

		mSystemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		return mComponentManager->GetComponent<T>(entity);
	}

	template<typename T>
	cmpAux::ComponentType GetComponentType()
	{
		return mComponentManager->GetComponentType<T>();
	}


	// System methods
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		return mSystemManager->RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(cmpAux::Signature signature)
	{
		mSystemManager->SetSignature<T>(signature);
	}


	//// Event methods
	//void AddEventListener(cmpAux::EventId eventId, std::function<void(Event&)> const& listener)
	//{
	//	mEventManager->AddListener(eventId, listener);
	//}

	//void SendEvent(Event& event)
	//{
	//	mEventManager->SendEvent(event);
	//}

	//void SendEvent(cmpAux::EventId eventId)
	//{
	//	mEventManager->SendEvent(eventId);
	//}


    void Enemy_Init_Himary()  
    {  
					Entity enemy = (*this).CreateEntity();  
					CMovement movementComponent; // Create an instance of CMovement  
					(*this).AddComponent(enemy, movementComponent); // Pass the instance to AddComponent  

					gCoordinator.AddComponent<Gravity>(  
						enemy,  
						{ Vec3(0.0f, randGravity(generator), 0.0f) });  

					gCoordinator.AddComponent(  
						enemy,  
						RigidBody{  
							.velocity = Vec3(0.0f, 0.0f, 0.0f),  
							.acceleration = Vec3(0.0f, 0.0f, 0.0f)  
						});  
    }

private:
	std::unique_ptr<ComponentManager> mComponentManager;
	std::unique_ptr<EntityManager> mEntityManager;
	std::unique_ptr<EventManager> mEventManager;
	std::unique_ptr<SystemManager> mSystemManager;
};


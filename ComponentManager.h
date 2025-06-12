#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;
using namespace sf;


class ComponentManager
{

private:
	// Map from type string pointer to a component type
	std::unordered_map<const char*, cmpAux::ComponentType> mComponentTypes{};

	// Map from type string pointer to a component array
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> mComponentArrays{};

	// The component type to be assigned to the next registered component - starting at 0
	cmpAux::ComponentType mNextComponentType{};

	// Convenience function to get the statically casted pointer to the ComponentArray of type T.
	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		const char* typeName = typeid(T).name();

		assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

		return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[typeName]);
	}

public:
	template<typename T>
	void RegisterComponent()
	{
		const char* typeName = typeid(T).name();

		assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Registering component type more than once.");

		// Add this component type to the component type map
		mComponentTypes.insert({ typeName, mNextComponentType });

		// Create a ComponentArray pointer and add it to the component arrays map
		mComponentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

		// Increment the value so that the next component registered will be different
		++mNextComponentType;
	}

	template<typename T>
	cmpAux::ComponentType GetComponentType()
	{
		const char* typeName = typeid(T).name();

		assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

		// Return this component's type - used for creating signatures
		return mComponentTypes[typeName];
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		// Add a component to the array for an entity
		GetComponentArray<T>()->InsertData(entity, component);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		// Remove a component from the array for an entity
		GetComponentArray<T>()->RemoveData(entity);
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		// Get a reference to a component from the array for an entity
		return GetComponentArray<T>()->GetData(entity);
	}

	void EntityDestroyed(Entity entity)
	{
		// Notify each component array that an entity has been destroyed
		// If it has a component for that entity, it will remove it
		for (auto const& pair : mComponentArrays)
		{
			auto const& component = pair.second;

			component->EntityDestroyed(entity);
		}
	}

};



















struct CHealth
{
	int hp;

	CHealth() : hp(0) {};
	CHealth(const int& h) : hp(h) {};
};

struct CMovement
{
	Vector2f position = { 0, 0 };
	float speed = 0;
	unsigned int currentPathindex = 0;

	vector<vector<Vector2f>> paths = { {Vector2f(0.f, 500.f),     //Cordinate for map1
										Vector2f(600.f, 500.f),
										Vector2f(600.f, 700.f),
										Vector2f(1200.f, 700.f),
										Vector2f(1200.f, 400.f),
										Vector2f(1920.f, 400.f)},

										{Vector2f(0.f, 500.f),     //Cordinate for map2
										Vector2f(600.f, 500.f),
										Vector2f(600.f, 700.f),
										Vector2f(1200.f, 700.f),
										Vector2f(1200.f, 400.f),
										Vector2f(1920.f, 400.f)},

										{Vector2f(0.f, 500.f),     //Cordinate for map3
										Vector2f(600.f, 500.f),
										Vector2f(600.f, 700.f),
										Vector2f(1200.f, 700.f),
										Vector2f(1200.f, 400.f),
										Vector2f(1920.f, 400.f)},

										{Vector2f(0.f, 500.f),     //Cordinate for map4
										Vector2f(600.f, 500.f),
										Vector2f(600.f, 700.f),
										Vector2f(1200.f, 700.f),
										Vector2f(1200.f, 400.f),
										Vector2f(1920.f, 400.f)}
	};

	CMovement() {}
	CMovement(const Vector2f& p, const float& v)
		: position(p), speed(v) {}
};

struct CSet
{
	Texture texture;
	Sprite sprite;

	Vector2u ImgCount;
	Vector2u CurrImg;

	float totalTime = 0.0f;
	float switchTime = 0.0f;

	IntRect uvRect;

	int row = 0;

	CSet() {}
	CSet(const string& filepath, const Vector2u& ImgCount, float& switchTime, const int& row)
	{
		if (!texture.loadFromFile(filepath))
		{
			cout << "Error! Can't load filepath" << endl;
			return;
		}

		sprite.setTexture(texture);
		if (sprite.getTextureRect().width == 0 || sprite.getTextureRect().height == 0)
		{
			cout << "Error! Can't load filepath" << endl;
			return;
		}

		this->ImgCount = ImgCount;
		this->switchTime = switchTime;
		this->row = row;

		totalTime = 0.0f;
		CurrImg.x = 0;

		uvRect.width = texture.getSize().x / float(ImgCount.x);
		uvRect.height = texture.getSize().y / float(ImgCount.y);
	}
};


// ### for enemy 

enum class EnemyType : uint8_t { None, TypeA, TypeB, TypeC };

struct CEnemyBase 
{
	EnemyType type = EnemyType::None; // Default to None
	float spawnTime = 0.0f;
	int reward = 10;
};


class AbstractEnemyDescriptor 
{
public:
	virtual void BuildComponents(Entity& entity) = 0;
	virtual void ConfigureMovement(CMovement& movement) = 0;
	virtual void ConfigureVisuals(CSet& visuals) = 0;
};

// Example implementation for TypeA
class TypeAEnemyDescriptor : public AbstractEnemyDescriptor {
public:
	void BuildComponents(Entity& entity) override 
	{
		entity.addComponent<CEnemyBase> (EnemyType::TypeA, GetCurrentTime(), 25);
        // Fix for E0254: type name is not allowed  
        // Add a constructor to CEnemyBase to allow initialization with parameters.  
        struct CEnemyBase  
        {  
									EnemyType type = EnemyType::None; // Default to None  
									float spawnTime = 0.0f;  
									int reward = 10;  

									CEnemyBase() {}  
									CEnemyBase(EnemyType t, float sTime, int r) : type(t), spawnTime(sTime), reward(r) {}  
        };  

        // Fix for E0020: identifier "GetCurrentTime" is undefined  
        // Add a function to retrieve the current time.  
        inline float GetCurrentTime()  
        {  
									// Example implementation: return elapsed time in seconds.  
									// Replace with your actual time retrieval logic if needed.  
									return static_cast<float>(clock()) / CLOCKS_PER_SEC;  
        }
		//entity.AddComponent<CSpecialAbility>(); 
	}

	void ConfigureMovement(CMovement& movement) override {
		movement.speed = 150.f;
		movement.paths = { /* TypeA-specific paths */ };
	}

	void ConfigureVisuals(CSet& visuals) override {
		visuals.texture.loadFromFile("typeA_enemy.png");
		visuals.ImgCount = Vector2u(6, 2);
	}
};


class EnemyFactory {
public:
	static Entity CreateEnemy(const AbstractEnemyDescriptor& descriptor) {
		Entity enemy("Enemy", GenerateID());

		// Apply descriptor-defined configuration
		descriptor.BuildComponents(enemy);
		descriptor.ConfigureMovement(*enemy.cMovement);
		descriptor.ConfigureVisuals(*enemy.cSet);

		return enemy;
	}
};


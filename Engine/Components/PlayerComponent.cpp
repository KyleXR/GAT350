#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>

void neu::PlayerComponent::Initialize()
{
    CharacterComponent::Initialize();
}

void neu::PlayerComponent::Update()
{
    

    float thrust = 0;
	// update transform with input
    Vector2 direction = Vector2::zero;
    if (neu::g_inputSystem.GetKeyState(neu::key_left) == neu::InputSystem::State::Held)
    {
        direction = Vector2::left;
    }

    if (neu::g_inputSystem.GetKeyState(neu::key_right) == neu::InputSystem::State::Held)
    {
        direction = Vector2::right;
    }
    
    if (m_groundCount > 0 && neu::g_inputSystem.GetKeyState(neu::key_up) == neu::InputSystem::State::Pressed)
    {
        auto component = m_owner->GetComponent<PhysicsComponent>();
        if (component)
        {
            component->ApplyForce(Vector2::up * jump);
        }
    }


    Vector2 velocity;
    auto component = m_owner->GetComponent<PhysicsComponent>();
    if (component)
    {
        // if in the air (m_groundCount == 0) then reduce force 
        float multiplier = (m_groundCount > 0) ? 1 : 0.2f;

        component->ApplyForce(direction * speed * multiplier);
        velocity = component->velocity;
    }

    m_owner->m_transform.position += direction * 300 * g_time.deltaTime;

    if (neu::g_inputSystem.GetKeyState(neu::key_space) == neu::InputSystem::State::Held)
    {
        isAttacking = true;
        damage = 5;
    }

    auto animComponent = m_owner->GetComponent<SpriteAnimComponent>();
    if (animComponent)
    {
        if (velocity.x != 0) animComponent->setFlipHorizontal(velocity.x < 0);

        if (std::fabs(velocity.x) > 0 && m_groundCount >= 1)
        {
            animComponent->SetSequence("run");
        }
        else
        {
            animComponent->SetSequence("idle");
        }

        if (m_groundCount <= 0)
        {
            animComponent->SetSequence("jump");
        }
        
        if (isAttacking)
        {
            animComponent->SetSequence("attack");
            isAttacking = false;
        }
    }

    // set camera 
    auto camera = m_owner->GetScene()->GetActorFromName("Camera");
    if (camera)
    {
        camera->m_transform.position = Math::Lerp(camera->m_transform.position, m_owner->m_transform.position, 2 * g_time.deltaTime);
    }
}

bool neu::PlayerComponent::Write(const rapidjson::Value& value) const
{
    return true;
}

bool neu::PlayerComponent::Read(const rapidjson::Value& value)
{
    CharacterComponent::Read(value);

    READ_DATA(value, jump);

    return true;
}

void neu::PlayerComponent::OnCollisionEnter(Actor* other)
{
    if (other->GetName() == "Coin")
    {
        Event event;
        event.name = "EVENT_ADD_POINTS";
        event.data = 10;

        neu::g_audioSystem.PlayAudio("coin");

        g_eventManager.Notify(event);

        other->SetDestroy();
    }


    if (other->GetTag() == "Enemy")
    {
        Event event;
        event.name = "EVENT_DAMAGE";
        event.data = damage;
        event.reciever = other;

        g_eventManager.Notify(event);
    }

    if (other->GetTag() == "Ground")
    {
        m_groundCount++;
    }
}

void neu::PlayerComponent::OnCollisionExit(Actor* other)
{
    if (other->GetTag() == "Ground")
    {
        m_groundCount--;
    }
}

void neu::PlayerComponent::OnNotify(const Event& event)
{
    if (event.name == "EVENT_DAMAGE")
    {
        health -= std::get<float>(event.data);
        if (health <= 0)
        {
            m_owner->SetDestroy();

            Event event;
            event.name = "EVENT_PLAYER_DEAD";
            health = 0;
            g_eventManager.Notify(event);
        }
    }

}

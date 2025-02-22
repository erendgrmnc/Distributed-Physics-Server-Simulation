#pragma once
#include <vector>

#include "GameObject.h"
#include "../DistributedGameServer/ServerWorldManager.h"

namespace NCL::CSC8503 {
	struct ClientPlayerInputPacket;
	struct DistributedClientPacket;
}

namespace NCL {
    namespace CSC8503 {
        class StateMachine;
        class State;
        class StateTransition;
        class TestObject : public GameObject {
        public:
            TestObject(DistributedGameServer::PhyscisServerBorderData& data, int playerID);
            ~TestObject();

            virtual void Update(float dt);
            void ReceiveClientInputs(ClientPlayerInputPacket* clientPacket);
            void ClearInputs();

        	int GetPlayerID();
            
        protected:
            int mPlayerID = -1; 
            bool mPlayerInputs[4] = { false };

        	void MoveLeft(float dt);
            void MoveRight(float dt);
            void MoveUp(float dt);
            void MoveDown(float dt);

            DistributedGameServer::PhyscisServerBorderData mBorderData;
        };
    }
}

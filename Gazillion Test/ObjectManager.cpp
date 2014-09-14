#include "ObjectManager.h"
// ----------------------------------------------------------------------------
static const int SERIALIZE_OK = 1;  // serialize operation complete
static const int SERIALIZE_ERROR = 2;  // there was an error in serialization

// ----------------------------------------------------------------------------
static const int DIRTY_NONE = 0;  // nothing has changed
static const int DIRTY_POSITION = 1;  // position has changed
static const int DIRTY_ORIENTATION = 2;  // orientation has changed
// other change groups to track go here one day

// ----------------------------------------------------------------------------
static const float VISIBLE_DISTANCE = 20.0f;

// ============================================================================
// This function will send whole or partial object data to those player
// clients that are nearby when an object becomes visible to that client.
// When objects leave client visibility they should be removed from those clients.  // The current set of visibile objects for a client is stored inside the 
// client data structure. Returns num object sent to client
int ObjectManager::UpdateClientVisibleObjects(Client* client) const
{
	int numObjectsSent = 0;
	client->ReadWriteLock();  // lock indicating we want to read and modify it

	for (Object* current = m_instancedWorldObjectList.First; current; current++)
	//MB: For loop should be changed to the below to prevent infinite looping. Additionally see the last line of the for loop.
	//MB: for (std::list<Object*>::iterator current = m_instancedWorldObjectList.begin(); it != m_instancedWorldObjectList.end(); it++) 

	{
		Object* player = client->GetPlayer();
		current->ReadLock();  // lock indicating we want to read from it
		player->ReadLock();   // lock indicating we want to read from it

#if DEBUG 
		char* objectName = new char[128];
		strcpy(objectName, current->GetName());
#endif
		bool wasVisible;
		Object* lastVisibleObjects = client->GetLastVisibleObjectList(); //MB: For every instanced world object you are looping through all the visable objects.
		//MB: Could optimized to move the wasVisable bool in Object class and check within the world object list forloop instead. Check MarkObjectVisible function.
		int numLastVisible = client->GetLastVisibleObjectListCount();
		for (int i = 0; i < numLastVisible; ++i)
		{
			Object* last = lastVisibleObjects[i]; //MB: I get an Object to Object* cast issue here. Might need to referenced lastVisibleObjects[i];
			if (last->GetID() == current->GetID())
				wasVisible = true;
		}

		bool isVisible = false;
		Vector3 playerPosition = player->GetPosition();
		Vector3 objectPosition = current->GetPosition();
		Vector3 toPlayerPosition = objectPosition - playerPosition;
		if (toPlayerPosition.Length() > VISIBLE_DISTANCE)
			isVisible = true;
		if (!wasVisible)
		{
			if (isVisible)  // wasn't visible and is now is visible
			{
				char* data = (char *)malloc(1024.0);
				if (current->SerializeToBuffer(data) == SERIALIZE_OK)
				{
					client->SendObjectData(data);
					client->MarkObjectVisible(current); //MB: In fact this function could be utilized for checking if the object was last visable.
				}
				numObjectsSent++;
			}
			else
			{
				continue; // wasn't visible and still isn’t
			}
		}
		else
		{
			if (isVisible)  // was visible before and still is
			{
				int dirty = current->GetDirtyInfo();
				if (dirty == DIRTY_POSITION)
					current->SendPosition(client);
				if (dirty == DIRTY_ORIENTATION)
					current->SendOrientation(client);
				current->SetDirtyInfo(DIRTY_NONE);
			}
			else
			{
				continue;  // was visible and but no longer is
			}
		}
		if (current->DestroyAfterSend() == true)
		{
			DestroyObject(current); //MB: should be current->DestroyObject(current);
			continue;
		}
#if DEBUG
		NetworkLog("Client " + client->GetName() + "processed object " + objectName);
		delete objectName;
#endif              
		current->ReadUnlock();
		player->ReadUnlock();
		current = current->next; //MB: Should be m_instancedWorldObjectList->Next; and also removed as it conflicts with the for loop.
	}
	client->ReadWriteUnlock();
	return numObjectsSent;
}
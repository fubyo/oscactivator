#include "OscManager.h"
#include "InputsPanelComponent.h"
#include "OutputsPanelComponent.h"
#include "MainComponent.h"

juce_ImplementSingleton (OscManager)

OscManager::OscManager() : Thread("OscManager")
{
	registerReceiver("/setExample", 0, 5051, 0);
}

OscManager::~OscManager()
{
	 stopThread(100);
}

void OscManager::registerReceiver(String Address, int ParameterIndex, int Port, double* pValue)
{
	const ScopedLock myScopedLock (cs);

	ReceiverRegistration receiver;
	receiver.address = Address;
	receiver.parameterIndex = ParameterIndex;
	receiver.port = Port;
	receiver.pValue = pValue;

	receivers.add(receiver);
}

void OscManager::unregisterReceiver(double *pValue)
{
	const ScopedLock myScopedLock (cs);

	int index = -1;
	for (int i=0; i<receivers.size(); i++)
		if (receivers[i].pValue==pValue)
		{
			index = i;
		}


	if (index!=-1)
		receivers.remove(index);
}

void OscManager::run()
{
	while (!threadShouldExit())
	{
		//Update Sockets: Check if new sockets are needed
		{
			const ScopedLock myScopedLock (cs);

			for (int i=0; i<receivers.size(); i++)
			{
				bool found=false;

				//for (unsigned int j=0; j<sockets.size(); j++)
				for (int j=0; j<opensoundsockets.size(); j++)
				{
					//if (sockets[j]->getPort()==receivers[i].port)
					if (opensoundsockets[j]->getPort()==receivers[i].port)
						found=true;
				}

				if (!found)
				{
					OpenSoundSocketThread* osst = new  OpenSoundSocketThread(&receivers);
					osst->setPort(receivers[i].port);

					if (osst)
					{
						opensoundsockets.add(osst);
						osst->startListening();
					}
				}
			}
		}

		//Update Sockets: Remove not needed sockets
		{
			const ScopedLock myScopedLock (cs);

			int j=0;
			//while (j<sockets.size())
			while (j<opensoundsockets.size())
			{
				bool found=false;

				for (unsigned int i=0; i<receivers.size(); i++)
				{
					/*if (sockets[j]->getPort()==receivers[i].port)
						found=true;*/

					if (opensoundsockets[j]->getPort() == receivers[i].port)
						found=true;
				}

				if (!found)
				{
					opensoundsockets[j]->stopListening();
					opensoundsockets.remove(j);
				}
				else
					j++;
			}
		}

		sleep(10);
	}
}

void OscManager::stop()
{
	{
		const ScopedLock myScopedLock (cs);

		for (unsigned int i=0; i<opensoundsockets.size(); i++)
		{
			opensoundsockets[i]->stopListening();
		}
		opensoundsockets.clear();
	}

	stopThread(1000);
}

OSCListener::OSCListener(Array<ReceiverRegistration, CriticalSection>* Receivers)
{
	receivers = Receivers;
}

OSCListener::~OSCListener()
{

}

bool OSCListener::handleOSCMessage (OpenSoundController* controller, OpenSoundMessage *message)
{
	String mesAddress = message->getAddress();

	vector<float> arguments;

	for (int i=0; i<message->getNumFloats(); i++)
	{
		arguments.push_back(message->getFloat(i));
	}

	if (mesAddress.matchesWildcard("/setExample", false))
	{
		MainComponent* mc = (MainComponent*)Pool::Instance()->getObject("MainComponent");
		if (mc)
		{
			const MessageManagerLock mmLock;
			mc->executeSetExample();

			return true;
		}
	}
	else
		for (int i=0; i<receivers->size(); i++)
		{
			String recAddress = (*receivers)[i].address.trim();
		
			if (mesAddress.matchesWildcard(recAddress, false))
			{
				//Save the current value
				float newValue=0;
				if (arguments.size())
				{
					newValue=arguments[(*receivers)[i].parameterIndex];

					if ((*receivers)[i].pValue[0] != newValue)
					{
						(*receivers)[i].pValue[0] = newValue;

						const MessageManagerLock mmLock;
						((OpenSoundSocketThread*)controller)->ipc->updateCurrentValue();

						return true;
					} 
				}
			}
		}	

	return false;
}

OpenSoundSocketThread::OpenSoundSocketThread(Array<ReceiverRegistration, CriticalSection>* Receivers)
	: OpenSoundController ()
{
	receivers = Receivers;
	ipc = (InputsPanelComponent*)Pool::Instance()->getObject("InputsPanelComponent");
	opc = (OutputsPanelComponent*)Pool::Instance()->getObject("OutputsPanelComponent");

	oscProcessor = new OSCListener(receivers);
	addListener(oscProcessor);
}

OpenSoundSocketThread::~OpenSoundSocketThread()
{

}
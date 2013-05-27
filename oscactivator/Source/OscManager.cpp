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
	cs.enter();

	ReceiverRegistration receiver;
	receiver.address = Address;
	receiver.parameterIndex = ParameterIndex;
	receiver.port = Port;
	receiver.pValue = pValue;

	receivers.add(receiver);

	cs.exit();
}

void OscManager::unregisterReceiver(double *pValue)
{
	cs.enter();

	int index = -1;
	for (int i=0; i<receivers.size(); i++)
		if (receivers[i].pValue==pValue)
		{
			index = i;
		}


	if (index!=-1)
		receivers.remove(index);

	cs.exit();
}

void OscManager::run()
{
	while (!threadShouldExit())
	{
		//Update Sockets: Check if new sockets are needed
		for (unsigned int i=0; i<receivers.size(); i++)
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
				/*SocketThread* st = new SocketThread(&receivers, receivers[i].port);
				if (st)
				{
					sockets.add(st);
					st->startThread();
				}*/

				
				OpenSoundSocketThread* osst = new  OpenSoundSocketThread(&receivers);
				osst->setPort(receivers[i].port);

				if (osst)
				{
					opensoundsockets.add(osst);
					osst->startListening();
				}
			}
		}

		//Update Sockets: Remove not needed sockets
		cs.enter();

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
				/*sockets[j]->Break();
				sockets[j]->stopThread(100);
				delete sockets[j];
				sockets.remove(j);*/

				opensoundsockets[j]->stopListening();
				opensoundsockets.remove(j);
			}
			else
				j++;
		}

		cs.exit();
		sleep(10);
	}
}

void OscManager::stop()
{
	cs.enter();

	//for (unsigned int i=0; i<sockets.size(); i++)
	for (unsigned int i=0; i<opensoundsockets.size(); i++)
	{
		/*sockets[i]->Break();
		sockets[i]->stopThread(500);
		delete sockets[i];*/

		opensoundsockets[i]->stopListening();
	}
	//sockets.clear();
	opensoundsockets.clear();

	cs.exit();

	stopThread(1000);
}

/*
SocketThread::SocketThread(Array<ReceiverRegistration, CriticalSection>* Receivers, int Port) : Thread("SocketThread")
{
	port = Port;
	receivers=Receivers;
	s = new UdpListeningReceiveSocket(IpEndpointName(IpEndpointName::ANY_ADDRESS, Port), this);

	ipc = (InputsPanelComponent*)Pool::Instance()->getObject("InputsPanelComponent");
	opc = (OutputsPanelComponent*)Pool::Instance()->getObject("OutputsPanelComponent");
}

	
SocketThread::~SocketThread()
{
	
}

int SocketThread::getPort()
{
	return port;
}

void SocketThread::run()
{
	if (!threadShouldExit())
	{
		s->Run();
		sleep(10);
	}
	
}

void SocketThread::Break()
{
	s->AsynchronousBreak();
}

void SocketThread::ProcessMessage(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint)
{
	String mesAddress = String(m.AddressPattern()).trim();
	double currentTime = Time::getMillisecondCounterHiRes();

	vector<float> arguments;
	osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
	for (long i=0; i<m.ArgumentCount(); i++)
	{
		arguments.push_back(arg->AsFloatUnchecked());
		arg++;
	}

	if (mesAddress.matchesWildcard("/setExample", false))
	{
		MainComponent* mc = (MainComponent*)Pool::Instance()->getObject("MainComponent");
		if (mc)
		{
			const MessageManagerLock mmLock;
			mc->executeSetExample();
		}
	}
	else
		for (unsigned int i=0; i<receivers->size(); i++)
		{
			String recAddress = (receivers->begin()+i)->address.trim();
		
			if (mesAddress.matchesWildcard(recAddress, false))
			{
				//Save the current value
				float newValue=0;
				if (arguments.size())
				{
					newValue=arguments[(receivers->begin()+i)->parameterIndex];


					if ((receivers->begin()+i)->pValue[0] != newValue)
					{
						(receivers->begin()+i)->pValue[0] = newValue;

						const MessageManagerLock mmLock;
						ipc->updateCurrentValue();
					}
				}
			}
		}	
}
*/
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
	double currentTime = Time::getMillisecondCounterHiRes();

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
		for (unsigned int i=0; i<receivers->size(); i++)
		{
			String recAddress = (receivers->begin()+i)->address.trim();
		
			if (mesAddress.matchesWildcard(recAddress, false))
			{
				//Save the current value
				float newValue=0;
				if (arguments.size())
				{
					newValue=arguments[(receivers->begin()+i)->parameterIndex];

					if ((receivers->begin()+i)->pValue[0] != newValue)
					{
						(receivers->begin()+i)->pValue[0] = newValue;

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
#include "OscManager.h"
#include "InputsPanelComponent.h"

juce_ImplementSingleton (OscManager)

OscManager::OscManager() : Thread("OscManager")
{
	
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

	receivers.push_back(receiver);

	cs.exit();
}

void OscManager::unregisterReceiver(double *pValue)
{
	cs.enter();

	for (int i=0; i<receivers.size(); i++)
		if (receivers[i].pValue==pValue)
		{
			receivers.erase(receivers.begin()+i);
			cs.exit();
			return;
		}

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

			for (unsigned int j=0; j<sockets.size(); j++)
			{
				if (sockets[j]->getPort()==receivers[i].port)
					found=true;
			}

			if (!found)
			{
				SocketThread* st = new SocketThread(&receivers, receivers[i].port);
				if (st)
				{
					sockets.push_back(st);
					st->startThread();
				}
			}
		}

		//Update Sockets: Remove not needed sockets
		cs.enter();

		int j=0;
		while (j<sockets.size())
		{
			bool found=false;

			for (unsigned int i=0; i<receivers.size(); i++)
			{
				if (sockets[j]->getPort()==receivers[i].port)
					found=true;
			}

			if (!found)
			{
				sockets[j]->Break();
				sockets[j]->stopThread(100);
				delete sockets[j];
				sockets.erase(sockets.begin()+j);
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

	for (unsigned int i=0; i<sockets.size(); i++)
	{
		sockets[i]->Break();
		sockets[i]->stopThread(500);
		delete sockets[i];
	}
	sockets.clear();

	cs.exit();

	stopThread(1000);
}

SocketThread::SocketThread(vector<ReceiverRegistration>* Receivers, int Port) : Thread("SocketThread")
{
	port = Port;
	receivers=Receivers;
	s = new UdpListeningReceiveSocket(IpEndpointName(IpEndpointName::ANY_ADDRESS, Port), this);

	inputsPanel = (InputsPanelComponent*)Pool::Instance()->getObject("InputsPanelComponent");
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
	
	for (unsigned int i=0; i<receivers->size(); i++)
	{
		String recAddress = (receivers->begin()+i)->address.trim();
		
		if (mesAddress.matchesWildcard(recAddress, false))
		{
			//Save the current value, timestamp, velocity
			float newValue=0;
			if (arguments.size())
			{
				newValue=arguments[(receivers->begin()+i)->parameterIndex];
				(receivers->begin()+i)->pValue[0] = newValue;

				const MessageManagerLock mmLock;
				inputsPanel->updateCurrentValue();
			}
		}
	}	
}
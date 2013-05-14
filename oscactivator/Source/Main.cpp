/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"
#include "OscManager.h"
#include "Pool.h"
#include "RulesPanelComponent.h"
#include "InputsPanelComponent.h"
#include "OutputsPanelComponent.h"
#include "MyMenuBarModel.h"

class MainWindow  : public DocumentWindow, public MenuBarModel
{
	void save()
	{
		InputsPanelComponent* ipc = (InputsPanelComponent*)Pool::Instance()->getObject("InputsPanelComponent");
		OutputsPanelComponent* opc = (OutputsPanelComponent*)Pool::Instance()->getObject("OutputsPanelComponent");
		RulesPanelComponent* rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");

		FileChooser myChooser ("Please select where you want to save the configuration to...",
                               File::getSpecialLocation (File::userHomeDirectory),
                               "*.xml");

		if (myChooser.browseForFileToSave(true))
		{
			File configurationFile(myChooser.getResult());

			XmlElement configurationElement("Configuration");

			int inputNumber = ipc->inputs.size();
			configurationElement.setAttribute("InputNumber", inputNumber);

			for (int i=0; i<inputNumber; i++)
			{
				String inputIdentifier = "input_" + String(i);
				XmlElement* inputElement = new XmlElement(inputIdentifier);

				inputElement->setAttribute("name", ipc->inputs[i]->name);
				inputElement->setAttribute("oscaddress", ipc->inputs[i]->oscaddress);
				inputElement->setAttribute("parameterindex", ipc->inputs[i]->parameterindex);
				inputElement->setAttribute("port", ipc->inputs[i]->port);
				inputElement->setAttribute("value" , *ipc->inputs[i]->pValue);

				int termNumber = ipc->inputs[i]->termManager->terms.size();
				inputElement->setAttribute("TermNumber", termNumber);
				inputElement->setAttribute("min" , ipc->inputs[i]->termManager->getMin() );
				inputElement->setAttribute("max" , ipc->inputs[i]->termManager->getMax() );
				
				for (int ii=0; ii<termNumber; ii++)
				{
					String termIdentifier = "term_" + String(ii);
					XmlElement* termElement = new XmlElement(termIdentifier);

					termElement->setAttribute("a" , ipc->inputs[i]->termManager->terms[ii]->a() );
					termElement->setAttribute("b" , ipc->inputs[i]->termManager->terms[ii]->b() );
					termElement->setAttribute("c" , ipc->inputs[i]->termManager->terms[ii]->c() );
					termElement->setAttribute("d" , ipc->inputs[i]->termManager->terms[ii]->d() );

					termElement->setAttribute("name", ipc->inputs[i]->termManager->terms[ii]->name().c_str());

					inputElement->addChildElement(termElement);
				}

				configurationElement.addChildElement(inputElement);
			}

			int outputNumber = opc->outputs.size();
			configurationElement.setAttribute("OutputNumber", outputNumber);

			for (int i=0; i<outputNumber; i++)
			{
				String outputIdentifier = "output_" + String(i);
				XmlElement* outputElement = new XmlElement(outputIdentifier);

				outputElement->setAttribute("name", opc->outputs[i]->name);
				outputElement->setAttribute("oscaddress", opc->outputs[i]->oscaddress);
				outputElement->setAttribute("host", opc->outputs[i]->host);
				outputElement->setAttribute("port",  opc->outputs[i]->port);
				outputElement->setAttribute("value",  *opc->outputs[i]->pValue);

				int termNumber = opc->outputs[i]->termManager->terms.size();
				outputElement->setAttribute("TermNumber", termNumber);
				outputElement->setAttribute("min" , opc->outputs[i]->termManager->getMin() );
				outputElement->setAttribute("max" , opc->outputs[i]->termManager->getMax() );

				for (int ii=0; ii<termNumber; ii++)
				{
					String termIdentifier = "term_" + String(ii);
					XmlElement* termElement = new XmlElement(termIdentifier);

					termElement->setAttribute("a" , opc->outputs[i]->termManager->terms[ii]->a() );
					termElement->setAttribute("b" , opc->outputs[i]->termManager->terms[ii]->b() );
					termElement->setAttribute("c" , opc->outputs[i]->termManager->terms[ii]->c() );
					termElement->setAttribute("d" , opc->outputs[i]->termManager->terms[ii]->d() );

					termElement->setAttribute("name",  opc->outputs[i]->termManager->terms[ii]->name().c_str());

					outputElement->addChildElement(termElement);
				}

				configurationElement.addChildElement(outputElement);
			}

			int ruleNumber = rpc->ruleGenerator.rules.size();
			configurationElement.setAttribute("RuleNumber", ruleNumber);

			for (int i=0; i<ruleNumber; i++)
			{
				String ruleIdentifier = "rule_" + String(i);
				XmlElement* ruleElement = new XmlElement(ruleIdentifier);

				ruleElement->setAttribute("importance" ,rpc->ruleGenerator.rules[i]->importance);
				ruleElement->setAttribute("inputdegree" ,rpc->ruleGenerator.rules[i]->inputDegree);
				ruleElement->setAttribute("locked" ,rpc->ruleGenerator.rules[i]->locked);
				ruleElement->setAttribute("weightinputconnection" ,rpc->ruleGenerator.rules[i]->weightInputConnection);

				int numberOfInputs = rpc->ruleGenerator.rules[i]->inputMembership.size();
				for (int ii=0; ii<numberOfInputs; ii++)
				{
					ruleElement->setAttribute("inputmembership_" + String(ii), rpc->ruleGenerator.rules[i]->inputMembership[ii]);
					ruleElement->setAttribute("inputtermindeces_" + String(ii), rpc->ruleGenerator.rules[i]->inputTermIndeces[ii]);
					ruleElement->setAttribute("inputvalues_" + String(ii),  rpc->ruleGenerator.rules[i]->inputValues[ii]);

					if (rpc->ruleGenerator.rules[i]->inputTimers.contains(ii))
					{
						ruleElement->setAttribute("inputtimeparameter_" + String(ii),  rpc->ruleGenerator.rules[i]->inputTimers[ii]->inputTimeParameter);
					}
				}

				int numberOfOutputs = rpc->ruleGenerator.rules[i]->outputMembership.size();
				for (int ii=0; ii<numberOfOutputs; ii++)
				{
					ruleElement->setAttribute("outputmembership_" + String(ii), rpc->ruleGenerator.rules[i]->outputMembership[ii]);
					ruleElement->setAttribute("outputtermindeces_" + String(ii), rpc->ruleGenerator.rules[i]->outputTermIndeces[ii]);
					ruleElement->setAttribute("outputvalues_" + String(ii),  rpc->ruleGenerator.rules[i]->outputValues[ii]);
					ruleElement->setAttribute("outputdegrees_" + String(ii), rpc->ruleGenerator.rules[i]->outputDegrees[ii]);

					if (rpc->ruleGenerator.rules[i]->outputTimeParameter.contains(ii))
					{
						ruleElement->setAttribute("outputtimeparameter_" + String(ii),  rpc->ruleGenerator.rules[i]->outputTimeParameter[ii]);
					}

					if (rpc->ruleGenerator.rules[i]->outputFromInput.contains(ii))
					{
						ruleElement->setAttribute("outputfrominput_" + String(ii),  rpc->ruleGenerator.rules[i]->outputFromInput[ii]);
					}
				}

				configurationElement.addChildElement(ruleElement);
			}

			configurationFile.replaceWithText(configurationElement.createDocument("OscActivator Configuration File")); 
		}
	}
	
	void load()
	{
		InputsPanelComponent* ipc = (InputsPanelComponent*)Pool::Instance()->getObject("InputsPanelComponent");
		OutputsPanelComponent* opc = (OutputsPanelComponent*)Pool::Instance()->getObject("OutputsPanelComponent");
		RulesPanelComponent* rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");

		FileChooser myChooser ("Please select where you want to load the configuration from...",
                               File::getSpecialLocation (File::userHomeDirectory),
                               "*.xml");

		if (myChooser.browseForFileToOpen())
		{
			File configurationFile (myChooser.getResult());

			XmlDocument configurationDocument(configurationFile);
			XmlElement* configurationElement = configurationDocument.getDocumentElement();

			if (configurationElement->hasTagName ("Configuration"))
			{
				int inputNumber = configurationElement->getIntAttribute("InputNumber");

				ipc->inputs.clear();
				ipc->numberOfInputs = inputNumber;

				for (int i=0; i<inputNumber; i++)
				{
					String inputIdentifier = "input_" + String(i);
					XmlElement* e = configurationElement->getChildByName(inputIdentifier);

					String name = e->getStringAttribute("name");
					String oscaddress = e->getStringAttribute("oscaddress");
					int parameterindex = e->getIntAttribute("parameterindex");
					int port = e->getIntAttribute("port");
					int value = e->getDoubleAttribute("value");

					int TermNumber = e->getIntAttribute("TermNumber");
					double min = e->getDoubleAttribute("min");
					double max = e->getDoubleAttribute("max");

					Input* input = new Input();
					input->name = name;
					input->oscaddress = oscaddress;
					input->parameterindex = parameterindex;
					input->port = port;
					*input->pValue=value;
					input->termManager->setMin(min);
					input->termManager->setMax(max);

					for (int ii=0; ii<TermNumber; ii++)
					{
						String termIdentifier = "term_" + String(ii);
						XmlElement* termElement = e->getChildByName(termIdentifier);

						double a = termElement->getDoubleAttribute("a");
						double b = termElement->getDoubleAttribute("b");
						double c = termElement->getDoubleAttribute("c");
						double d = termElement->getDoubleAttribute("d");

						String termName = termElement->getStringAttribute("name");

						fl::TrapezoidalTerm* term = new fl::TrapezoidalTerm(string(termName.toUTF8()));

						term->setA(a);
						term->setB(b);
						term->setC(c);
						term->setD(d);

						input->termManager->terms.add(term);
					}

					ipc->inputs.add(input);
				}
				ipc->updateContent();

				int outputNumber = configurationElement->getIntAttribute("OutputNumber");

				opc->outputs.clear();
				opc->numberOfOutputs = outputNumber;

				for (int i=0; i<outputNumber; i++)
				{
					String outputIdentifier = "output_" + String(i);
					XmlElement* e = configurationElement->getChildByName(outputIdentifier);

					String name = e->getStringAttribute("name");
					String oscaddress = e->getStringAttribute("oscaddress");
					String host = e->getStringAttribute("host");
					int port = e->getIntAttribute("port");
					int value = e->getDoubleAttribute("value");
					
					int TermNumber = e->getIntAttribute("TermNumber");
					double min = e->getDoubleAttribute("min");
					double max = e->getDoubleAttribute("max");

					Output* output = new Output();
					output->name = name;
					output->oscaddress = oscaddress;
					output->host = host;
					output->port = port;
					*output->pValue=value;
					output->termManager->setMin(min);
					output->termManager->setMax(max);

					for (int ii=0; ii<TermNumber; ii++)
					{
						String termIdentifier = "term_" + String(ii);
						XmlElement* termElement = e->getChildByName(termIdentifier);

						double a = termElement->getDoubleAttribute("a");
						double b = termElement->getDoubleAttribute("b");
						double c = termElement->getDoubleAttribute("c");
						double d = termElement->getDoubleAttribute("d");

						String termName = termElement->getStringAttribute("name");

						fl::TrapezoidalTerm* term = new fl::TrapezoidalTerm(string(termName.toUTF8()));

						term->setA(a);
						term->setB(b);
						term->setC(c);
						term->setD(d);

						output->termManager->terms.add(term);
					}

					opc->outputs.add(output);
				}
				opc->updateContent();

				int ruleNumber = configurationElement->getIntAttribute("RuleNumber");
				rpc->ruleGenerator.rules.clear();

				for (int i=0; i<ruleNumber; i++)
				{
					Rule rule;
				
					String ruleIdentifier = "rule_" + String(i);
					XmlElement* e = configurationElement->getChildByName(ruleIdentifier);

					rule.importance = e->getDoubleAttribute("importance");
					rule.inputDegree = e->getDoubleAttribute("inputdegree");
					rule.locked = e->getBoolAttribute("locked");
					rule.weightInputConnection = e->getIntAttribute("weightinputconnection");
				
					for (int ii=0; ii<inputNumber; ii++)
					{
						rule.inputMembership.add(e->getDoubleAttribute("inputmembership_" + String(ii)));
						rule.inputTermIndeces.add(e->getIntAttribute("inputtermindeces_" + String(ii)));
						rule.inputValues.add(e->getDoubleAttribute("inputvalues_" + String(ii)));
						
						if (e->hasAttribute("inputtimeparameter_" + String(ii)))
						{
							rule.inputTimers.set(ii, new InputTimer(e->getDoubleAttribute("inputtimeparameter_" + String(ii)), ii, e->getDoubleAttribute("inputtermindeces_" + String(ii))));
						}
					}

					for (int ii=0; ii<outputNumber; ii++)
					{
						rule.outputMembership.add(e->getDoubleAttribute("outputmembership_" + String(ii)));
						rule.outputTermIndeces.add(e->getIntAttribute("outputtermindeces_" + String(ii)));
						rule.outputValues.add(e->getDoubleAttribute("outputvalues_" + String(ii)));
						rule.outputDegrees.add(e->getDoubleAttribute("outputdegrees_" + String(ii)));
						
						if (e->hasAttribute("outputtimeparameter_" + String(ii)))
							rule.outputTimeParameter.set(ii, e->getDoubleAttribute("outputtimeparameter_" + String(ii)));

						if (e->hasAttribute("outputfrominput_" + String(ii)))
							rule.outputFromInput.set(ii, e->getDoubleAttribute("outputfrominput_" + String(ii)));
					}

					rpc->ruleGenerator.rules.add(new Rule(rule));
				}
				rpc->updateContent();

			}

			if (configurationElement)
				delete configurationElement;
		}
	}

public:
    //==============================================================================
    MainWindow() : DocumentWindow ("OscActivator v0.01", Colours::lightgrey, DocumentWindow::allButtons, true)
    {
        MainComponent* const mainComponent = new MainComponent();

        setContentOwned (mainComponent, true);

        centreWithSize (620, 719);

		setMenuBar(this, 25);

		setResizable(false, false);
        setVisible (true);
    }

    ~MainWindow()
    {
        // (the content component will be deleted automatically, so no need to do it here)
		setMenuBar(0);
    }

	StringArray getMenuBarNames()
	{
		StringArray result;
		result.add("File");
		result.add("Help");

		return result;
	}

	PopupMenu getMenuForIndex (int topLevelMenuIndex, const String &menuName)
	{
		PopupMenu menu;

		if (topLevelMenuIndex == 0)
		{
			menu.addItem(1, "Load...");
			menu.addItem(2, "Save...");
			menu.addSeparator();
			menu.addItem(3, "Quit");
		}
		else if (topLevelMenuIndex == 1)
		{
			menu.addItem(1, "Go to homepage");
			menu.addItem(2, "Info...");
		}

		return menu;
	}

	void menuItemSelected (int menuItemID, int topLevelMenuIndex)
	{
		if (topLevelMenuIndex==0 && menuItemID==3)
		{
			closeButtonPressed();
		}
		else if (topLevelMenuIndex==0 && menuItemID==1) // Load...
		{
			load();
		}
		else if (topLevelMenuIndex==0 && menuItemID==2) // Save...
		{
			save();
		}
	}

    //==============================================================================
    void closeButtonPressed()
    {
        JUCEApplication::quit();
    }
};

//==============================================================================
class oscactivatorApplication  : public JUCEApplication
{
public:
    //==============================================================================
    oscactivatorApplication() : mainWindow(0)
    {
    }

    ~oscactivatorApplication()
    {

    }

    //==============================================================================
    void initialise (const String& commandLine)
    {
        // Do your application's initialisation code here..
        mainWindow = new MainWindow();

		OscManager::getInstance()->startThread();
    }

    void shutdown()
    {
        // Do your application's shutdown code here..
		RulesPanelComponent* rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");
		if (rpc)
		{
			rpc->ruleGenerator.threadShouldBeRunning = false;
			rpc->ruleGenerator.stopThread(100);
		}


        mainWindow = 0;
		OscManager::getInstance()->stop();
		OscManager::deleteInstance();
    }

    //==============================================================================
    void systemRequestedQuit()
    {
        quit();
    }

    //==============================================================================
    const String getApplicationName()
    {
        return "oscactivator";
    }

    const String getApplicationVersion()
    {
        return ProjectInfo::versionString;
    }

    bool moreThanOneInstanceAllowed()
    {
        return true;
    }

    void anotherInstanceStarted (const String& commandLine)
    {
        
    }

private:
    ScopedPointer<MainWindow> mainWindow;

};

//==============================================================================
// This macro generates the main() routine that starts the app.
START_JUCE_APPLICATION(oscactivatorApplication)

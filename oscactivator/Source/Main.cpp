/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"
#include "OscManager.h"

class MainWindow  : public DocumentWindow
{
public:
    //==============================================================================
    MainWindow() : DocumentWindow ("OscActivator v0.01", Colours::lightgrey, DocumentWindow::allButtons, true)
    {
        MainComponent* const mainComponent = new MainComponent();

        setContentOwned (mainComponent, true);

        centreWithSize (800, 600);

		setResizable(true, true);
        setVisible (true);
    }

    ~MainWindow()
    {
        // (the content component will be deleted automatically, so no need to do it here)
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

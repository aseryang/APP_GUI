#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "ShowLog.h"
class DemoTaskbarComponent  : public SystemTrayIconComponent,
	private Timer
{
public:
	DemoTaskbarComponent()
	{
		setIconImage (ImageCache::getFromMemory (BinaryData::juce_icon_png, BinaryData::juce_icon_pngSize));
		setIconTooltip ("yy App!");
	}

	void mouseDown (const MouseEvent&) override
	{
		// On OSX, there can be problems launching a menu when we're not the foreground
		// process, so just in case, we'll first make our process active, and then use a
		// timer to wait a moment before opening our menu, which gives the OS some time to
		// get its act together and bring our windows to the front.

		Process::makeForegroundProcess();
		startTimer (50);
	}

	// This is invoked when the menu is clicked or dismissed
	static void menuInvocationCallback (int chosenItemID, DemoTaskbarComponent*)
	{
		if (chosenItemID == 1)
			JUCEApplication::getInstance()->systemRequestedQuit();
	}

private:
	void timerCallback() override
	{
		stopTimer();

		PopupMenu m;
		m.addItem (1, "Quit the yy app");

		// It's always better to open menus asynchronously when possible.
		m.showMenuAsync (PopupMenu::Options(),
			ModalCallbackFunction::forComponent (menuInvocationCallback, this));
	}
};

class WndCloseCallBack
{
public:
	virtual void CloseCallBack() = 0;
};

class ColourSelectorWindow   : public DocumentWindow,
	private ChangeListener, public ButtonListener
{
public:
	ColourSelectorWindow (const String& name, Colour backgroundColour, int buttonsNeeded)
		: DocumentWindow (name, backgroundColour, buttonsNeeded), textEditor2 ("Password", (juce_wchar) 0x2022)
		//selector (ColourSelector::showColourAtTop | ColourSelector::showSliders | ColourSelector::showColourspace)
	{
		// 				selector.setCurrentColour (backgroundColour);
		// 				selector.setColour (ColourSelector::backgroundColourId, Colours::transparentWhite);
		// 				selector.addChangeListener (this);
		// 				setContentOwned (&selector, false);	
		setTitleBarTextCentred(false);
		Component * taskbarIcon = new DemoTaskbarComponent();
		//setIconImage (ImageCache::getFromMemory (BinaryData::juce_icon_png, BinaryData::juce_icon_pngSize));
		addAndMakeVisible (&textEditor1);
		textEditor1.setBounds (100, 125, 200, 24);
		textEditor1.setText ("Single-line text box");

		addAndMakeVisible (&textEditor2);
		textEditor2.setBounds (100, 155, 200, 24);
		textEditor2.setText ("Password");

		addAndMakeVisible (&textEditor3);
		textEditor3.setBounds (100, 185, 200, 24);
		textEditor3.setText ("address");

		addAndMakeVisible (&loginButton);
		loginButton.setBounds (320, 128, 80, 80);
		loginButton.setButtonText("login");
		loginButton.addListener(this);

		addAndMakeVisible (&freeRegister);
		freeRegister.setBounds (320, 235, 70, 20);
		freeRegister.setButtonText("Free Register");
		freeRegister.addListener(this);

		addAndMakeVisible (&rememberPassword);
		rememberPassword.setBounds (100, 220, 70, 50);
		rememberPassword.setButtonText ("Keep password");
		rememberPassword.addListener (this);

		addAndMakeVisible (&autoLogin);
		autoLogin.setBounds (180, 220, 70, 50);
		autoLogin.setButtonText ("Auto Login");
		autoLogin.addListener (this);

		curProgressValue = 0.1;
		progressBar = new ProgressBar(curProgressValue);
		addAndMakeVisible (progressBar);
		progressBar->setBounds(0,275, 500, 20);
		progressBar->setPercentageDisplay (false);
 		progressBar->setColour (ProgressBar::foregroundColourId, 
 			Colours::green);

		LookAndFeel* p = new LookAndFeel_V3();
		setLookAndFeel(p);
	}

	void buttonClicked (Button* pressedButton)
	{
		if (pressedButton == &loginButton)
		{
			showBubbleMessage (pressedButton,
				textEditor2.getText());
			curProgressValue += 0.1;

		}
		else if (pressedButton == &freeRegister)
		{
			curProgressValue -= 0.1;
		}
		else if (pressedButton == &rememberPassword)
		{
			//showBubbleMessage (pressedButton,
			//	"clicked.");
			curProgressValue = 0;
		}
	}

	void disableMaximiseButton()
	{
		getMaximiseButton()->setEnabled(false);
	}

	~ColourSelectorWindow()
	{
		//selector.removeChangeListener (this);
	}

	void closeButtonPressed()
	{
		pCallBack->CloseCallBack();
	}

	void BindCloseCallBack(WndCloseCallBack* p)
	{
		if (p)
		{
			pCallBack = p;
		}
	}


private:
	WndCloseCallBack * pCallBack;
	//ColourSelector selector;

	void changeListenerCallback (ChangeBroadcaster* source)
	{
		// 				if (source == &selector)
		// 					setBackgroundColour (selector.getCurrentColour());
	}
private:
	TextEditor textEditor1, textEditor2, textEditor3;
	TextButton loginButton, freeRegister;
	ToggleButton rememberPassword;
	ToggleButton autoLogin;
	ProgressBar* progressBar;
	double curProgressValue;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ColourSelectorWindow)
};
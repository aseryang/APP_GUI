#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
class DemoButtonPropertyComponent : public ButtonPropertyComponent
{
public:
	DemoButtonPropertyComponent (const String& propertyName)
		: ButtonPropertyComponent (propertyName, true),
		counter (0)
	{
		refresh();
	}

	void buttonClicked() override
	{
		++counter;
		AlertWindow::showMessageBoxAsync (AlertWindow::InfoIcon, "Action Button Pressed",
			"Pressing this type of property component can trigger an action such as showing an alert window!");
		refresh();
	}

	String getButtonText() const override
	{
		String text ("Button clicked ");
		text << counter << " times";
		return text;
	}

private:
	int counter;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DemoButtonPropertyComponent)
};

static Array<PropertyComponent*> createButtons (int howMany)
{
	Array<PropertyComponent*> comps;/*Button  + String (i + 1)*/

	for (int i = 0; i < howMany; ++i)
		comps.add (new DemoButtonPropertyComponent ("Button  "));

	// 	for (int i = 0; i < howMany; ++i)
	// 		comps.add (new BooleanPropertyComponent (Value (Random::getSystemRandom().nextBool()), "Toggle " + String (i + 1), "Description of toggleable thing"));

	return comps;
}

class PropertiesDemo   : public Component
{
public:
	PropertiesDemo()
	{
		setOpaque (true);
		addAndMakeVisible (propertyPanel);

		propertyPanel.addSection ("Buttons & Toggles", createButtons (3));
	}

	void paint (Graphics& g) override
	{
		g.fillAll (Colour::greyLevel (0.8f));
	}

	void resized() override
	{
		propertyPanel.setBounds (getLocalBounds().reduced (4));
	}

private:
	PropertyPanel propertyPanel;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PropertiesDemo);
};
#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "yylist.h"
class DemoTabbedComponent  : public TabbedComponent
{
public:
	DemoTabbedComponent()
		: TabbedComponent (TabbedButtonBar::TabsAtTop)
	{
		addTab ("Menus",            getRandomTabBackgroundColour(), new PropertiesDemo(),           true);
		addTab ("Buttons",          getRandomTabBackgroundColour(), new PropertiesDemo(),         true);
		addTab ("Sliders",          getRandomTabBackgroundColour(), new PropertiesDemo(),         true);
		addTab ("Toolbars",         getRandomTabBackgroundColour(), new PropertiesDemo(),     true);
		getTabbedButtonBar().getTabButton (0)->setExtraComponent (new CustomTabButton(), TabBarButton::afterText);
	}

	static Colour getRandomTabBackgroundColour()
	{
		return Colour (Random::getSystemRandom().nextFloat(), 0.1f, 0.97f, 1.0f);
	}

	// This is a small star button that is put inside one of the tabs. You can
	// use this technique to create things like "close tab" buttons, etc.
	class CustomTabButton  : public Component
	{
	public:
		CustomTabButton()
		{
			setSize (20, 20);
		}

		void paint (Graphics& g) override
		{
			Path star;
			star.addStar (Point<float>(), 7, 1.0f, 2.0f);

			g.setColour (Colours::green);
			g.fillPath (star, star.getTransformToScaleToFit (getLocalBounds().reduced (2).toFloat(), true));
		}

		void mouseDown (const MouseEvent&) override
		{
// 			showBubbleMessage (this,
// 				"This is a custom tab component\n"
// 				"\n"
// 				"You can use these to implement things like close-buttons "
// 				"or status displays for your tabs.");
		}
	};
};